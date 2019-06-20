#include <iostream>
#include <vector>

// Helper generic function with a generic vector<T> parameter
template <typename _Tf>
void print(std::vector<_Tf> v) 
{
    for (_Tf i : v) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

// Multiple use of type parameters for unique types.
// _Tf_1 supports basic operation, but _Tf_2 can be used as indexed container 
// and object which contains method size()
template <typename _Tf_1,typename _Tf_2>
void scale(_Tf_1 num, _Tf_2& container) 
{
    for (auto& i : container) {
        i *= num;
    }
}
//main function
int main()
{
    std::vector<int> container = {2,3,17,23,14,18,21};
    print(container);

    scale(3, container);
    print(container);
    
    scale('Z', container); // 'Z' will convert to 90 when used as an integer
    print(container);

}
