// Copyright (c) 2021 LootLocker

#pragma once

/// @addtogroup Init
/// @{

#include "CoreMinimal.h"
#include "LootLockerServerFileConfig.generated.h"

/**
 * Data struct for the pre-configured file config, loaded at startup from the "<PackageName>ServerPreConfig[-<identifier>].bytes"
 * file in the plugin's Config directory. When present and containing a non-empty api_key, it overrides
 * DefaultGame.ini settings and locks the editor UI to prevent drift.
 *
 * The file supports plain JSON or AES-256-ECB + PKCS7 + Base64 encrypted content. Plain JSON is
 * recommended during development; encrypted files should be used for distribution.
 *
 * Supported JSON fields:
 *   api_key                                       (string, required — empty or missing means "inactive")
 *   domain_key                                    (string)
 *   game_version                                  (string, default "1.0.0.0")
 *   log_outside_of_editor                         (bool, default false)
 *   log_level                                     (string: "Error"|"Warning"|"Display"|"Verbose"|"VeryVerbose"|"NoLogging", default "Warning")
 *   enable_file_logging                           (bool, default false)
 */
USTRUCT()
struct LOOTLOCKERSERVERSDK_API FLootLockerServerFileConfig
{
	GENERATED_BODY()

	UPROPERTY()
	FString api_key;

	UPROPERTY()
	FString domain_key;

	UPROPERTY()
	FString game_version = TEXT("1.0.0.0");

	UPROPERTY()
	bool log_outside_of_editor = false;

	UPROPERTY()
	FString log_level = TEXT("Warning");

	UPROPERTY()
	bool enable_file_logging = false;
};

/// @}
