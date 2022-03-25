#include "cstring"
#include "stdio.h"

// https://en.wikipedia.org/wiki/Edit_distance, longest common subsequence -> insertion and deletion but not subsitution
// https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
// https://www.enjoyalgorithms.com/blog/longest-common-subsequence
// dynamic programMINg problem

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define Min(a, b) ((a) > (b) ? (a) = (b) : 0)
#define ABS(a) ((a) < 0 ? (-1 * a) : (a))

int dp[2][10000];

// spaced optimized bottom up approach using 2D array
int lcs(char *a, char *b, int n, int m, int k) {
  int len[2][m + 1];
  memset(len, 0, sizeof(len));

  bool index;
  for (int i = 0; i <= n; ++i) {
    index = i & 1; // even or odd
    for (int j = 0; j <= m; ++j) {
      if (i == 0 || j == 0) { // initialize borders as zero
        len[index][j] = 0;
      } else if (a[i - 1] == b[j - 1]) { // characters match -> diagonal + current
        len[index][j] = len[1 - index][j - 1] + 1;
      } else { // dont match, take the MAX of values to bottom and to the right
        len[index][j] = MAX(len[1 - index][j], len[index][j - 1]);
      }
    }
  }

  int sol = n - len[index][m] + m - len[index][m];
  if (sol <= k) return sol;
  else return -1;
}

int lcs_k(char *a, char *b, int n, int m, int k) {
  
  dp[0][99] = 0;
  for (int i = 1; i <= k; ++i) {
    dp[0][99 + i] = i;
    dp[i % 2][99 - i] = i;
  }


  bool index;
  for (int i = 1; i <= n; ++i) {
    index = i & 1;
    for (int j = MAX(1, i - k), je = MIN(m, i + k); j <= je; ++j) {
      dp[index][j - i + 99] = (a[i] == b[j] ? dp[1-index][j - i + 99] : i + j);
      if (ABS(j - i + 1) <= k)
        Min(dp[index][j - i + 99], dp[1-index][j - i + 1 + 99] + 1);
      if (ABS(j - 1 - i) <= k)
        Min(dp[index][j - i + 99], dp[index][j - 1 - i + 99] + 1);
    }
  }

  // for(int i = 0; i < (990); i++) {
  //   for(int j = 0; j < 990; j++) {
  //     printf("%d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }

  // for(int i = 0; i < m - n + 99; i++) printf("%d ", dp[index][i]);
  // printf("\n");
  if (dp[index][m - n + 99] <= k)
    return dp[index][m - n + 99];
  else
    return -1;

  
}

// int lcs_bottom_up(char *a, char *b, int n, int m, int k) {
//   // int dp[strlen(a) + 1][strlen(b) + 1];
//   // memset(dp, 0, sizeof(dp));

//   // time complexity is (O(MN)), also memory complexity, memory surpasses
//   for (int i = n - 1; i >= 0; --i) {
//     for (int j = m - 1; j >= 0; --j) {
//       if (a[i] == b[j]) {
//         dp[i][j] = 1 + dp[i + 1][j + 1];
//       } else {
//         dp[i][j] = MAX(dp[i][j + 1], dp[i + 1][j]);
//       }
//     }
//   }

//   // result at dp[0][0]
//   int sol = n - dp[0][0] + m - dp[0][0];
//   if (sol <= k) return sol;
//   else return -1;

// }

int main() {
  int m, n, k;

  // scanf("%d %d %d %s %s", &n, &m, &k, a, b);
  scanf("%d %d %d", &n, &m, &k);
  char a[n];
  char b[m];
  scanf("%s %s", a, b);


  // int lcsval = lcs(a, b, n, m, k);
  int lcsval = lcs_k(a, b, n, m, k); // find longest common subsequence and subtract from total string = how many insertions/deletions there must be
  // int lcsval1 = lcs(a, b, n, m); // find lcs using bottom up arroach with space reduction
  // int lcsval2 = lcs_bottom_up(a, b, n, m, k); // find lcs using bottom up approach
  
  printf("%d\n", lcsval);
  // printf("%d\n", lcsval2);
  return 0;
}