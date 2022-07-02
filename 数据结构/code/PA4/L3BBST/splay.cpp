#include "time.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define Height(node) node == NULL ? 0 : node->height
#define LeftChild(node) node == NULL ? NULL : node->leftChild
#define RightChild(node) node == NULL ? NULL : node->rightChild
#define Balance(node) node == NULL ? NULL : node->balanceFactor
#define TESTING
// #define OJ

struct node {
  int balanceFactor;
  int height;
  int key;
  node *leftChild;
  node *rightChild;
  node(){};
  node(int _key) : balanceFactor(0), height(1), key(_key), leftChild(NULL), rightChild(NULL){};
};

// right and left rotation
node *rightRotation(node *a) {
  node *b = a->leftChild;
  a->leftChild = b->rightChild;
  b->rightChild = a;
  // update(a);
  // update(b);
  return b;
}
node *leftRotation(node *a) {
  node *b = a->rightChild;
  a->rightChild = b->leftChild;
  b->leftChild = a;
  // update(a);
  // update(b);
  return b;
}

// splay operations and remove/insert
node *splay(node *root, int key) {
  // if root is NULL or key is present at root
  if (root == NULL || root->key == key)
    return root;

  // key lies in left subtree
  if (root->key > key) {
    // key is not in tree, we are done
    if (root->leftChild == NULL)
      return root;
    // Zig-Zig (Left Left)
    if (root->leftChild->key > key) {
      // First recursively bring the key as root of left-left
      root->leftChild->leftChild = splay(root->leftChild->leftChild, key);

      // Do first rotation for root, second rotation is done after else
      root = rightRotation(root);
    } else if (root->leftChild->key < key) { // Zig-Zag (Left Right)
      // First recursively bring, the key as root of left-right
      root->leftChild->rightChild = splay(root->leftChild->rightChild, key);

      // Do first rotation for root->left
      if (root->leftChild->rightChild != NULL)
        root->leftChild = leftRotation(root->leftChild);
    }

    // Do second rotation for root
    return (root->leftChild == NULL) ? root : rightRotation(root);
  } else { // key lies in right subtree
    // key is not in tree, we are done
    if (root->rightChild == NULL)
      return root;

    // Zag-Zig (Right Left)
    if (root->rightChild->key > key) {
      // Bring the key as root of right-left
      root->rightChild->leftChild = splay(root->rightChild->leftChild, key);

      // Do first rotation for root->rightChild
      if (root->rightChild->leftChild != NULL)
        root->rightChild = rightRotation(root->rightChild);
    } else if (root->rightChild->key < key) { // Zag-Zag (Right Right)
      // Bring the key as root of, right-right and do first rotation
      root->rightChild->rightChild = splay(root->rightChild->rightChild, key);
      root = leftRotation(root);
    }

    // Do second rotation for root
    return (root->rightChild == NULL) ? root : leftRotation(root);
  }
}
node *remove(node *root, int key) {
  node *temp;
  if (!root)
    return NULL;
  root = splay(root, key); // move target node to root
  // If key is not present, then return root
  if (key != root->key)
    return root;

  // If key is present
  // If left child of root does not exist, make root->right as root
  if (!root->leftChild) {
    temp = root;
    root = root->rightChild;
  }

  // Else if left child exits
  else {
    temp = root;

    /*Note: Since key == root->key,
    so after Splay(key, root->lchild),
    the tree we get will have no right child tree
    and maximum node in left subtree will get splayed*/
    // New root
    root = splay(root->leftChild, key);

    // Make right child of previous root as new root's right child
    root->rightChild = temp->rightChild;
  }

  // free the previous root node, that is, the node containing the key
  delete temp;

  // return root of the new Splay Tree
  return root;
}
node *insert(node *root, int key) {
  // if tree is empty
  if (root == NULL)
    return new node(key);
  // bring the closest leaf to to root
  root = splay(root, key);
  if (root->key == key)
    return root;
  node *tmp = new node(key); // new node

  // if root's key is greater
  // make root as right child of new node
  // and copy left child of root to the new node
  if (root->key > key) {
    tmp->rightChild = root;
    tmp->leftChild = root->leftChild;
    root->leftChild = NULL;
  }

  // if root's key is smaller
  // make root as left child of new node
  // and copy the right child of root to new node
  else {
    tmp->leftChild = root;
    tmp->rightChild = root->rightChild;
    root->rightChild = NULL;
  }

  return tmp;
}

// search if exist
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

class Splay {
  public:
  node *root;
} spl;

int main(int argc, char *argv[]) {
  int n;
#ifdef OJ
  scanf("%d", &n);
#endif
#ifdef TESTING
  std::string testcasePath = "testcase/";
  std::string testcaseString = testcasePath + argv[1];
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
    case 'A': {
      spl.root = insert(spl.root, key);
      break;
    }
    case 'B': {
      spl.root = remove(spl.root, key);
      break;
    }
    case 'C': {
      int nodeKey = findC(spl.root, key); // find largest
      // if (nodeKey != -1)
      //   splay(spl.root, nodeKey); // splay largest ?
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
  return 0;
}