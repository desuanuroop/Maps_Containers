//ALSO check for num in nodes, we are starting from 0.
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include "Map.hpp"

using namespace std;
using namespace cs540;
void original();

/*
 * Person class.
 */

template <typename K, typename V>
class test_map : public std::map<K, V> {
    private:
        using base_t = std::map<K, V>;
    public:
        using Iterator = typename base_t::iterator;
        std::pair<typename base_t::iterator, bool>insert(const std::pair<const K, V> &p) {
            return this->base_t::insert(p);
        }
};

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

void
print(const std::pair<const Person, int> &p) {
    p.first.print();
    printf("    %d\n", p.second);
}

/*
 * MyClass class.
 */

struct MyClass {
    friend bool operator<(const MyClass &o1, const MyClass &o2) {
        return o1.num < o2.num;
    }
    friend bool operator==(const MyClass &o1, const MyClass &o2) {
        return o1.num == o2.num;
    }
    MyClass(double n) : num(n) {}
    double num;
};

void
print(const std::pair<const int, std::string> &p) {
    printf("%d, %s; ", p.first, p.second.c_str());
}

/*
 * Stress class.
 */

struct Stress {
    friend bool operator<(const Stress& o1, const Stress& o2) {
        return o1.val < o2.val;
    }
    friend bool operator==(const Stress& o1, const Stress& o2) {
        return o1.val == o2.val;
    }
    Stress(int _v) : val(_v){}
    int val;
};
// Helper function for stress testing. This orders iterators by what they point to.
template <template <typename, typename> class MAP_T>
inline bool
less(const typename MAP_T<const Stress, double>::Iterator &lhs, const typename MAP_T<const Stress, double>::Iterator &rhs) {
    return (*lhs).first.val < (*rhs).first.val;
}

/*
 * Additional test functions for BST.
 */

template <template <typename, typename> class MAP_T>
void traverse(const MAP_T<const Person, int> &, int level);

template <template <typename, typename> class MAP_T>
void traverse2(int level);

template <template <typename, typename> class MAP_T>
void check(const MAP_T<const Stress, double> &, const std::map<const Stress, double> &);

/*
 * The actual test code.  It's a template so that it can be run with the std::map and the
 * assignment Map.
 */

int main(int argc, char *argv[]){
	if (argc ==2 ){
		original();
		Person p1("Jane");
	        Person p2("John");
	        Person p3("Mary");
	        Person p4("Dave");

        	Map<const Person, int> map;

	        // Insert people into the map.
	        auto p1_it = map.insert(std::make_pair(p1, 1));
	        map.insert(std::make_pair(p2, 2));
	        map.insert(std::make_pair(p3, 3));
	        map.insert(std::make_pair(p4, 4));

		// Check iterator equality.
        {
            // Returns an iterator pointing to the first element.
            auto it1 = map.begin();
            // Returns an iterator pointing to one PAST the last element.  This
            // iterator is obviously conceptual only.  It cannot be
            // dereferenced.
            auto it2 = map.end();

            it1++; // Second node now.
            it1++; // Third node now.
            it2--; // Fourth node now.
            it2--; // Third node now.
		assert(map == map);
		assert(it1 == it2);
//            assert(it1 == it2);
            it2--; // Second node now.
            it2--; // First node now.
            assert(map.begin() == it2);
        }
	// Check insert return value.
        {
		auto itp = map.begin();
		++itp;++itp;
		++itp;
		assert(itp->second == 3);
            printf("---- Test insert() return.\n");
            // Insert returns an interator.  If it's already in, it returns an
            // iterator to the already inserted element.
            auto it = map.insert(std::make_pair(p1, 1));
            assert(it.first == p1_it.first);
            // Now insert one that is new.
           it = map.insert(std::make_pair(Person("Larry"), 5));
            print(*(it.first));
//	    itp =  map.begin();
//	    ++itp;
//	    map.erase(itp);
            map.erase(it.first);
        }
	for(auto it = map.begin(); it != map.end(); ++it){
//        for (auto &e : map) {
            print(*it);
	}

	}//end of if
/*	if(argc == 2)
		original();*/
	else{
		Map<int, int> map;
		auto b = map.insert(make_pair(10, 10));
		b = map.insert(make_pair(20, 20));
		map.insert(make_pair(30, 30));
		map.insert(make_pair(40, 40));
		map.insert(make_pair(50, 50));
		map.insert({2, 3});
//		Map_T<int, int> map2{{61, 61}, {71, 71}};
		b = map.insert(make_pair(50, 50));
		assert(map.begin()->first == 2);
		auto it = map.end();
		auto i(it);
		auto j = it;
	}
return 0;
}

void original(){
	std::map<int, int> ma;
	ma.insert(make_pair(10, 10));
	ma.insert(make_pair(20, 20));
	ma.insert(make_pair(30, 30));
/*	ma.insert(make_pair(40, 40));
	ma.insert(make_pair(50, 50));
	ma.insert(make_pair(60, 60));*/
	for (std::map<int,int>::iterator it=ma.begin(); it!=ma.end(); ++it){
//		cout<< it->first<<endl;
//		it->first = 100;
		std::cout << it->first << " => " << it->second << '\n';
	}
	auto it = ma.begin();
	++it;
	++it;
	assert(it->first == 30);
	++it;
//	ma.erase(ma.end());
}
