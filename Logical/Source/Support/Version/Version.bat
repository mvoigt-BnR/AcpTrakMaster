@echo off
FOR /F "tokens=* USEBACKQ" %%F IN (`%USERPROFILE%\AppData\Local\Atlassian\SourceTree\git_local\bin\git.exe -C %~dp0 describe --always`) DO (
SET VERSION=%%F
)
FOR /F "tokens=* USEBACKQ" %%F IN (`%USERPROFILE%\AppData\Local\Atlassian\SourceTree\git_local\bin\git.exe -C %~dp0 show -s --pretty^=format:%%cn`) DO (
SET AUTHOR=%%F
)
FOR /F "tokens=* USEBACKQ" %%F IN (`%USERPROFILE%\AppData\Local\Atlassian\SourceTree\git_local\bin\git.exe -C %~dp0 show -s --date^=format:"%%d %%B, %%Y" --pretty^=format:"%%cd"`) DO (
SET COMMITDATE=%%F
)
echo PROGRAM _CYCLIC> %~dp0Version\Version.st
echo Version := '%VERSION%';>> %~dp0Version\Version.st
echo Author := '%AUTHOR%';>> %~dp0Version\Version.st
echo Date := '%COMMITDATE%';>> %~dp0Version\Version.st
echo END_PROGRAM>> %~dp0Version\Version.st
