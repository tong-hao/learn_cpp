#include <iostream>

using namespace std;
int main(int argc, char const *argv[]) {
	//if
	{
		int i = 0;
		if (i > 0) {
			cout << "i>0" << endl;
		} else if (i < 0) {
			cout << "i<0" << endl;
		} else {
			cout << "i==0" << endl;
		}


	}

	// switch
	{
		int flag = 1;
		switch (flag) {
		case 1:
			cout << "is 1" << endl;
			break;
		case 2:
			cout << "is 1" << endl;
			break;
		default:
			cout << "is error." << endl;


		}
	}
	// while
	{
		int i = 10;
		while (i > 0) {
			--i;
		}
	}

	// for

	for (int i = 0; i < 10; i++) {

	}

	// for range
	for (auto i : {1, 2, 3}) {

	}

	// do while
	{
		int i = 10;
		do {
			cout << "do while"<< endl;
		} while (i < 0);
	}


	// break; continue;

	// goto
	{
		goto end;

		begin:
			cout << "enter: begin" << endl;

		end:
			cout << "enter: end" << endl;
	}

	// try catch
	{
		try{
			double i = 1/0;
		}catch(std::exception err){
			cout << "error:" << endl;
			cout << err.what() << endl;
		}
	}

	return 0;
}