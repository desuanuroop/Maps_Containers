#include <iostream>
using namespace std;
template<class key_T>
void p(const key_T &k){
	cout<<k<<endl;
}

int main(){
	p(4);
	p(12.2);
return 0;
}
