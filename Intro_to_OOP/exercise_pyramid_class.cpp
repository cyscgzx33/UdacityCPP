#include <iostream>
#include <cmath>

class Pyramid {
  private:
  	double base_length_;
  	double base_width_;
  	double height_;
  public:
  	Pyramid(double base_length, double base_width, double height);
  	Pyramid();
  	// getter functions
  	double getBaseLength() const;
  	double getBaseWidth() const;
  	double getHeight() const;

  	// setter functions
  	void setBaseLength(double base_length);
  	void setBaseWidth(double base_width);
  	void setHeight(double height);

  	// member functions
  	double Volume() const; // const also works here, as long as member attributes are not changed/modified
  	double SurfaceArea() const;
  	bool IsAllPositive() const;
};

Pyramid::Pyramid(double base_length, double base_width, double height) : 
	base_length_(base_length), base_width_(base_width), height_(height) {}

Pyramid::Pyramid() {}

double Pyramid::getBaseLength() const { return this->base_length_; }

double Pyramid::getBaseWidth() const { return this->base_width_; }

double Pyramid::getHeight() const { return this->height_; }

void Pyramid::setBaseLength(double base_length) { base_length_ = base_length; }

void Pyramid::setBaseWidth(double base_width) { base_width_ = base_width; }

void Pyramid::setHeight(double height) {height_ = height; }

double Pyramid::SurfaceArea() const {
	double bl = this->base_length_;
	double bw = this->base_width_;
	double h = this->height_;

	return (bl*bw + bl*sqrt( (bw/2)*(bw/2) + h*h)  + bw*sqrt( (bl/2)*(bl/2) + h*h) );
}

double Pyramid::Volume() const {
	return this->base_length_ * this->base_width_ * this->height_ / 3;
}

bool Pyramid::IsAllPositive() const {
	return this->base_length_ >= 0 && this->base_width_ >= 0 && this->height_ >= 0;
}


int main() {
	Pyramid prmd_1(12.5, 23.3, 50.5);
	Pyramid prmd_2;

	prmd_2.setBaseLength(12.0);
	prmd_2.setHeight(50.0); 
	prmd_2.setBaseWidth(23.0);



	std::cout << "prmd_1: (base_width, base_length, height) = (" << prmd_1.getBaseWidth() << " ," 
			  << prmd_1.getBaseLength() << " ," << prmd_1.getHeight() << ")." << std::endl;
	std::cout << "prmd_2: (base_width, base_length, height) = (" << prmd_2.getBaseWidth() << " ," 
			  << prmd_2.getBaseLength() << " ," << prmd_2.getHeight() << ")." << std::endl;

	std::cout << prmd_1.Volume() << std::endl;

	return 0;
}
