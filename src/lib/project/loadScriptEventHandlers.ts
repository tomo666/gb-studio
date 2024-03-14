import glob from "glob";
import { promisify } from "util";
import { eventsRoot } from "consts";
import * as l10n from "shared/lib/lang/l10n";
import * as eventHelpers from "lib/events/helpers";
import * as eventSystemHelpers from "lib/helpers/eventSystem";
import * as compileEntityEvents from "lib/compiler/compileEntityEvents";
import type { ScriptEventFieldSchema } from "shared/lib/entities/entitiesTypes";
import { Dictionary } from "@reduxjs/toolkit";
import { readFile } from "fs-extra";
import trimLines from "shared/lib/helpers/trimlines";

const globAsync = promisify(glob);

const ivm = __non_webpack_require__("isolated-vm");
const isolate = new ivm.Isolate({ memoryLimit: 128 });

export interface ScriptEventDef {
  id: string;
  fields: ScriptEventFieldSchema[];
  name?: string;
  description?: string;
  groups?: string[] | string;
  deprecated?: boolean;
  isConditional?: boolean;
  editableSymbol?: boolean;
  allowChildrenBeforeInitFade?: boolean;
  waitUntilAfterInitFade?: boolean;
  hasAutoLabel: boolean;
  fieldsLookup: Record<string, ScriptEventFieldSchema>;
}

export type ScriptEventHandlerFieldSchema = ScriptEventFieldSchema & {
  postUpdateFn?: (
    newArgs: Record<string, unknown>,
    prevArgs: Record<string, unknown>
  ) => void | Record<string, unknown>;
};

export type ScriptEventHandler = ScriptEventDef & {
  autoLabel?: (
    lookup: (key: string) => string,
    args: Record<string, unknown>
  ) => string;
  compile: (input: unknown, helpers: unknown) => void;
  fields: ScriptEventHandlerFieldSchema[];
  fieldsLookup: Record<string, ScriptEventHandlerFieldSchema>;
};

export type ScriptEventHandlers = Dictionary<ScriptEventHandler>;

const sandboxedRequire = (moduleName: keyof typeof allowedModules) => {
  const allowedModules = {
    "./helpers": wrapFunctions(eventHelpers),
    "../helpers/l10n": wrapFunctions(l10n),
    "../helpers/eventSystem": wrapFunctions(eventSystemHelpers),
    "../compiler/compileEntityEvents": wrapFunctions(compileEntityEvents),
    "../helpers/trimlines": wrapFunctions(trimLines),
    "shared/lib/helpers/trimlines": wrapFunctions(trimLines),
  };

  if (allowedModules[moduleName]) {
    return allowedModules[moduleName];
  }
  throw Error(`Module not available from within an event "${moduleName}"`);
};

function wrapFunctions(inputObj) {
  const helpers = Object.keys(inputObj).reduce((acc, key) => {
    // Wrap each function from inputObj in an ivm.Callback and assign to acc
    acc[key] = new ivm.Callback((...args) => inputObj[key](...args));
    return acc;
  }, {});

  // Use ivm.ExternalCopy to wrap the helpers object and call copyInto
  const output = new ivm.ExternalCopy(helpers).copyInto({ transferIn: true });

  return output;
}

const loadScriptEventHandler = async (
  path: string
): Promise<ScriptEventHandler> => {
  const context = isolate.createContextSync();
  const jail = context.global;

  jail.setSync("global", jail.derefInto());
  jail.setSync("require", sandboxedRequire);
  jail.setSync("module", {}, { copy: true });

  const handlerCode = await readFile(path, "utf8");
  const script = isolate.compileScriptSync(handlerCode);
  await script.run(context).catch((err: unknown) => console.error(err));

  // Add hasAutoLabel flag
  context.evalSync(`module.exports.hasAutoLabel = !!module.exports.autoLabel`);

  // Add hasPostUpdateFn flag to fields
  context.evalSync(
    `module.exports.fields && module.exports.fields.forEach((field) => field.hasPostUpdateFn = !!field.postUpdateFn)`
  );

  // Add isConditional flag
  context.evalSync(
    `module.exports.isConditional = module.exports.fields && !!module.exports.fields.find((f) => f.type === "events")`
  );

  // Build serializable scriptEventDef to export from VM
  context.evalSync(
    "scriptEventDef = JSON.parse(JSON.stringify(module.exports))"
  );

  const exportedCompileFunctionReference = jail
    .getSync("module", { copy: false })
    .getSync("exports")
    .getSync("compile");

  const handler = {
    ...jail.getSync("scriptEventDef", { copy: true }),
    compile: (input: Record<string, unknown>, helpers: any) => {
      const argument1 = new ivm.ExternalCopy(input).copyInto({
        transferIn: true,
      });
      const argument2 = wrapFunctions(helpers);
      exportedCompileFunctionReference.apply(null, [argument1, argument2], {
        result: { copy: true },
      });
    },
    autoLabel: () => "Hello World",
  };

  if (!handler.id) {
    throw new Error(`Event handler ${path} is missing id`);
  }
  // handler.hasAutoLabel = !!handler.autoLabel;
  handler.fieldsLookup = {};

  // Build flat lookup table of field keys to field
  // To prevent needing to recursively loop through
  // nested fields at editor runtime
  const buildFieldsLookup = (fields: ScriptEventHandlerFieldSchema[]): void => {
    for (const field of fields) {
      if (field.type === "group" && field.fields) {
        buildFieldsLookup(field.fields);
      } else if (field.key) {
        if (field.hasPostUpdateFn) {
          field.postUpdateFn = () => {
            console.warn("TODO: pass postUpdateFn to isolated-vm");
          };
        }
        handler.fieldsLookup[field.key] = field;
      }
    }
  };
  buildFieldsLookup(handler.fields);

  return handler;
};

const loadAllScriptEventHandlers = async (projectRoot: string) => {
  const corePaths = await globAsync(`${eventsRoot}/event*.js`);

  const pluginPaths = await globAsync(
    `${projectRoot}/plugins/**/events/event*.js`
  );

  const eventHandlers: ScriptEventHandlers = {};
  for (const path of corePaths) {
    const handler = await loadScriptEventHandler(path);
    eventHandlers[handler.id] = handler;
  }
  for (const path of pluginPaths) {
    const handler = await loadScriptEventHandler(path);
    eventHandlers[handler.id] = handler;
  }

  return eventHandlers;
};

export default loadAllScriptEventHandlers;
