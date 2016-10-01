#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
#include "Map.hpp"

using namespace std;
void original();
int main(int argc, char *argv[]){
	if (argc ==2){
		original();
	}
	else{
		Map_T<int, int> map;
		map.insert(make_pair(10, 10));
		map.insert(make_pair(20, 20));
		map.insert(make_pair(30, 30));
		map.insert(make_pair(40, 40));
		map.insert(make_pair(50, 50));
		auto it = map.end();
		assert(it.first == 0);
		it = map.begin();
		assert(it.first == 10);
		it = map.rbegin();
		assert(it.first == 50);
		it = map.rend();
		assert(it.first == 0);
		map.insert(make_pair(60, 60));
		bool thrown = false;
/*		try {
			map.at(100) = 100;
			assert(map.root->left->left->data.second == 100);
		}catch(std::out_of_range e){
			thrown = true;
		}*/
		map[1] = 100;
		assert(!map.empty());
/*		assert(map.root->left->left->data.second == 100);
		cout<<"Out of try"<<endl;
		assert(thrown);
		pair<int, int> a = make_pair(10, 10);
		auto fin = map.find(10);
		assert(fin.first == 10);
		assert(map.size() == 6);
		assert(!map.empty());
		it = map.begin();
		Map_T<int, int> map2;
		map2 = map;
		assert(map2.size() == map.size());
		cout<<"Begin is: "<<map.root<<" "<<it.second<<endl;
		Map_T<int, int> map2(map);
		cout<<"Begin is: "<< map2.root->left->data.first<<endl;
		assert(map.begin().first == map2.begin().first);*/
	}
return 0;
}

void original(){
	std::map<int, int> ma;
	ma.insert(make_pair(10, 10));
	ma.insert(make_pair(20, 20));
	ma.insert(make_pair(30, 30));
	ma.insert(make_pair(40, 40));
	ma.insert(make_pair(50, 50));
	ma.insert(make_pair(60, 60));
	ma[1] = 1000;
	for (std::map<int,int>::iterator it=ma.begin(); it!=ma.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	ma.insert(make_pair(100, 100));
}
