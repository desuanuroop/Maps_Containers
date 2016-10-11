//ALSO check for num in nodes, we are starting from 0.
#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <stdio.h>
#include "Map.hpp"

using namespace std;
void original();

/*
 * Person class.
 */

struct Person {
    friend bool operator<(const Person &p1, const Person &p2) {
        return p1.name < p2.name;
    }
    friend bool operator==(const Person &p1, const Person &p2) {
        return p1.name == p2.name;
    }
    Person(const char *n) : name(n) {}
    void print() const {
        printf("Name: %s\n", name.c_str());
    }
    const std::string name;
    Person &operator=(const Person &) = delete;
};

int main(int argc, char *argv[]){
/*	if (argc ==2 ){
		Person p1("Jane");
		Person p2("Lisbon");
		Person p3("Cho");
		Map_T<const Person, int > map;
		map.insert(make_pair(p3, 3));
		assert(map.root->data->second == 3);
		map.insert(make_pair(p2, 2));
		map.insert(make_pair(p1, 1));
		cout<<"fdfd"<<endl;
	}
	else{*/
		Map_T<int, int> map;
		auto b = map.insert(make_pair(10, 10));
		map.insert(make_pair(20, 20));
		map.insert(make_pair(30, 30));
		map.insert(make_pair(40, 40));
		map.insert(make_pair(50, 50));
		b = map.insert(make_pair(50, 50));
		cout<<b.second<<endl;
		auto it = map.end();
		auto i(it);
		assert(i.first == it.first);
		assert(it.first == 0);
		it = map.begin();
		assert(it.first == 10);
		++it;
		--it;
		it++;
		it--;
		const auto c = map.begin();
		auto p = *c;
		p.second = 100;
		assert(p.first == it.first);
		assert(it.second == 10);
		assert(it.first == 10);
		it = map.rbegin();
		assert(it.first == 50);
		it = map.rend();
		assert(it.first == 0);
		map.insert(make_pair(60, 60));
		bool thrown = false;
		try {
			map.at(100) = 100;
			assert(map.root->left->left->data->second == 100);
		}catch(std::out_of_range e){
			thrown = true;
		}
		map[1] = 100;
		assert(!map.empty());
		assert(map.root->left->left->left->data->second == 100);
		cout<<"Out of try"<<endl;
		assert(thrown);
		pair<int, int> a = make_pair(10, 10);
		auto fin = map.find(10);
		assert(fin.first == 10);
		assert(map.size() == 7);
		assert(!map.empty());
		it = map.begin();
		Map_T<int, int> map2;
		map2 = map;
		assert(map2.size() == map.size());
		cout<<"Begin is: "<<it.second<<endl;
//		Map_T<int, int> map3(map);
//		cout<<"Begin is: "<< map3.root->left->data->first<<endl;
//		assert(map.begin().first == map3.begin().first);
//	}
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
