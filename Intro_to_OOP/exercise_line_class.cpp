#include <string>
#include <iostream>

class Line {
  protected:
  	double length_;
};

class Circle : Line {
  public:
  	double getArea() const;
  	void setRadius(double radius);
};

const double PI = 3.14;

double Circle::getArea() const {
	return this->length_ * this->length_ * PI;
}

void Circle::setRadius(double radius) {
	this->length_ = radius;
}


int main() {
	Circle c;
	c.setRadius(3.2);
	std::cout << "The Circle c has an area as: " << c.getArea() << std::endl;
}