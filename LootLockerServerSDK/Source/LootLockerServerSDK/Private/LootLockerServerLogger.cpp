// Copyright (c) 2021 LootLocker

#include "LootLockerServerLogger.h"
#include "Logging/LogVerbosity.h"
#include "LootLockerServerConfig.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Utils/LootLockerServerUtilities.h"

DEFINE_LOG_CATEGORY(LogLootLockerServer);

FLootLockerServerOnLogMessage FLootLockerServerLogger::OnLogMessage;

void FLootLockerServerLogger::Log(const FString& Message, ELootLockerServerLogLevel Verbosity)
{
    switch (Verbosity)
    {
    case ELootLockerServerLogLevel::Fatal:
    case ELootLockerServerLogLevel::Error:
        UE_LOG(LogLootLockerServer, Error, TEXT("%s"), *Message);
        break;
    case ELootLockerServerLogLevel::Warning:
        UE_LOG(LogLootLockerServer, Warning, TEXT("%s"), *Message);
        break;
    case ELootLockerServerLogLevel::Display:
    case ELootLockerServerLogLevel::Log:
        UE_LOG(LogLootLockerServer, Display, TEXT("%s"), *Message);
        break;
    case ELootLockerServerLogLevel::Verbose:
        UE_LOG(LogLootLockerServer, Verbose, TEXT("%s"), *Message);
        break;
    case ELootLockerServerLogLevel::VeryVerbose:
        UE_LOG(LogLootLockerServer, VeryVerbose, TEXT("%s"), *Message);
        break;
    default:
        break;
    }
    WriteToFile(Message);
    OnLogMessage.Broadcast(Message, Verbosity);
}

void FLootLockerServerLogger::LogHttpRequest(const FLootLockerServerHttpLogEntry& Entry)
{
    // Sanitize once and use the sanitized copy for every surface: the log line, the file log and
    // the OnHttpLogEntry broadcast. Only player-file endpoints can carry a signed URL, so every
    // other entry is used as-is and the common path does no copying or JSON traversal.
    FLootLockerServerHttpLogEntry SanitizedEntry = Entry;
    if (LootLockerServerUtilities::CanReturnSignedDownloadUrl(Entry.Path))
    {
        SanitizedEntry.ResponseData = LootLockerServerUtilities::RedactSignedDownloadUrlsForLogging(Entry.ResponseData);
        SanitizedEntry.ErrorData.Message = LootLockerServerUtilities::RedactSignedDownloadUrlsForLogging(Entry.ErrorData.Message);
    }

    FString LogString;
    LogString += FString::Printf(TEXT("[HTTP] %s %s  Status: %d  Duration: %.3fs"), *SanitizedEntry.Method, *SanitizedEntry.Path, SanitizedEntry.StatusCode, SanitizedEntry.Duration);
    if (!SanitizedEntry.bSuccess)
    {
        if (!SanitizedEntry.ErrorData.Code.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Error Code: %s"), *SanitizedEntry.ErrorData.Code);
        if (!SanitizedEntry.ErrorData.Message.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Error Message: %s"), *SanitizedEntry.ErrorData.Message);
        if (!SanitizedEntry.ErrorData.Doc_url.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Further Information: %s"), *SanitizedEntry.ErrorData.Doc_url);
        if (!SanitizedEntry.ErrorData.Request_id.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Request ID: %s"), *SanitizedEntry.ErrorData.Request_id);
        if (!SanitizedEntry.ErrorData.Trace_id.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Trace ID: %s"), *SanitizedEntry.ErrorData.Trace_id);
    }
    LogString += FString::Printf(TEXT("\n   Request Data: %s"), *SanitizedEntry.RequestData);
    LogString += FString::Printf(TEXT("\n   Response Data: %s"), *SanitizedEntry.ResponseData);
    LogString += FString::Printf(TEXT("\n   Request Headers: %s"), *SanitizedEntry.RequestHeaders);
    LogString += TEXT("\n###");
    Log(LogString, SanitizedEntry.bSuccess ? ELootLockerServerLogLevel::VeryVerbose : ELootLockerServerLogLevel::Warning);
    OnHttpLogEntry.Broadcast(SanitizedEntry);
}

void FLootLockerServerLogger::WriteToFile(const FString& Message)
{
    if (!ULootLockerServerConfig::IsFileLoggingEnabled()) return;
    FScopeLock Lock(&FileLogCriticalSection);
    FString Timestamp = FDateTime::UtcNow().ToIso8601();
    FString OutLine = FString::Printf(TEXT("[%s] %s%s"), *Timestamp, *Message, LINE_TERMINATOR);
    FString LogFilePath = ULootLockerServerConfig::GetLogFilePath();
    if (!LogFilePath.IsEmpty())
    {
        FFileHelper::SaveStringToFile(OutLine, *LogFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
    }
}

FLootLockerServerOnHttpLogEntry FLootLockerServerLogger::OnHttpLogEntry;
FCriticalSection FLootLockerServerLogger::FileLogCriticalSection;