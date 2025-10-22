@echo off
echo Building xv6 Networking Stack...
echo.

echo Compiling kernel modules...
gcc -Wall -Wextra -std=c99 -O2 -g -c kernel/*.c
if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo Linking test program...
gcc -Wall -Wextra -std=c99 -O2 -g -I. test_networking.c kernel/*.o -o test_networking.exe
if %errorlevel% neq 0 (
    echo Linking failed!
    pause
    exit /b 1
)

echo.
echo Build successful! Running tests...
echo.
test_networking.exe

echo.
echo Build complete!
pause
