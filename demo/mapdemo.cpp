#include <iostream>
#include <map>
#include <assert.h>
using namespace std;

void original();
int main(){
	map<int, int> ma;
	ma.insert(make_pair(1, 1));
	ma.insert(make_pair(2, 2));
	ma.insert(make_pair(3, 3));
	map<int, int> m;
	m.insert(make_pair(1, 1));
	m.insert(make_pair(2, 2));
	assert(m < ma);
	original();
return 1;
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
        for (std::map<int,int>::iterator it=ma.begin(); it!=ma.end(); ++it){
//              cout<< it->first<<endl;
//              it->first = 100;
                std::cout << it->first << " => " << it->second << '\n';
        }
        ma.insert(make_pair(100, 100));
}

