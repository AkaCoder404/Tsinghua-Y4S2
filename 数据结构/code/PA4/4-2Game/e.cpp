#include <stdio.h>  // scanf,printf
#include <stdlib.h> // malloc
#define MAXN 100000
#define MOD 1000000007
#define INT_MAX 2147483647
int *difficulty;
int *dist;
int *way;

struct AdjListNode {
  int destinationNode; // destinationNode
  int edgeWeight;
  AdjListNode *next;
  AdjListNode(int dest, int weight) : destinationNode(dest), edgeWeight(weight), next(NULL) {};
};

struct AdjList {
  AdjListNode *head, *trailer;
};

class Graph {
  public:
  int numVertices;
  AdjList *array; // array of AdjList
  Graph(){};
  Graph(int _numVertices) : numVertices(_numVertices) {
    array = (AdjList *)malloc(_numVertices * sizeof(AdjList));
    for (int i = 0; i < _numVertices; ++i)
      array[i].head = NULL;
  };
  ~Graph(){};

  void addEdge(int src, int dest, int weight) {
    // add an edge from src to dest at the beggining of adjacency list of src.
    AdjListNode *newNode = new AdjListNode(dest, weight);
    newNode->next = array[src].head;
    array[src].head = newNode;
  }
};

struct MinHeapNode {
  int v;
  int dist;
  MinHeapNode(int _v, int _dist) : v(_v), dist(_dist) {}; 
};

struct MinHeap {
  int size;
  int capacity;
  int *pos;
  MinHeapNode **array; // array of minheapnode pointers
};

MinHeap *createMinHeap(int capacity) {
  MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
  minHeap->pos = (int *)malloc(capacity * sizeof(int));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
  return minHeap;
}

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
  MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

void minHeapify(MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist) {
    smallest = left;
  }

  if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist) {
    smallest = right;
  }

  if (smallest != idx) {
    // nodes to be swapped in minHeap
    MinHeapNode *smallestNode = minHeap->array[smallest];
    MinHeapNode *idxNode = minHeap->array[idx];

    // Swap positions
    minHeap->pos[smallestNode->v] = idx;
    minHeap->pos[idxNode->v] = smallest;

    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

bool isEmpty(MinHeap *minHeap) {
  return minHeap->size == 0;
}

MinHeapNode *extractMin(MinHeap *minHeap) {
  if (isEmpty(minHeap))
    return NULL;

  MinHeapNode *root = minHeap->array[0];
  MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
  minHeap->array[0] = lastNode;

  minHeap->pos[root->v] = minHeap->size - 1;
  minHeap->pos[lastNode->v] = 0;
  --minHeap->size;
  minHeapify(minHeap, 0); // heapify at route
  return root;
}

void decreaseKey(MinHeap *minHeap, int v, int dist) {
  int i = minHeap->pos[v];
  minHeap->array[i]->dist = dist;

  while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
    minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
    minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
    swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

bool isInMinHeap(MinHeap *minHeap, int v) {
  if (minHeap->pos[v] < minHeap->size)
    return true;
  return false;
}

void dijkstra(Graph *graph, int src) {
  int V = graph->numVertices;

  dist = new int[V]; // distance from source to target
  way = new int[V];  // number of shortest paths to vertex v
  // pre = new int[V];   // the predecessor nodes

  // initialize heap
  MinHeap *minHeap = createMinHeap(V);
  for (int v = 0; v < V; ++v) {
    dist[v] = INT_MAX;
    way[v] = 0;
    minHeap->array[v] = new MinHeapNode(v, dist[v]);
    minHeap->pos[v] = v;
  }

  // make dist value of src vertex as 0 so that it is extracted first
  minHeap->array[src] = new MinHeapNode(src, dist[src]);
  minHeap->pos[src] = src;
  dist[src] = 0; // distance from starting point to itself is 0
  way[src] = 1;  // the number pf paths from starting point to itself is 1
  decreaseKey(minHeap, src, dist[src]);

  minHeap->size = V;

  // minHeap contains nodes that have not been visited
  while (!isEmpty(minHeap)) { // as long is minHeap contains nodes to be visited
    MinHeapNode *minHeapNode = extractMin(minHeap);
    int u = minHeapNode->v;

    // traverse through all adjacent vertices of u and update their distance values
    AdjListNode *adjacent = graph->array[u].head;
    while (adjacent != NULL) {
      int v = adjacent->destinationNode;

      // if node v has not been visited yet
      // and there is a path from u to v
      // and the current weight of path from src to v through u is smaller than current value of d[v]
      // d[u]+graph[u][v] < d[v]
      if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX) {
        if (adjacent->edgeWeight + dist[u] == dist[v]) {
          way[v] = (way[v] + way[u]) % MOD; // there are multiple shortest paths to v
        }
        if (adjacent->edgeWeight + dist[u] < dist[v]) {
          dist[v] = dist[u] + adjacent->edgeWeight; // update distance dist[v]
          // pre[v] = u;                          // compute prcedessor nodes
          way[v] = way[u]; // if shortest path is same, simply copy
        }

        // also update distance value in min heap
        decreaseKey(minHeap, v, dist[v]);
      }
      adjacent = adjacent->next;
    }
  }
}

int main() {
  // number of nodes and edges
  int N, M;
  scanf("%d %d", &N, &M);

  // level difficulties
  difficulty = new int[N];
  for (int i = 0; i < N; i++) {
    scanf("%d", &difficulty[i]);
  }

  // create graph
  int ver1, ver2;
  int weight;
  Graph *graph = new Graph(N);
  for (int i = 0; i < M; i++) {
    scanf("%d %d", &ver1, &ver2);
    // directed graph
    graph->addEdge(ver1 - 1, ver2 - 1, difficulty[ver1 - 1]);
    graph->addEdge(ver2 - 1, ver1 - 1, difficulty[ver2 - 1]);
  }

  // dijkstra's algorithm
  dijkstra(graph, 0);

  printf("%d\n%d\n", dist[graph->numVertices - 1] + difficulty[graph->numVertices - 1], way[graph->numVertices - 1] % MOD);
  return 0;
}