#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <cstring>

// time complexity O(64n * k)
// space complexity O(64n)

// convert string of 0 and 1's to uint64_t
uint64_t convertStringToInt(const char *s) {
  uint64_t res = 0;
  size_t i, n;
  for (i = 0, n = strlen(s) - 1; i < n; ++i) {
    res = (res | (unsigned int)(s[i] - '0')) << 1;
  }
  return res;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  char buffer[65];
  uint64_t circuit[n];
  for (int i = 0; i < n; i++) {
    std::cin >> buffer;
    circuit[i] = convertStringToInt(buffer);
  }

  // 
  for (int i = 0; i < n; i++) {
    uint64_t max = 0;
    int maxIndex = 0;
    int j = 1;
    while (j <= k + 1) {
      // check after (输出最靠前的)
      if ((i + j < n) && (circuit[i] ^ circuit[i + j]) > max) {
        max = (circuit[i] ^ circuit[i + j]);
        maxIndex = i + j;
      }
      // check before (输出最靠前的)
      if( (i - j >= 0) && (circuit[i] ^ circuit[i - j]) >= max) {
        max = (circuit[i] ^ circuit[i - j]);
        maxIndex = i - j;
      }
      //  std::cout << max << "\n";
      j++;
    }
    // std::cout << i << ":" << maxIndex << "\n";
    std::cout << maxIndex << "\n";
  }

  return 0;
}