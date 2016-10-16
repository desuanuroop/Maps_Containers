#include <malloc.h>
#include <iostream>
class demo{
	public:
		int *z;
};
int main(){
	int *a = new int(10);
	demo *d = new demo();
	d->z = a;
	std::cout<<*d->z<<std::endl;
	delete d;
	std::cout<<*a<<std::endl;
return 1;
}
