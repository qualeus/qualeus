#!/bin/sh
NUM_BUILD_THREADS=$(nproc --all)

pause()
{
  read -p "Press enter to continue"
}

build_debug()
{
  if [ ! -e "build/Debug/" ]; then mkdir -p "build/Debug/"; fi
  clear
  echo [7mCompiling for Debug...                                                           [$NUM_BUILD_THREADS threads][0m[32m
  cd build/Debug
  cmake -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . -j $NUM_BUILD_THREADS
  pause
  cd bin
  ./Qualeus
  if [ !$?==0 ]; then pause; fi
  cd ../../..
}

run_debug()
{
  cd build/Debug/bin
  ./Qualeus
  if [ !$?==0 ]; then pause; fi
  cd ../../..
}

build_release()
{
  if [ ! -e "build/Release/" ]; then mkdir -p "build/Release/"; fi
  clear
  echo [7mCompiling for Release...                                                         [$NUM_BUILD_THREADS threads][0m[32m
  cd build/Release
  cmake -DCMAKE_BUILD_TYPE=Release ../.. && cmake --build . -j $NUM_BUILD_THREADS
  pause
  cd bin
  ./Qualeus
  if [ !$?==0 ]; then pause; fi
  cd ../../..
}

run_release()
{
  cd build/Release/bin
  ./Qualeus
  if [ !$?==0 ]; then pause; fi
  cd ../../..
}

while true
do
  clear
  echo [7m ./Qualeus Build Tool [0m[32m
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

  read input

  case $input in
    0) build_debug ;;
    1) run_debug ;;
    2) build_release ;;
    3) run_release ;;
    4);;
    5);;
    6);;
    7);;
    8);;
    9) clear & exit /B 2 ;;
    *) read -p "invalid input"
  esac
done