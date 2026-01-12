@echo off
chcp 65001 >nul
echo ---------------------------------------------------
echo  Onigiri Development Server Start
echo ---------------------------------------------------

cd /d "%~dp0frontend"

:: Start server in a new window
echo Starting server...
start "Onigiri React Server" npm run dev -- --host 127.0.0.1

:: Wait for startup (5 seconds)
echo Waiting for startup...
timeout /t 5 /nobreak >nul

:: Open browser
echo Opening browser...
start http://127.0.0.1:5173/

echo.
echo Ready!
echo Server is running in a separate window.
echo Close that window to stop the server.
pause
