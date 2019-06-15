#include <iostream>

// an example with bad intuition to explain the meaning
class Point {
  private:
  	double x_;
  	double y_;
  public:
  	Point(double x = 0, double y = 0) : x_(x), y_(y) {}
  	void Print() const; // original Print() function w/o parameters
  	void Print(double x) const;
  	void Print(double x, double y) const;
};

void Point::Print() const {
	std::cout << "The point has a coordinate (x, y) = (" 
		      << this->x_ << ", " << this->y_ << ").\n";
}

void Point::Print(double x) const {
	std::cout << "(NOT intuitive) The point has a coordinate (x, y) = (" 
		      << x << ", " << this->y_ << ").\n";
}

void Point::Print(double x, double y) const {
	std::cout << "(NOT intuitive) The point has a coordinate (x, y) = (" 
		      << x << ", " << y << ").\n";
}

int main() {
	Point p(3.5, 2.8);

	// Intuitive
	p.Print();

	// Not intuitive
	p.Print(1.2);
	p.Print(1.2, 3);

	return 0;
}