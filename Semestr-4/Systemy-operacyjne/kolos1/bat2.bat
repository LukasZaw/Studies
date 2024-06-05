@echo off
set suma=0

:powrot
set /P liczba="Podaj liczbe: " 
if %liczba% equ 0 goto end
set /a suma+=liczba

goto powrot 

:end
echo suma: %suma%
pause