@REM set abi=armeabi-v7a
set abi=arm64-v8a
set ANDROID_SDK_HOME=C:/Users/000/AppData/Local/Android/Sdk

if not exist %abi% md %abi%
cd %abi%

%ANDROID_SDK_HOME%/cmake/3.10.2.4988404/bin/cmake ^
  -DANDROID_ABI=%abi% ^
  -DANDROID_NDK=%ANDROID_SDK_HOME%/ndk-bundle ^
  -DCMAKE_BUILD_TYPE=Debug ^
@REM  -DCMAKE_BUILD_TYPE=Release^
  -DCMAKE_TOOLCHAIN_FILE=%ANDROID_SDK_HOME%/ndk-bundle/build/cmake/android.toolchain.cmake ^
  -DANDROID_NATIVE_API_LEVEL=9 ^
  -DANDROID_TOOLCHAIN=clang -DCMAKE_GENERATOR="Ninja" ^
  -DCMAKE_MAKE_PROGRAM=%ANDROID_SDK_HOME%/cmake/3.10.2.4988404/bin/ninja ^
  ..

%ANDROID_SDK_HOME%/cmake/3.10.2.4988404/bin/ninja

cd ..
