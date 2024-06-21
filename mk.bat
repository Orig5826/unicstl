@REM D:\Lang\cmake-3.27.5-windows-x86_64\bin\cmake.EXE --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=D:\Software\mingw64\bin\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=D:\Software\mingw64\bin\g++.exe -SF:/OpenDemo/1_vsc_cmake -Bf:/OpenDemo/1_vsc_cmake/build -G "MinGW Makefiles"
@REM cmake -Bbuild -G "Visual Studio 17 2022"

cmake -B build -G "MinGW Makefiles"

make -C build
make -C install 
