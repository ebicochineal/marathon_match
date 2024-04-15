PATH=%path%;C:/mingw-w64/x86_64-6.2.0-posix-seh-rt_v5-rev1/mingw64/bin
g++ -O3 -std=c++1z -static-libstdc++ -static -lstdc++ -mwindows ./vis.cpp -o ./vis.exe
SET /P INPUTSTR="exit"