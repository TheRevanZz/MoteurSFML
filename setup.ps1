param(
    [ValidateSet("Debug","Release")]
    [string]$BuildType = "Debug",

    [string]$BuildPath = "build",
    [string]$CCompiler = "cc",
    [string]$CPPCompiler = "c++"
)

& "$PSScriptRoot\conan-setup.ps1"

mkdir $BuildPath -ErrorAction SilentlyContinue

cmake -S . -B $BuildPath -DCMAKE_TOOLCHAIN_FILE="out/build/conan-$($BuildType.ToLower())/conan_toolchain.cmake" -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER="$($CPPCompiler)" -DCMAKE_C_COMPILER="$($CCompiler)" -DCMAKE_BUILD_TYPE="$($BuildType)"

