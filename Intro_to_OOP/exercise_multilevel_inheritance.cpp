#include <iostream>

//Base Class : class A
class A {
  private:
      int a_attr;
  public:
      void SetA(int val_a);
      int GetA(void);
};

void A::SetA(int val_a) {
    A::a_attr = val_a;
}

int A::GetA(void) {
    return A::a_attr;
}
//Here Class B is base class for class C
//and Derived class for class A
class B : public A {
  private:
      int b_attr;
  public:
      //assign value of a from here
      void SetAB(int val_a, int val_b);
      void PrintAB(void);
      int GetB(void);
};

void B::SetAB(int val_a, int  val_b) {
    //assign value of a by calling function of class A
    B::SetA(val_a);
    b_attr = val_b;
}
void B::PrintAB() {
    std::cout << B::GetA() << B::b_attr << "\n";
}
int B::GetB() {
    return B::b_attr;
}
//Here class C is derived class and B is Base class
class C : public B {
  private:
      int c_attr;
  public:
      //assign value of a from here
      void SetABC(int val_a, int val_b, int val_c);
      void PrintABC(void);
};

void C::SetABC(int val_a, int val_b, int val_c) {
    /*** Multilevel Inheritance ***/
    //assign value of a, bby calling function of class B and Class A
    //here Class A is inherited on Class B, and Class B in inherited on Class B
    C::SetAB(val_a, val_b);
    C::c_attr = val_c;
}

void C::PrintABC() {
    std::cout << C::c_attr << C::GetB() << C::GetA() << "\n";
}

int main()
{
    C c;
    c.SetABC(1, 2, 3);
    c.PrintABC();
    
    
}