@echo off
echo ******** TEST %1 *******
cmake-build-debug\lab_09.exe < in_%1.txt > out_%1.txt
echo Input:
for /f "usebackq tokens=*" %%a in ("in_%1.txt") do (echo %%~a)
echo Output:
for /f "usebackq tokens=*" %%a in ("out_%1.txt") do (echo %%~a)
fc out.txt out_%1.txt
pause