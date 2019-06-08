#include <iostream>

class Abstraction {
  public:
  	void SetAttributes(int number, char character);
  	void GetAttributes();

  private:
  	int number_;
  	char character_;
  	void ProcessAttributes();
};

void Abstraction::SetAttributes(int number, char character) {
	this->number_ = number;
	this->character_ = character;
}

void Abstraction::GetAttributes() {
	// run the private method
	this->ProcessAttributes();
	// print the resulting values but not return them
	std::cout << "The number value is: " << this->number_ << std::endl
			  << "The character value is: " << this->character_ << std::endl;
}

void Abstraction::ProcessAttributes() {
	number_ *= 6;
	character_ += 1; // I'll take a guess here, the ASCII code will be added by 1
}


int main() {
	Abstraction abs;
	abs.SetAttributes(5, 'c');
	abs.GetAttributes();

	return 0;
}