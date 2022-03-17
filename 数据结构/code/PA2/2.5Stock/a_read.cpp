
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <cstdlib> // atoi
#include <iostream>

int main() {
  int N;
  std::cin >> N;
  std::cin.ignore();
  N = N << 1; // 2 * N

  for (int i = 0; i < N; i++) {

    int D = -1; // days
    int X = -1; // value

    char name[256];
    // std::cin.ignore();
    std::cin.getline(name, 256);

    int posn = -1;
    int len = strlen(name);
    char *space_ptr = (strchr(name, ' '));
    if (space_ptr != NULL)
      posn = space_ptr - name;

    if (posn == -1) {
      char subrow[posn];
      memcpy(subrow, &name[0], len);
      subrow[len] = '\0';
      D = atoi(subrow);
    } else {
      // read first character
      char subrow[posn];
      memcpy(subrow, &name[0], posn);
      subrow[posn] = '\0';
      // printf("subrow %s\n", subrow);

      D = atoi(subrow);
      // printf("Input 1 [%d]\n", D);
      // read second character
      int len_of_second = strlen(name) - posn;
      char subsubrow[len_of_second];
      memcpy(subsubrow, &name[posn + 1], len_of_second);
      subsubrow[len_of_second] = '\0';
      X = atoi(subsubrow);
      // printf("Input 2 [%d]\n", X);
    }
  }

  printf("%d", 5000);
  return 0;
}