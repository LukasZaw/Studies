@echo off
setlocal EnableDelayedExpansion
set encr=0
for /F %%i in ('cipher') do (
 if %%i EQU E (
 set /A encr=!encr!+1
 )
)
echo Zaszyfrowanych: %encr%
pause