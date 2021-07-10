@echo off
if "%1"=="" goto loop
copy minsum%1.in minsum.in >nul
echo Problem Test
echo Data %1
time<enter
minsum.exe
time<enter
copy minsum%1.out minsum.ans >nul
fc minsum.out minsum.ans
del minsum.in
del minsum.out
del minsum.ans
pause
goto quit
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20) do call %0 %%i
:quit
