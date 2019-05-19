/* 

The istringstream object can also be used as a boolean to determine 

if the last extraction operation failed --

this happens if there wasn't any more of the string to stream, 

for example. If the stream still has more characters, you are able to stream again. 

See the following code for an example of using the istringstream this way:

*/

#include <iostream>
#include <sstream>
#include <string>

using std::istringstream;
using std::string;
using std::cout;

int main() 
{
    string a("1 2 3");

    istringstream my_stream(a);

    int n;
    
    // Testing to see if the stream was successful and printing results.
    while (my_stream) {
        my_stream >> n;
        if (my_stream) {
            cout << "That stream was successful: " << n << "\n";
        }
        else {
            cout << "That stream was NOT successful!" << "\n";            
        }
    }
}