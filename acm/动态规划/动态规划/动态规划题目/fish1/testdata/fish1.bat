@echo off
if "%1"=="" goto loop
copy fish1%1.in fish1.in >nul
echo Problem Test
echo Data %1
time<enter
fish1.exe
time<enter
fc fish1.out fish1%1.out
del fish1.in
del fish1.out
pause
goto end
:loop
for %%i in (8 9 0 ) do call %0 %%i
:end
