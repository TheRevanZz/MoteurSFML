Remove-Item -Recurse -Force out -ErrorAction SilentlyContinue

Remove-Item -Recurse -Force -Path build -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force -Path out -ErrorAction SilentlyContinue

conan install . -s compiler=gcc -s compiler.version=16.1 -s compiler.libcxx=libstdc++11 --build missing -s compiler.cppstd=20 --output-folder out\build\conan-release
conan install . -s compiler=gcc -s compiler.version=16.1 -s compiler.libcxx=libstdc++11 --build missing -s compiler.cppstd=20 --output-folder out\build\conan-debug -s build_type=Debug