# Move-EnumDocComments.ps1
# Moves /** */ doc comment blocks from BEFORE UENUM(...) to BETWEEN UENUM(...) and enum class.
# This is necessary because UENUM(...) expands to blank via PREDEFINED, creating a blank line
# between the doc comment and the enum class, causing Doxygen to disassociate them.

param([switch]$DryRun)

$enc = New-Object System.Text.UTF8Encoding($false)
$base = "LootLockerSDK/Source/LootLockerSDK/Public/GameAPI"
$totalMoved = 0

foreach ($f in (Get-ChildItem $base -Filter "*.h")) {
    $lines = [System.Collections.Generic.List[string]]::new(
        [IO.File]::ReadAllLines($f.FullName, $enc)
    )
    $fileMoved = 0

    # Walk from bottom to top so line-index removals don't shift upcoming targets
    $i = $lines.Count - 1
    while ($i -ge 0) {
        # Step 1: find "enum class E..."
        if ($lines[$i] -notmatch '^\s*enum\s+class\s+E\w+') { $i--; continue }

        # Step 2: find the UENUM line immediately above
        $ue = $i - 1
        while ($ue -ge 0 -and $lines[$ue] -match '^\s*$') { $ue-- }
        if ($ue -lt 0 -or $lines[$ue] -notmatch '^\s*UENUM\s*\(') { $i--; continue }

        # Step 3: find doc comment ending just above UENUM (skip blank lines)
        $commentEnd = $ue - 1
        while ($commentEnd -ge 0 -and $lines[$commentEnd] -match '^\s*$') { $commentEnd-- }
        if ($commentEnd -lt 0 -or $lines[$commentEnd] -notmatch '\*/\s*$') { $i--; continue }

        # Step 4: walk back to find the opening /** of the comment block
        $commentStart = $commentEnd
        while ($commentStart -ge 0 -and $lines[$commentStart] -notmatch '/\*\*') { $commentStart-- }
        if ($commentStart -lt 0) { $i--; continue }

        # We have: commentStart..commentEnd = doc block
        # Lines commentEnd+1 .. ue-1 = blank lines between comment and UENUM
        # Line ue = UENUM(...)
        # Line i = enum class E...

        $docBlock = @($lines[$commentStart..$commentEnd])

        if ($DryRun) {
            Write-Host "[DRY RUN] $($f.Name) line $($i+1): would move doc block ($($docBlock.Count) line(s)) from before UENUM to after UENUM"
            $fileMoved++
            $i = $commentStart - 1
            continue
        }

        # Remove: everything from commentStart up to (but not including) the UENUM line
        $removeCount = $ue - $commentStart   # note: includes blank lines between comment and UENUM
        for ($r = 0; $r -lt $removeCount; $r++) {
            $lines.RemoveAt($commentStart)
        }
        # After removal, the UENUM line is now at $commentStart.
        # The enum class line is at $commentStart + ($i - $ue) = $commentStart + ($i - $ue)
        # But since we removed $removeCount lines starting at $commentStart,
        # and $ue = $commentStart + $removeCount (before removal), UENUM is now at $commentStart.
        # enum class was at $i = $ue + (something), now at $i - $removeCount.

        $newUe = $commentStart  # UENUM line after removal
        $newI  = $i - $removeCount  # enum class line after removal

        # Insert doc block between UENUM (newUe) and enum class (newI)
        # That means insert at index newUe + 1 (right after UENUM)
        $insertAt = $newUe + 1
        for ($d = $docBlock.Count - 1; $d -ge 0; $d--) {
            $lines.Insert($insertAt, $docBlock[$d])
        }

        $fileMoved++
        $totalMoved++

        # Jump back past what we just processed (above the comment block now moved)
        $i = $newUe - 1
    }

    if ($fileMoved -gt 0 -and -not $DryRun) {
        [IO.File]::WriteAllBytes(
            $f.FullName,
            $enc.GetBytes(($lines -join "`n") + "`n")
        )
        Write-Host "$($f.Name): moved $fileMoved doc comment(s)"
    } elseif ($fileMoved -eq 0) {
        Write-Verbose "$($f.Name): nothing to move"
    }
}

$dryMsg = if ($DryRun) { " (dry run)" } else { "" }
Write-Host ""
Write-Host "Done$dryMsg. Moved $totalMoved enum doc comment(s) to between UENUM and enum class."
