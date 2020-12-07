#include<iostream>
#include<string>

template<typename T, typename... Args>
auto sum(T x, Args... args) {
	return x+sum(args...);
}

template<typename T>
T sum(T x){
	return x;
}

int main() {
	auto x = sum(42.5, 10, 11.1f, 1234);
	std::cout << x;

	getchar();
}