#include <iostream>
#include <stdlib.h>
#include "Map.hpp"

using namespace std;
int main(){
	Map_T<int, int>map;
//	assert(map.size == 0);
	map.insert(std::make_pair(10, 10));
	map.insert(std::make_pair(20, 20));
//	assert(map.root->right->data.first == 20);
return 0;
}
