
// Directions
// From the 34th century to the 72nd century, Moon City was in the outbreak of the new respiratory disease DIVOC-34. 
// Every day in Moon City was one of three states: 
// - low risk
// - medium risk
// - high risk.


// IVOC-34 is a viral disease, but it does not produce permanent antibodies after getting sick, and even a person may recover after being diagnosed today, and be diagnosed again tomorrow. 
// Of course, each person is diagnosed at most once a day. 
// Fortunately, DIVOC-34 is not lethal, and the only symptom people have when they get it is constant hiccups. 
// Of course, this still has a great impact on people's daily life!

// Moon City has a population of 2 million, people are immortal, and no one is born or cloned in the city. 
// And in order to prevent the spread of the DIVOC-34 epidemic, the Solar System Security Council decided to implement an extreme city closure, and there is no population movement between inside and outside the Moon City.


// We now study n consecutive days starting from the day when the first confirmed case appeared in Moon City. 
// The number of confirmed cases on day i is xi.

// The Moon City Council decides on two thresholds p and q for assessing risk "(0≤p<q)"


// On the ith day, we judge the risk level of Moon City as follows: 
// consider the mi days before the ith day 
// (that is, from the i−mi day to the i−1th day, 
// note that the diagnosis data of the day has not yet been counted on the ith day
//  If
//  0≤k<p, Moon City is low risk; 
//  p≤k<q, Moon City is medium risk; 
//  q≤k, Moon City is high risk.


// Now the Moon City Council wants to know how the number of 
// low risk, 
// medium risk and 
// high risk 
// days will change in the n days if we change the value of the threshold p,q

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