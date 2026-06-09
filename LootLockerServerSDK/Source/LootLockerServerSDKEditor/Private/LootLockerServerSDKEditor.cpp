// Copyright (c) 2025 LootLocker
// LootLockerServerSDKEditor.cpp
#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "Widgets/Layout/SBox.h"
#include "LootLockerServerLogViewerWidget.h"
#include "LootLockerServerUpdateChecker.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/App.h"

static const FName LootLockerServerLogViewerTabName("LootLockerServerLogViewerTab");

class FLootLockerServerSDKEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        // Do not register Slate widgets in headless/unattended mode (automated tests, commandlets).
        if (FApp::IsUnattended() || !FSlateApplication::IsInitialized())
        {
            return;
        }

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
                Section.AddMenuEntry(
                    "LootLockerServerLogViewerMenuEntry",
                    FText::FromString("LootLocker Server Log Viewer"),
                    FText::FromString("Open the LootLocker Server Log Viewer window."),
                    FSlateIcon(),
                    FUIAction(FExecuteAction::CreateLambda([]
                    {
                        FGlobalTabmanager::Get()->TryInvokeTab(LootLockerServerLogViewerTabName);
                    }))
                );
                Section.AddMenuEntry(
                    "LootLockerServerCheckForUpdates",
                    FText::FromString("Check for Updates"),
                    FText::FromString("Check if a newer version of the LootLocker Server SDK is available."),
                    FSlateIcon(),
                    FUIAction(FExecuteAction::CreateStatic(&FLootLockerServerUpdateChecker::ManualCheck))
                );
            }
        }));

        // Delayed update check (fires after StartupDelaySeconds)
        FLootLockerServerUpdateChecker::Initialize();
    }

    virtual void ShutdownModule() override
    {
        FLootLockerServerUpdateChecker::Shutdown();
        FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(LootLockerServerLogViewerTabName);
    }
};

IMPLEMENT_MODULE(FLootLockerServerSDKEditorModule, LootLockerServerSDKEditor)
