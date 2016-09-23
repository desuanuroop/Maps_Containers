#include <iostream>
#include <stdlib.h>
#include "Map.hpp"

using namespace std;
int main(){
	Map_T<int, int>map;
	map.insert(make_pair(10, 10));
	map.insert(make_pair(20, 20));
	map.insert(make_pair(30, 30));
	map.insert(make_pair(40, 40));
	assert(map.size == 4);
return 0;
}
