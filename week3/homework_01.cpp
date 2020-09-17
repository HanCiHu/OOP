#include <iostream>
class SetValue {
private:
	int x, y;
public:
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
};

int main() {
	SetValue obj;
	obj.setX(33);
	obj.setY(44);

	std::cout << "X = " << obj.getX() << " ,Y = " << obj.getY() << std::endl;
	return 0;
}