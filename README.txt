Program not working correctly. It seems  to be a segfault issue in extractComponent() in PGMProcessor.cpp.

To compile the program, type "make".
"make clean" will clear the assignment folder of any .obj and .exe files.

Due to issues with my home PC, I have added some Compiler Flags to the makefile to ensure my program at least compiles.
Specifically "-static-libgcc -static-libstdc++". If not included, programs crash on my home PC whenever vectors are used.