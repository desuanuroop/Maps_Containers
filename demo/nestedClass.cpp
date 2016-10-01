#include <iostream>
using namespace std;

class OuterClass{
	public:
		int i;
	class InnerClass{
		public:
		int j;
		void print (){
			OuterClass ob;
			cout<<"Values of both: i and j are: "<<ob.i<<" "<<j<<endl;
		}
		InnerClass();
	};
	OuterClass(){
		i = 100;
	}
	InnerClass It();
};

OuterClass::InnerClass::InnerClass(){
	cout<<"In inneraClass construction"<<endl;
	j = 1000;
}
OuterClass::InnerClass OuterClass::It(){
return InnerClass();
}

int main(){
	OuterClass obj1;
	cout<<"i value is: "<<obj1.i<<endl;
	auto i = obj1.It();
	cout<<"j value is: "<<i.j<<endl;
return 0;
}
