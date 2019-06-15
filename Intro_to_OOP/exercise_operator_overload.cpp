#include <iostream>

class Point {
  private:
  	double x_;
  	double y_;

  public:
  	// Constructor, with default value of x/y equals to 0
  	Point(double x = 0, double y = 0) : x_(x), y_(y) {}
  	// Operator "+" overload
  	Point operator+ (Point const& pt);
  	// We have to create a Print() method otherwise we cannot access x_ and y_
  	void Print();
};

// An example of define operator+ overloading outside of a class, after it has been declared inside of the class
Point Point::operator+(Point const& pt) {
	this->x_ += pt.x_;
	this->y_ += pt.y_;

	return *this;
}

void Point::Print() {
	std::cout << '(' << this->x_ << ", " << this->y_ << ")\n";
}

int main() {
	Point pt(1.5, 2.5);
	Point another_pt(1, -1);

	// invoke the overloaded operator+
	pt = pt + another_pt;

	std::cout << "After the addition calculation, the current pt has (x, y) = ";
	pt.Print();

	return 0;
}