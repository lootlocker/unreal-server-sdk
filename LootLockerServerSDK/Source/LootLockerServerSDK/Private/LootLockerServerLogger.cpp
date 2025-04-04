// Copyright (c) 2021 LootLocker

#include "LootLockerServerLogger.h"
#include "Logging/LogVerbosity.h"
#include "LootLockerServerConfig.h"

DEFINE_LOG_CATEGORY(LogLootLockerServer);

ULootLockerServerLogger::ULootLockerServerLogger()
{
}

void ULootLockerServerLogger::Log(FString LogMessage) {
	Log(ELootLockerServerLogLevel::Display, LogMessage);
}

void ULootLockerServerLogger::Log(ELootLockerServerLogLevel Verbosity, FString LogMessage)
{
	if(Verbosity == ELootLockerServerLogLevel::Ignore) {
		return;
	}

	const ULootLockerServerConfig* Config = GetDefault<ULootLockerServerConfig>();

	if (!ULootLockerServerConfig::ShouldLog() && Verbosity >= ELootLockerServerLogLevel::Error)
	{
		return;
	}

	if(Config->LimitLogLevelTo != ELootLockerServerLogLevelConfiguration::NoLogging && Config->LimitLogLevelTo >= (ELootLockerServerLogLevelConfiguration)Verbosity) {
        if (Config->LimitLogLevelTo == ELootLockerServerLogLevelConfiguration::AllAsNormal) {
            Verbosity = ELootLockerServerLogLevel::Display;
		}

		switch (Verbosity) {
                case ELootLockerServerLogLevel::Fatal:
					UE_LOG(LogLootLockerServer, Fatal, TEXT("%s"), *LogMessage);
					break;
                case ELootLockerServerLogLevel::Error:
					UE_LOG(LogLootLockerServer, Error, TEXT("%s"), *LogMessage);
					break;
                case ELootLockerServerLogLevel::Warning:
					UE_LOG(LogLootLockerServer, Warning, TEXT("%s"), *LogMessage);
					break;
				default:
                case ELootLockerServerLogLevel::Display:
					UE_LOG(LogLootLockerServer, Display, TEXT("%s"), *LogMessage);
					break;
                case ELootLockerServerLogLevel::Log:
					UE_LOG(LogLootLockerServer, Log, TEXT("%s"), *LogMessage);
					break;
                case ELootLockerServerLogLevel::Verbose:
					UE_LOG(LogLootLockerServer, Verbose, TEXT("%s"), *LogMessage);
					break;
                case ELootLockerServerLogLevel::VeryVerbose:
					UE_LOG(LogLootLockerServer, VeryVerbose, TEXT("%s"), *LogMessage);
					break;
        }
	}
}