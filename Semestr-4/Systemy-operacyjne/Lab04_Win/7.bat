@echo off

set folder_zrodlo="C:\Users\Łukasz\Desktop\Systemy\test"

set folder_docelowy="C:\Users\Łukasz\Desktop\Systemy"

set rozszerzenie="*.txt"

xcopy "%folder_zrodlo%\%rozszerzenie%" "%folder_docelowy%"

echo Pliki zostały skopiowane.

pause