@echo OFF
g++ index.cpp matrix.cpp -o index.exe
if %errorlevel% neq 0 exit /b %errorlevel%
index.exe