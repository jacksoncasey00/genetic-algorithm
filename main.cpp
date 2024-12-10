#include <iostream>
#include <vector>
#include <string>

#include "genetic-algorithm.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  string program = argv[1];
  vector<pair<string, string>> schema;
  string type;
  string quit = "";
  int i = 0;
  int generations = stoi(argv[2]);
  int populationSize = stoi(argv[3]);
  string coverageFlag = "";
  if (argc > 4) {
    coverageFlag = argv[4];
  }
  bool fullCoverageDesired = false;
  if (coverageFlag == "--full") {
    fullCoverageDesired = true;
  }

  // CODE TO ACCEPT USE INPUT TO GET INITIAL VALUES. UNCOMMENT IF PREFERRED.
  //cout << "Enter the Name of the Program You Wish to Test: ";
  //cin >> program;
  // CODE TO ACCEPT FUNCTION ARGUMENT TYPES. SINCE EXAMPLE PROGRAMS ALL TAKE A SINGLE STRING, THIS IS NOT NEEDED
  /*cin.ignore();
  cout << "Enter the Typing for Each Argument of the Program You Wish to Test (Type 'Q' when done): ";
  while (true) {
    cin >> type;
    if (type == "Q") {
      break;
    }
    schema.emplace_back("var" + to_string(i), type);
    i++;
  }*/
  //cout << "Enter the Number of Generations you want the Algorithm to Run for: ";
  //cin >> generations;
  //cout << "Enter the Desired Population Size: ";
  //cin >> populationSize;

  schema.emplace_back("var", "string");

  geneticAlgorithm(program, schema, generations, populationSize, fullCoverageDesired);
  return 0;
}