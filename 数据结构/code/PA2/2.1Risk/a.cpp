
/

#include <cstdio>
// #include <stdio.h>
// #include <iostream>


// implement queap : queue + heap + getMax
const int N = 1e7;
int day[N]; 
int max[N]; 


int main() {
  long long int n;
  day[0] = 0;
  max[0] = 0;

  // std::ios::sync_with_stdio(false); can't use this

  // number of days
  scanf("%lld", &n);
  // std::cin >> n;

  // confirmed cases per day

  for (int i = 1; i <= n ; i++) {
    scanf("%d", &day[i]);
    // std::cin >> day[i];
  }

  // number of days back when assessing risk on day i
  int d;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &d);
    
    int j = 1;
    int max_case = day[i - 1];
    while (d--) {
      if (day[i - j] > max_case) max_case = day[i - j];
      j++;
    }
    max[i] = max_case;
  }


  // number of queries T
  long long int T;
  scanf("%lld", &T);
  long long int p, q;

  int low, mid, hig;
  for (int i = 0; i < T; i++) {
    scanf("%lld %lld", &p, &q);

    // see how risk
    low = mid = hig = 0;
    for (int j = 1; j <= n; j++ ) {
      if (max[j] < p) low++; 
      else if (p  <= max[j] && max[j] < q) mid++;
      else hig++;

      if ((low + mid + hig) == n) { // we only need two of them
        printf("%d %d\n", low, mid);
        break;
      }
    } 

  }

  // for (int i = 1; i <= n; i++) {
  //   printf("%d ", max[i]);
  // }

  return 0;
}

// 
// 8
// 1 1000 2 3000 8 7 6 4
// 1 2 3 3 3 4 3 2
// 1 
// 7 9
// 3 1