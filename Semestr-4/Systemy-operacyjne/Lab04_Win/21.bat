@echo off

if "%~2"=="" (
    echo Użycie: %0 "ciag_znakow" "wynik.txt"
    exit /b 1
)

set "search_string=%~1"
set "output_file=%~2"

findstr /c:"%search_string%" "plik.txt" > "%output_file%"

echo Zakończono wyszukiwanie. Wyniki zapisano do pliku %output_file%.

pause
exit /b 0