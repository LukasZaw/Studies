@echo off 
echo 1) Stworz nowy katalog
echo 2) Stworz nowy plik
echo 3) Usuń plik
Set /P wybor=Podaj numer operacji jaka chcesz wykonac: 

SETLOCAL EnableDelayedExpansion
if %wybor% == 1 (
    Set /P nazwa=Podaj nazwe katalogu jaki chcesz utworzyc: 
    mkdir !nazwa!
) else if %wybor%==2 (
    Set /P nazwa=Podaj nazwe pliku jaki chcesz utworzyc:
    type nul > !nazwa!
) else if %wybor%==3 (
    Set /P nazwa=Podaj nazwe pliku jaki chcesz usunac: 
    del !nazwa!
) else (    
    echo Podano zly parametr 
)
SETLOCAL DisableDelayedExpansion
dir