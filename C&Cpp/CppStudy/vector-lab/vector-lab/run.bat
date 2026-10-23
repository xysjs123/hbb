@echo off
setlocal
cd /d "%~dp0"
chcp 65001 >nul
if not exist student_grades.exe (
    call build.bat
    if errorlevel 1 (
        pause
        exit /b 1
    )
)
student_grades.exe
pause
