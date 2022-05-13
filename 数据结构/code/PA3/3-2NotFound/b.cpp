#include <cstdio>
#define MAX 1049000
#define LENGTH 24

void insert(char chr, unsigned int* nodes, int* tailList, int& listSize) {
  int rank = tailList[listSize % LENGTH];
  while (rank > 0 && (nodes[rank >> 5] & (1 << (rank - ((rank >> 5) << 5)))) == 0) {
    nodes[rank >> 5] |= (1 << (rank - ((rank >> 5) << 5)));
    rank = (rank - 1) >> 1;
  }
  tailList[listSize++ % LENGTH] = 0;
  for (int i = listSize - LENGTH > 0 ? listSize - LENGTH : 0; i < listSize; i++) {
    rank = tailList[i % LENGTH];
    rank = chr == '0' ? (rank << 1) + 1 : (rank << 1) + 2;
    tailList[i % LENGTH] = rank;
  }
}

void process(unsigned int* nodes, int (&tailList)[LENGTH + 5]) {
  for (int rank : tailList) {
    while (rank > 0 && (nodes[rank >> 5] & (1 << (rank - ((rank >> 5) << 5)))) == 0) {
      nodes[rank >> 5] |= (1 << (rank - ((rank >> 5) << 5)));
      rank = (rank - 1) >> 1;
    }
  }
}

void search(unsigned int* nodes) {
  int i;
  for (i = 1; i < (1 << (LENGTH + 1)) - 1; i++)
    if ((nodes[i >> 5] & ((unsigned int)1 << (i % 32))) == 0)
      break;
  char stack[LENGTH + 5];
  int tail = 0;
  while (i > 0) {
    bool check = i % 2 == 0;
    stack[tail++] = check ? '1' : '0';
    i = (i - 1) >> 1;
  }
  for (int i = tail - 1; i >= 0; i--) {
    putchar(stack[i]);
  }
}

int main() {
    int tailList[LENGTH + 5] = {0};
    unsigned int* nodes = new unsigned int[MAX]();
    int listSize = 0;

  while (true) {
    char c = fgetc(stdin);
    if (c == '\n')
      break;
    insert(c, nodes, tailList, listSize);
  }
  process(nodes, tailList);
  search(nodes);
  return 0;
}