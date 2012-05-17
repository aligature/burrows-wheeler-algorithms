#include <iostream>
#include "burrows_wheeler.hpp"

using namespace std;

int main()
{
   string input{"^banana|"};
   auto output = burrows_wheeler_copy(input);
   cout << "in:  " << input << endl;
   cout << "out: " << output << endl;
}
