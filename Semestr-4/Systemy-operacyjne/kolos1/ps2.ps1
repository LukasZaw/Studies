
try{ [int32]$s = Read-Host -Prompt "Podaj numer pory roku którą chcesz wybrać:"}
catch{ Write-Host "Wprowadzono nieprawidłowe dane"}

Switch ($s){
    1 {Write-Host "Do wiosny należą: marzec,kwiecień,maj"}
    2 {Write-Host "Do lata należą: czerwiec,lipiec,sierpień"}
    3 {Write-Host "Do jesieni należą: wrzesień,październik,listopad"}
    4 {Write-Host "Do zimy należą: grudzień,styczeń,luty"}
    default{ Write-Host "Podany numer nie odpowiada żadnej pory roku"}}