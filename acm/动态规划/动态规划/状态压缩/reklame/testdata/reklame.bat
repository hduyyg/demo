@echo off
if "%1"=="" goto loop
copy reklame%1.in reklame.in >nul
echo Problem Test
echo Data %1
time<enter
reklame
time<enter
fc reklame.out reklame%1.out
del reklame.in
del reklame.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
