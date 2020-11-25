class PairDouble {
public:
	PairDouble(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}
	double returnX() const { return x_; }
	double returnY() const { return y_; }
private:
	double x_, y_;
};

class PairFloat {
public:
	PairFloat(float x = 0.0, float y = 0.0) : x_(x), y_(y) {}
	float returnX() const { return x_; }
	float returnY() const { return y_; }
private:
	float x_, y_;
};

int main() {
	PairDouble pd = PairDouble();
	PairFloat  pf = PairFloat();
	return 0;
}