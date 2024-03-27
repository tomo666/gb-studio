import { assetFilename } from "shared/lib/helpers/assets";
import getFileModifiedTime from "lib/helpers/fs/getModifiedTime";
import { getBackgroundInfo } from "lib/helpers/validation";
import {
  tileLookupToTileData,
  tileArrayToTileData,
  tilesAndLookupToTilemap,
  toTileLookup,
  TileLookup,
} from "shared/lib/tiles/tileData";
import { readFileToTilesDataArray } from "lib/tiles/readFileToTiles";
import { BackgroundData } from "shared/lib/entities/entitiesTypes";

type CompileImageOptions = {
  warnings: (msg: string) => void;
};

interface CompiledImagesResult {
  tilesets: Uint8Array[];
  tilemaps: Record<string, number[] | Uint8Array>;
  tilemapsTileset: Record<string, number[]>;
}

const imageBuildCache: Record<
  string,
  {
    timestamp: number;
    data: TileLookup;
    tileData: Uint8Array[];
  }
> = {};

let lastOutput: CompiledImagesResult | null = null;
let lastOutputIds = "";

const compileImages = async (
  imgs: BackgroundData[],
  generate360Ids: string[],
  cgbOnly: boolean,
  projectPath: string,
  tmpPath: string,
  { warnings }: CompileImageOptions
): Promise<CompiledImagesResult> => {
  const tilesetLookups: (TileLookup | null)[] = [];
  const tilesetIndexes: number[] = [];
  const imgTiles: Uint8Array[][] = [];
  const output: CompiledImagesResult = {
    tilesets: [],
    tilemaps: {},
    tilemapsTileset: {},
  };
  let uncachedCount = 0;

  // Build lookups
  for (let i = 0; i < imgs.length; i++) {
    const img = imgs[i];

    const filename = assetFilename(projectPath, "backgrounds", img);
    let tilesetLookup : TileLookup | undefined;

    const imageModifiedTime = await getFileModifiedTime(filename);

    const is360 = generate360Ids.includes(img.id);
    const cacheKey = `${img.id}${is360 ? "_360" : ""}`;

    if (
      imageBuildCache[cacheKey] &&
      imageBuildCache[cacheKey].timestamp >= imageModifiedTime
    ) {
      tilesetLookup = imageBuildCache[cacheKey].data;
      imgTiles.push(imageBuildCache[cacheKey].tileData);
    } else {
      const tileData = await readFileToTilesDataArray(filename);
      tilesetLookup = toTileLookup(tileData);
      imageBuildCache[cacheKey] = {
        data: tilesetLookup,
        tileData,
        timestamp: imageModifiedTime,
      };
      imgTiles.push(tileData);
      uncachedCount++;
    }

    const tilesetLength = Object.keys(tilesetLookup).length;
    tilesetIndexes[i] = i;

    const backgroundInfo = await getBackgroundInfo(
      img,
      is360,
      projectPath,
      tilesetLength
    );
    const backgroundWarnings = backgroundInfo.warnings;
    if (backgroundWarnings.length > 0) {
      backgroundWarnings.forEach((warning) => {
        warnings(`${img.filename}: ${warning}`);
      });
    }

    if (is360) {
      // Skip lookups for 360 images (generated later)
      tilesetLookups.push(null);
      continue;
    }
    tilesetLookups.push(tilesetLookup);
  }

  // If previous build generated the same images all unmodified
  // no need to recalculate image tiles and tile lookups,
  // just reuse last compile
  const ids = imgs.map((img) => img.id).join();
  if (uncachedCount === 0 && ids === lastOutputIds && lastOutput) {
    return lastOutput;
  }

  // Share identical tilesets
  for (let i = 0; i < imgs.length - 1; i++) {
    if (!tilesetLookups[i]) {
      continue;
    }
    for (let j = i + 1; j < imgs.length; j++) {
      if (!tilesetLookups[j]) {
        continue;
      }
      if (tilesetLookups[i] === tilesetLookups[j]) {
        continue;
      }

      if (
        JSON.stringify(tilesetLookups[i]) === JSON.stringify(tilesetLookups[j])
      ) {
        tilesetLookups[j] = tilesetLookups[i];
      }
    }
  }

  // Remove unneeded tilesets
  for (let i = 0; i < imgs.length - 1; i++) {
    for (let j = imgs.length - 1; j >= i + 1; j--) {
      if (tilesetLookups[i] === tilesetLookups[j]) {
        tilesetIndexes[i] = j;
        tilesetLookups[i] = null;
        break;
      }
    }
  }

  for (let i = 0; i < imgs.length; i++) {
    if (generate360Ids.includes(imgs[i].id)) {
      // Generate 360 tileset
      const tileSetIndex = output.tilesets.length;
      output.tilesets.push(tileArrayToTileData(imgTiles[i]));
      // Generate 360 tilemap
      output.tilemaps[imgs[i].id] = Array.from(Array(360)).map((_, i) => i);
      output.tilemapsTileset[imgs[i].id] = [tileSetIndex];
    } else {
      const tiles = tileLookupToTileData(tilesetLookups[i] ?? {});
      const tileSetIndex = output.tilesets.length;
      const bank1Tiles = cgbOnly ? tiles.slice(0, 192 * 16) : tiles;
      const bank2Tiles = cgbOnly ? tiles.slice(192 * 16, 192 * 16 * 2) : new Uint8Array();

      output.tilesets.push(bank1Tiles);
      if (bank2Tiles.length > 0) {
        // Two banks
        output.tilesets.push(bank2Tiles);
      }
      const tilemap = tilesAndLookupToTilemap(
        imgTiles[i],
        tilesetLookups[tilesetIndexes[i]] ?? {}
      );
      output.tilemaps[imgs[i].id] = tilemap;
      output.tilemapsTileset[imgs[i].id] = bank2Tiles.length > 0 ? [tileSetIndex, tileSetIndex+1] : [tileSetIndex];
    }
  }

  lastOutput = output;
  lastOutputIds = ids;

  return output;
};

export default compileImages;
