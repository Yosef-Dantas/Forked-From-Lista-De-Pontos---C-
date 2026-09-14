@echo off
echo [INFO] Compilando projeto com OpenCV...
call "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars64.bat" > nul

cl.exe /Zi /EHsc /nologo /Fe:projeto.exe folders.cpp\*.cpp /I folders.h /I C:\vcpkg\installed\x64-windows\include /I C:\vcpkg\installed\x64-windows\include\opencv4 /link /LIBPATH:C:\vcpkg\installed\x64-windows\lib opencv_core4.lib opencv_imgproc4.lib opencv_highgui4.lib

if %errorlevel% equ 0 (
    echo [INFO] Sucesso!
)