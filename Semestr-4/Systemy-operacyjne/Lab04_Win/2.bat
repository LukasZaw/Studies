@echo off

set plik="moj_plik.txt"

set fso=CreateObject("Scripting.FileSystemObject")
set plikotw=fso.OpenTextFile(plik, 1)

set licznik=1

:loop
set wiersz=plikotw.ReadLine

if instr(wiersz, "aCzwartek") > 0 then

echo >> aczwartek.txt
echo **Wiersz %licznik%:** >> aczwartek.txt
echo %wiersz% >> aczwartek.txt

set /a licznik+=1

fi

goto loop

plikotw.Close

echo Plik aczwartek.txt został utworzony.

pause