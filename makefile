all:
	g++ test2.cpp -g -std=c++11
	./a.out
val:
	g++ test2.cpp -g -std=c++11
	valgrind ./a.out
t1:
	g++ test1.cpp -g -std=c++11 -Wall -Wextra -pedantic
	./a.out
valt1:
	g++ test1.cpp -g -std=c++11 -Wall -Wextra -pedantic
	valgrind ./a.out
