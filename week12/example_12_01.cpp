#include <iostream>

template<typename T>
void swapXX(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}
template<>
void swapXX(std::string& a, std::string& b) {
	std::cout << "string swap" << std::endl;
}

int main() {
	int a = 1;
	int b = 2;
	float c = 3.3;
	float d = 4.4;
	std::string e = "world";
	std::string f = "hello";

	swapXX<int>(a, b);
	swapXX<float>(c, d);
	swapXX < std::string>(e, f);

	std::cout << "a:" << a << ",b:" << b << std::endl;
	std::cout << "c:" << c << ",d:" << d << std::endl;
	std::cout << "e:" << e << ",f:" << f << std::endl;

	return 0;
}
