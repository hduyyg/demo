@echo off
if "%1"=="" goto loop
copy godfather%1.in godfather.in >nul
echo Problem Test
echo Data %1
time<enter
godfather.exe
time<enter
fc godfather.out godfather%1.out
del godfather.in
del godfather.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
