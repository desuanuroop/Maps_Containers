#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;
template<class t1, class t2, class t3>
class tdemo{
	public:
		t1 name;
		t2 age;
		t3 gpa;
	tdemo(t1 name, t2 age, t3 gpa){
		this->name = name;
		this->age = age;
		this->gpa = gpa;
	}
};
int main(){
	tdemo<string, int, double> obj1(string("Anuroop"), 22, 3.5);
	tdemo<string, double, int> oib2(string("desu"), 22.3, 10);
	cout<<"Name is: "<<obj1.name<<endl<<typeid(obj1.gpa).name()<<endl<<typeid(oib2.gpa).name()<<endl;
return 0;
}


