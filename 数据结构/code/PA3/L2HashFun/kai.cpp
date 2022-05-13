#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

const int size = 620000;
string lines[size];

int main() {
  fstream input, output;
  // string lines[size];
  // int id[10000];


  int insertion_num, query_num, filechoice;

  // parameters
  cout << " Number of Insertion / Query " << endl;
  cin >> insertion_num >> query_num;

  cout << " From which dataset? (1:poj | 2:hdu)" << endl;
  cin >> filechoice;

  // read all lines from file and store in vector
  int totline = 0;
  srand(time(0));

  // open file
  if (filechoice == 1) {
    input.open("./datasets/poj.txt", ios::in);
  } else {
    input.open("./datasets/hdu.txt", ios::in);
  }

  // output.open("example.txt", ios::out);

  string line, a, user_name, id, b;

  if (!input) {
    cout << "No input file!";
  } else {
    // count total line of file
    while (!input.eof()) {
      //  getline(input,line);
      // cout << line << endl;
      input >> a >> user_name >> id >> b;
      line = user_name + " " + id;
      lines[totline] = line;
      totline++;
      if (totline > 1000) break;
    }
    cout << totline << endl;
    cout << lines[0] << endl;

    // store into array
    // for (int i = 0; i < totline; i++) {
    //   while (!input.eof()) {
    //     input >> a >> user_name >> id >> b;
    //     line = user_name + " " + id;
    //     lines[i] = line;
    //   }
    // }
    // cout << lines[0] << endl;
  }

  // write files
  // -- write insertions

  // for (int i = 0; i < insertion_num; i++ ){

  // output << "Hi"<< endl;
  // input >> a >> user_name >> id >> b;
  // line = user_name + " " +id;
  // getline(input,line);
  // output << line <<endl;

  // }
  // output.close();

  input.close();

  return 0;
}