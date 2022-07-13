#include <iostream>


struct SaleData
{
	std::string book_no;
	unsigned sold_num;
	double revenue;
};

int main(int argc, char const *argv[])
{	
	SaleData s1;
	double price;

	std::cin >> s1.book_no >> s1.sold_num >> price;
	s1.revenue = price * s1.sold_num;

	std::cout << "book_no:" << s1.book_no << ", sold_num:" << s1.sold_num << ", revenue:" << s1.revenue;
	
	return 0;
}