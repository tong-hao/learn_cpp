#ifndef __COMPLEX__
#define __COMPLEX__
#include <iostream>

// usage:
// Complex a;
// Complex b(1.0, 2.0);
// Complex c = a + b;
// Complex c = a + 1.0;
// a += b;
// std::cout << a << b;

class Complex {
public:
	Complex(double r = 0, double i = 0) : re(r), im(i) {
	}
	double real() const {
		return re;
	}
	double imag() const {
		return im;
	}
	inline Complex& operator+=(const Complex& b);

private:
	double re, im;

	inline friend Complex& doapl(Complex* ths, const Complex& b);
};

Complex& Complex::operator+=(const Complex& b) {
	return doapl(this, b);
}
Complex& doapl(Complex* ths, const Complex& b) {
	ths->re += b.re;
	ths->im += b.im;
	return *ths;
}

inline std::ostream& operator<<(std::ostream& os, const Complex& b) {
	return os << "(" << b.real() << "," << b.imag() << ")";
}

Complex operator+(const Complex& a, const Complex& b) {
	return Complex(a.real() + b.real(), a.imag() + b.imag());
}

Complex operator+(const Complex& a, double re) {
	return Complex(a.real() + re, a.imag());
}

Complex operator-(const Complex& a) {
	return Complex(0 - a.real(), 0 - a.imag());
}

#endif
