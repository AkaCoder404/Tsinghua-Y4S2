#include <iostream>
class process {
public:
  int id;
  int priority;
  int creationTime;
  int executionTime;
public:
  process() : id(0), priority(0), creationTime(0), executionTime(0){};
  process(int _id, int _priority, int _creationTime, int _executionTime)
      : id(_id), priority(_priority), creationTime(_creationTime), executionTime(_executionTime){};
};

// binary heap construction O(n)
// delete O(log(n)), // insert O(log(n))
// top/peek O(1)

struct node {
  // node *parent;
  // node *left;
  // node *right;
  process *data;

  friend bool operator>(const process &lhs, const process &rhs);
};
bool operator> (const process &lhs, const process &rhs){
  if (lhs.priority > rhs.priority) {// order by priority 
    return true;
  }
  else if (lhs.priority == rhs.priority) { // if equal priority, compare execution time
    if (lhs.creationTime < rhs.creationTime) { // earlier execution time has higher priority
      return true;
    }
    
    // if execution time, is same, process id
    else if (lhs.creationTime == rhs.creationTime) {
      if (lhs.id < rhs.id) { // smaller id has higher higher priority
        return true;
      }
    }
  }
  return false; // smaller priority
}

struct MinHeap {
  int size;
  int capacity;
  // implement using array
  node **array;
};

node *newNode(process *data) {
  node *temp = (node *)malloc(sizeof(node)); // allocate space
  // temp->left = NULL;
  // temp->right = NULL;
  temp->data = data;
  return temp;
}

MinHeap *createMinHeap(int capacity) {
  MinHeap *minheap = (MinHeap *)malloc(sizeof(MinHeap)); // allocate space
  minheap->size = 0;
  minheap->capacity = capacity;
  minheap->array = (node **)malloc(minheap->capacity * sizeof(node *));
  return minheap;
}

void swapMinHeapNode(node **a, node **b) {
  node *temp = *a;
  *a = *b;
  *b = temp;
}

void minHeapify(MinHeap *minHeap, int idx) {
  int smallest = idx;      // parent
  int left = 2 * idx + 1;  // left child
  int right = 2 * idx + 2; // right child

  // if left child has higher priority than parent
  if (left < minHeap->size && (*(minHeap->array[left]->data) > *(minHeap->array[smallest]->data))) {
    smallest = left;
  }

  // if right child has higher priority than parent
  if (right < minHeap->size && (*(minHeap->array[right]->data) > *(minHeap->array[smallest]->data))) {
    smallest = right;
  }

  // bubble up and heapify until no more bigger
  if (smallest != idx) {
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isSizeOne(MinHeap *minHeap) {
  return (minHeap->size == 1);
}

node *extractMin(MinHeap *minHeap) {
  node *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1]; // move node furthest to the right to root, then heapify

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}

void insertMinHeap(MinHeap *minHeap, node *minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && (*(minHeapNode->data) > *(minHeap->array[(i - 1) / 2]->data))) {
    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap *minHeap) {
  int n = minHeap->size - 1;
  int i;
  for (i = (n - 1) / 2; i >= 0; --i) {
    minHeapify(minHeap, i);
  }
}

int main() {
  int n;
  std::cin >> n;
  int id, priority, creationTime, executionTime;
  int totalRunTime = 0;
  // create and build minheap
  MinHeap *minHeap = createMinHeap(n);
  process processes[n];
  for (int i = 0; i < n; i++) {
    // std::cin >> id >> priority >> creationTime >> executionTime;
    scanf("%d %d %d %d", &id, &priority, &creationTime, &executionTime);
    processes[i].id = id;
    processes[i].priority = priority;
    processes[i].creationTime = creationTime;
    processes[i].executionTime = executionTime;
    if (i == 0) totalRunTime = creationTime;
    totalRunTime += executionTime;
    // minHeap->array[i] = newNode(new process(id, priority, creationTime, executionTime));
  }

  minHeap->size = 0;
  buildMinHeap(minHeap);

  int time = processes[0].creationTime;
  int i = 0;
  process *currentProcess = new process(0, -1, 0, 0); 
  while (time < totalRunTime) {
    // insert processes where creation time is less than current time 
    while (i < n && processes[i].creationTime <= time) {
      insertMinHeap(minHeap, newNode(&processes[i])); 
      i++;
    }
    // pick the one with best priority, peek at max
    process *temp = minHeap->array[0]->data;
    if ((*temp) > (*currentProcess)) { // if max priority is > temp priority, choose that
      currentProcess = temp;
    }

    currentProcess->executionTime--; // decrease execution time

    if (currentProcess->executionTime == 0) {
      extractMin(minHeap);
      printf("%d %d\n", currentProcess->id, time + 1);
      currentProcess = minHeap->array[0]->data; // current equals next max
    }
    time++;
  }
  

  return 0;
}
