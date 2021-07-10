@echo off
if "%1"=="" goto loop
copy mis%1.in mis.in >nul
echo Problem Test
echo Data %1
time<enter
mis
time<enter
fc mis.out mis%1.out
del mis.in
del mis.out
pause
goto end
:loop
for %%i in (1 2 3 4) do call %0 %%i
:end
