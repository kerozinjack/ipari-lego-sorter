$folderPath = ".\BASE"
$outputFile = "output.txt"

$files = Get-ChildItem $folderPath | Where-Object {!$_.PSIsContainer}

$formattedFileNames = @()

$files | ForEach-Object {
    $formattedFileName = "BASE\$($_.Name)"
    $formattedFileNames += $formattedFileName
}

$formattedFileNames | Out-File $outputFile -Encoding UTF8