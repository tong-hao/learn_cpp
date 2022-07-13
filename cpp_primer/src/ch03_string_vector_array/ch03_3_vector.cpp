#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	vector<int> v1{1,2,3};
	v1.push_back(4);

	for(auto i : v1) {
		cout << i << endl;
	}

	cout << "size:" << v1.size() << endl;
	cout << "empty?" << v1.empty() << endl;
	cout << "[0]" << v1[0] << endl;

	
	return 0;
}
