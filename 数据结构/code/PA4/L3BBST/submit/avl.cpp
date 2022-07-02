#include "time.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define Height(node) node == NULL ? 0 : node->height
#define LeftChild(node) node == NULL ? NULL : node->leftChild
#define RightChild(node) node == NULL ? NULL : node->rightChild
#define Balance(node) node == NULL ? NULL : node->balanceFactor
#define OJ

struct node{
  int balanceFactor;
  int height;
  int key;
  node *leftChild;
  node *rightChild;
  node(){};
  node(int _key) : balanceFactor(0), height(1), key(_key), leftChild(NULL), rightChild(NULL){};
};

void update(node *a) {
  a->height = 1 + MAX(Height(a->leftChild), Height(a->rightChild));
  a->balanceFactor = int(Height(a->rightChild)) - int(Height(a->leftChild));
}

// right and left rotation
node *rightRotation(node *a) {
  node *b = a->leftChild;
  a->leftChild = b->rightChild;
  b->rightChild = a;
  update(a);
  update(b);
  return b;
}
node *leftRotation(node *a) {
  node *b = a->rightChild;
  a->rightChild = b->leftChild;
  b->leftChild = a;
  update(a);
  update(b);
  return b;
}

// four different cases
node *leftLeftCase(node *a) {
  return rightRotation(a);
}
node *leftRightCase(node *a) {
  a->leftChild = leftRotation(a->leftChild);
  return leftLeftCase(a);
}
node *rightRightCase(node *a) {
  return leftRotation(a);
}
node *rightLeftCase(node *a) {
  a->rightChild = rightRotation(a->rightChild);
  return rightRightCase(a);
}

node *balance(node *a) {
  // left heavy
  if (a->balanceFactor == -2) {
    if (a->leftChild->balanceFactor <= 0)
      return leftLeftCase(a);
    else
      return leftRightCase(a);
  }
  // right heavy
  else if (a->balanceFactor == 2) {
    if (a->rightChild->balanceFactor >= 0)
      return rightRightCase(a);
    else
      return rightLeftCase(a);
  }

  return a;
}

class AVL {
  public:
  node *root;
} avl;

int findC(node *a, int x) {
  // Base cases
  if (a == NULL)
    return -1;
  if (a->key == x)
    return a->key;

  // If root's value is smaller, try in right subtree
  else if (a->key < x) {
    int k = findC(a->rightChild, x);
    if (k == -1)
      return a->key; // if nothing to the right, then this is largest
    else
      return k; //
  }
  // If root's key is greater, return value from left subtree.
  else if (a->key > x)
    return findC(a->leftChild, x);
}
int findMax(node *a) {
  while (a->rightChild != NULL)
    a = a->rightChild;
  return a->key;
}
int findMin(node *a) {
  while (a->leftChild != NULL)
    a = a->leftChild;
  return a->key;
}

node *remove(node *a, int key) {
  node *find = a;
  if (find == NULL)
    return NULL; // if node can't be found

  if (key < find->key)
    find->leftChild = remove(find->leftChild, key);
  else if (key > find->key)
    find->rightChild = remove(find->rightChild, key);
  else {

    if (find->leftChild == NULL) {         // only right subtree or no subtree
      return find->rightChild;             // swap the node we wish to remove with its right child
    } else if (find->rightChild == NULL) { // only left subtree or no subtree at all
      return find->leftChild;              // swap the node we wish to remove with its left child
    } else {
      // node that is to be removed can either be largest value in left subtree
      // or smallest value in right subtree, use hueristic to remove from subtree with greatest height
      // to promote more balancing
      if (int(Height(find->leftChild)) > int(Height(find->rightChild))) { // remove from left subtree
        int value = findMax(find->leftChild);
        find->key = value;
        find->leftChild = remove(find->leftChild, value);
      } else { // remove from right subtree
        int value = findMin(find->rightChild);
        find->key = value;
        find->rightChild = remove(find->rightChild, value);
      }
    }
  }
  update(find);
  return balance(find);
}
node *insert(node *a, int key) {
  if (a == NULL)
    return new node(key);

  if (key < a->key)
    a->leftChild = insert(a->leftChild, key);
  else if (key > a->key)
    a->rightChild = insert(a->rightChild, key);
  else
    return a; // no equal keys

  update(a);
  return balance(a);
}

int main(int argc, char *argv[]) {
  int n;
#ifdef OJ
  scanf("%d", &n);
#endif
#ifdef TESTING
  std::string testcasePath = "testcase/";
  std::string testcaseString = testcasePath + argv[1];
  // std::cout << testcaseString << "\n";
  const char *testcaseFileName = testcaseString.c_str();
  std::ifstream dataFile;
  dataFile.open(testcaseFileName);
  if (!dataFile) {
    printf("Unable to open dataFile %s\n", testcaseFileName);
    exit(1); // call system to stop
  }
  dataFile >> n;
  clock_t startTime = clock();
#endif
  char command;
  int key;
  for (int i = 0; i < n; i++) {
#ifdef OJ
    scanf(" %c %d", &command, &key);
#endif
#ifdef TESTING
    dataFile >> command >> key;
#endif
    switch (command) {
    case 'A': { // insert node with key x
      avl.root = insert(avl.root, key);
      break;
    }
    case 'B': { // remove node with key x
      avl.root = remove(avl.root, key);
      break;
    }
    case 'C': { // find node with largest key that satisfies <= x
      int nodeKey = findC(avl.root, key);
      // int nodeKey = avl.root->key;
#ifdef OJ
      printf("%d\n", nodeKey);
#endif
      break;
    }
    }
  }
#ifdef TESTING
  clock_t endTime = clock();
  std::string resultFilePath = "results/";
  std::string resultFileString = resultFilePath + "results.csv";
  const char *resultFileName = resultFileString.c_str();
  std::ofstream resultFile;
  resultFile.open(resultFileName, std::ios::app);
  if (!resultFile) {
    printf("Unable to open dataFile %s\n", resultFileName);
    exit(1); // call system to stop
  }
  resultFile << ((float)(endTime - startTime)) / CLOCKS_PER_SEC << ",";
  dataFile.close();
#endif
}