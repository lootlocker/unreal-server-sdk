import re

filepath = r'LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerForCpp.h'

with open(filepath, encoding='utf-8') as f:
    content = f.read()

sections = [
    ("Authentication",            "Authentication"),
    ("Token Exchange",            "TokenExchange"),
    ("Leaderboards",              "Leaderboard"),
    ("Leaderboard Archives",      "Leaderboard"),
    ("Triggers",                  "Triggers"),
    ("Player Persistent Storage", "PlayerStorage"),
    ("Characters",                "Characters"),
    ("Heroes",                    "Hero"),
    ("Player Inventory",          "AssetInstance"),
    ("Assets",                    "Assets"),
    ("Asset Instances",           "AssetInstance"),
    ("Drop Tables",               "DropTables"),
    ("Friends",                   "Friends"),
    ("Connected Accounts",        "ConnectedAccounts"),
    ("Player",                    "Player"),
    ("Player Files",              "PlayerFiles"),
    ("Game Progressions",         "Progressions"),
    ("Player Progressions",       "PlayerProgressions"),
    ("Character Progressions",    "CharacterProgressions"),
    ("Instance Progressions",     "AssetInstanceProgressions"),
    ("Currencies",                "Currency"),
    ("Balances",                  "Balances"),
    ("Metadata",                  "Metadata"),
    ("Notifications",             "Notifications"),
]

divider = "    //=================================================="

def make_header(name):
    return f"{divider}\n    // {name}\n{divider}"

for i, (name, group) in enumerate(sections):
    header = make_header(name)
    if header not in content:
        print(f"WARNING: could not find section '{name}'")
        continue
    if i == 0:
        replacement = f"{header}\n    /// @addtogroup {group}\n    /// @{{"
    else:
        replacement = f"    /// @}}\n\n{header}\n    /// @addtogroup {group}\n    /// @{{"
    content = content.replace(header, replacement, 1)

# Close the last group before the final };
content = content.rstrip('\n').rstrip('}').rstrip(';').rstrip()
content = content + "\n    /// @}\n};\n"

with open(filepath, 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)

print("Done")
