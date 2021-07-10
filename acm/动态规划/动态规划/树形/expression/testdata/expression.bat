@echo off
if "%1"=="" goto loop
copy expression%1.in expression.in >nul
echo Problem Test
echo Data %1
time<enter
expression.exe
time<enter
fc expression.out expression%1.out
del expression.in
del expression.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
