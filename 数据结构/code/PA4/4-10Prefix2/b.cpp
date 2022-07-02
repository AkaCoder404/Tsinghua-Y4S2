#include <iostream>
#include <string>

// KMP algorithm
// time complexity O(n + m)
// space complexity O(n)


// Z algorithm
// time complexity O(n + m)
// space complexity O(n)

int* zAlgorithm(std::string s) {
  int *Z = new int[s.length()];
  int leftBound = 0;
  int rightBound = 0;

  for (int k = 1; k < s.length(); k++) {
    if (k > rightBound) { // 
      leftBound = rightBound = k;
      while(rightBound < s.length() && s[rightBound] == s[rightBound - leftBound]) {
        rightBound++;
      }
      Z[k] = rightBound - leftBound; // length of LCP
      rightBound--;
    } else { // operating inside the box
      int k1 = k - leftBound;
      if(Z[k1] < rightBound - k + 1) { // value does not exceed rightBound
        Z[k] = Z[k1]; // copy over
      } else { // value does exceed right bond, check for more matches
        leftBound = k;
        while (rightBound < s.length() && s[rightBound] == s[rightBound - leftBound]) {
          rightBound++;
        }
        Z[k] = rightBound - leftBound;
        rightBound--;
      }
    }  
  }
  return Z;
}

int main() {
  std::string s;
  std::cin >> s;

  int *z = zAlgorithm(s);
  int sum = s.length(); // Z[0] is the length of string
  for(int i = 1; i < s.length(); i++) {
    sum += z[i];
  }
  std::cout << sum << "\n";
  // longest prefix suffix of searched string
  return 0;
}