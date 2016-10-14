#include <iostream>

class B{
	public:
		int x;
};
class A: public B{
	public:
	A(int a){
		x = a;
	}
};
int main(){
	A(2);
return 1;
}
