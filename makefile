all:
	g++ test1.cpp -g -std=c++11
	valgrind ./a.out
