#include <variant>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <set>

using namespace std;

struct InputSpec
{
  string name;
  variant<int, double, string> value; // vector<int>
};

struct Chromosome
{
  vector<InputSpec> inputs;
};

set<int> previouslyExecutedLines; //, vector<int>
vector<string> usefulInputs;
bool allStatementsExecuted = false;
bool fullCoverage = false;
static mt19937 rng(random_device{}());
string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

variant<int, double, string> generateRandomValue(const string &type)
{
  if (type == "int")
  {
    uniform_int_distribution<int> dist(0, 100);
    return dist(rng);
  }
  else if (type == "double")
  {
    uniform_real_distribution<double> dist(0.0, 10.0);
    return dist(rng);
  }
  else if (type == "string")
  {
    /*uniform_int_distribution<char> char_dist(32, 126); // Printable ASCII range
    string result(10, ' ');
    for (auto& ch : result) {
        ch = char_dist(rng);
    }
    return result;*/
    string str(rand() % 10, '\0'); // rng() % 10
    for (auto &ch : str)
      ch = characters[(rng() % characters.length())];
    return str;
  }
  // POTENTIAL OPTION FOR ACCEPTING VECTOR INPUTS
  /*else if (type == "vectorint")
  {
    vector<int> veci;
    for (int i = 0; i < rng() % 20; i++)
    {
      uniform_int_distribution<int> dist(0, 100);
      veci.push_back(dist(rng));
    }
    return veci;
  }*/
  throw runtime_error("Unsupported type");
}

Chromosome initializeChromosome(const vector<pair<string, string>> &schema)
{
  Chromosome chromosome;
  for (const auto &[name, type] : schema)
  {
    chromosome.inputs.push_back({name, generateRandomValue(type)});
  }
  return chromosome;
}

double evaluateFitness(const Chromosome &chromosome, const string &program)
{
  // Serialize inputs into arguments
  string args;
  args += program + " ";
  for (const auto &input : chromosome.inputs)
  {
    if (holds_alternative<int>(input.value))
    {
      args += to_string(get<int>(input.value)) + " ";
    }
    else if (holds_alternative<double>(input.value))
    {
      args += to_string(get<double>(input.value)) + " ";
    }
    else if (holds_alternative<string>(input.value))
    {
      args += get<string>(input.value) + " ";
    }

    // POTENTIAL OPTION FOR ACCEPTING VECTOR INPUTS
    /*else if (holds_alternative<vector<int>>(input.value))
    {
      for (int i = 0; i < get<vector<int>>(input.value).size(); i++) {
        args += to_string(get<vector<int>>(input.value)[i]) + " ";
      }
    }*/
  }

  // Run the target program with the arguments
  string command = "start /B /wait example_programs/functionParser.exe " + args;
  system(command.c_str());

  command = "gcov -r ./example_programs/functionParser.cpp > NUL 2>&1";
  system(command.c_str());

  command = "del /s /q *.gcda > NUL 2>&1";
  system(command.c_str());

  // Parse .gcov file to compute fitness
  ifstream gcovFile(program + ".cpp.gcov");
  int coveredLines = 0, totalLines = 0;
  int newLines = 0;
  string line;
  set<int> currentExecution;
  int currentLine = 0;

  // OLD METHOD FOR CALCULATING FITNESS
  /*while (std::getline(gcovFile, line)) {
        if (line.find("####") == std::string::npos) {  // Lines not executed
            ++coveredLines;
        }
        ++totalLines;
    }
    return static_cast<double>(coveredLines) / totalLines * 100.0;  // Coverage %*/
  while (getline(gcovFile, line))
  {
    // Parse line number from gcov output
    if (currentLine > 3)
    {
      // size_t lineStart = line.find_last_of(':') + 1;
      char indicator = line[line.find_first_of(':') - 1];
      if (indicator != '-')
      {
        int lineNumber = currentLine - 3;
        ++totalLines;

        // Check if the line was executed
        if (indicator != '#')
        {
          ++coveredLines;
          currentExecution.insert(lineNumber);

          // Check if this is a new line
          if (previouslyExecutedLines.find(lineNumber) == previouslyExecutedLines.end())
          {
            cout << "NEW CHARACTER INTRODUCED" << endl;
            usefulInputs.push_back(get<string>(chromosome.inputs[0].value));
            previouslyExecutedLines.insert(lineNumber);
            ++newLines; // Increment new line count
          }
        }
      }
    }
    currentLine++;
  }

  if (newLines > 0)
  {
    // usefulInputs.push_back(args);
  }

  if (previouslyExecutedLines.size() == totalLines)
  {
    allStatementsExecuted = true;
    // usefulInputs.push_back(args);
  }

  // Calculate fitness
  double baseCoverage = static_cast<double>(coveredLines) / totalLines * 100.0; // Base coverage %

  double fitness = newLines > 0 ? 100.0 : baseCoverage;
  if (baseCoverage == 100)
  {
    fullCoverage = true;
  }

  return fitness; // Coverage %
}

// Tournament Selection (NOT CURRENTLY USED)
Chromosome tournamentSelect(const vector<pair<Chromosome, double>> &fitnessScores, int tournamentSize)
{
  vector<pair<Chromosome, double>> tournamentGroup;

  // Randomly select individuals for the tournament
  for (int i = 0; i < tournamentSize; ++i)
  {
    int randomIndex = rand() % fitnessScores.size();
    tournamentGroup.push_back(fitnessScores[randomIndex]);
  }

  // Select the best individual from the tournament group
  auto best = max_element(tournamentGroup.begin(), tournamentGroup.end(),
                          [](const auto &a, const auto &b)
                          {
                            return a.second < b.second; // Higher fitness wins
                          });
  return best->first;
}

// Rank Selection Function (NOT CURRENTLY USED)
Chromosome rankSelect(const vector<pair<Chromosome, double>> &fitnessScores)
{
  // Sort individuals by fitness in ascending order (lower fitness first)
  vector<size_t> indices(fitnessScores.size());
  iota(indices.begin(), indices.end(), 0); // Generate indices [0, 1, 2, ..., n-1]
  sort(indices.begin(), indices.end(), [&](size_t a, size_t b)
       {
         return fitnessScores[a].second < fitnessScores[b].second; // Sort by fitness
       });

  // Assign selection probabilities based on rank
  vector<double> probabilities(fitnessScores.size());
  double rankSum = (fitnessScores.size() * (fitnessScores.size() + 1)) / 2.0; // Sum of ranks
  for (size_t i = 0; i < indices.size(); ++i)
  {
    probabilities[indices[i]] = static_cast<double>(i + 1) / rankSum; // Higher rank = higher probability
  }

  // Perform weighted random selection
  random_device rd;
  mt19937 gen(rd());
  discrete_distribution<> dist(probabilities.begin(), probabilities.end());
  return fitnessScores[dist(gen)].first;
}

Chromosome crossover(const Chromosome &parent1, const Chromosome &parent2)
{
  Chromosome child;
  for (size_t i = 0; i < parent1.inputs.size(); ++i)
  {
    string replacement = get<string>(parent1.inputs[i].value);
    for (size_t n = 0; n < replacement.length(); ++n)
    {
      if (rand() % 2 == 0)
      {
        replacement[n] = get<string>(parent2.inputs[i].value)[n];
      }
    }
    string childName = parent1.inputs[i].name;
    variant<int, double, string> childValue = replacement;
    child.inputs.push_back({childName, childValue});
  }
  return child;
  // OLD CHROMOSOME CALCULATOR (USEFUL FOR NON-STRING VALUES)
  /*Chromosome child = parent1;
    for (size_t i = 0; i < child.inputs.size(); ++i) {
        if (rand() % 2 == 0) {
            child.inputs[i].value = parent2.inputs[i].value;
        }
    }
    return child;*/
}

void mutate(Chromosome &chromosome, const vector<pair<string, string>> &schema, double mutationRate = 0.1)
{
  for (size_t i = 0; i < chromosome.inputs.size(); ++i)
  {
    string newString = get<string>(chromosome.inputs[i].value);
    if (rand() % 4 < 3)
    {
      for (size_t n = 0; n < get<string>(chromosome.inputs[i].value).length(); ++n)
      {
        if ((rand() / static_cast<double>(RAND_MAX)) < mutationRate)
        {
          newString[n] = (characters[(rng() % characters.length())]);// 'a' + (rand() % 26);
        }
      }
    }
    else
    {
      if ((rand() / static_cast<double>(RAND_MAX)) < mutationRate)
      {
        newString = "";
        for (int i = 0; i < rand() % 10; i++) {
          newString.push_back(characters[(rng() % characters.length())]);
        }
      }
    }
    chromosome.inputs[i].value = newString;
  }
}

void geneticAlgorithm(const string &program, const vector<pair<string, string>> &schema, int generations, int populationSize, bool fullCoverageDesired)
{
  vector<Chromosome> population;

  // Initialize population
  for (int i = 0; i < populationSize; ++i)
  {
    population.push_back(initializeChromosome(schema));
  }

  for (int gen = 0; gen < generations; ++gen)
  {
    // Evaluate fitness
    vector<pair<Chromosome, double>> fitnessScores;
    for (const auto &individual : population)
    {
      fitnessScores.emplace_back(individual, evaluateFitness(individual, program));
      cout << "Gen: " << gen << " Input: " << get<string>(individual.inputs[0].value) << " Coverage: " << fitnessScores[fitnessScores.size() - 1].second << endl;

      if ((allStatementsExecuted && !fullCoverageDesired) || (allStatementsExecuted && fullCoverageDesired && fullCoverage))
      {
        cout << "Useful Inputs: " << endl;
        for (int i = 0; i < usefulInputs.size(); i++)
        {
          cout << usefulInputs[i] << endl;
        }
        cout << get<string>(individual.inputs[0].value) << endl;
        break;
      }
    }
    if ((allStatementsExecuted && !fullCoverageDesired) || (allStatementsExecuted && fullCoverageDesired && fullCoverage))
    {
      cout << "All Statements Executed!" << endl;
      break;
    }

    // Sort by fitness
    sort(fitnessScores.begin(), fitnessScores.end(), [](auto &a, auto &b)
         { return a.second > b.second; });
    // Selection (Top 50%)
    vector<Chromosome> newPopulation;
    for (size_t i = 0; i < populationSize / 2; ++i)
    {
      newPopulation.push_back(fitnessScores[i].first);

      // POSSIBLE DATA SELECTION METHOD IF YOU WANT MORE EMPHASIS ON WEAKER INPUTS
      /*if (i % 2 == 0)
      {
        newPopulation.push_back(fitnessScores[i].first);
      }
      else
      {
        newPopulation.push_back(fitnessScores[i + (populationSize / 2)].first);
      }*/
    }

    // Tournament/Rank Selection
    /*vector<Chromosome> newPopulation;
    while (newPopulation.size() < populationSize / 2)
    {
      //newPopulation.push_back(tournamentSelect(fitnessScores, 4)); // tournamentSize
      newPopulation.push_back(rankSelect(fitnessScores));
    }*/

    // Crossover and Mutation
    while (newPopulation.size() < populationSize)
    {
      Chromosome parent1 = newPopulation[rand() % (populationSize / 2)];
      Chromosome parent2 = newPopulation[rand() % (populationSize / 2)];
      Chromosome child = crossover(parent1, parent2);
      mutate(child, schema, 0.2);
      newPopulation.push_back(child);
    }

    population = newPopulation;

    // Print generation stats
    cout << "Generation " << gen << ": Best fitness = " << fitnessScores[0].second << "%\n";
  }
}
