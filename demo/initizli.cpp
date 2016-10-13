#include <iostream>          // std::cout
#include <string>            // std::string
#include <sstream>           // std::stringstream
#include <initializer_list>  // std::initializer_list

using namespace std;
class demo{
	public:
		demo(std::initializer_list< std::int> args){
			cout<<"Hello"<<endl;
		}
};
int main(){
	demo d{{1, 2, 3}};
return 1;
}

