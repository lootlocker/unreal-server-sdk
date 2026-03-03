#!/usr/bin/env sh
set -eu

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

UE_ROOT="${UE_ROOT:-/home/ue4/UnrealEngine}"
RUN_UAT="$UE_ROOT/Engine/Build/BatchFiles/RunUAT.sh"

TARGET_PLATFORM="${TARGET_PLATFORM:-Linux}"
OUTPUT_DIR="${OUTPUT_DIR:-$REPO_ROOT/tmp/build}"
LOG_DIR="${LOG_DIR:-$REPO_ROOT/tmp/logs}"
LOG_PATH="$LOG_DIR/UAT-BuildPlugin.log"

UPLUGIN_PATH="$REPO_ROOT/LootLockerServerSDK/LootLockerServerSDK.uplugin"

if [ ! -f "$RUN_UAT" ]; then
  echo "RunUAT.sh not found at: $RUN_UAT" >&2
  echo "Set UE_ROOT to your Unreal Engine root (inside the container this is usually /home/ue4/UnrealEngine)." >&2
  exit 2
fi

if [ ! -f "$UPLUGIN_PATH" ]; then
  echo "Plugin descriptor not found at: $UPLUGIN_PATH" >&2
  exit 2
fi

mkdir -p "$OUTPUT_DIR" "$LOG_DIR"
rm -f "$LOG_PATH"

echo "Using Unreal Engine: $UE_ROOT"
echo "Building plugin: $UPLUGIN_PATH"
echo "Target platform: $TARGET_PLATFORM"
echo "Output directory: $OUTPUT_DIR"
echo "Log file: $LOG_PATH"

"$RUN_UAT" BuildPlugin \
  "-Plugin=$UPLUGIN_PATH" \
  "-Package=$OUTPUT_DIR" \
  "-TargetPlatforms=$TARGET_PLATFORM" \
  -Rocket \
  2>&1 | tee "$LOG_PATH"

# UAT prints the final ExitCode; keep this check consistent with other workflows.
if ! grep -i -q -E 'AutomationTool exiting with ExitCode=0' "$LOG_PATH"; then
  echo "BuildPlugin did not report success. Showing errors/warnings/exit code (if present):" >&2
  grep -i -E 'error' "$LOG_PATH" || true
  grep -i -E 'warning' "$LOG_PATH" || true
  grep -i -E 'ExitCode' "$LOG_PATH" || true
  exit 1
fi

echo "Compile verification succeeded."
