#include <iostream>

template <typename T>
void func(const T& x) {
	static int count = 0;
	std::cout << "x = " << x << ", count = " << count << std::endl;
	++count;
}

int main() {
	func<int>(1);
	std::cout << std::endl;
	func<int>(1);
	std::cout << std::endl;
	func<double>(1.1);
	std::cout << std::endl;
	func<int>(1);
	return 0;
}
