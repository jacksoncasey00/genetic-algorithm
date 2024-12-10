#include <iostream>
#include <vector>
#include <string>

#include "testProgram.cpp"
#include "functionA.cpp"
#include "functionB.cpp"
#include "functionC.cpp"
#include "functionD.cpp"
#include "functionE.cpp"
#include "functionF.cpp"
#include "functionG.cpp"

// Parses Call From Genetic Algorithm and Calls Appropriate Function
int main(int argc, char *argv[])
{
  string functionName = argv[1];

  if (functionName == "testProgram")
  {
    if (argc > 2)
    {
      test(argv[2]);
    }
  }
  else if (functionName == "functionA")
  {
    if (argc > 2)
    {
      functionA(argv[2]);
    }
  }
  else if (functionName == "functionB")
  {
    if (argc > 2)
    {
      functionB(argv[2]);
    }
  }
  else if (functionName == "functionC")
  {
    if (argc > 2)
    {
      functionC(argv[2]);
    }
  }
  else if (functionName == "functionD")
  {
    if (argc > 2)
    {
      functionD(argv[2]);
    }
  }
  else if (functionName == "functionE")
  {
    if (argc > 2)
    {
      functionE(argv[2]);
    }
  }
  else if (functionName == "functionF")
  {
    if (argc > 2)
    {
      functionF(argv[2]);
    }
  }
  else if (functionName == "functionG")
  {
    if (argc > 2)
    {
      functionG(argv[2]);
    }
  }
  return 0;
}