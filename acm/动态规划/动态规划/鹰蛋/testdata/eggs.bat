@echo off
if "%1"=="" goto loop
copy eggs%1.in eggs.in >nul
echo Problem Test
echo Data %1
time<enter
eggs
time<enter
fc eggs.out eggs%1.out
del eggs.in
del eggs.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
