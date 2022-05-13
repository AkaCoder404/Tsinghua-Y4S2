#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <stdbool.h>
#define N 100000

// insert, delete, search are all fast

// number of characters in our set of symbols that we have to consider
#define NUM_CHAR 256 

typedef struct TrieNode {
  bool terminal; // whether or not node is terminal of string
  struct TrieNode *children[NUM_CHAR]; // lookup table 
  // know whether or not a character is a child of this node

} trieNode;

TrieNode *createNode() {
  TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));

  for (int i = 0; i < NUM_CHAR; i++) {
    newNode->children[i] = NULL;
  }

  newNode->terminal = false;
  return newNode;
}

// true if inserted, false if not inserted
bool trieInsert(TrieNode **root, char *signedText, int suffixStartIndex) { 
  // if root is null / tree is empty
  if (*root == NULL) {
    *root = createNode(); 
  }

  unsigned char *text = (unsigned char*)signedText;
  TrieNode *temp = *root;
  int length = strlen(signedText);

  for (int i = suffixStartIndex; i < length; i++) {

    // if child for this symbol is null
    if (temp->children[text[i]] == NULL) {
      temp->children[text[i]] = createNode();
    }

    temp = temp->children[text[i]];
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

  for (int i = 48; i < 50; i++) {
    if (node->children[i] != NULL ) {
      // printf("%d ", i);
      newprefix[length] = i;
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

void search(TrieNode *root, unsigned char* prefix, int length) {
  // perform bfs
  TrieNode* array = new TrieNode[100000];
  int head = 0;
  int tail = 1;
  array[0] = *root;

  // printTrie(&array[0]);
  
  unsigned char notFound[100000];
  int* traceBack = new int[100000];
  traceBack[0] = -1;
  
  char notFoundResult[100000];

  TrieNode *currentNode;
  while (head < tail) {
    currentNode = &array[head];
    for (int i = 48; i < 50; i++) {
      // no node for that character -> this word doesn't exist so print
      if (currentNode->children[i] == NULL) {
        notFound[tail] = (char)i;
        traceBack[tail] = head;
        int k = 0;
        while (tail != 0) {
          // printf("%c", notFound[tail]);
          notFoundResult[k] = notFound[tail];
          tail = traceBack[tail];
          k++;
        }
        // printf("%c", notFound[tail]);
        notFoundResult[k] = notFound[tail];

        // printf("%s\n", notFoundResult);
        int len = strlen(notFoundResult);
        for(int j = len - 1; j >= 0; j--) {
          printf("%c", notFoundResult[j]);
        }

        // printf("asdasd\n");
        // for (int j = 0; j < 10; j++) {
        //   printf("%d ", traceBack[j]);
        // }
        return;
      }
      // if found add to stack
      else {
        array[tail] = *currentNode->children[i];
        traceBack[tail] = head;
        notFound[tail] = (char)i;
        tail++;
      }
    }
    head++;
  }

  // backtrack

  

  



} 

int main() {
  char c[N];
  scanf("%s", c); 
  

  int len = strlen(c);
  // c[len] = '$';       // dollar to help one to one mapping of suffix tree
  // c[len + 1] = '\0';

  
  // for (int i = 0; i < len + 1; i++) {
  //   printf("%c", c[i]);
  // }

  // printf("\nTrieNode Create\n");
  TrieNode *trieNode = NULL;
  trieInsert(&trieNode, c, 0);
  // printTrie(trieNode);

  // printf("Suffixes\n");

  // create suffix trie,
  // contains all suffixes of original string
  for (int i = 1; i < len; i++) {
    trieInsert(&trieNode, c, i);
  }
  // printTrie(trieNode);


  // printf("Search\n");

  // search for first non similar
  search(trieNode, NULL, 0);
}