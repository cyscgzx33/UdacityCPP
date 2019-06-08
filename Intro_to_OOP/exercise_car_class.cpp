#include <string>
#include <cstring>
#include <iostream>

class Car {
    // Declare private attributes
    private:
        int horsepower;
        int weight;
        char* brand; // Note(very important): we are not sure about the size of setter function input, 
        			 // thus it must be declared as char*, dynamic char array.

    public:
    	// Declare getter functions
    	int getHorsepower() const;
    	int getWeight() const;
    	std::string getBrand() const;

    	// Declare setter functions
    	void setHorsepower(int);
    	void setWeight(int);
    	void setBrand(std::string);
};

// Define setters
void Car::setHorsepower(int horsepower) {
	this->horsepower = horsepower;
}

void Car::setWeight(int weight) {
	this->weight = weight;
}

void Car::setBrand(std::string brand) {
	this->brand = new char[brand.length() + 1]; // Note: why + 1? Since a character array (or a C style string), 
												// which ends with an NULL terminating character.
	strcpy(this->brand, brand.c_str());
}

// Define getters

int Car::getHorsepower() const {
	return this->horsepower;
}

int Car::getWeight() const {
	return this->weight;
}

std::string Car::getBrand() const {
	std::string brand_res;
	return brand_res + this->brand;
}


// Test in main()
int main() 
{
    Car car;
    car.setBrand("Peugeot");
    std::cout << car.getBrand() << "\n";   
}