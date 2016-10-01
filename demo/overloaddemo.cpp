#include <iostream>
using namespace std;
class Demo{
	public:
		int l;
	Demo();
        int at() const;
	void operator[](int);
};
Demo::Demo(){
    l = 12;
}
int Demo::at() const{
   cout<<"In const of at"<<endl;
   int a =3;
return a;
}

void Demo::operator[](int x){
	cout<<"X is: "<< x<<endl;
}

int main(){
    const Demo a;
    const int z = a.at();
    cout<<"z val:"<<z<<endl;
    Demo b;
    b.at();
    b[3];
return 0;
}
