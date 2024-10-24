import React, { useEffect, useRef } from "react";
import { useAppSelector } from "store/hooks";
import { CollisionTileDef } from "shared/lib/resources/types";
import {
  defaultCollisionTileColor,
  defaultCollisionTileIcon,
  defaultCollisionTileDefs,
} from "consts";
import {
  isCollisionTileActive,
  renderCollisionTileIcon,
} from "shared/lib/collisions/collisionTiles";
import { decHexVal } from "shared/lib/helpers/8bit";

const TILE_SIZE = 16;

interface SceneCollisionsProps {
  width: number;
  height: number;
  collisions: number[];
  sceneTypeKey: string;
}

const SceneCollisions = ({
  width,
  height,
  collisions,
  sceneTypeKey,
}: SceneCollisionsProps) => {
  const canvas = useRef<HTMLCanvasElement>(null);

  const showCollisionTileValues = useAppSelector(
    (state) => state.project.present.settings.showCollisionTileValues
  );

  const collisionLayerOpacity = useAppSelector(
    (state) =>
      Math.floor(state.project.present.settings.collisionLayerOpacity) / 100
  );

  const collisionTileDefs = useAppSelector((state) => {
    const sceneType = state.engine.sceneTypes.find(
      (s) => s.key === sceneTypeKey
    );
    if (sceneType && sceneType.collisionTiles) return sceneType.collisionTiles;
    return defaultCollisionTileDefs;
  });

  const drawCollisionTile = (
    tile: CollisionTileDef,
    ctx: CanvasRenderingContext2D,
    xi: number,
    yi: number
  ) => {
    const tileIcon = renderCollisionTileIcon(
      tile.icon ?? defaultCollisionTileIcon,
      tile.color ?? defaultCollisionTileColor
    );
    ctx.drawImage(
      tileIcon,
      0,
      0,
      8,
      8,
      xi * TILE_SIZE,
      yi * TILE_SIZE,
      TILE_SIZE,
      TILE_SIZE
    );
  };

  const drawLetter = (
    letter: string,
    ctx: CanvasRenderingContext2D,
    x: number,
    y: number
  ) => {
    ctx.textBaseline = "middle";
    const tx = x * TILE_SIZE;
    const ty = (y + 0.5) * TILE_SIZE;
    ctx.strokeStyle = "black";
    ctx.lineWidth = 2;
    ctx.strokeText(letter, tx, ty);
    ctx.fillStyle = "white";
    ctx.fillText(letter, tx, ty);
  };

  useEffect(() => {
    if (canvas.current) {
      // eslint-disable-next-line no-self-assign
      canvas.current.width = canvas.current.width; // Clear canvas
      const ctx = canvas.current.getContext("2d");

      if (!ctx) return;

      ctx.font = "8px Public Pixel";
      ctx.imageSmoothingEnabled = false;

      const sortedTileDefs = collisionTileDefs.map((t) => t);
      sortedTileDefs.sort((a, b) => {
        if (a.mask) {
          if (b.mask) {
            const aCount = a.mask.toString(2).split("1").length - 1;
            const bCount = b.mask.toString(2).split("1").length - 1;
            if (aCount > bCount) return -1;
            else if (bCount > aCount) return 1;
          } else return 1;
        } else if (b.mask) return -1;

        const aCount = a.flag.toString(2).split("1").length - 1;
        const bCount = b.flag.toString(2).split("1").length - 1;
        return bCount - aCount;
      });

      for (let yi = 0; yi < height; yi++) {
        for (let xi = 0; xi < width; xi++) {
          const collisionIndex = width * yi + xi;
          const tile = collisions[collisionIndex] ?? 0;
          let unknownTile = tile !== 0;

          for (const tileDef of sortedTileDefs) {
            if (isCollisionTileActive(tile, tileDef)) {
              ctx.fillStyle = tileDef.color;
              drawCollisionTile(tileDef, ctx, xi, yi);
              if (tileDef.icon) {
                unknownTile = false;
              }
            }
          }
          if (
            unknownTile ||
            (showCollisionTileValues && tile !== 0 && tile !== undefined)
          ) {
            drawLetter(decHexVal(tile), ctx, xi, yi);
          }
        }
      }
    }
  }, [collisionTileDefs, collisions, height, showCollisionTileValues, width]);

  return (
    <canvas
      ref={canvas}
      width={width * TILE_SIZE}
      height={height * TILE_SIZE}
      style={{
        opacity: collisionLayerOpacity,
        width: width * TILE_SIZE * 0.5,
        imageRendering: "pixelated",
      }}
    />
  );
};

export default SceneCollisions;
