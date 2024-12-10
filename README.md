# Genetic Algorithm
Genetic Algorithm Aimed at Achieving High Code Coverage and Killing Mutants

## How to Use
1. Clone Repositiory
2. Install Coverage Gutters Extension in VSCode
3. Run the following commands in project folder to compile:
```
g++ -fprofile-arcs -ftest-coverage -o example_programs/functionParser example_programs/functionParser.cpp
g++ -fprofile-arcs -ftest-coverage -o main main.cpp
```
4. Run the following command to run the program:
```
main {name of file with functino you are testing} {max number of generations} {population size} {'--full' if code coverage must reach 100% with single input to stop program. Otherwise stops when all lines of code are executed at least once} 
```
