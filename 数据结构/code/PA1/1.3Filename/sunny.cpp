#include "stdio.h"

// https://en.wikipedia.org/wiki/Edit_distance, longest common subsequence -> insertion and deletion but not subsitution
// https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
// dynamic programming problem
int lcs(char *a, char *b, int n, int m) {
  int len[2][m + 1];
  bool index;
  for (int i = 0; i <= n; ++i) {
    index = i & 1;
    for (int j = 0; j <= m; ++j) {
      if (i == 0 || j == 0) {
        len[index][j] = 0;
      } else if (a[i - 1] == b[j - 1]) {
        len[index][j] = len[1 - index][j - 1] + 1;
      } else {
        len[index][j] = (len[1 - index][j] > len[index][j - 1]) ? len[1 - index][j] : len[index][j - 1];
      }
    }
  }
  return len[index][m];
}

int main() {
  int m, n, k;
  char a[501000];
  char b[501000];

  scanf("%d %d %d %s %s", &n, &m, &k, a, b);
  int lcsval = lcs(a, b, n, m);     // find longest common subsequence and subtract from total string = how many insertions/delitions there must be
  int sol = n - lcsval + m - lcsval;
  if (sol <= k) {
    printf("%d\n", sol);
  } else {
    printf("%d\n", -1);
  }
  return 0;
}