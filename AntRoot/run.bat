@echo off
set "ROOT_DIR=%~dp0"
set "CONFIG_DIR=%ROOT_DIR%configs"
set "CENTRAL_CONFIG=%ROOT_DIR%modelParameters.cfg"
set "INPUT_FILE=%ROOT_DIR%L-input\in.txt"
set "EXE_FILE=%ROOT_DIR%MravljiAlgoritam.exe"

echo Starting configuration processing...
echo.

for %%F in ("%CONFIG_DIR%\*") do (
	echo === Using config: %%~nxF ===
	
	copy /Y "%%F" "%CENTRAL_CONFIG%" >nul
	if errorlevel 1 (
		echo [ERROR] Failed to copy %%~nxF to modelParameters.cfg. Skipping this file.
		echo.
	) else (	
		echo Runnung MravljiAlgoritam.exe with input from in.txt 
		"%EXE_FILE%" < "%INPUT_FILE%"
		echo === Finished with "%%~nxF" ===
		echo.
	)
	
)

echo All configurations processed.
pause