// Copyright (c) 2021 LootLocker

#include "LootLockerServerLogger.h"
#include "Logging/LogVerbosity.h"
#include "LootLockerServerConfig.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"

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
    FString LogString;
    LogString += FString::Printf(TEXT("[HTTP] %s %s  Status: %d  Duration: %.3fs"), *Entry.Method, *Entry.Path, Entry.StatusCode, Entry.Duration);
    if (!Entry.bSuccess)
    {
        if (!Entry.ErrorData.Code.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Error Code: %s"), *Entry.ErrorData.Code);
        if (!Entry.ErrorData.Message.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Error Message: %s"), *Entry.ErrorData.Message);
        if (!Entry.ErrorData.Doc_url.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Further Information: %s"), *Entry.ErrorData.Doc_url);
        if (!Entry.ErrorData.Request_id.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Request ID: %s"), *Entry.ErrorData.Request_id);
        if (!Entry.ErrorData.Trace_id.IsEmpty())
            LogString += FString::Printf(TEXT("\n   Trace ID: %s"), *Entry.ErrorData.Trace_id);
    }
    LogString += FString::Printf(TEXT("\n   Request Data: %s"), *Entry.RequestData);
    LogString += FString::Printf(TEXT("\n   Response Data: %s"), *Entry.ResponseData);
    LogString += FString::Printf(TEXT("\n   Request Headers: %s"), *Entry.RequestHeaders);
    LogString += TEXT("\n###");
    Log(LogString, Entry.bSuccess ? ELootLockerServerLogLevel::VeryVerbose : ELootLockerServerLogLevel::Warning);
    OnHttpLogEntry.Broadcast(Entry);
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