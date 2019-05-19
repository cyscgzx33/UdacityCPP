/*

The extraction operator >> writes the stream to the variable on the right of 

the operator and returns the istringstream object, 

so the entire expression my_stream >> n is an istringstream object and can be used as a boolean! 

Because of this, a common way to use istringstream is to 

use the entire extraction expression in a while loop as follows:

*/



#include <iostream>
#include <sstream>
#include <string>

using std::istringstream;
using std::string;
using std::cout;

int main () {
    string a("1 2 3");

    istringstream my_stream(a);
    
    int n;
    
    while (my_stream >> n) {
      cout << "That stream was successful: " << n << "\n";
    }
    cout << "The stream has failed." << "\n";
    
}