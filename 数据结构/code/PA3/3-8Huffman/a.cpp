#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <iostream>

#define N 500000
int encoding_length = 0;


// Huffman TreeNode Node
class TreeNode {
public:
  TreeNode* parent;   // parent 
  TreeNode* left;     // left child
  TreeNode* right;    // right child

  char data;     // store character
  int freq;   // store frequency

  TreeNode (TreeNode* parent, TreeNode* left, TreeNode* right) {
    parent = parent;
    left = left;
    right = right;
  }

  ~TreeNode() {}
};

// Minheap of (Huffman TreeNode) nodes
class MinHeap {
public:
  int size;
  int capacity;

  // array of minheap node pointers
  TreeNode** array;
};

TreeNode* newNode(char data, int freq) {
  TreeNode* temp = (TreeNode *)malloc(sizeof(TreeNode));  // allocate space 
  temp->left = temp->right = NULL;
  temp->data = data;
  temp->freq = freq;

  return temp;
}

MinHeap* createMinHeap(int capacity) {
  MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap)); // allocate space
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (TreeNode**)malloc(minHeap->capacity * sizeof(TreeNode*));
  return minHeap;
}

void swapMinHeapNode(TreeNode** a, TreeNode** b) {
  TreeNode* temp = *a;
  *a = *b; 
  *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
  int smallest = idx;  // checking current parent node 
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  // if left child is smaller than parent
  if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
    smallest = left;
  }

  // if right child is smaller than parent and left child
  if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
    smallest = right;
  }

  // if there is a smaller, swap
  if (smallest != idx) {
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isSizeOne(MinHeap* minHeap) {
  return (minHeap->size == 1);
}

TreeNode* extractMin(MinHeap* minHeap) {
  TreeNode* temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size-1];

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}

void insertMinHeap(MinHeap* minHeap, TreeNode* minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->freq < minHeap->array[(i- 1) / 2]->freq) {
    minHeap->array[i] = minHeap->array[(i-1)/2];
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap* minHeap) {
  int n = minHeap->size - 1;
  int i;
  for (i = (n - 1) / 2; i >= 0; --i) {
    minHeapify(minHeap,i);
  }
}


// Huffman Algorithm
TreeNode* buildHuffmanTree(MinHeap* minHeap) {
  TreeNode* left, *right, *parent;


  // while there ae still nodes to combine (heap size is not 1)
  while(!isSizeOne(minHeap)) {
    // extract two min freq nodes from heap
    left = extractMin(minHeap);
    right = extractMin(minHeap);

    // create new node equal to the sum of the two smallest nodes, set children to left, right
    parent = newNode('$', left->freq + right->freq);
    parent->left = left;
    parent->right = right;
    insertMinHeap(minHeap, parent);
  }
  // remaining node is the root node and huffman algo is done
  return extractMin(minHeap);
}


void printHuffmanCodes(TreeNode* root, std::string code, int freq[], std::string arr[]) {
  if (root->left) {
    // code += "0";
    printHuffmanCodes(root->left, code + "0", freq, arr);
  }

  if (root->right) {
    // code += "1";
    printHuffmanCodes(root->right, code + "1", freq, arr);
  }

  // if leaf node, then it is a character
  if (root->left == NULL && root->right == NULL) {
    // printf("%c ", root->data);
    // std::cout << code << "\n";
    arr[(int)(root->data) - 97] = code;
    encoding_length += (code.length()) * freq[(int)root->data - 97];
  }
}

int main() {
  char c[N];
  scanf("%s", c);


  // create frequency chart
  int freq[26] = {0};
  char arr[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 
  int len = strlen(c);
  for (int i = 0; i < len;i++) {
    // printf("%c", c[i]);
    freq[(int)c[i] - 97]++;
  }

  // create arr[] and freq[] of only the non-zero entries
  int count = 0;
  for (int i = 0; i < 26; i++) {
    if (freq[i] != 0) count++; 
  }

  char arr_n[count];
  int freq_n[count];

  len = count;
  for (int i = 0, j = 0; i < 26, j < count; i++) {
    if (freq[i] != 0) {
      arr_n[j] = arr[i];
      freq_n[j] = freq[i];
      j++;
    }
  }


  // create and build minheap
  MinHeap *minHeap = createMinHeap(len);
  for (int i = 0; i < len; i++) {
    minHeap->array[i] = newNode(arr_n[i], freq_n[i]);
  }

  minHeap->size = len;
  buildMinHeap(minHeap);


  // huffman algorithm
  TreeNode *root = buildHuffmanTree(minHeap);


  // huffman codes 
  std::string code = "";
  std::string encodings[26];
  printHuffmanCodes(root, code, freq, encodings);
  printf("%d\n", encoding_length);

  for (int i = 0; i < 26; i++) {
    if (freq[i] != 0) {
      printf("%c ", arr[i]);
      std::cout << encodings[i] << "\n";
    }
  }
  

  return 0;
}