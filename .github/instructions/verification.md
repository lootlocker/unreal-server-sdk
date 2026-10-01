# Verification (Unreal Server SDK)

This repository is an **Unreal Engine plugin**. The fastest, most deterministic compile verification is to run Unreal Automation Tool (UAT) `BuildPlugin`.

This doc describes the two supported verification paths:
- **Local (Windows):** for contributors using the repo on a workstation.
- **CI (GitHub Actions):** for cloud verification and GH Coding Agent.

## A) Local compile verification (Windows)

### Prerequisites
- Unreal Engine installed locally (e.g. UE 5.5)
- Visual Studio / MSVC toolchain that matches your UE install

### Command

From repo root:

```powershell
# Run UAT BuildPlugin for Win64 (full clean build)
.\github\scripts\verify-compilation.ps1 -Clean

# Incremental build (skip clean)
.\github\scripts\verify-compilation.ps1
```

### Configuring your local Unreal Engine path

Create a repo-local, gitignored file in repo root: `unreal-dev-settings.json`

```json
{ "unreal_engine_path": "C:\\Program Files\\Epic Games\\UE_5.5" }
```

`.github\scripts\verify-compilation.ps1` reads this file automatically.

### Outputs
- Build output: `Build~\PluginBuild\`
- Log file: `Build~\UAT.log`

## B) CI compile verification (GitHub Actions)

The lightweight workflow runs the same check in a single Unreal Engine container image:
- Workflow: `.github/workflows/verify-compile.yml`
- Script invoked inside the container: `scripts/verify-compile.sh`

### Default behavior
- Uses `vars.AGENT_CHECK_UE_IMAGE`.
- If not set, defaults to `dev-5.5`.
- Runs `RunUAT.sh BuildPlugin` for `Linux`.
- Uploads the UAT log as an artifact.

### Manual runs
You can override the UE image tag via the workflow dispatch input `ueImage`.

## What "compile verified" means here

A change is considered compile-verified when:
- Local: `scripts/verify-compile.ps1` exits with code `0`.
- CI: the `Verify compile (quick)` workflow job succeeds.

This check is intentionally narrower than the full matrix builds (it is meant to be a fast per-commit gate). For broad version coverage, use the existing matrix workflow.

## C) Running the automation tests locally (Windows)

Backend-dependent tests provision their own isolated game through the admin API, so they need
admin credentials for the LootLocker backend. Offline tests (`Config.SaveConfig`,
`Config.FileConfig`) run without any credentials.

```powershell
# All LootLockerServer tests
.\scripts\run-tests.ps1

# A single test or suite
.\scripts\run-tests.ps1 -TestFilter "LootLockerServer.Player"

# Reuse the binaries from the previous run (much faster when only test code changed)
.\scripts\run-tests.ps1 -NoBuild

# Force a full rebuild
.\scripts\run-tests.ps1 -Clean
```

The script exits `0` only when every selected test passed.

### Admin credentials

The first run of the day signs up a throwaway account, so by default no configuration is needed.
To reuse an existing (verified) account instead, set these environment variables:

```powershell
$env:LOOTLOCKER_ADMIN_EMAIL    = "ci-testrun@example.com"
$env:LOOTLOCKER_ADMIN_PASSWORD = "..."
```

If they are set, the harness never attempts a signup — a login failure is reported as-is. This is
what CI uses.

### Running against a local backend (devenv)

To run the tests against a locally running `devenv` + `go-backend` stack instead of production:

```powershell
$env:LOOTLOCKER_USE_LOCAL_DEVENV = "1"
.\scripts\run-tests.ps1
```

This switches the SDK's base URL and the admin API URL to `http://localhost:8080/`. It is a
**build-time** flag — the define is baked into the binaries, so a rebuild is required after
changing it. See the repository README for how to start the local stack.

> **Known limitation:** in a local devenv setup the php-backend-backed endpoints
> (`GET /server/ping` and `/server/players/storage`) reject the session token that go-backend
> minted, because php-backend binds the token to a client IP that no longer matches once the
> request passes through the proxy. Two tests (`When Start/End server session` and
> `When Server PersistentStorage`) therefore fail locally. They pass in CI, which runs against the
> real backend. This is tracked as a devenv limitation, not a test suite defect.

### Troubleshooting

- **`unreal-dev-settings.json` not found** — create it as described in section A.
- **Build fails with `UbaDetours`/`rc.exe` errors** — the script already disables the UBA
  executors; make sure nothing else rewrote
  `%APPDATA%\Unreal Engine\UnrealBuildTool\BuildConfiguration.xml` mid-run.
- **`LootLockerServerLeaderboardArchiveRequestHandler.cpp` fails to compile** — this is a Windows
  MAX_PATH issue. Build output must go to a short path; the script uses
  `%TEMP%\LLServerSdkTestBuild` for exactly this reason. Do not redirect it under a deep worktree.
- **`user is not verified` when creating a game** — the admin account has not been verified. Use a
  different account, or set `LOOTLOCKER_ADMIN_EMAIL`/`LOOTLOCKER_ADMIN_PASSWORD` to a verified one.
