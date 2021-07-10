@echo off
if "%1"=="" goto loop
copy shinkei%1.in shinkei.in >nul
echo Problem Test
echo Data %1
time<enter
shinkei
time<enter
fc shinkei.out shinkei%1.out
del shinkei.in
del shinkei.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
