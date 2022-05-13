#include "crc32.h"
#include <stdio.h>
#include <cstring>


char encoding[18] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
  't', 's', 'i', 'n', 'g', 'h', 'u', 'a'
};

int main() {
  int n; 
  scanf("%d", n);

  unsigned char salt[5];
  scanf("%c", salt);
  int saltLen = 0;

  // length of unsigned char (can't use strlen)
  while(salt[saltLen]) saltLen++;


  // read in encrypted
  long long int encryption[n];
  for (int i = 0; i < n; i++) {
    scanf("%lld", encryption[i]);
  } 


  return 0;  
}