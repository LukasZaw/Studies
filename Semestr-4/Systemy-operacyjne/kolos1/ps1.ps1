"Styczeń`nLuty`nMarzec`nKwiecień`nMaj`nCzerwiec`nLipiec`nSierpień`nWrzesień`nPaździernik`nListopad`nGrudzień" > Miesiące.txt
Write-Host "Exercise1"
type Miesiące.txt

[string]$variable = Get-Content -Path Miesiące.txt
$variable

$variable.Substring($variable.IndexOf("Luty"), 4) | Out-File "Miesiąc roku przestępnego.txt"
type .\"Miesiąc roku przestępnego.txt"

