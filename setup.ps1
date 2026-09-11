param(
    [ValidateSet("Debug","Release")]
    [string]$B = "Debug"
)

Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force out -ErrorAction SilentlyContinue

conan install . -s compiler=gcc -s compiler.version=16.1 -s compiler.libcxx=libstdc++11 --build missing -s compiler.cppstd=20 --output-folder out\build\conan-release
conan install . -s compiler=gcc -s compiler.version=16.1 -s compiler.libcxx=libstdc++11 --build missing -s compiler.cppstd=20 --output-folder out\build\conan-debug -s build_type=Debug

mkdir build -ErrorAction SilentlyContinue

cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="out/build/conan-debug/conan_toolchain.cmake" -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=c++ -DCMAKE_C_COMPILER=cc -DCMAKE_BUILD_TYPE=Debug

