@echo off

echo Nazwa użytkownika: %USERNAME%

echo Katalog macierzysty: %HOMEDRIVE%%HOMEPATH%

wmic baseboard get product,Manufacturer


pause