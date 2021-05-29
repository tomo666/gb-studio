import { Middleware } from "@reduxjs/toolkit";
import { RootState } from "store/configureStore";
import actions from "./spriteActions";
import projectActions from "../project/projectActions";
import {
  metaspriteSelectors,
  metaspriteTileSelectors,
  spriteAnimationSelectors,
  spriteSheetSelectors,
} from "../entities/entitiesState";
import entitiesActions from "../entities/entitiesActions";
import { detect, detectClassic } from "lib/sprite/detect";
import { compileSprite } from "lib/compiler/compileSprites";
import { denormalizeSprite } from "../entities/entitiesHelpers";

const spriteMiddleware: Middleware<{}, RootState> =
  (store) => (next) => async (action) => {
    if (actions.detectSprite.match(action)) {
      const state = store.getState();
      const projectRoot = state.document.root;

      const spriteSheet = spriteSheetSelectors.selectById(
        state,
        action.payload.spriteSheetId
      );

      if (!spriteSheet) {
        return next(action);
      }

      if (spriteSheet.height === 16) {
        store.dispatch(
          actions.detectSpriteComplete(
            // Classic Sprite Format
            detectClassic(spriteSheet)
          )
        );
      } else {
        store.dispatch(
          actions.detectSpriteComplete(await detect(spriteSheet, projectRoot))
        );
      }

      store.dispatch(
        actions.compileSprite({ spriteSheetId: action.payload.spriteSheetId })
      );
    }

    next(action);

    // Trigger recompile if sprite has changed
    if (entitiesActions.editSpriteSheet.match(action)) {
      if (
        action.payload.changes.numTiles === undefined &&
        action.payload.changes.autoDetect === undefined
      ) {
        store.dispatch(
          actions.compileSprite({ spriteSheetId: action.payload.spriteSheetId })
        );
      }
    }

    // Trigger recompile if sprite animations or tiles have changed
    if (
      entitiesActions.addMetasprite.match(action) ||
      entitiesActions.cloneMetasprite.match(action) ||
      entitiesActions.sendMetaspriteTilesToFront.match(action) ||
      entitiesActions.sendMetaspriteTilesToBack.match(action) ||
      entitiesActions.removeMetasprite.match(action) ||
      entitiesActions.addMetaspriteTile.match(action) ||
      entitiesActions.moveMetaspriteTiles.match(action) ||
      entitiesActions.moveMetaspriteTilesRelative.match(action) ||
      entitiesActions.flipXMetaspriteTiles.match(action) ||
      entitiesActions.flipYMetaspriteTiles.match(action) ||
      entitiesActions.editMetaspriteTile.match(action) ||
      entitiesActions.editMetaspriteTiles.match(action) ||
      entitiesActions.removeMetaspriteTiles.match(action) ||
      entitiesActions.removeMetaspriteTilesOutsideCanvas.match(action) ||
      entitiesActions.editSpriteAnimation.match(action) ||
      entitiesActions.swapSpriteAnimationFrames.match(action)
    ) {
      const state = store.getState();
      const spriteSheet = spriteSheetSelectors.selectById(
        state,
        action.payload.spriteSheetId
      );
      store.dispatch(
        actions.compileSprite({ spriteSheetId: action.payload.spriteSheetId })
      );
      if (spriteSheet?.autoDetect) {
        store.dispatch(
          entitiesActions.editSpriteSheet({
            spriteSheetId: action.payload.spriteSheetId,
            changes: {
              autoDetect: false,
            },
          })
        );
      }
    }

    // Compile sprite to determine how many tiles it will use
    if (actions.compileSprite.match(action)) {
      const state = store.getState();
      const projectRoot = state.document.root;

      const spriteSheet = spriteSheetSelectors.selectById(
        state,
        action.payload.spriteSheetId
      );

      if (!spriteSheet) {
        return next(action);
      }

      const metasprites = metaspriteSelectors.selectEntities(state);
      const metaspriteTiles = metaspriteTileSelectors.selectEntities(state);
      const spriteAnimations = spriteAnimationSelectors.selectEntities(state);

      const spriteData = denormalizeSprite({
        sprite: spriteSheet,
        metasprites,
        metaspriteTiles,
        spriteAnimations,
      });

      const res = await compileSprite(spriteData, projectRoot);
      const numTiles = res.tiles.length / 2;

      if (numTiles !== spriteSheet.numTiles) {
        store.dispatch(
          entitiesActions.editSpriteSheet({
            spriteSheetId: action.payload.spriteSheetId,
            changes: {
              numTiles,
            },
          })
        );
      }
    }

    if (projectActions.loadProject.fulfilled.match(action)) {
      for (const spriteSheetId of action.payload.modifiedSpriteIds) {
        store.dispatch(actions.detectSprite({ spriteSheetId }));
      }
    }

    if (projectActions.loadSprite.fulfilled.match(action)) {
      const state = store.getState();
      const spriteSheet = spriteSheetSelectors.selectById(
        state,
        action.payload.data.id
      );
      if (spriteSheet) {
        if (
          !spriteSheet.animations ||
          spriteSheet.animations.length === 0 ||
          spriteSheet.autoDetect
        ) {
          store.dispatch(
            actions.detectSprite({ spriteSheetId: spriteSheet.id })
          );
        }
      }
    }
  };

export default spriteMiddleware;
