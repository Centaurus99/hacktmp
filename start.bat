@echo off
:r
set/p n=进程数(1~4)
set ok=0
for /l %%i in (1,1,4) do if "%%i"=="%n%" set ok=1
if "%ok%"=="0" echo 输入错误
if "%ok%"=="0" goto r
"C:\Program Files\Dev-Cpp\MinGW64\bin\g++.exe" -o cpp\1.exe cpp\1.cpp -m32 -O2
"C:\Program Files\Dev-Cpp\MinGW64\bin\g++.exe" -o cpp\2.exe cpp\2.cpp -m32 -O2
"C:\Program Files\Dev-Cpp\MinGW64\bin\g++.exe" -o cpp\create.exe cpp\create.cpp -m32 -O2
@echo off
for /l %%i in (1,1,%n%) do (
xcopy/y cpp\1.exe tmp\%%i\
xcopy/y cpp\2.exe tmp\%%i\
copy/y cpp\create.exe tmp\%%i\create-%%i.exe
cd tmp\%%i
start create-%%i.exe
cd ..
cd ..
)
cd bat
call manager.bat %n%