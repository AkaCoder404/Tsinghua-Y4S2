#include <cstdio>
#include <iostream>
#include <limits.h>
#define MAXN 5000
#define MOD 1000000007


int N, M;
int graph[MAXN][MAXN];
int difficulty[MAXN];

//先求最短距离
bool vis[MAXN] = {false}; // indicates whether or not the node has been visited
int d[MAXN];              // distance from source to target

int pre[MAXN]; // predecessor node of v
int way[MAXN]; // number of shortest paths from starting point s to verex u be num[u]

int minDistance() {
  int u = -1, MIN = INT_MAX;    // this vertex of the current shortest path
  for (int j = 0; j < N; j++) { // find the shortest path in the node that has not been traversed
    // vis[j] == false => not yet traversed
    // shortest path d[j] < MIN, update
    if (vis[j] == false && d[j] < MIN) { //更新 MIN 值
      u = j;
      MIN = d[j];
    }
  }
  return u;
}

void dijkstra(int s) {
  std::fill(d,d+MAXN,INT_MAX); // assigns entire d array to INT_MAX
  std::fill(way,way+MAXN,0);  // set the number of paths from source to vertex to be 0

  d[s] = 0;   // distance from starting point to itself is 0
  way[s] = 1; // the path from starting point to itself is 1
  for (int i = 0; i < N; i++) {
    int u = minDistance();

    if (u == -1)
      return;
    vis[u] = true; //对节点u标记为已访问
    for (int v = 0; v < N; v++) {
      // if node v has not been visited yet
      // and there is a path from u to v
      // and the current weight of path from src to v through u is smaller than current value of d[v]
      // d[u]+graph[u][v] < d[v]
      if (vis[v] == false && graph[u][v] != INT_MAX) {
        if (d[u] + graph[u][v] == d[v]) {
          way[v] = (way[v] + way[u]) % MOD; // there are multiple shortest paths to v
				}
        if (d[u] + graph[u][v] < d[v]) {
          d[v] = d[u] + graph[u][v]; // update distance d[v]
          pre[v] = u;                // compute precedecessor nodes
          way[v] = way[u];           // if the shortest path is the same, you can simply copy
        }
      }
    }
  }
}

int main() {
  scanf("%d %d", &N, &M);
  std::fill(graph[0], graph[0] + MAXN * MAXN, INT_MAX); // initiallize graph

  for (int i = 0; i < N; i++) { // difficulties
    scanf("%d", &difficulty[i]);
  }

  // int i,j;
  int ver1, ver2;
  int weight;
  for (int i = 0; i < M; i++) {
    scanf("%d %d", &ver1, &ver2);
    graph[ver1 - 1][ver2 - 1] = difficulty[ver1 - 1]; // edge is simply difficulty of current level
		graph[ver2 - 1][ver1 - 1] = difficulty[ver2 - 1];
  }

  dijkstra(0);
  printf("%d\n%d\n", d[N - 1] + difficulty[N - 1], way[N - 1] % MOD);
}
