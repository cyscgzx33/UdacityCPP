#include <iostream>

class Pyramid {
  private:
  	double base_length_;
  	double base_width_;
  	double height_;
  public:
  	Pyramid(double base_length, double base_width, double height);
  	
  	// getter functions
  	double getBaseLength() const;
  	double getBaseWidth() const;
  	double getHeight() const;

  	// setter functions
  	void setBaseLength(double base_length);
  	void setBaseWidth(double base_width);
  	void setHeigth(double height);

  	// member functions
  	double Volume();
  	double SurfaceArea();
  	bool IsAllPositive();
};

Pyramid::Pyramid(double base_length, double base_width, double height) : 
	base_length_(base_length), base_width_(base_width), height_(height) {}

double Pyramid::getBaseLength() const { return base_length_};

double Pyramid::getBaseWidth() const { return base_width_};

double Pyramid::getHeight() const { return height_};

void Pyramid::setBaseLength(double base_length) { base_length_ = base_length; }

void Pyramid::setBaseWidth(double base_width) { base_width_ = base_width; }

void Pyramid::setHeigth(double height) {height_ = height; }


