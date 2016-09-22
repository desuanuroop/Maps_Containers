#include <iostream>
#include <string>
#include <iostream>
using namespace std;
int main(){
	pair <string, double> product1;
	pair <string, double> product2("iphone", 649);
	pair <string, double> product3(product2);

	product1 = make_pair(string("samsung"), 700);
	cout<<"product name is:"<<product2.first<<endl;
//	cout<<"product price is:"<<product2.second.print()<<endl;

return 1;
}
