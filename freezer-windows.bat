@echo off
setlocal
set VCPKG_DIR=.vessel\externals\vcpkg
set TOOLCHAIN_FILE=%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake
set VCPKG_REPO=https://github.com/microsoft/vcpkg.git
set TRIPLET=x64-windows

echo Setting up vcpkg in %VCPKG_DIR%...

:: Step 1: Clone vcpkg if not already cloned
if not exist "%VCPKG_DIR%" (
    echo Cloning vcpkg...
    mkdir .vessel\externals
    git clone %VCPKG_REPO% %VCPKG_DIR%
) else (
    echo vcpkg already exists, skipping clone.
)

:: Step 2: Bootstrap vcpkg
echo Bootstrapping vcpkg...
call "%VCPKG_DIR%\bootstrap-vcpkg.bat"

:: Step 3: Install required dependencies
echo Installing dependencies...
call "%VCPKG_DIR%\vcpkg.exe" install --recurse sdl3 sdl3-image[png] sdl3-image sdl3-ttf sdl2-mixer lua glm imgui sol2 --triplet=%TRIPLET%

::Step 4: Install required dependencies
call "%VCPKG_DIR%\vcpkg.exe" list


@pause
endlocal
exit