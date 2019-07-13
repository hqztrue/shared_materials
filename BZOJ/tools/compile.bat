@echo off
echo start>error_file.txt
for %%x in (*.cpp) do (
	g++ "%%x"
	if errorlevel==1 echo "%%x">>error_file.txt&echo %%x
)
del *.exe
echo end
pause
