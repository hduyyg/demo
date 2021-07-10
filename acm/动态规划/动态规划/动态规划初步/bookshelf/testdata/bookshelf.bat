@echo off
if "%1"=="" goto loop
copy bookshelf%1.in bookshelf.in >nul
echo Problem Test
echo Data %1
time<enter
bookshelf
time<enter
fc bookshelf.out bookshelf%1.out
del bookshelf.in
del bookshelf.out
pause
goto end
:loop
for %%i in (1 2 3 4 5) do call %0 %%i
:end
