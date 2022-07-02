#include <stdio.h>
#define NMAX 20000000
#define NMIN 500000
#define KMAX 500000
#define LEN 64

struct ListNode {
  int value;
  ListNode *next;
  ListNode() : next(nullptr) {}
  ListNode(int e) : value(e), next(nullptr) {}
};

class Queue {
  public:
  ListNode *header, *trailer;
  Queue() : header(nullptr), trailer(nullptr) {};
  void enqueue(int e) {
    trailer->next = new ListNode(e);
    trailer = trailer->next;
  }
  ListNode *front() {
    return header->next;
  }
  void dequeue() {
    ListNode *tmp = header;
    header = header->next;
    delete tmp;
  }
};

struct Node {
  int zero, one; // left child and right child
  int childs;    // number of child nodes till termination of string
  Queue *queue;
  Node() : zero(0), one(0), childs(0), queue(NULL) {};
};

Node memory[NMAX];    
class Trie {
  public:
  int root;
  int nodeCount = 1;
  Trie() : root(nodeCount++){};
  // insertion
  void insert(int id, char *a) {
    Node *current = memory + root;
    for (int i = 0; i < LEN; i++) {
      current->childs++;
      if (a[i] == '1') {
        if (current->one == 0) { // does not match, create a new branch
          current->one = nodeCount++;
        }
        current = memory + current->one;
      } else if (a[i] == '0') { // does not match, create a new branch
        if (current->zero == 0) {
          current->zero = nodeCount++;
        }
        current = memory + current->zero;
      }
    }
    // one final node may represent multiple component
    if (current->queue == NULL) {
      current->queue = new Queue();
      current->queue->header = new ListNode();
      current->queue->trailer = current->queue->header;
    }
    current->queue->enqueue(id);
    current->childs++;

  }

  void remove(char *a) {
    Node *current = memory + root;
    for (int i = 0; i < LEN; i++) {
      current->childs--;
      if (a[i] == '1') {
        current = memory + current->one;
      } else if (a[i] == '0') {
        current = memory + current->zero;
      }
    }
    current->queue->dequeue();
    current->childs--;
  }

  int search(int target, char *a) {
    Node *current = memory + root;
    for (int i = 0; i < LEN; i++) {
      if (a[i] == '1') {
        // has rightChild of zero and rightChild has children
        if (current->zero != 0 && (memory + current->zero)->childs) // finding first difference
          current = memory + current->zero;
        else // has only leftChild of one, keep going along same branch
          current = memory + current->one;
      } else if (a[i] == '0') {
        // has leftChild of one and leftChild has children
        if (current->one != 0 && (memory + current->one)->childs) // finding first difference
          current = memory + current->one;
        else // only has rightChild of zero, keep going along same branch
          current = memory + current->zero;
      }
    }

    // when reach leaf/terminal node
    // return (terminal[current->one].front()->value == target)
    //            ? terminal[current->one].front()->next->value // node after front
    //            : terminal[current->one].front()->value;      // node after header
    return (current->queue->front()->value == target)  
          ? current->queue->front()->next->value 
          : current->queue->front()->value;
  }
} trie;

int main() {
  int N, K;
  scanf("%d %d", &N, &K);
  char circuit[N][LEN + 1];
  for (int i = 0; i < N; i++) {
    scanf("%s", circuit[i]);
  }

  // build partial tree looking foward
  for (int i = 0; i <= K && i < N; i++) {
    trie.insert(i, circuit[i]);
  }

  // get max for each element
  for (int i = 0; i < N; i++) {
    int left = i - K - 2; // compare left
    if (left >= 0) {
      trie.remove(circuit[left]);
    }
    int right = i + K + 1; // compare right
    if (right < N) {
      trie.insert(right, circuit[right]);
    }
    printf("%d\n", trie.search(i, circuit[i]));
  }

  return 0;
}
