all:
	g++ map3.cpp -g -std=c++11
	valgrind ./a.out
