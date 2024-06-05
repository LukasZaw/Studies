@echo off
set "ciag=%~1"
set "wyjscie=%~2"
findstr /C:%ciag% "plik.txt" > "%wyjscie%"
