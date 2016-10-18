
#include <iostream>
#include <assert.h>
#include <time.h>
#include "Map.hpp"
using namespace cs540;
int main(int argc, char *argv[]){
	Map<int, int> m;
	m.insert(make_pair(10, 10));
	m.insert(make_pair(15, 10));
        m.insert(make_pair(25, 10));
/*        m.insert(make_pair(30, 10));
        m.insert(make_pair(35, 10));
        m.insert(make_pair(38, 10));
        m.insert(make_pair(50, 10));
        m.insert(make_pair(65, 10));
        m.insert(make_pair(75, 10));
        m.insert(make_pair(76, 10));
        m.insert(make_pair(77, 10));
        m.insert(make_pair(80, 10));
        m.insert(make_pair(85, 10));
	int keys[] = {10, 15, 25, 30, 35, 38, 50, 65, 75, 76, 77, 80, 85};*/
	srand(time(NULL));
/*	for(int i=0;i<1000;i++)
                m.insert(std::make_pair(i, i));
	for(int i=0;i<1000;i--){
		m.erase(i);
	}*/
//	assert(m.root->data->first == 75);
	m.erase(15);
	m.erase(10);
	m.erase(25);
/*	for(int i=0;i<2;i++){
		auto z = m.begin();
		m.erase(z);
	}*/
//	m.erase(65);
//	auto it = m.begin();
//	++it;++it;
//	assert(it->first == 35);
//	}
}
