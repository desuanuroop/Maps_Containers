#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;
class d{
	int z;
};
template<class t1>
class demo{
	t1 a;
};
template<class t1, class t2, class t3>
class tdemo{
	public:
		t1 name;
		t2 age;
		t3 gpa;
//		const d zp;
//		const demo<t1> dp;
//		const int test;
	tdemo(t1 name, t2 age, t3 gpa){
		this->name = name;
		this->age = age;
		this->gpa = gpa;
	}
};
int main(){
	int a, c;
	const int *b;
	b = &a;
	b = &c;
	tdemo<string, int, double> obj1(string("Anuroop"), 22, 3.5);
	tdemo<string, double, int> oib2(string("desu"), 22.3, 10);
	cout<<"Name is: "<<obj1.name<<endl<<typeid(obj1.gpa).name()<<endl<<typeid(oib2.gpa).name()<<endl;
return 0;
}


