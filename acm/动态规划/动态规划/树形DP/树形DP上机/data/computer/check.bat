@echo off
if "%1"=="" goto loop
copy computer%1.in computer.in >nul
echo Problem Test
echo Data %1
time<enter
computer.exe
time<enter
fc computer.out computer%1.out
del computer.in
del computer.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
