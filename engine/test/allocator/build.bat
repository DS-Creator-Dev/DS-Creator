:: requires g++ in PATH (normal windows compiler)

i686-w64-mingw32-g++ -fpermissive -o main.exe^
 -I../../include/DSCEngine/video^
 -I../../include^
 -I../../source/DSCEngine/video/^
 main.cpp ../../source/DSCEngine/video/allocator.cpp ../../source/DSCEngine/video/allocs_table.cpp -std=c++17