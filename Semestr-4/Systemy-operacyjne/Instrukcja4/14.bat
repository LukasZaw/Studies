@echo off
echo Informacje o serwerze:
systeminfo | findstr /C:"Nazwa komputera:" /C:"Producent:" /C:"Model:" /C:"System operacyjny:"
echo.
echo Informacje o stacji roboczej:
systeminfo | findstr /C:"Nazwa komputera:" /C:"Producent:" /C:"Model:" /C:"System operacyjny:"
echo.
echo Grupy:
net user %USERNAME% | findstr /C:"Local Group Memberships"
pause