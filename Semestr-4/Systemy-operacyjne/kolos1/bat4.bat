@echo off
echo Petla nr.1:
for /L %%i in (1, 1, 5) do echo %%i
echo Petla nr.2:
for %%i in (11 13 17 29) do echo %%i
echo Petla nr.3:
for /F "delims=%TAB%" %%i in ('dir C:\ /B') do echo %%i 