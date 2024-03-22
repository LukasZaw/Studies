@echo off

if exist "%SystemRoot%\SysWOW64\drivers\etc\services" (
  echo Typ systemu: Serwer
) else (
  echo Typ systemu: Stacja robocza
)

net view

net user

systeminfo

pause
