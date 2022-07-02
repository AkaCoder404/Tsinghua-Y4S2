#include <stdio.h>
using namespace std;

// time complexity O(64n)
// space complexity O(n)

// implement node 
struct listnode {
  listnode *next;
  int val;
  listnode()
      : next(nullptr) {}
  listnode(int e)
      : val(e), next(nullptr) {}
};

// implement queue using list
struct queue {
  listnode *header, *last;
  void enqueue(int e) {
    last = last->next = new listnode(e);
  }
  int front() {
    return header->next->val;
  }
  void dequeue() {
    listnode *tmp = header;
    header = header->next;
    delete tmp;
  }
  bool empty() {
    return header == last;
  }
};

struct Node {
  int zero, one; // 对应左孩子lc与右孩子rc
  int childs;    // 终止节点数目
};

Node memory[28000000];
int applied = 1;

queue leafs[500010];
int leaf_cnt = 0;

// implment Trie
class Trie {
  public:
  int root;
  Trie() {
    root = applied++;
  }

  // insertion
  void insert(int id, char *a) {
    Node *cur = memory + root;
    for (int i = 0; i < 64; ++i) {
      cur->childs++;
      if (a[i] - '0') {  // if '1'
        if (cur->one == 0) {
          cur->one = applied++;
        }
        cur = memory + cur->one;
      } else {          // if '0'
        if (cur->zero == 0) {
          cur->zero = applied++;
        }
        cur = memory + cur->zero;
      }
    }
    
    if (cur->one == 0) {
      cur->one = ++leaf_cnt;
      leafs[cur->one].last = leafs[cur->one].header = new listnode();
    }
    leafs[cur->one].enqueue(id);
    cur->childs++;
  }

  // remove
  void remove(char *a) {
    Node *cur = memory + root;
    for (int i = 0; i < 64; ++i) {
      cur->childs--;
      if (a[i] - '0')
        cur = memory + cur->one;
      else
        cur = memory + cur->zero;
    }
    leafs[cur->one].dequeue();
    cur->childs--;
  }

  // search
  int find(int i, char *a) {
    Node *cur = memory + root;
    for (int i = 0; i < 64; ++i) {
      if (a[i] - '0') {
        if (0 != cur->zero && (memory + cur->zero)->childs)
          cur = memory + cur->zero;
        else
          cur = memory + cur->one;
      } else {
        if (0 != cur->one && (memory + cur->one)->childs)
          cur = memory + cur->one;
        else
          cur = memory + cur->zero;
      }
    }

    return (leafs[cur->one].front() == i)
               ? leafs[cur->one].header->next->next->val
               : leafs[cur->one].front();
  }
};



Trie trie;
int main() { 

  // read inputs
  int n, k;
  scanf("%d %d", &n, &k);
  char circuit[n][65]; // circuit
  for (int i = 0; i < n; ++i)
    scanf("%s", circuit[i]);


  // build tree
  for (int i = 0; i <= k && i < n; ++i) // 注意预插入的时候留最后一个节点，到遍历的时候再插入
    trie.insert(i, circuit[i]);

  // get max
  for (int i = 0; i < n; ++i) {
    if (i - k - 2 >= 0) // compare left
      trie.remove(circuit[i - k - 2]);
    if (i + k + 1 < n)  // compare right
      trie.insert(i + k + 1, circuit[i + k + 1]);
    printf("%d\n", trie.find(i, circuit[i]));
  }
  return 0;
}