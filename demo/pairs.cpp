#include <iostream>
#include <string>
#include <iostream>
using namespace std;
template<class t1, class t2>
pair<t1, t2> ret(t1 a, t2 b){
	make_pair(a, b);
}
int main(){
	pair <string, double> product1;
	pair <string, double> product2("iphone", 649);
	pair <string, double> product3(product2);

	product1 = make_pair(string("samsung"), 700);
	cout<<"product name is:"<<product2.first<<endl;
	pair <string, double> *pointer = &product1;
	cout<<"product price is:"<< pointer->second<<endl;

	pair<int, int> p = ret(1, 23);
	cout<<p.first<<p.second<<endl;
return 1;
}
