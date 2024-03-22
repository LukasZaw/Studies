@echo off

chkdsk /scan

for /f "tokens=1-3 delims=:" %%A in ('chkdsk /scan') do (

if "%%B"=="Uszkodzony" then (

echo Uszkodzony wolumin: %%A
echo Typ woluminu: %%C

)

)

echo Skanowanie uszkodzonych woluminów zostało zakończone.

pause