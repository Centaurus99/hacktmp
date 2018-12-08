@echo off
set n=%1
:start
for /l %%i in (1,1,%n%) do (tasklist | find "create-%%i.exe"||call copy.bat %%i)
choice /t 1 /d y /n >nul
goto start