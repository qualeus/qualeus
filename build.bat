@echo off
set /A NUM_BUILD_THREADS = %NUMBER_OF_PROCESSORS%
:menu
cls
color 0a
echo [7m Qualeus Build Tool [0m[32m
echo [0] Build/Run Debug 
echo [1] Run Debug 
echo [2] Build/Run Release
echo [3] Run Release
echo [4] Build Demos
echo [5] Build/Run Tests
echo [6] Build Docs
echo [7] Build WebAssembly
echo [8] Sonar Scanner
echo [9] Exit
set /p user=
if %user% == 0 goto build_debug
if %user% == 1 goto run_debug
if %user% == 2 goto build_release
if %user% == 3 goto run_release
if %user% == 4 goto build_demos
if %user% == 5 goto build_tests
if %user% == 6 goto build_docs
if %user% == 7 goto build_webassembly
if %user% == 8 goto sonar_scanner
if %user% == 9 cls & exit /B 2

:build_debug
if not exist "build/Debug/" mkdir "build/Debug/"
cls
echo [7mCompiling for Debug...                                                           [%NUM_BUILD_THREADS% threads][0m[32m
cd build\Debug
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . -j %NUM_BUILD_THREADS%
if errorlevel 1 pause && cd ..\.. && goto menu
pause
cd bin
Qualeus.exe
if errorlevel 1 pause
cd ..\..\..
goto menu

:run_debug
cd build\Debug\bin
Qualeus.exe
if errorlevel 1 pause
cd ..\..\..
goto menu

:build_release
if not exist "build/Release/" mkdir "build/Release/"
cls
echo [7mCompiling for Release...                                                           [%NUM_BUILD_THREADS% threads][0m[32m
cd build\Release
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ../.. && cmake --build . -j %NUM_BUILD_THREADS%
if errorlevel 1 pause && cd ..\.. && goto menu
cd bin
Qualeus.exe
if errorlevel 1 pause
cd ..\..\..
goto menu

:run_release
cd build\Release\bin
Qualeus.exe
if errorlevel 1 pause
cd ..\..\..
goto menu

:build_demos
goto menu

:build_tests
if not exist "build/Tests/" mkdir "build/Tests/"
cls
echo [7mCompiling Tests...                                                                  [%NUM_BUILD_THREADS% threads][0m[32m
cd build\Tests
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON  ../.. && cmake --build . -j %NUM_BUILD_THREADS%
mingw32-make CTEST_OUTPUT_ON_FAILURE=TRUE test
pause
cd ..\..
goto menu

:build_docs
if not exist "build/Docs/" mkdir "build/Docs/"
if not exist "docs/doxygen/" mkdir "docs/doxygen/"
cls
echo [7mBuilding Docs...                                                                   [%NUM_BUILD_THREADS% threads][0m[32m
cd build\Docs
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_DOCS=ON  ../.. && cmake --build . -j %NUM_BUILD_THREADS%
cd ..\..
pause
goto menu

:build_webassembly
if not exist "build/WebAssembly/" mkdir "build/WebAssembly/"
cls
echo [7mCompiling WebAssembly...                                                           [%NUM_BUILD_THREADS% threads][0m[32m
cd build\WebAssembly\
call conda activate
emcmake cmake -S . -B build ../.. && cmake --build build
call conda deactivate
cd ..\..
goto menu

:build_wrapper
if not exist "build/Debug/" mkdir "build/Debug/"
del /s /q "build/Debug/CMakeFiles"
rmdir /s /q "build/Debug/CMakeFiles"
cls
echo Compiling for Debug...
cd build\Debug
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ../.. 
build-wrapper --out-dir ../../bw-outputs cmake --build .
cd ..\..
goto menu

:sonar_scanner
sonar-scanner.bat \
  -D"sonar.organization=mlhoutel" \
  -D"sonar.projectKey=mlhoutel_Qualeus" \
  -D"sonar.sources=." \
  -D"sonar.cfamily.build-wrapper-output=bw-output" \
  -D"sonar.host.url=https://sonarcloud.io"
goto menu

:commit_push
cls
set /p message=Message du commit:
git add .
git commit -m "%message%"
git push
git pull
echo Done && pause >nul
goto menu
