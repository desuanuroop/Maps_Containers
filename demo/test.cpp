#include <iostream>
#include <typeinfo>
using namespace std;
template<class key_T>
void p(const key_T &k){
	cout<<k<<endl;
}

class demo{
	public:
		int const  *p;
	demo(){}
};

int main(){
	int a=10;
	demo d;
	d.p = &a;
	*d.p =100; //not allowed. We're chaging value which is const pointed by dp
return 1;
}
