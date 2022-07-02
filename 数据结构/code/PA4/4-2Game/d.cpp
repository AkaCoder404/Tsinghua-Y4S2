#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXN 100000
#define MOD 1000000007
int *difficulty; 

// A structure to represent a node in adjacency list
struct AdjListNode {
  int dest;
  int weight;
  struct AdjListNode *next;
};

// A structure to represent an adjacency list
struct AdjList {
  // Pointer to head node of list
  struct AdjListNode *head;
};

// A structure to represent a graph.
// A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph {
  int V;
  struct AdjList *array; 
};

// A utility function to create a new adjacency list node
struct AdjListNode *newAdjListNode(int dest, int weight) {
  struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
  newNode->dest = dest;
  newNode->weight = weight;
  newNode->next = NULL;
  return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph *createGraph(int V) {
  struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
  graph->V = V;

  // Create an array of adjacency lists of size V
  graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

  // Initialize each adjacency list as empty by making head as NULL
  for (int i = 0; i < V; ++i)
    graph->array[i].head = NULL;

  return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph *graph, int src, int dest, int weight) {
  // Add an edge from src to dest.
  // A new node is added to the adjacency list of src.
  // The node is added at the beginning 
  struct AdjListNode *newNode = newAdjListNode(dest, weight);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;
}

// Structure to represent a min heap node
struct MinHeapNode {
  int v;
  int dist;
};

// Structure to represent a min heap
struct MinHeap {
  int size;  // Number of heap nodes present currently
  int capacity; // Capacity of min heap

  // This is needed for decreaseKey()
  int *pos;
  struct MinHeapNode **array; 
};

// A utility function to create a new Min Heap Node
struct MinHeapNode *newMinHeapNode(int v, int dist) {
  struct MinHeapNode *minHeapNode = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
  minHeapNode->v = v;
  minHeapNode->dist = dist;
  return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap *createMinHeap(int capacity) {
  struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
  minHeap->pos = (int *)malloc(capacity * sizeof(int));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (struct MinHeapNode **)malloc(capacity * sizeof(struct MinHeapNode *));
  return minHeap;
}

// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
  struct MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
    smallest = left;

  if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
    smallest = right;

  if (smallest != idx) {
    // The nodes to be swapped in min heap
    MinHeapNode *smallestNode = minHeap->array[smallest];
    MinHeapNode *idxNode = minHeap->array[idx];

    // Swap positions
    minHeap->pos[smallestNode->v] = idx;
    minHeap->pos[idxNode->v] = smallest;

    // Swap nodes
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isEmpty(struct MinHeap *minHeap) {
  return minHeap->size == 0;
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
  if (isEmpty(minHeap))
    return NULL;

  // Store the root node
  struct MinHeapNode *root = minHeap->array[0];

  // Replace root node with last node
  struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
  minHeap->array[0] = lastNode;

  // Update position of last node
  minHeap->pos[root->v] = minHeap->size - 1;
  minHeap->pos[lastNode->v] = 0;

  // Reduce heap size and heapify root
  --minHeap->size;
  minHeapify(minHeap, 0);

  return root;
}

// Function to decrease dist value of a given vertex v. 
// This function uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap *minHeap, int v, int dist) {
  // Get the index of v in  heap array
  int i = minHeap->pos[v];

  // Get the node and update its dist value
  minHeap->array[i]->dist = dist;

  // Travel up while the complete tree is not hepified.
  // This is a O(Logn) loop
  while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
    // Swap this node with its parent
    minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
    minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
    swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
    // move to parent index
    i = (i - 1) / 2;
  }
}

// A utility function to check if a given vertex v is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v) {
  if (minHeap->pos[v] < minHeap->size)
    return true;
  return false;
}


// A utility function toReturn the shortest path distances
void dijkstra(struct Graph *graph, int src) {

  // Get the number of vertices in graph
  int V = graph->V;

  int *dist = new int[V];  // distance from source to target
  int *way = new int[V];   // number of shortest paths to vertex v
  int *pre = new int[V];   // the predecessor nodes

  struct MinHeap *minHeap = createMinHeap(V);

  // Initialize min heap 
  for (int v = 0; v < V; ++v) {
    dist[v] = INT_MAX;
    way[v] = 0;
    minHeap->array[v] = newMinHeapNode(v, dist[v]);
    minHeap->pos[v] = v;
  }

  // Make dist value of src vertex as 0 so that it is extracted first
  minHeap->array[src] = newMinHeapNode(src, dist[src]);
  minHeap->pos[src] = src;
  dist[src] = 0; // distance from starting point to itself is 0
  way[src] = 1;  // the number pf paths from starting point to itself is 1
  decreaseKey(minHeap, src, dist[src]);

  // Initially size of min heap is equal to V
  minHeap->size = V;

  // In the followin loop, min heap contains all nodes whose shortest distance is not yet finalized.
  while (!isEmpty(minHeap)) {
    // Extract the vertex with minimum distance value
    struct MinHeapNode *minHeapNode = extractMin(minHeap);

    // Store the extracted vertex number
    int u = minHeapNode->v;

    // Traverse through all adjacent vertices of u (the extracted vertex) and update their distance values
    struct AdjListNode *adjacent = graph->array[u].head;
    while (adjacent != NULL) {
      int v = adjacent->dest;

      // if node v has not been visited yet
      // and there is a path from u to v
      // and the current weight of path from src to v through u is smaller than current value of d[v]
      // d[u]+graph[u][v] < d[v]
      if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX) {
        if (adjacent->weight + dist[u] == dist[v]) {
          way[v] = (way[v] + way[u]) % MOD;    // there are multiple shortest paths to v
        }
        if (adjacent->weight + dist[u] < dist[v]) {
          dist[v] = dist[u] + adjacent->weight;  // update distance dist[v]
          pre[v] = u;                          // compute prcedessor nodes
          way[v] = way[u];                     // if shortest path is same, simply copy
        }

        // update distance value in min heap also
        decreaseKey(minHeap, v, dist[v]);
      }
      adjacent = adjacent->next;
    }
  }

  // print out results
  printf("%d\n%d\n", dist[graph->V - 1] + difficulty[graph->V - 1], way[graph->V - 1] % MOD) ;
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
  struct Graph *graph = createGraph(N);
  for (int i = 0; i < M; i++) {
    scanf("%d %d", &ver1, &ver2);
    addEdge(graph, ver1 - 1, ver2 - 1, difficulty[ver1 - 1]);
    addEdge(graph, ver2 - 1, ver1 - 1, difficulty[ver2 - 1]);
  }

  // dijkstra's algorithm
  dijkstra(graph, 0);

  return 0;
}