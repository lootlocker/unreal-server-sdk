<h1 align="center">LootLocker Unreal Server SDK</h1>

<h1 align="center">
  <a href="https://www.lootlocker.io/"><img src="https://s3.eu-west-1.amazonaws.com/cdn.lootlocker.io/public/lootlocker-github-bg.png" alt="LootLocker"></a>
</h1>

<p align="center">
  <a href="#about">About</a> •
  <a href="#Installation">Installation</a> •
  <a href="#configuration">Configuration</a> •
  <a href="#sample-app">Sample App</a> •
  <a href="#support">Support</a>
</p>

---

## About

LootLocker is a game backend-as-a-service that unlocks cross-platform systems so you can build, ship, and run your best games.

Full documentation is available [here](https://docs.lootlocker.com/)

## Installation

For a more detailed guide on installation, please see our [User Documentation](https://docs.lootlocker.com/getting-started/unreal-tutorials/getting-started-with-unreal)

1. Download the latest Unreal [Package release](https://github.com/LootLocker/unreal-server-sdk/releases) or clone the [repo](https://github.com/LootLocker/unreal-server-sdk/releases).
2. Copy the LootLockerServerSDK folder.
3. Paste the LootLockerServerSDK folder into the plugins folder created in the root of your project (create if it doesn't exist)
4. Right-click on the "Unreal Engine Project Launch" file in the root of your project and click on "Generate Visual Studio Project Files"
5. Open the .sln file of your project
6. Open your project's Build.cs file
7. Add `LootLockerServerSDK` to the PublicDependencyModuleNames list

    Example: 
    ```cpp
    PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "LootLockerServerSDK" });
    ```
8. Add `{"HTTP", "Json", "JsonUtilities"}` to the PrivateDependencyModuleNames list

    Example: 
    ```cpp
    PrivateDependencyModuleNames.AddRange(new string[] { "HTTP", "Json", "JsonUtilities" });
    ```

## Configuration

1. Navigate to Edit/Project Settings in the editor, Scroll down on the left panel until the plugins sections of the project settings, Click on LootLockerServerSDK
2. Modify the LootLockerServerKey, Domain Key, Game Version, and AllowTokenRefresh (Set to true if you want the LootLockerServerSDK to attempt to refresh the token if it expires). What values to set, you can find in the LootLocker dashboard. You should already have an account from [https://console.lootlocker.com/login](https://console.lootlocker.com/login "https://console.lootlocker.com/login")

## Support

If you have any issues or just wanna chat you can reach us on our [Discord Server](https://discord.lootlocker.io/)
