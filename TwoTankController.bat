@echo off
SET PATH=;C:/Program Files/OpenModelica1.27.1-64bit/bin/;%PATH%;
SET ERRORLEVEL=
CALL "%CD%/TwoTankController.exe" %*
SET RESULT=%ERRORLEVEL%

EXIT /b %RESULT%
