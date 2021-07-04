# Compile + Link
gcc -O3 test1.c																\
../build/bench/bench.o														\
../build/mem/mem.o															\
-o ../bin/test1
# Run
cd ..
cd bin
./test1