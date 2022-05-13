#include <iostream>
// #include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SET_SIZE 620000

struct User {
  char ID[1000];
  int rank;
  bool inserted = false;
} dataSet[SET_SIZE];

void handleArguments(int argc){
  if (argc != 5) printf("missing arguments");
}

int main(int argc, char *argv[]) {
  handleArguments(argc);
  std::string dataFileTemp = argv[1]; // dataSet file to read from
  int insertCount = atoi(argv[2]);    // number of input operations
  int queryCount = atoi(argv[3]);     // number of query operations
  std::string fileNameTemp = argv[4]; // output new dataSet to new file

  std::string temp = ("datasets/" + dataFileTemp + ".txt");
  const char *dataFileString = temp.c_str();
  std::string temp2 = ("testsets/" + fileNameTemp + ".in");
  const char *fileName = temp2.c_str();
  // freopen(dataFile, "r", stdin);
  // std::cout << dataFileTemp << " " << dataFileString << "\n";
  // std::cout << fileNameTemp << " " << fileName << "\n";

  std::ifstream dataFile;
  dataFile.open(dataFileString);

  if (!dataFile) {
    printf("Unable to open dataFile %s\n", dataFileString);
    exit(1);   // call system to stop
  }

  // read word by word
  int unused;
  int userCount = 0;
  while(dataFile >> unused) {
    dataFile >> dataSet[userCount].ID >> dataSet[userCount].rank >> unused;
    userCount++;
  }
  // printf("userCount %d\n", userCount);
  dataFile.close();
  std::ofstream outputFile;
  outputFile.open(fileName);
  if (!outputFile) {
    printf("Unable to open fileName %s\n", fileName);
    exit(1);   // call system to stop
  }
  // printf("open");



  // using rand (get non related pseudo random numbers, but sequence of rand numbers always the same)
  // use srand with time as seed to generate batch of new psued-random numbers each time run
  srand((unsigned int)time(NULL));
  int user;           // user to be selected
  int operation;      // input or query operation
  while(insertCount + queryCount > 0) {
    user = rand() % userCount;
    operation = rand() % 2;
    if((operation == 0 && insertCount > 0) || queryCount <= 0) {
		    while(dataSet[user].inserted) user = rand() % userCount;
            outputFile  << 0 << " " << dataSet[user].ID << " " << dataSet[user].rank << "\n";
            dataSet[user].inserted = true;
            insertCount--;
        }
        else {
            outputFile  << 1 << " " << dataSet[user].ID << "\n";
            queryCount--;
        }
  }
  // end
  outputFile  << 2 << "\n";
  outputFile.close();
  return 0;
}
