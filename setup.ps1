conan install . --build missing -s compiler.cppstd=20 --output-folder out\build\conan-toolchain
conan install . --build missing -s compiler.cppstd=20 --output-folder out\build\conan-toolchain -s build_type=Debug
mkdir build -ErrorAction SilentlyContinue
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="out/build/conan-toolchain/conan_toolchain.cmake"
cd ..
