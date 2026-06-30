#Requires -Version 5.0
<#
.SYNOPSIS
    Verifies that the LootLocker Unreal Server SDK plugin compiles without errors.

.DESCRIPTION
    Reads unreal-dev-settings.json from the repo root, locates the plugin's
    .uplugin file, then runs Unreal's RunUAT BuildPlugin in batch mode to
    check that the plugin compiles cleanly on the local machine.

    See .github/instructions/verification.md for setup instructions.

.PARAMETER Clean
    Delete the previous build output and plugin Intermediate/Binaries before
    building. Omit for a faster incremental build (UAT reuses cached artifacts).

.NOTES
    Exit codes: 0 = compilation succeeded, 1 = compilation failed or setup error.
#>
param(
    [switch]$Clean
)

$ErrorActionPreference = 'Stop'

$RepoRoot   = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
$SettingsFile = Join-Path $RepoRoot "unreal-dev-settings.json"
# Use a short temp path for build output to avoid Windows MAX_PATH (260 char)
# issues with the server SDK's long filenames (e.g. LootLockerServerLeaderboardArchiveRequestHandler.cpp).
$BuildOutput  = Join-Path $env:TEMP "LLServerSdkBuild"
$LogFile      = Join-Path $RepoRoot "Build~\UAT.log"

function Write-Step { param([string]$Msg) Write-Host $Msg }
function Write-Ok   { param([string]$Msg) Write-Host $Msg -ForegroundColor Green }
function Write-Fail { param([string]$Msg) Write-Host $Msg -ForegroundColor Red }
function Write-Warn { param([string]$Msg) Write-Host $Msg -ForegroundColor Yellow }

Write-Step "==========================================="
Write-Step "  LootLocker Unreal Server SDK - Compile Check"
Write-Step "==========================================="
Write-Step ""

# ---------------------------------------------------------------------------
# 1. Load settings
# ---------------------------------------------------------------------------
if (-not (Test-Path $SettingsFile)) {
    Write-Warn "SETUP REQUIRED: 'unreal-dev-settings.json' not found at repo root."
    Write-Step ""
    Write-Step "Create the file with the following content:"
    Write-Step '  { "unreal_engine_path": "C:\\Program Files\\Epic Games\\UE_5.5" }'
    Write-Step ""
    Write-Step "See .github/instructions/verification.md for details."
    exit 1
}

$Settings      = Get-Content $SettingsFile -Raw | ConvertFrom-Json
$UnrealRoot    = $Settings.unreal_engine_path

if ([string]::IsNullOrWhiteSpace($UnrealRoot)) {
    Write-Fail "ERROR: 'unreal_engine_path' is empty in unreal-dev-settings.json."
    exit 1
}
if (-not (Test-Path $UnrealRoot)) {
    Write-Fail "ERROR: Unreal Engine path not found: $UnrealRoot"
    exit 1
}

$RunUAT = Join-Path $UnrealRoot "Engine\Build\BatchFiles\RunUAT.bat"
if (-not (Test-Path $RunUAT)) {
    Write-Fail "ERROR: RunUAT.bat not found at: $RunUAT"
    Write-Step "       Check that 'unreal_engine_path' points to the UE install root."
    exit 1
}

# ---------------------------------------------------------------------------
# 2. Locate the plugin uplugin file
# ---------------------------------------------------------------------------
$PluginFile = Get-ChildItem -Path $RepoRoot -Filter "*.uplugin" -Recurse -Depth 2 |
              Where-Object { $_.FullName -notlike "*\Build~\*" } |
              Select-Object -First 1

if (-not $PluginFile) {
    Write-Fail "ERROR: No .uplugin file found under $RepoRoot"
    exit 1
}

Write-Step "Plugin  : $($PluginFile.FullName)"
Write-Step "Engine  : $UnrealRoot"
Write-Step "Output  : $BuildOutput"
Write-Step "Log     : $LogFile"
Write-Step ""

# ---------------------------------------------------------------------------
# 3. Prepare output directories and clear stale log
# ---------------------------------------------------------------------------
if ($Clean) {
    if (Test-Path $BuildOutput) {
        Write-Step "Cleaning previous build output..."
        & cmd /c "rmdir /S /Q `"$BuildOutput`"" 2>&1 | Out-Null
        if (Test-Path $BuildOutput) {
            Write-Warn "Warning: Could not fully remove previous build output at $BuildOutput - UAT will attempt to overwrite it."
        }
    }
} elseif (Test-Path $BuildOutput) {
    Write-Step "Reusing existing build output (pass -Clean to force a full rebuild)."
}
$LogDir = Split-Path $LogFile
if (-not (Test-Path $LogDir)) { New-Item -ItemType Directory -Path $LogDir -Force | Out-Null }
if (Test-Path $LogFile) { Remove-Item $LogFile -Force }

# Clear the plugin's Intermediate and Binaries directories before UAT runs.
if ($Clean) {
    foreach ($staleDir in @("Intermediate", "Binaries")) {
        $dirPath = Join-Path (Split-Path $PluginFile.FullName) $staleDir
        if (Test-Path $dirPath) {
            Write-Step "Clearing plugin $staleDir directory before UAT copy..."
            & cmd /c "rmdir /S /Q `"$dirPath`"" 2>&1 | Out-Null
        }
    }
}

# ---------------------------------------------------------------------------
# 4. Temporarily disable UBA local execution
# ---------------------------------------------------------------------------
$UbtConfigDir = Join-Path $env:APPDATA "Unreal Engine\UnrealBuildTool"
$UbtConfigFile = Join-Path $UbtConfigDir "BuildConfiguration.xml"
$UbtConfigBackup = $UbtConfigFile + ".verify-compilation-backup"
$WroteUbtConfig = $false

if (-not (Test-Path $UbtConfigDir)) { New-Item -ItemType Directory -Path $UbtConfigDir -Force | Out-Null }

if (Test-Path $UbtConfigFile) {
    Copy-Item $UbtConfigFile $UbtConfigBackup -Force
}

$noUbaXml = @'
<?xml version="1.0" encoding="utf-8" ?>
<Configuration xmlns="https://www.unrealengine.com/BuildConfiguration">
  <BuildConfiguration>
    <bAllowUBAExecutor>false</bAllowUBAExecutor>
    <bAllowUBALocalExecutor>false</bAllowUBALocalExecutor>
    <bAllowUBALocalExecutor>false</bAllowUBALocalExecutor>
  </BuildConfiguration>
</Configuration>
'@
[IO.File]::WriteAllText($UbtConfigFile, $noUbaXml)
$WroteUbtConfig = $true

$env:UnrealBuildTool_BuildConfiguration__bAllowUBAExecutor = "false"

# Kill any lingering dotnet processes from previous crashed builds.
Get-CimInstance Win32_Process -Filter "Name = 'dotnet.exe'" -ErrorAction SilentlyContinue |
    Where-Object { $_.CommandLine -like "*UnrealBuildTool.dll*" } |
    ForEach-Object {
        Stop-Process -Id $_.ProcessId -Force -ErrorAction SilentlyContinue
    }

Write-Step "Note: Disabled UBA local executor to avoid UbaDetours/rc.exe crash (restored after build)."
Write-Step ""

# ---------------------------------------------------------------------------
# 5. Run RunUAT BuildPlugin
# ---------------------------------------------------------------------------
Write-Step "Running: RunUAT BuildPlugin (Win64, this may take a few minutes on a cold cache) ..."
Write-Step ""

$uatArgs = @(
    "BuildPlugin"
    "-Plugin=`"$($PluginFile.FullName)`""
    "-Package=`"$BuildOutput`""
    "-Rocket"
    "-TargetPlatforms=Win64"
    "-VS2022"
)

$prevEAP = $ErrorActionPreference
$ErrorActionPreference = 'Continue'

$uatOutput = [System.Collections.Generic.List[string]]::new()
$logStream = [System.IO.StreamWriter]::new($LogFile, $false, [System.Text.Encoding]::UTF8)
try {
    & $RunUAT @uatArgs 2>&1 | ForEach-Object {
        $line = "$_"
        $uatOutput.Add($line)
        $logStream.WriteLine($line)
        $logStream.Flush()
        Write-Host $line
    }
} finally {
    $logStream.Close()

    if ($WroteUbtConfig) {
        if (Test-Path $UbtConfigBackup) {
            Move-Item $UbtConfigBackup $UbtConfigFile -Force
        } else {
            Remove-Item $UbtConfigFile -Force -ErrorAction SilentlyContinue
        }
    }

    Remove-Item Env:\UnrealBuildTool_BuildConfiguration__bAllowUBAExecutor -ErrorAction SilentlyContinue
}
$script:uat_exit = $LASTEXITCODE

$ErrorActionPreference = $prevEAP

# ---------------------------------------------------------------------------
# 6. Report results
# ---------------------------------------------------------------------------
Write-Step ""
Write-Step "--- Compilation result ---"
Write-Step ""

$compilerErrors = $uatOutput | Select-String -Pattern "error C\d+|error LNK\d+|Error:|Deprecation:|Result: Failed" | Select-String -NotMatch "0 error\(s\)|not a preferred version"
if ($compilerErrors) {
    $compilerErrors | ForEach-Object { Write-Host $_.Line }
    Write-Step ""
}

Write-Step "----------------------------------"
Write-Step ""

if ($script:uat_exit -eq 0) {
    Write-Ok "COMPILATION SUCCEEDED"
}
else {
    $failureLine = $uatOutput | Select-String -Pattern "BUILD FAILED|Failed to build|ExitCode=\d+" | Select-Object -First 1
    $reason = if ($failureLine) { $failureLine.Line.Trim() } else { "exit code: $script:uat_exit" }
    Write-Fail "COMPILATION FAILED ($reason)"
    Write-Step "Full log: $LogFile"
    exit 1
}
