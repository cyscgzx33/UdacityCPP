#include <iostream>
#include <vector>

// generic class definition type _Tc
template <typename _Tc>
class Container {
  private:
    std::vector<_Tc> arr_;
    int s_;
  public:
    Container() : s_(0) 
    {
        arr_.clear();
    }
    int size() const 
    {
        return Container::s_;
    }
    void add(_Tc el) 
    {
        Container::s_++;
        arr_.push_back(el);
    }
    void print() const
    {
        for (_Tc i : arr_) {
            std::cout << i << " ";
        }
        std::cout << "\n" << "Container::size: " << Container::s_ << "\n";
    }
};


int main()
{
    Container<double> obj; // Partial deduction: element type is specified
    obj.add(2.00329132);
    obj.print();
    obj.add(8.83);
    obj.print();
    // TARGET OUTPUT:
    /*
        2.00329
        Size is:1
        2.00329 8.83
        Size is:2
    */
    return 0;
}