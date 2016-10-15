#include <iostream>
#include <assert.h>

template<typename key_T>
class Demo{
	public:
		int l;
	Demo();
        int at() const;
	void operator[](int);
};
template<typename key_T>
Demo<key_T>::Demo(){
    l = 12;
}
template<typename key_T>
int Demo<key_T>::at() const{
   std::cout<<"In const of at"<<std::endl;
   int a =3;
return a;
}

template<typename key_T>
void Demo<key_T>::operator[](int x){
	std::cout<<"X is: "<< x<<std::endl;
}
template<typename key_T>
bool operator==(const Demo<key_T> &d1, const Demo<key_T> d2){
return true;
}
int main(){
    const Demo<int> a;
    const int z = a.at();
    std::cout<<"z val:"<<z<<std::endl;
    Demo<int> b;
	assert(a == b);
    b.at();
    b[3];
return 0;
}
