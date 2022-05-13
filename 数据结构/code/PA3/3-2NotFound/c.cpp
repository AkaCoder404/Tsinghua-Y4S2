#include <cstdio>
#define MAX 1049000
#define LENGTH 24

// insert the node whose length is before the last 24, and calculate the rank by rigt recursion
void insert(char c, char *buffer, int& bufferTail, int &rank, unsigned int *nodes) {
  buffer[bufferTail++ % LENGTH] = c;
  int left = bufferTail - LENGTH;
  int right = bufferTail;
  rank <<= 1; // rank = 2 * 2^1

  if (c == 'l')
    rank++;
  rank &= ((1 << LENGTH) - 1); // 2^N - 1

  if (left > 0) {
    int tmp = (1 << LENGTH) - 1 + rank;
    // set bit 
    nodes[tmp >> 5] |= (1 << (tmp - ((tmp >> 5) << 5))); // nodes[temp / 2^5 or (1 * temp - 2^(temp / 2^5) * 2^5)
  }
}

// Find the first node with 0, backtrack up to find the corresponding string, and output in reverse order
void search(unsigned int *nodes) {
  int i;
  for (i = 1; i < (1 << (LENGTH + 1)) - 1; i++) {
    if ((nodes[i >> 5] & ((unsigned int)1 << (i % 32))) == 0) {
       break;
    }
  }

  char stack[LENGTH + 5];
  int stackTail = 0;

  while (i > 0) {
    stack[stackTail++] = i % 2 == 0 ? '1' : '0';
    i = (i - 1) >> 1;
  }
  for (int i = stackTail - 1; i >= 0; i--) {
    putchar(stack[i]);
  }
}

void process(unsigned int *nodes, char *buffer, int *rankList, int &rank, int &bufferTail, int &rankTail) {
  // Process the last 24 characters individually and insert them one by one, (very fast)
  for (int i = bufferTail - LENGTH > 0 ? bufferTail - LENGTH : 0; i < bufferTail; ++i) {
    int left = i;
    int right = bufferTail;
    rank = 0;
    for (int j = left; j < right; ++j) {
       rank = buffer[j % LENGTH] == '0' ? (rank << 1) + 1 : (rank << 1) + 2;
    }
    nodes[rank >> 5] |= (1 << (rank - ((rank >> 5) << 5)));
    rankList[rankTail++] = rank;
  }
  // Update all the nodes on the previous path of the leaf nodes on the 24th layer (slow)
  for (int i = (1 << LENGTH) - 1; i < (1 << (LENGTH + 1)) - 1; ++i) {
    rank = i;
    if ((nodes[rank >> 5] & (1 << (rank - ((rank >> 5) << 5)))) > 0) {
      rank = (i - 1) >> 1;
      while (rank > 0 && (nodes[rank >> 5] & (1 << (rank - ((rank >> 5) << 5)))) == 0) {
        nodes[rank >> 5] |= (1 << (rank - ((rank >> 5) << 5)));
        rank = (rank - 1) >> 1;
      }
    }
  }
  // Update the last 24 nodes, the end point is not on the leaf node (fast)
  for (int i = 0; i < rankTail; ++i) {
    rank = (rankList[i] - 1) >> 1;
    while (rank > 0 && (nodes[rank >> 5] & (1 << (rank - ((rank >> 5) << 5)))) == 0) {
      nodes[rank >> 5] |= (1 << (rank - ((rank >> 5) << 5)));
      rank = (rank - 1) >> 1;
    }
  }
}

int main() {
  unsigned int *nodes = new unsigned int[MAX]();
  char *buffer = new char[LENGTH + 5];
  // bitmap
  // to set bit i
  // bit[i / 32] |= 1 << (31 - (i % 32));
  // to get bit i
  // bit[i / 32] >> (31 - (i % 32) & 1)
  int bufferTail = 0;

  int *rankList = new int[LENGTH + 24];
  int rankTail = 0;
  int rank = 0;

  while (true) {
    char c = fgetc(stdin);
    if (c == '\n')
      break;
    insert(c, buffer, bufferTail, rank, nodes);
  }

  process(nodes, buffer, rankList, rank, bufferTail, rankTail);
  search(nodes);
  return 0;
}