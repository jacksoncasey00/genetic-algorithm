#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void functionE(const string &input)
{
  if (input.empty())
  {
    int i = 3;
  }
  else
  {
    int i = 3;
    functionE(input.substr(1));
  }
}