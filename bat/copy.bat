@echo off
set i=%1
set YYYYmmdd=%date:~0,4%%date:~5,2%%date:~8,2%
set hh_ten=%time:~0,1%
if "%hh_ten:~0,1%"==" " set hh_ten=0
set hh=%time:~1,1%
set miss=%time:~3,2%%time:~6,2%
cd ..
echo f|xcopy tmp\%i%\input OK\%YYYYmmdd%-%hh_ten%%hh%%miss%-%i%.in
echo f|xcopy tmp\%i%\*.log OK\%YYYYmmdd%-%hh_ten%%hh%%miss%-%i%.log
cd tmp\%i%
start create-%i%.exe
cd ..
cd ..
cd bat