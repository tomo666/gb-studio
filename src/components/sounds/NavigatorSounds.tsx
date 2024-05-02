import React, { useCallback, useMemo, useState } from "react";
import { soundSelectors } from "store/features/entities/entitiesState";
import { FlatList } from "ui/lists/FlatList";
import { Sound } from "shared/lib/entities/entitiesTypes";
import { EntityListItem } from "ui/lists/EntityListItem";
import l10n from "shared/lib/lang/l10n";
import { SplitPaneHeader } from "ui/splitpane/SplitPaneHeader";
import styled from "styled-components";
import navigationActions from "store/features/navigation/navigationActions";
import { useAppDispatch, useAppSelector } from "store/hooks";
import { MenuDivider, MenuItem } from "ui/menu/Menu";
import { stripInvalidPathCharacters } from "shared/lib/helpers/stripInvalidFilenameCharacters";
import projectActions from "store/features/project/projectActions";
import {
  FileSystemNavigatorItem,
  buildAssetNavigatorItems,
} from "shared/lib/assets/buildAssetNavigatorItems";
import useToggleableList from "ui/hooks/use-toggleable-list";

interface NavigatorSoundsProps {
  height: number;
  selectedId: string;
}

const Pane = styled.div`
  overflow: hidden;
`;

export const NavigatorSounds = ({
  height,
  selectedId,
}: NavigatorSoundsProps) => {
  const allSounds = useAppSelector((state) => soundSelectors.selectAll(state));
  const dispatch = useAppDispatch();

  const {
    values: openFolders,
    isSet: isFolderOpen,
    toggle: toggleFolderOpen,
    set: openFolder,
    unset: closeFolder,
  } = useToggleableList<string>([]);

  const nestedSoundItems = useMemo(
    () => buildAssetNavigatorItems(allSounds, openFolders),
    [allSounds, openFolders]
  );

  const setSelectedId = useCallback(
    (id: string) => {
      dispatch(navigationActions.setNavigationId(id));
    },
    [dispatch]
  );

  const [renameId, setRenameId] = useState("");

  const listenForRenameStart = useCallback(
    (e) => {
      if (e.key === "Enter") {
        setRenameId(selectedId);
      }
    },
    [selectedId]
  );

  const onRenameComplete = useCallback(
    (name: string) => {
      if (renameId) {
        dispatch(
          projectActions.renameSoundAsset({
            soundId: renameId,
            newFilename: stripInvalidPathCharacters(name),
          })
        );
      }
      setRenameId("");
    },
    [dispatch, renameId]
  );

  const onRenameCancel = useCallback(() => {
    setRenameId("");
  }, []);

  const renderContextMenu = useCallback(
    (item: FileSystemNavigatorItem<Sound>) => {
      return [
        <MenuItem key="rename" onClick={() => setRenameId(item.id)}>
          {l10n("FIELD_RENAME")}
        </MenuItem>,
        <MenuDivider key="div-delete" />,
        <MenuItem
          key="delete"
          onClick={() =>
            dispatch(projectActions.removeSoundAsset({ soundId: item.id }))
          }
        >
          {l10n("MENU_DELETE_SONG")}
        </MenuItem>,
      ];
    },
    [dispatch]
  );

  const renderLabel = useCallback(
    (item: FileSystemNavigatorItem<Sound>) => {
      if (item.type === "folder") {
        return (
          <div onClick={() => toggleFolderOpen(item.id)}>{item.filename}</div>
        );
      }
      return item.filename;
    },
    [toggleFolderOpen]
  );

  return (
    <Pane style={{ height }}>
      <SplitPaneHeader collapsed={false}>{l10n("MENU_SFX")}</SplitPaneHeader>

      <FlatList
        selectedId={selectedId}
        items={nestedSoundItems}
        setSelectedId={setSelectedId}
        height={height - 30}
        onKeyDown={(e: KeyboardEvent, item) => {
          listenForRenameStart(e);
          if (item?.type === "folder") {
            if (e.key === "ArrowRight") {
              openFolder(selectedId);
            } else if (e.key === "ArrowLeft") {
              closeFolder(selectedId);
            }
          }
        }}
      >
        {({ item }) => (
          <EntityListItem
            type={item.type === "folder" ? "folder" : "sound"}
            item={item}
            rename={item.type === "file" && renameId === item.id}
            onRename={onRenameComplete}
            onRenameCancel={onRenameCancel}
            renderContextMenu={renderContextMenu}
            renderLabel={renderLabel}
            collapsable={item.type === "folder"}
            collapsed={!isFolderOpen(item.name)}
            onToggleCollapse={() => toggleFolderOpen(item.name)}
            nestLevel={item.nestLevel}
          />
        )}
      </FlatList>
    </Pane>
  );
};
