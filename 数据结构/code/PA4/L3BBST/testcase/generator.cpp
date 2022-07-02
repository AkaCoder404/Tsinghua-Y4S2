#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#define NMAX 1000000
#define XMAX 3500000

std::default_random_engine e;
// generate uniformly distributed integer values on the closed interval (lo, hi)
std::uniform_int_distribution<int> u(0, XMAX); 
std::uniform_int_distribution<int> percentage(0, 100); 

int num[NMAX];


// randomly determine an operation time according to distribution
char randomOperation(int ins, int del, int que) {
  del += ins; 
  que += del;
  int op = percentage(e);
  if (op <= ins)
    return 'A';
  if (op <= del)
    return 'B';
  return 'C';
}

// generate an ordered sequence of opeartions
void sortedSequence(std::ofstream &dataFile, int length, int lo, int hi, int ins, int del, int que) {
  std::uniform_int_distribution<int> interval(lo, hi); 
  for (int i = 0; i < length; i++)
    num[i] = interval(e);
  std::sort(num, num + length);

  for (int i = 0; i < length; i++) {
    dataFile << randomOperation(ins, del, que) << " " << num[i] << std::endl;
  }
}

// generate an unordered sequence of operations
void randomSequence(std::ofstream &dataFile, int length, int lo, int hi, int ins, int del, int que) {
  std::uniform_int_distribution<int> interval(lo, hi);
  for (int i = 0; i < length; i++) {
    dataFile << randomOperation(ins, del, que) << " " << interval(e) << std::endl;
  }
}

// generate an unordered sequence of operations, with adjacent elements differing by no more than 10
void neighborSequence(std::ofstream &dataFile, int length, int lo, int hi, int ins, int del, int que) {
  std::uniform_int_distribution<int> interval(lo, hi);
  int start = interval(e);
  for (int i = 0; i < length; i++) {
    std::uniform_int_distribution<int> neighbor(start - 10, start + 10);
    start = neighbor(e);
    dataFile << randomOperation(ins, del, que) << " " << start << std::endl;
  }
}

// randomly determine the length of a sequence of operations according to normal/uniform distribution
int random_length(int total, bool normal) {
  if (normal) {
    std::normal_distribution<float> normald(total / 2, 1);
    int length = (int)normald(e);
    return std::min(std::max(total / 16, length), total);
  } else {
    std::uniform_int_distribution<int> l(total / 16, total);
    return l(e);
  }
}

// random unsorted insertions
void testcase1(std::ofstream &dataFile) {
  dataFile << NMAX << std::endl;
  randomSequence(dataFile, NMAX, 0, XMAX, 100, 0, 0); 
}

// random unsorted & segmented insertion
void testcase2(std::ofstream &dataFile) {
  dataFile << (NMAX / 1000) * 1000 << std::endl;
  for (int i = 0; i < 1000; ++i) {
    randomSequence(dataFile, NMAX / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 100, 0, 0);
  }
}

// sorted and segmented insertions
void testcase3(std::ofstream &dataFile) {
  dataFile << (NMAX / 1000) * 1000 << std::endl;
  for (int i = 0; i < 1000; ++i) {
    sortedSequence(dataFile, NMAX / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 100, 0, 0);
  }
}

// first 1/3 randomly insert, last 2/3 random insert/delete
void testcase4(std::ofstream &dataFile) {
  dataFile << NMAX / 3 + (NMAX / 3) * 2 << std::endl;
  randomSequence(dataFile, NMAX / 3, 0, XMAX, 100, 0, 0);
  randomSequence(dataFile, 2 * (NMAX / 3), 0, XMAX, 50, 50, 0);
}

// first 1/3 randomly insert, last 2/3 randomly locally insert/delete
void testcase5(std::ofstream &dataFile) {
  dataFile << NMAX / 3 + (NMAX / 3) * 2 << std::endl;
  randomSequence(dataFile, NMAX / 3, 0, XMAX, 100, 0, 0);
  for (int i = 0; i < 1000; ++i) {
    randomSequence(dataFile, 2 * (NMAX / 3) / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 50, 50, 0);
  }
}

// first 1/3 randomly insert, last 2/3 are segmented with local ordered random insert/delete
void testcase6(std::ofstream &dataFile) {
  dataFile << NMAX / 3 + (NMAX / 3) * 2 << std::endl;
  randomSequence(dataFile, NMAX / 3, 0, XMAX, 100, 0, 0);
  for (int i = 0; i < 1000; ++i) {
    sortedSequence(dataFile, 2 * (NMAX / 3) / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 50, 50, 0);
  }
}

// uniform insertion/deletion/search, operation interval random
void testcase7(std::ofstream &dataFile) {
  dataFile << NMAX << std::endl;
  randomSequence(dataFile, NMAX, 0, XMAX, 33, 33, 33);
}

// uniform insertion/deletion/search, operation interval segmented
void testcase8(std::ofstream &dataFile) {
  dataFile << (NMAX / 1000) * 1000 << std::endl;
  for (int i = 0; i < 1000; ++i) {
    randomSequence(dataFile, NMAX / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 33, 33, 33);
  }
}

// uniform insertion/deletion/search, operation interval segmented, adjacent operation 
void testcase9(std::ofstream &dataFile) {
  dataFile << (NMAX / 1000) * 1000 << std::endl;
  for (int i = 0; i < 1000; ++i) {
    neighborSequence(dataFile, NMAX / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 33, 33, 33);
  }
}

int main(int argc, char *argv[]) {
  int x = atoi(argv[1]);

  // output to dataFile
  std::string temp = "testcase" + std::to_string(x) + ".txt";
  const char *fileName = temp.c_str();
  std::ofstream dataFile;
  dataFile.open(fileName);

  if (!dataFile) {
    printf("Unable to open dataFile %s\n", fileName);
    exit(1); // call system to stop
  }

  srand(x * 3);
  e.seed(rand());
  std::cout << "seed " << e << "\n";
  std::cout << "percentage " << percentage(e) << "\n";

  // testcases
  switch (x) {
  case 1:
    testcase1(dataFile);
    break; 
  case 2:
    testcase2(dataFile);
    break; 
  case 3:
    testcase3(dataFile);
    break; 
  case 4:
    testcase4(dataFile);
    break;
  case 5:
    testcase5(dataFile);
    break; 
  case 6:
    testcase6(dataFile);
    break; 
  case 7:
    testcase7(dataFile);
    break; 
  case 8:
    testcase8(dataFile);
    break; 
  case 9:
    testcase9(dataFile);
    break; 
  }

 
  dataFile.close();
}