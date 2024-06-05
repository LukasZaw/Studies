@echo off
echo Uzytkownik: %USERNAME%
echo Litera dysku: %USERPROFILE:~0,1%
echo Katalog macierzysty: %USERPROFILE%
echo Producent procesora: 
wmic cpu get manufacturer | findstr /v "Manufacturer"
pause