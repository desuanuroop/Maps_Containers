#include <iostream>

class A{
	public:
		class B{
			public:
				int i;
		};
		int j;
		B bs();
};

A::B A::bs(){
        B();
}

int main(){
	A::B obj;
	obj.i =100;
}
