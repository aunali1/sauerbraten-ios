REM Process our images and textures and copy them into the bin directory

rmdir ..\bin\interface /S /Q

REM copy the stuff we care about

mkdir ..\bin\interface

xcopy interface ..\bin\interface /E /F /Y /EXCLUDE:exclude.txt

REM Convert everything to lowercase, otherwise the iphone will choke on the files
for /r %%f in (*.*) do ..\media\LowerCase.bat  %%f

pause
