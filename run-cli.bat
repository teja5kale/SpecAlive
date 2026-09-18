@echo off
REM ============================================================
REM  SpecAlive - one-click CLI run
REM  Double-click to run the full spec->model->sim->validate->refine
REM  loop and write SysML v2 / Modelica / JSON / diagram to .\out\
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

REM --- ensure deps (pydantic + numpy) are installed ---
python -c "import pydantic, numpy" >nul 2>&1
if errorlevel 1 (
    echo [setup] Installing dependencies, one moment...
    python -m pip install -r requirements.txt
    if errorlevel 1 (
        echo [ERROR] Dependency install failed. See messages above.
        pause
        exit /b 1
    )
)

REM --- run the loop (default Enrich spec). Pass a spec path as an argument
REM     by dragging a .txt onto this .bat, or edit the line below. ---
echo.
echo ============================================================
echo   Running SpecAlive loop...  (artifacts will land in .\out\)
echo ============================================================
echo.

REM %* passes through any args: a spec path (or drag a .txt onto this file),
REM and/or --correct to size strings cold-Voc-aware from the start.
python cli.py %*

echo.
echo ============================================================
echo   Done. Generated files in:  %~dp0out
echo ============================================================
echo.
pause
