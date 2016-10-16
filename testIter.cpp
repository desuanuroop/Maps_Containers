#include "Map.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <random>
#include <chrono>
#include <iterator>
#include <cassert>

using namespace cs540;

int main(){
	Map<int, int> m;
/*	m.insert(make_pair(1, 1));
	m.insert(make_pair(2, 2));
	m.insert(make_pair(3, 3));
	m.insert(make_pair(4, 4));
	m.insert(make_pair(5, 5));
	assert(m.root->data->first ==  2);*/

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine gen(seed);
	std::uniform_int_distribution<unsigned int> dist(0, 10000);
	for(int i = 0; i < 10; ++i){
        	auto g = dist(gen);
	        m.insert({g, g});
    	}
	assert(m.size() == 10);
	for(int i=0;i<10;i++){
		auto it = m.begin();
		m.erase(it);
	}
	std::cout<<"END"<<std::endl;
return 0;
}
