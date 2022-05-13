#include <cstdio>
#include <cstring>
#define MAX 200100

struct TreeNode {
  int left = 0;
  int right = 0;
  long long value = 0;
  long long lazyTag = 0;
};

TreeNode nodes[MAX];

// common merge sort algorithm
void mergeSort(int *arr, int left, int right) {
  if (right - left == 1) {
    return;
  }
  int mid = (left + right) >> 1;
  mergeSort(arr, left, mid);
  mergeSort(arr, mid, right);
  int *tmp = new int[right - left];
  int left_pos = left;
  int right_pos = mid;
  int i = 0;
  while (left_pos < mid && right_pos < right) {
    if (arr[left_pos] < arr[right_pos]) {
      tmp[++i] = arr[left_pos++];
    } else {
      tmp[++i] = arr[right_pos++];
    }
  }
  while (left_pos < mid) {
    tmp[++i] = arr[left_pos++];
  }
  while (right_pos < right) {
    tmp[++i] = arr[right_pos++];
  }
  memcpy(arr + left, tmp, sizeof(int) * (right - left));
  delete[] tmp;
  return;
}

// build a balanced binary segment tree
void buildBalancedSegmentBinTree(int* edge, int left, int right, int rank) {
  if (left > 0) {
    nodes[rank].left = edge[left - 1] + 1;
  } else {
    nodes[rank].left = 1;
  }
  nodes[rank].right = edge[right - 1];
  if (right - left > 1) {
    buildBalancedSegmentBinTree(edge, left, (left + right) >> 1, (rank << 1) + 1);
    buildBalancedSegmentBinTree(edge, (left + right) >> 1, right, (rank << 1) + 2);
  }
  return;
}

// update the value in the [left, right] interval, the number of flips + 1
void updateTreeNode(int left, int right, int rank) {
  if (nodes[rank].left == left && nodes[rank].right == right) {
    nodes[rank].lazyTag += 1;
    return;
  }
  nodes[rank].value += (right - left + 1);
  if (nodes[rank].lazyTag > 0) {
    long long currentLazyTag = nodes[rank].lazyTag;
    nodes[rank].value += currentLazyTag * (long long)(nodes[rank].right - nodes[rank].left + 1);
    nodes[(rank << 1) + 1].lazyTag += currentLazyTag;
    nodes[(rank << 1) + 2].lazyTag += currentLazyTag;
    nodes[rank].lazyTag = 0;
  }
  if (left <= nodes[(rank << 1) + 1].right) {
    updateTreeNode(left, (nodes[(rank << 1) + 1].right < right ? nodes[(rank << 1) + 1].right : right), (rank << 1) + 1);
  }
  if (right >= nodes[(rank << 1) + 2].left) {
    updateTreeNode((nodes[(rank << 1) + 2].left > left ? nodes[(rank << 1) + 2].left : left), right, (rank << 1) + 2);
  }
  return;
}

// find the sum in the [left, right] interval
long long getSum(int left, int right, int rank) {

  if (nodes[rank].value == 0 && nodes[rank].lazyTag == 0) {
    return 0;
  }
  if (left == nodes[rank].left && right == nodes[rank].right) {
    return nodes[rank].lazyTag * (long long)(right - left + 1) + nodes[rank].value;
  }
  if (nodes[rank].lazyTag > 0) {
    long long currentLazyTag = nodes[rank].lazyTag;
    nodes[rank].value += currentLazyTag *
                         (long long)(nodes[rank].right - nodes[rank].left + 1);
    nodes[(rank << 1) + 1].lazyTag += currentLazyTag;
    nodes[(rank << 1) + 2].lazyTag += currentLazyTag;
    nodes[rank].lazyTag = 0;
  }
  long long res = 0;
  if (left <= nodes[(rank << 1) + 1].right) {
    res += getSum(left, (nodes[(rank << 1) + 1].right < right ? nodes[(rank << 1) + 1].right : right), (rank << 1) + 1);
  }
  if (right >= nodes[(rank << 1) + 2].left) {
    res += getSum((nodes[(rank << 1) + 2].left > left ? nodes[(rank << 1) + 2].left : left), right, (rank << 1) + 2);
  }
  return res;
}

int main() {
  // int n, m;
  // scanf("%d %d\n", &n, &m);
  // input data to hq and separate boundaries to edge.
  
  int input[MAX][3];
  int inputLen = 0;
  // int edge[MAX];
  int* edge = new int[MAX];
  int edgeLen = 0;

  int n, m;
  scanf("%d %d\n", &n, &m);
  char op;
  int left, right;
  for (int i = 0; i < m; ++i) {
    scanf("%c %d %d", &op, &left, &right);
    getchar();
    if (op == 'Q') {
      input[inputLen][0] = 1;
      input[inputLen][1] = left;
      input[inputLen][2] = right;
      inputLen++;
    } else if (op == 'H') {
      input[inputLen][0] = 0;
      input[inputLen][1] = left;
      input[inputLen][2] = right;
      inputLen++;
    }
    edge[edgeLen++] = left - 1;
    edge[edgeLen++] = right;

  }

  edge[edgeLen++] = n;
  // sort the separated boundaries and remove the duplicates
  mergeSort(edge, 0, edgeLen);
  int memory = 0;
  int tempEdgeLen = 0;
  for (int i = 0; i < edgeLen; ++i) {
    if (edge[i] == memory) {
      continue;
    }
    memory = edge[i];
    edge[tempEdgeLen++] = edge[i];
  }
  edgeLen = tempEdgeLen;
  // at this point, the separated monotonically increasing boundary array is obtained,
  // and each value represents the end of the interval
  // create a balanced binary segment tree
  buildBalancedSegmentBinTree(edge, 0, edgeLen, 0);
  // Handling tree modification operations
  for (int i = 0; i < inputLen; ++i) {
    if (input[i][0] == 0) {
      updateTreeNode(input[i][1], input[i][2], 0);
    } else {
      printf("%lld\n", getSum(input[i][1], input[i][2], 0));
    }
  }
  return 0;
}
