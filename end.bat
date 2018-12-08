@echo off
taskkill /f /t /im create-1.exe
taskkill /f /t /im create-2.exe
taskkill /f /t /im create-3.exe
taskkill /f /t /im create-4.exe
taskkill /f /t /im 1.exe
taskkill /f /t /im 2.exe
rd /s/q tmp
cd cpp
del/f/s/q *.exe
taskkill /f /t /im cmd.exe