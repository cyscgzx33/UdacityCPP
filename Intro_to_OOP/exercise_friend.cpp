#include <iostream>

class Rectangle; // this is only declaration, no definition here

class Square {
    friend class Rectangle; // add class Rectangle as a friend to the class Square
  private:
  	double side_;
  public:
  	Square(double square_side);
};

Square::Square(double square_side) {
	this->side_ = square_side;
}

// Implement class Rectangle
class Rectangle {
  private:
  	double rec_width_;
  	double rec_height_;

  public:
  	double Rec_Area() const;
  	void Convert_SquToRec(Square squ); // use the object of squ as a parameter,
  	                                   // to access its private attribute side_ and init rec_width_ and rec_height_
};

double Rectangle::Rec_Area() const {
	return this->rec_width_ * this->rec_height_;
}

void Rectangle::Convert_SquToRec(Square squ) {
	this->rec_width_ = squ.side_;
	this->rec_height_ = squ.side_;
}

int main() {
	Square squ(3.3);
	
	Rectangle rec;
	rec.Convert_SquToRec(squ);

	// print out the results
	std::cout << "The rec has an area of : " << rec.Rec_Area() << std::endl;
}