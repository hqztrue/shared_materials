@echo off
echo start>file.txt
for %%x in (*) do (
	echo %%x>>file.txt
)
::pause
