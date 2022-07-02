#include <iostream>
#include <string>
#define MAX_SIZE 20000000

// time complexity O(n^2) where n is original length of string
// space complexity O(n)

int main() {
  std::string s;
  std::cin >> s;

  int sum = s.length();
  // subsections S[i, n - 1]
  for (int i = 1; i < s.length(); i++) {
    int matchingPrefixCount = 0;
    for (int j = 0; j < s.length(); j++) {
      // compare S to S[i, n - 1] to find longest common prefix
      if (s[j] == s[i + j]) {
        matchingPrefixCount++;
      } 
      else break;
    }
    sum += matchingPrefixCount;
  }
  std::cout << sum;
  return 0;
}