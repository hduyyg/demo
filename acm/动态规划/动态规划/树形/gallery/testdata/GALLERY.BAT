@echo off
if "%1"=="" goto loop
copy gallery%1.in gallery.in >nul
echo Problem Test
echo Data %1
time<enter
gallery
time<enter
fc gallery.out gallery%1.out
del gallery.in
del gallery.out
pause
goto end
:loop
for %%i in (1 2 3 4) do call %0 %%i
:end
