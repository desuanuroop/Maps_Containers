#include <iostream>
using namespace std;
class Base{
	public:
		void operator++(int x){
			cout<<"In parent"<<endl;
			j = j+100;
		}
	int j;
};
class child: public Base{
	public:
		void operator++(int k){
			this.Base::++;
			cout<<"In child "<<endl;
			j = j+50;
			x = x+30;
		}
	int x;
};

int main(){
	Base b;
	b.j = 0;
	b++;
	child c;
	c.x = 66;
	c.j = 78;
	c++;
return 1;
}
