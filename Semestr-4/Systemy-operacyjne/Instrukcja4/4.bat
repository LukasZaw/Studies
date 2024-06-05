@echo off
for /F "tokens=1,* delims=:" %%a in ('chkdsk ^| find "uszkodzony"') do (
    echo Uszkodzony wolumin: %%b
)
pause
