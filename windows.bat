conan install --build=missing -s compiler="Visual Studio" -s compiler.version=15 -s "arch=x86" -s "arch_build=x86" .. && cmake .. -G "Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=Release