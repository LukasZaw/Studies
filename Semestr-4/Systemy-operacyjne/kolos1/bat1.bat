@echo off
set /P katalog="Podaj nazwe katalogu: " 


if exist %katalog% (
 echo Instanieje zmiena nazwy na .old
 rename %katalog% %katalog%.old
 mkdir %katalog%
) else (
 echo nie Instanieje
) 
pause