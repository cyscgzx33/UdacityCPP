#include <iostream>

const double PI = 3.1415;

class Shape {
  public:
    Shape() {}

    /* Important Node:
     * [pure vertual function <=> delegation with "= 0" (NOT necessarily with "const")]
     * declare each of these functions with a "const = 0" flag is, 
     * to identify them as "prototypes" in the base class.
     * We said that in the base class, virtual methods can but
     * do not have to be implemented.
     * If we delegate with instruction "= 0", we are notifying compiler that
     * this (base) class doesn't have virtual method implementation,
     * but EVERY OTHER DERIVED CLASS IS REQUIRED TO IMPLEMENT THIS METHOD.
     */
    virtual double Area() const = 0;
    virtual double PerimeterLength() const = 0;
};

class Rectangle : public Shape {
  private:
    double width_;
    double height_;
  public:
    Rectangle(double width, double height);

    // Override virtual base class functions

    /* Note: If we have created a virtual function in the base class 
     * and it is being overridden in the derived class then we don’t 
     * need virtual keyword in the derived class, functions are 
     * automatically considered as virtual functions in the derived class.
     */
    double Area() const;
    double PerimeterLength() const;
};

class Circle : public Shape {
  private:
    double radius_;

  public:
    Circle(double radius);

    // Override virtual base class functions
    double Area() const;
    double PerimeterLength() const;
};

Rectangle::Rectangle(double width, double height) {
    this->width_ = width;
    this->height_ = height;
}

double Rectangle::Area() const {
    return this->width_ * this->height_;
}

double Rectangle::PerimeterLength() const {
    return 2 * (this->width_ + this->height_);
}

Circle::Circle(double radius) {
    this->radius_ = radius;
}

double Circle::Area() const {
    return PI * this->radius_ * this->radius_;
}

double Circle::PerimeterLength() const {
    return 2 * PI * this->radius_; 
}

int main() {

    /* written by cyscgzx33 */
    Circle cir(2.3);
    Rectangle rec(1.5, 2.0);

    std::cout << "The Circle cir has an area equals to " << cir.Area() 
              << ", and a perimeter length equals to " << cir.PerimeterLength() << std::endl;
    std::cout << "The Rectangle rec has an area equals to " << rec.Area() 
              << ", and a perimeter length equals to " << rec.PerimeterLength() << std::endl;

    /* written by Udacity */

    // Generic containter of Shapes (array) :
    Shape** shapes = new Shape*[2];
    shapes[0] = new Circle(12.31);
    shapes[1] = new Rectangle(10, 6);
    
    for (int i = 0;i < 2;i++) {
        std::cout << "Area: " << shapes[i]->Area()<< "\n";
        std::cout << "Perimeter: " << shapes[i]->PerimeterLength() << "\n";

    } 
}
