#include <cstdio>
#include <cstring>
#include <stdlib.h>
#define N 50000

// number of characters in our character set (2 for bin)
#define NUM_CHAR 2

typedef struct TrieNode {
  bool terminal;
  struct TrieNode *children[NUM_CHAR];
} trieNode;

TrieNode *createNode() {
  TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));

  for (int i = 0; i < NUM_CHAR; i++) {
    newNode->children[i] = NULL;
  }
  newNode->terminal = false;
  return newNode;
}

bool trieInsert(TrieNode **root, char *signedText, int suffixStartIndex) {
  if (*root == NULL) {
    *root = createNode();
  }

  unsigned char *text = (unsigned char*)signedText;
  TrieNode *temp = *root;
  int length = strlen(signedText);
  
  int bin;
  for (int i = suffixStartIndex; i < length; i++) { 
    // int bin = text[i] == '0' ? 0 : 1;
    if (text[i] == '0') bin = 0;
    else bin = 1;

    if (temp->children[bin] == NULL) {
      temp->children[bin] = createNode();
    }

    temp = temp->children[bin];
  }

  if (temp->terminal) {
    return false;
  } else {
    temp->terminal = true;
    return true;
  }
}


void printTrieRecursive(TrieNode* node, unsigned char*prefix, int length) {
  unsigned char newprefix[length + 2];
  memcpy(newprefix, prefix, length);
  newprefix[length + 1] = 0;

  // base case
  if (node->terminal) {
    printf("%s\n", prefix);
    
  }

  for (int i = 0; i < 2; i++) {
    if (node->children[i] != NULL ) {
      newprefix[length] = i == 0 ? '0' : '1';
      printTrieRecursive(node->children[i], newprefix, length+1);
    }
  }
}

void printTrie(TrieNode *root) {
  if (root == NULL) {
    printf("empty\n");
  }
  printTrieRecursive(root, NULL, 0);

}


void search(TrieNode *root) {
  TrieNode* array = new TrieNode[N];
  int head = 0;
  int tail = 1;
  array[0] = *root;

  unsigned char* notFound = new unsigned char[N];
  // unsigned char notFound[N];
  char* notFoundResult = new char[N];
  // char notFoundResult[N];
  int* traceBack = new int[N];
  traceBack[0] = -1;

  TrieNode *currentNode; 
  while (head < tail) {
    currentNode = &array[head];
    for (int i = 0; i < 2; i++) {
      if (currentNode->children[i] == NULL) {
        notFound[tail] = (i == 0 ? '0' : '1');
        traceBack[tail] = head;
        int k = 0;
        while (tail != 0) {
          notFoundResult[k] = notFound[tail];
          tail = traceBack[tail];
          k++;
        }
        notFoundResult[k] = notFound[tail];
        int len = strlen(notFoundResult);
        for(int j = len - 1; j >= 0; j--) {
          printf("%c", notFoundResult[j]);
        }
        return;
      }
      // if found add to stack
      else {
        array[tail] = *currentNode->children[i];
        traceBack[tail] = head;
        notFound[tail] = (i == 0 ? '0' : '1');
        tail++;
      }
    }
    head++;
  }
}

int main() {
  char c[N];
  scanf("%s", c);

  int len = strlen(c);

  TrieNode *trieNode = NULL;
  trieInsert(&trieNode, c, 0);
  for (int i = 1; i < len; i++) {
    trieInsert(&trieNode, c, i);
  }
  // printTrie(trieNode);

  search(trieNode);
}
