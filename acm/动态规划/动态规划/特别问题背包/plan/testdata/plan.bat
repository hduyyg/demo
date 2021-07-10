@echo off
if "%1"=="" goto loop
copy plan%1.in plan.in >nul
echo Problem Test
echo Data %1
time<enter
plan.exe
time<enter
fc plan.out plan%1.out
del plan.in
del plan.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
