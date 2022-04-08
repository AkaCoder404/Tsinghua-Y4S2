#include <cstdio>
#include <stdio.h>
#include <string.h>

const int X_MAX = 2000010;
long long value[X_MAX] = {0};

void pri(int arr[], int arr2[], long long int arr3[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr2[i]);
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%lld ", arr3[i]);
  }
  printf("\n");
}

int main() {
  int n; // number of total days
  scanf("%d", &n);

  int *x = new int[n];             // confirmed cases per day
  long long *m = new long long[n]; // number of days traced backwards
  for (int i = 0; i < n; i++) scanf("%d", &x[i]);
  for (int i = 0; i < n; i++) scanf("%lld", &m[i]);

  int *que_max = new int[n]; memset(que_max, 0, n*sizeof(que_max[0])); // number of confirmed cases
  int *que_day = new int[n]; memset(que_day, 0, n*sizeof(que_day[0])); // respective days

  int head = 0, tail = 1; 

  que_max[0] = x[0];
  for (int i = 1; i < n; ++i) {
    // Check 1: empty smaller elements from the end of the queue
    while (x[i - 1] >= que_max[tail - 1] && tail > head) {
      tail--;
    }
    que_max[tail] = x[i - 1];
    que_day[tail++] = i - 1;
    // Check 2: empty out of time elements from the front of the queue
    while (i - m[i] > que_day[head]) {
      head++;
    }
    value[que_max[head]]++;
    // printf("i = %d\n", i);
    // pri(que, que_day, value, n);
  }

  // prefix sum
  for (int i = 1; i < X_MAX; i++) value[i] += value[i - 1];

  int t; // number of threshold queries
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    long long p, q;
    scanf("%lld%lld", &p, &q);
    if (p > X_MAX) p = X_MAX;
    if (q > X_MAX) q = X_MAX;

    // consider edge cases
    if (q == 0) {
      printf("%d %d\n", 0, 0);
      continue;
    }
    if (p == 0) {
      printf("%d %lld\n", 0, value[q - 1] + 1);
      continue;
    }

    printf("%lld %lld\n", value[p - 1] + 1, value[q - 1] - value[p - 1]);
  }

  return 0;
}
