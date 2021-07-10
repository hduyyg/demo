@echo off
if "%1"=="" goto loop
copy fish2%1.in fish2.in >nul
echo Problem Test
echo Data %1
time <enter
fish2
time <enter
fc fish2.out fish2%1.out
del fish2.in
del fish2.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12) do call %0 %%i
:end
