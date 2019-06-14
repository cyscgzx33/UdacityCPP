#include <iostream>
#include <string>


/* In the code below, the Dog class inherits from both Animal and Pet. 
 * Once you have examined the code below, add a Cat class that also inherits from Animal and Pet.
 * The Cat class should have the attributes string eye_color and int age. 
 * When you are finished implementing the Cat class, 
 * create a cat instance in main and set and print those attributes.
 */


class Animal {
  public:
      double weight;
      double size;
      // rest of class interface
};

class Pet {
  public:
      std::string name;
      std::string owner_name;
      // rest of class interface
};

// Dog is derived class with inherited properties
class Dog : public Animal, public Pet {
  public:
      bool has_long_fur;
      bool has_short_fur;
  // rest of class interface
};

class Cat : public Animal, Pet {
  public:
      std::string eye_color_;
      int age_;
};


int main()
{
    Dog d;
    d.has_long_fur = true;
    d.weight = 10;
    d.size = 43;
    d.owner_name = "Ryan";
    std::cout << d.has_long_fur << "\n";
    std::cout << d.owner_name << "\n";

    Cat c;
    c.eye_color_ = "Red";
    c.age_ = 4;
    std::cout << "Cat c has a eye_color_ : " << c.eye_color_ << std::endl;
    std::cout << "Cat c has a age_ : " << c.age_ << std::endl;
    
};