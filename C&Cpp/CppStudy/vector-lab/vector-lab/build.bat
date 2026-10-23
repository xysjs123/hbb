@echo off
setlocal
cd /d "%~dp0"
set "CXX=g++"
where g++ >nul 2>nul
if errorlevel 1 (
    if exist "E:\Dev-Cpp\TDM-GCC-64\bin\g++.exe" (
        set "CXX=E:\Dev-Cpp\TDM-GCC-64\bin\g++.exe"
    ) else (
        echo Please install GCC or add g++ to PATH.
        exit /b 1
    )
)
"%CXX%" -std=c++11 -Wall -Wextra -pedantic -finput-charset=UTF-8 -fexec-charset=UTF-8 -static main.cpp StudentManager.cpp -o student_grades.exe
if errorlevel 1 exit /b 1
echo Build succeeded: student_grades.exe
