[CmdletBinding()]
param(
    [Parameter(Mandatory = $false)]
    [string]$UnrealEnginePath,

    [Parameter(Mandatory = $false)]
    [ValidateSet('Win64')]
    [string]$TargetPlatform = 'Win64',

    [Parameter(Mandatory = $false)]
    [string]$OutputDir,

    [Parameter(Mandatory = $false)]
    [string]$LogDir
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Resolve-RepoRoot {
    $repoRoot = Resolve-Path (Join-Path $PSScriptRoot '..')
    return $repoRoot.Path
}

$repoRoot = Resolve-RepoRoot
Set-Location $repoRoot

if ([string]::IsNullOrWhiteSpace($OutputDir)) {
    $OutputDir = Join-Path $repoRoot 'tmp\build'
}

if ([string]::IsNullOrWhiteSpace($LogDir)) {
    $LogDir = Join-Path $repoRoot 'tmp\logs'
}

function Get-UnrealEnginePathFromDevSettings {
    param(
        [Parameter(Mandatory = $true)]
        [string]$RepoRoot
    )

    $settingsPath = Join-Path $RepoRoot 'unreal-dev-settings.json'
    if (-not (Test-Path $settingsPath)) {
        return $null
    }

    try {
        $settings = Get-Content -Raw -Path $settingsPath | ConvertFrom-Json
    } catch {
        throw 'Failed to parse unreal-dev-settings.json. Expected JSON like: { "unreal_engine_path": "C:\Program Files\Epic Games\UE_5.5" }'
    }

    if ($null -eq $settings -or [string]::IsNullOrWhiteSpace($settings.unreal_engine_path)) {
        throw 'unreal-dev-settings.json is missing required field "unreal_engine_path".'
    }

    return [string]$settings.unreal_engine_path
}

if ([string]::IsNullOrWhiteSpace($UnrealEnginePath)) {
    $UnrealEnginePath = Get-UnrealEnginePathFromDevSettings -RepoRoot $repoRoot
}

if ([string]::IsNullOrWhiteSpace($UnrealEnginePath)) {
    $UnrealEnginePath = 'C:\Program Files\Epic Games\UE_5.5'
}

$unrealEnginePathResolved = Resolve-Path -Path $UnrealEnginePath -ErrorAction Stop
$runUatBat = Join-Path $unrealEnginePathResolved.Path 'Engine\Build\BatchFiles\RunUAT.bat'

if (-not (Test-Path $runUatBat)) {
    throw "RunUAT.bat not found at: $runUatBat. Provide -UnrealEnginePath or create unreal-dev-settings.json."
}

$uplugin = Join-Path $repoRoot 'LootLockerServerSDK\LootLockerServerSDK.uplugin'
if (-not (Test-Path $uplugin)) {
    throw "Plugin descriptor not found at: $uplugin"
}

if (Test-Path $OutputDir) {
    try {
        Remove-Item -Recurse -Force -Path $OutputDir
    } catch {
        throw "Failed to clean output directory: $OutputDir. Close any Unreal/VS processes that might have files locked and try again."
    }
}

New-Item -ItemType Directory -Force -Path $OutputDir | Out-Null
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null

$logPath = Join-Path $LogDir 'UAT-BuildPlugin.log'
if (Test-Path $logPath) {
    Remove-Item -Force $logPath
}

Write-Host "Using Unreal Engine: $($unrealEnginePathResolved.Path)"
Write-Host "Building plugin: $uplugin"
Write-Host "Target platform: $TargetPlatform"
Write-Host "Output directory: $OutputDir"
Write-Host "Log file: $logPath"

& $runUatBat BuildPlugin `
    "-Plugin=$uplugin" `
    "-Package=$OutputDir" `
    "-TargetPlatforms=$TargetPlatform" `
    -Rocket 2>&1 | Tee-Object -FilePath $logPath

if ($LASTEXITCODE -ne 0) {
    Write-Error "BuildPlugin failed with exit code $LASTEXITCODE. See log: $logPath"
    exit $LASTEXITCODE
}

Write-Host 'Compile verification succeeded.'
