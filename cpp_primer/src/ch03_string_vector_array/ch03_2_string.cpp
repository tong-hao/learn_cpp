#include <iostream>
#include <string>
#include <cctype> //isprint

using namespace std;

int main(int argc, char const *argv[])
{
	string s1 = "abc"; // copy
	string s2("abc");

	cout << "s1==s2 ? " << (s1 == s2) << endl;

	// operation
	string line;
	getline(cin, line);
	cout << "line: " << line << endl;
	cout << "isempty?" << line.empty()<< endl;
	cout << "size = " << line.size() << endl;
	cout << "s1+s2 = " << (s1+s2) << endl;
	cout << s1[1] << endl;

	// for
	for(auto c : s1) {
		cout << c << " "<< isprint(c)<< endl;
	}



	return 0;
}