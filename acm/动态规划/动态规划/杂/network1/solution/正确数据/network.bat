@echo off
if "%1"=="" goto loop
copy network%1.in network.in >nul
echo Problem Test
echo Data %1
time<enter
network
time<enter
fc network.out network%1.out
del network.in
del network.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
