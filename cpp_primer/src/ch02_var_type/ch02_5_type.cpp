
int main(int argc, char const *argv[]) {

	// typedef, using
	{
		typedef double D1;
		using D2 = double;

		D1 d1 = 1;
		D2 d2 = 2;

		typedef char *pstring;
		pstring pstr = "abc"; // char指针

		pstring *ppstr = &pstr; // char指针的指针

	}

	// auto
	{
		int i = 0;
		auto i2 = i;
		auto i3 = &i; // i3 is a point
		auto &i4 = i; // i4 is a reference

		const int ci = 1;
		const auto ci1 = &ci;
		const auto &ci2 = ci;

	}

	// decltype(xxx)
	{
		auto call = []() {
			return 10;
		};
		decltype(call()) result = call();

		int i = 1;
		decltype(i + 1) i2;

		int *p = &i;
		decltype(*p) p2 = i;  // p2是引用
	}





	return 0;
}