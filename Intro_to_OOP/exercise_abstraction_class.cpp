// Include iostream for printing
#include <iostream>

// Define Abstraction class
    // Define private attributes
    // Define public setter and printing functions
class Abstraction{
  private:
  	int var1_;
  	double var2_;
  public:
  	Abstraction(int var1, double var2);
  	void printVal();
}; 

Abstraction::Abstraction(int var1, double var2) : var1_(var1), var2_(var2) {};

void Abstraction::printVal() {
	std::cout << "var1 = " << this->var1_ << " var2 = " << this->var2_ << std::endl;
}
        
// Test in main()
int main() {
	Abstraction abs(1, 2.0);
	abs.printVal();

	return 0;
}