// Copyright (c) 2025 LootLocker
// LootLockerServerSDKEditor.cpp
#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "Widgets/Layout/SBox.h"
#include "LootLockerServerLogViewerWidget.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"

static const FName LootLockerServerLogViewerTabName("LootLockerServerLogViewerTab");

class FLootLockerServerSDKEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        FGlobalTabmanager::Get()->RegisterNomadTabSpawner(LootLockerServerLogViewerTabName,
            FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& Args) {
                return SNew(SDockTab)
                    .TabRole(ETabRole::NomadTab)
                    [
                        SNew(SLootLockerServerLogViewerWidget)
                    ];
            })
        ).SetDisplayName(FText::FromString("LootLocker Server Log Viewer"))
         .SetMenuType(ETabSpawnerMenuType::Enabled);

        UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateLambda([]
        {
            UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
            if (Menu)
            {
                FToolMenuSection& Section = Menu->AddSection("LootLocker Tools", FText::FromString("LootLocker Tools"));
            }
        }));
    }

    virtual void ShutdownModule() override
    {
        FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(LootLockerServerLogViewerTabName);
    }
};

IMPLEMENT_MODULE(FLootLockerServerSDKEditorModule, LootLockerServerSDKEditor)
