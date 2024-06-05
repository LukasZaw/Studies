@ECHO off
date /t > net.txt
time /t >> net.txt
net statistics workstation | find "Bajty" >> net.txt
mkdir C:\tep 2> nul