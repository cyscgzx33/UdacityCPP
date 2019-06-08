#include <iostream>
#include <cmath> // to access M_PI

// Define class Sphere
class Sphere {
  // Define public constructor
  // Define a function to return the volume
  public:
  	Sphere(double radius);
  	double getVolume();

  // Define private attributes    
  private:
  	double radius_;
    
};

Sphere::Sphere(double radius) : radius_(radius) {}

double Sphere::getVolume() {
	return M_PI * 4/3 * pow(radius_, 3);
}

// Test in main()
int main() {
	Sphere s(5);
	std::cout << "The volume of the Sphere s is : " << s.getVolume() << std::endl;
}
