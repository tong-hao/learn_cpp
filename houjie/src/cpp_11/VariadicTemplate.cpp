
void print() {
}

template <typename T, typename... Types>
void print(const T& arg1, const Types... args) {
	sizeof...(args);
	std::cout << arg1 << std::endl;
	print(args);
}

template <typename... Types>
void print2(const Types... args) {
	sizeof...(args);
	print2(args);
}

int main(int argc, char const* argv[]) {
	print(1, "a", "b", "3", "4");

	return 0;
}
