@echo on
@rem copy ..\PyQt5\Qt5\bin\*.dll ..\
@rem copy ..\PyQt5\Qt5\bin\*.exe ..\
xcopy ..\static ..\..\static\ /S /E /Y
del ..\..\static\step1.bat
del ..\..\static\step1.sh
pause & exit
