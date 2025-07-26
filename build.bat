@echo off
echo Building C++ REST API...

REM Create build directories
if not exist "build\obj" mkdir build\obj
if not exist "build\bin" mkdir build\bin

REM Check for Visual Studio compiler
where cl >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Using Visual Studio compiler...
    cl /std:c++17 /EHsc /I external /I src src\main.cpp /Fe:build\bin\CppRestAPI.exe /link ws2_32.lib wsock32.lib
    goto :end
)

REM Check for MinGW/GCC
where g++ >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Using MinGW/GCC compiler...
    g++ -std=c++17 -Wall -Wextra -O2 -I external -I src src\main.cpp -o build\bin\CppRestAPI.exe -lws2_32 -lwsock32
    goto :end
)

REM Check for Clang
where clang++ >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Using Clang compiler...
    clang++ -std=c++17 -Wall -Wextra -O2 -I external -I src src\main.cpp -o build\bin\CppRestAPI.exe -lws2_32 -lwsock32
    goto :end
)

echo ERROR: No suitable C++ compiler found!
echo Please install one of the following:
echo - Visual Studio Build Tools (cl)
echo - MinGW-w64 (g++)
echo - LLVM/Clang (clang++)
exit /b 1

:end
echo Build completed successfully!
echo Run the application with: build\bin\CppRestAPI.exe