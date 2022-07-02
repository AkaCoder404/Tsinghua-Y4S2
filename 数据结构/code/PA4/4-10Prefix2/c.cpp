#include <iostream>
// #include <string>
#include <cstring>

#define SIZE 20000000
char s[SIZE];
int Z[SIZE];
int length;

void zAlgorithm() {
  int leftBound = 0;
  int rightBound = 0;
  for (int k = 1; k < length; k++) {
    if (k > rightBound) {
      leftBound = rightBound = k;
      while(rightBound < length && s[rightBound] == s[rightBound - leftBound]) {
        rightBound++;
      }
      Z[k] = rightBound - leftBound;
      rightBound--;
    } else { // operating inside the box
      int k1 = k - leftBound;
      if(Z[k1] < rightBound - k + 1) { // value does not exceed rightBound
        Z[k] = Z[k1];
      } else { // see if anymore matches
        leftBound = k;
        while (rightBound < length && s[rightBound] == s[rightBound - leftBound]) {
          rightBound++;
        }
        Z[k] = rightBound - leftBound;
        rightBound--;
      }
    }  
  }
}

int main() {
  scanf("%s", s);
  length = strlen(s);
  zAlgorithm();
  long long int sum = length;
  for(int i = 1; i < length; i++) {
    sum += Z[i];
  }
  printf("%lld\n", sum);
  return 0;
}