#include <cstdio>
#include <limits.h>
#define MOD 1000000007
#define MAX_SIZE 1000
int n; // number of levels
int m; // number of roads
int *difficulty;
int totalMinDistanceCount = 1;
int totalMinDistanceValFinal = INT_MAX; // distance between 1 and n

int minDistance(int dist[], bool sptSet[]) {
  // Initialize min value
  int min = INT_MAX;
  int min_index;
  for (int v = 0; v < n; v++)
    if (sptSet[v] == false && dist[v] <= min) { // 
      min = dist[v];
      min_index = v;
    }
  return min_index;
}

void printSolution(int dist[]) {
  printf("Vertex \t Distance from Source\n");
  for (int i = 0; i < n; i++) {
    printf("%d \t\t %d\n", i + 1, dist[i]);
  }
  printf("minimum distance\n");
  printf("%d\n%d\n", (dist[n - 1] + difficulty[n - 1]), totalMinDistanceCount%MOD);
}

void dijkstra(int graph[MAX_SIZE][MAX_SIZE], int src) {
  int dist[n]; // The output array. dist[i] will hold the shortest distance from src to i

  bool sptSet[n]; // sptSet[i] will be true if vertex i is included in shortest
  // path tree or shortest distance from src to i is finalized

  // Initialize all distances as INFINITE and stpSet[] as false
  for (int i = 0; i < n; i++) {
    dist[i] = INT_MAX;
    sptSet[i] = false;
  }

  // Distance of source vertex from itself is always 0
  dist[src] = 0;

  // Find shortest path for all vertices
  for (int count = 0; count < n - 1; count++) {
    // Pick the minimum distance vertex from the set of vertices not
    // yet processed. u is always equal to src in the first iteration.
    int u = minDistance(dist, sptSet);

    // Mark the picked vertex as processed
    sptSet[u] = true;

    // Update dist value of the adjacent vertices of the picked vertex.
    for (int v = 0; v < n; v++) {
      if (v == n - 1) printf("update last %d\n", v);

      // Update dist[v] only if is not in sptSet, there is an edge from
      // u to v, and total weight of path from src to  v through u is
      // smaller than current value of dist[v]
      int newMinDistance = dist[u] + graph[u][v];
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && newMinDistance < dist[v]) {
        dist[v] = newMinDistance;
      }

      // for final node
      if (v == n - 1 && graph[u][v] && dist[u] != INT_MAX && newMinDistance <= dist[v]) {
        printf("v %d\n", v);
        if (newMinDistance < totalMinDistanceValFinal) { // updating last level
          totalMinDistanceCount = 1;
          totalMinDistanceValFinal = newMinDistance;
          printf("tmd %d\n", newMinDistance);
        }
        else if (newMinDistance == totalMinDistanceValFinal) {
          printf("tmds %d\n", newMinDistance);
          totalMinDistanceCount++;
        }
        dist[v] = newMinDistance;
      }
    }
  }

  // print the constructed distance array
  printSolution(dist);
}

int main() {
  scanf("%d %d", &n, &m);

  difficulty = new int[n];
  for (int i = 0; i < m; i++) {
    scanf("%d", &difficulty[i]);
  }

  int tmp1, tmp2;
  int graph[MAX_SIZE][MAX_SIZE];
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &tmp1, &tmp2);                     // connected levels
    graph[tmp1 - 1][tmp2 - 1] = difficulty[tmp1 - 1]; // difficulty as weight
    graph[tmp2 - 1][tmp1 - 1] = difficulty[tmp1 - 1];
  }

  dijkstra(graph, 0);
}