setlocal
@echo off

SET CURR_DIR=%cd%
SET THIS_SCRIPT_PATH=%~dp0
cd %THIS_SCRIPT_PATH%

SET PATH=%PATH%;%THIS_SCRIPT_PATH%\..\build-tools

del /Q CMakeCache.txt
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=./bin -DWT_INSTALLED_DIR="C:/Program Files/Wt 3.3.7 msvs2015 x64" ..
cd %CURR_DIR%

endlocal