// Copyright (c) 2025 LootLocker
#include "LootLockerServerUpdateChecker.h"
#include "SLootLockerServerUpdateNotification.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/DateTime.h"
#include "Misc/ConfigCacheIni.h"
#include "Containers/Ticker.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "HAL/PlatformProcess.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogLootLockerServerSDKEditor, Log, All);

// --- Static member definitions ---
FTSTicker::FDelegateHandle FLootLockerServerUpdateChecker::TickerHandle;
const TCHAR* FLootLockerServerUpdateChecker::ConfigSection =
    TEXT("/Script/LootLockerServerSDKEditor.UpdateChecker");
const TCHAR* FLootLockerServerUpdateChecker::GitHubReleasesUrl =
    TEXT("https://api.github.com/repos/lootlocker/unreal-server-sdk/releases/latest");

// ---------------------------------------------------------------------------

void FLootLockerServerUpdateChecker::Initialize()
{
    // Fire once after StartupDelaySeconds — return false in the callback to auto-unregister.
    TickerHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateStatic(&FLootLockerServerUpdateChecker::OnStartupTick),
        StartupDelaySeconds
    );
}

void FLootLockerServerUpdateChecker::Shutdown()
{
    if (TickerHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
        TickerHandle.Reset();
    }
}

void FLootLockerServerUpdateChecker::ManualCheck()
{
    CheckForUpdate(/*bManual=*/true);
}

bool FLootLockerServerUpdateChecker::OnStartupTick(float DeltaTime)
{
    CheckForUpdate(/*bManual=*/false);
    return false;  // one-shot — unregister immediately
}

void FLootLockerServerUpdateChecker::CheckForUpdate(bool bManual)
{
    if (!bManual && !ShouldCheck())
    {
        return;
    }
    FetchLatestRelease(bManual);
}

bool FLootLockerServerUpdateChecker::ShouldCheck()
{
    if (GetNeverNotify())
    {
        return false;
    }

    const FDateTime RemindAfter = GetRemindAfterTime();
    if (FDateTime::UtcNow() < RemindAfter)
    {
        return false;
    }

    const FDateTime LastChecked = GetLastCheckedTime();
    const FTimespan TimeSinceLastCheck = FDateTime::UtcNow() - LastChecked;
    if (TimeSinceLastCheck.GetTotalHours() < CheckIntervalHours)
    {
        return false;
    }

    return true;
}

bool FLootLockerServerUpdateChecker::ShouldNotify(const FString& LatestVersion)
{
    return GetSkippedVersion() != LatestVersion;
}

void FLootLockerServerUpdateChecker::FetchLatestRelease(bool bManual)
{
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(GitHubReleasesUrl);
    Request->SetVerb(TEXT("GET"));
    Request->SetHeader(TEXT("Accept"), TEXT("application/vnd.github.v3+json"));
    Request->SetHeader(TEXT("User-Agent"), TEXT("LootLockerServerSDK-UnrealEditor"));

    Request->OnProcessRequestComplete().BindLambda(
        [bManual](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bWasSuccessful)
        {
            FLootLockerServerUpdateChecker::OnResponseReceived(Req, Resp, bWasSuccessful, bManual);
        }
    );

    Request->ProcessRequest();
}

void FLootLockerServerUpdateChecker::OnResponseReceived(
    FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, bool bManual)
{
    if (!bWasSuccessful || !Response.IsValid() || Response->GetResponseCode() != 200)
    {
        if (bManual)
        {
            UE_LOG(LogLootLockerServerSDKEditor, Warning,
                TEXT("LootLocker Server SDK update check failed (HTTP %d)."),
                Response.IsValid() ? Response->GetResponseCode() : 0);

            FNotificationInfo Info(FText::FromString(
                TEXT("LootLocker Server SDK: Could not reach GitHub to check for updates.")));
            Info.ExpireDuration = 5.0f;
            Info.bFireAndForget = true;
            FSlateNotificationManager::Get().AddNotification(Info);
        }
        return;
    }

    TSharedPtr<FJsonObject> JsonObject;
    const TSharedRef<TJsonReader<>> Reader =
        TJsonReaderFactory<>::Create(Response->GetContentAsString());

    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        UE_LOG(LogLootLockerServerSDKEditor, Warning,
            TEXT("LootLocker Server SDK update check: failed to parse GitHub response."));
        return;
    }

    FString TagName;
    FString HtmlUrl;
    if (!JsonObject->TryGetStringField(TEXT("tag_name"), TagName) ||
        !JsonObject->TryGetStringField(TEXT("html_url"), HtmlUrl))
    {
        UE_LOG(LogLootLockerServerSDKEditor, Warning,
            TEXT("LootLocker Server SDK update check: GitHub response is missing expected fields."));
        return;
    }

    // Strip leading 'v' or 'V'
    if (TagName.StartsWith(TEXT("v")) || TagName.StartsWith(TEXT("V")))
    {
        TagName.RightChopInline(1);
    }

    // Strip pre-release suffix
    int32 DashIndex;
    if (TagName.FindChar(TEXT('-'), DashIndex))
    {
        TagName = TagName.Left(DashIndex);
    }
    int32 PlusIndex;
    if (TagName.FindChar(TEXT('+'), PlusIndex))
    {
        TagName = TagName.Left(PlusIndex);
    }

    SaveLastCheckedTime(FDateTime::UtcNow());

    if (IsVersionNewer(TagName, GetCurrentVersion()))
    {
        if (bManual || ShouldNotify(TagName))
        {
            ShowUpdateNotification(TagName, HtmlUrl);
        }
    }
    else if (bManual)
    {
        ShowUpToDateNotification();
    }
}

void FLootLockerServerUpdateChecker::ShowUpdateNotification(
    const FString& LatestVersion, const FString& ReleaseUrl)
{
    if (!FSlateApplication::IsInitialized())
    {
        return;
    }

    const TSharedRef<SWindow> Window = SNew(SWindow)
        .Title(FText::FromString(TEXT("LootLocker Server SDK Update Available")))
        .ClientSize(FVector2D(580.0f, 210.0f))
        .SupportsMinimize(false)
        .SupportsMaximize(false)
        .IsTopmostWindow(false)
        .SizingRule(ESizingRule::FixedSize);

    Window->SetContent(
        SNew(SLootLockerServerUpdateNotification)
            .CurrentVersion(GetCurrentVersion())
            .LatestVersion(LatestVersion)
            .ReleaseUrl(ReleaseUrl)
            .ParentWindow(Window)
    );

    FSlateApplication::Get().AddWindow(Window);
}

void FLootLockerServerUpdateChecker::ShowUpToDateNotification()
{
    FNotificationInfo Info(FText::FromString(
        TEXT("LootLocker Server SDK is up to date!")));
    Info.ExpireDuration = 5.0f;
    Info.bFireAndForget = true;
    FSlateNotificationManager::Get().AddNotification(Info);
}

bool FLootLockerServerUpdateChecker::IsVersionNewer(
    const FString& RemoteVersion, const FString& LocalVersion)
{
    TArray<FString> RemoteParts, LocalParts;
    RemoteVersion.ParseIntoArray(RemoteParts, TEXT("."));
    LocalVersion.ParseIntoArray(LocalParts, TEXT("."));

    const int32 MaxParts = FMath::Max(RemoteParts.Num(), LocalParts.Num());
    for (int32 i = 0; i < MaxParts; ++i)
    {
        const int32 Remote = (i < RemoteParts.Num()) ? FCString::Atoi(*RemoteParts[i]) : 0;
        const int32 Local  = (i < LocalParts.Num())  ? FCString::Atoi(*LocalParts[i])  : 0;
        if (Remote > Local) return true;
        if (Remote < Local) return false;
    }
    return false;
}

FString FLootLockerServerUpdateChecker::GetCurrentVersion()
{
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("LootLockerServerSDK"));
    if (Plugin.IsValid())
    {
        return Plugin->GetDescriptor().VersionName;
    }
    return TEXT("0.0.0");
}

// --- Config helpers ---

bool FLootLockerServerUpdateChecker::GetNeverNotify()
{
    bool bValue = false;
    GConfig->GetBool(ConfigSection, TEXT("NeverNotify"), bValue, GEditorPerProjectIni);
    return bValue;
}

void FLootLockerServerUpdateChecker::SetNeverNotify(bool bValue)
{
    GConfig->SetBool(ConfigSection, TEXT("NeverNotify"), bValue, GEditorPerProjectIni);
    GConfig->Flush(false, GEditorPerProjectIni);
}

FString FLootLockerServerUpdateChecker::GetSkippedVersion()
{
    FString Value;
    GConfig->GetString(ConfigSection, TEXT("SkippedVersion"), Value, GEditorPerProjectIni);
    return Value;
}

void FLootLockerServerUpdateChecker::SetSkippedVersion(const FString& Version)
{
    GConfig->SetString(ConfigSection, TEXT("SkippedVersion"), *Version, GEditorPerProjectIni);
    GConfig->Flush(false, GEditorPerProjectIni);
}

FDateTime FLootLockerServerUpdateChecker::GetRemindAfterTime()
{
    FString Value;
    GConfig->GetString(ConfigSection, TEXT("RemindAfterUtc"), Value, GEditorPerProjectIni);
    FDateTime Result;
    if (FDateTime::ParseIso8601(*Value, Result))
    {
        return Result;
    }
    return FDateTime::MinValue();
}

void FLootLockerServerUpdateChecker::SetRemindAfterTime(const FDateTime& Time)
{
    GConfig->SetString(ConfigSection, TEXT("RemindAfterUtc"), *Time.ToIso8601(), GEditorPerProjectIni);
    GConfig->Flush(false, GEditorPerProjectIni);
}

FDateTime FLootLockerServerUpdateChecker::GetLastCheckedTime()
{
    FString Value;
    GConfig->GetString(ConfigSection, TEXT("LastCheckedUtc"), Value, GEditorPerProjectIni);
    FDateTime Result;
    if (FDateTime::ParseIso8601(*Value, Result))
    {
        return Result;
    }
    return FDateTime::MinValue();
}

void FLootLockerServerUpdateChecker::SaveLastCheckedTime(const FDateTime& Time)
{
    GConfig->SetString(ConfigSection, TEXT("LastCheckedUtc"), *Time.ToIso8601(), GEditorPerProjectIni);
    GConfig->Flush(false, GEditorPerProjectIni);
}
