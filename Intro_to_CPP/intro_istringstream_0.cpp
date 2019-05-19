/*

In C++ strings can be streamed into temporary variables, 

similarly to how files can be streamed into strings. 

Streaming a string allows us to work with each character individually.

One way to stream a string is to use an input string stream object istringstream from the <sstream> header.

Once an istringstream object has been created, 

parts of the string can be streamed and stored using the "extraction operator": >>. 

The extraction operator will read until whitespace is reached or until the stream fails. 

Execute the following code to see how this works: 

*/

#include <iostream>
#include <sstream>
#include <string>

using std::istringstream;
using std::string;
using std::cout;

int main () 
{
    string a("1 2 3");

    istringstream my_stream(a);

    int n;
    my_stream >> n;
    cout << n << "\n";
}