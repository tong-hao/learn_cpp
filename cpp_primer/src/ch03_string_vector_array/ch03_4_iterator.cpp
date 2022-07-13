#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	std::vector<int> v{1,2,3};
	string s = "abcdef";

	for(auto iter = s.begin(); iter < s.end(); iter++) {
		cout << *iter << endl;
	}

	for(auto iter = v.begin(); iter < v.end(); iter++){
		cout << *iter << endl;
	}
	
	return 0;
}
