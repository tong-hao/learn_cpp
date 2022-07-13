
template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << ", ";
		begin++;
	}
	std::cout << std::endl;
}
