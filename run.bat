@echo off
REM ============================================================
REM  SpecAlive - one-click launcher for the Streamlit UI
REM  Double-click this file to start the app.
REM ============================================================
setlocal
cd /d "%~dp0"

REM --- check Python ---
where python >nul 2>&1
if errorlevel 1 (
    echo [ERROR] Python was not found on PATH.
    echo Install Python 3.11+ from https://python.org and try again.
    echo.
    pause
    exit /b 1
)

REM --- ensure Streamlit ^& deps are installed ---
python -c "import streamlit" >nul 2>&1
if errorlevel 1 (
    echo [setup] Installing dependencies, one moment...
    python -m pip install -r requirements.txt
    if errorlevel 1 (
        echo [ERROR] Dependency install failed. See messages above.
        pause
        exit /b 1
    )
)

echo.
echo ============================================================
echo   Launching SpecAlive UI  ->  http://localhost:8501
echo   (a browser tab will open automatically)
echo   Press Ctrl+C in this window to stop the app.
echo ============================================================
echo.

python -m streamlit run app.py --server.port 8501

echo.
echo SpecAlive stopped.
pause
