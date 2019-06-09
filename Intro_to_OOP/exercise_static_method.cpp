#include <iostream>

class  Abstraction {
private:
    int number;
    char character;
public:
    void static PrintCharAsNumber(char c);
    void static PrintNumberPlusOne(int num);
};

void Abstraction::PrintCharAsNumber(char c) {
    int result = c;
    std::cout << result << "\n";
}

void Abstraction::PrintNumberPlusOne(int num) {
	num++;
	std::cout << "The plus one result is : " << num << "\n";
}


/*
 *    Note: we have NOT instantiate an instance of Abstraction,
 *	        we have only specified which scope this function it belongs to.
 *	        Which means that a class which implements a static method can 
 *	        invoke this method without the initialization of an instance of the class.
 */



int main() {
    char c = 'X';
    Abstraction::PrintCharAsNumber(c);
    // OUTPUT: 88

    int one = 1;
    Abstraction::PrintNumberPlusOne(one);
    // OUTPUT: The plus one results is : 2
}