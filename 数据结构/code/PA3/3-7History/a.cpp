#include <cstdio>
#define N 10000000

int hash[N] = {0};

int main() {
  int n;
  scanf("%d", &n);

  int i; // input
  int lastAnswer = 0;
  for (int j = 1; j < n + 1; j++) {
    scanf("%d", &i);
    // student id is equal to input xor output
    int student = i ^ lastAnswer;
    int newAnswer;

    // if student does not exist yet
    if (hash[student] == 0) {
      newAnswer = j;
    } else { // if student already exists
      newAnswer = hash[student];
    }
    hash[student] = j; // set last answer to this time

    printf("%d\n", newAnswer);
    lastAnswer = newAnswer;
  }
}