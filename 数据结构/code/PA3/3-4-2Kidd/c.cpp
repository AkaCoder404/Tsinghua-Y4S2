#include <cstdio>
#include <iostream>
#include <math.h>

int* createSegmentTree(long long int capacity) {
  long long int x = (long long int)(ceil)(log2(capacity)); // max height of segment tree
  long long int maxSize = 2 * (long long int)pow(2, x) - 1;
  // return new int[maxSize]();
  return new int[4 * capacity]();
}

long long int constructSegmentTree(int *segmentTree, long long int pos, long long int arr[], int l, int r) {
  if (l == r) {
    segmentTree[pos] = arr[l];
    return arr[l];
  }

  long long int mid = l + (r - l) / 2;
  segmentTree[pos] = constructSegmentTree(segmentTree, 2 * pos + 1, arr, l, mid) 
    + constructSegmentTree(segmentTree, 2 * pos + 2, arr, mid + 1, r);

  return segmentTree[pos];
}

long long int getSum(int* segmentTree, long long int pos, int sl, int sr, int l, int r, int n) {
  if (l <= sl && r >= sr) {
    return segmentTree[pos];
  }

  if (sr < l || sl > r) {
    return 0;
  }

  long long int mid = sl + (sr - sl) / 2;
  return getSum(segmentTree, 2 * pos + 1, sl, mid, l, r, n) 
    + getSum(segmentTree, 2 * pos + 2, mid + 1, sr, l, r, n);
}

void updateNode(int *segmentTree, int currentNode, int sl, int sr, int pos, int diff, int n) {
  if (sl > pos || sr < pos) {
    return;
  }

  segmentTree[currentNode] += diff;

  if (sl != sr) {
    long long int mid = sl + (sr - sl) / 2;
    updateNode(segmentTree, 2 * currentNode + 1, sl, mid, pos, diff, n);
    updateNode(segmentTree, 2 * currentNode + 2, mid + 1, sr, pos, diff, n);
  }
}

int main() {
  long long int n = 0;
  int m;
  scanf("%lld %d", &n, &m);
  
  int* segmentTree = createSegmentTree(n);


  
  char op;
  long long int left, right;
  for (int i = 0; i < m; i++) {
    std::cin >> op >> left >> right;
    if (op == 'H') {
      for (int j = left; j < right + 1; j++) {
        updateNode(segmentTree, 0, 0, n - 1, j, 1, n);
      }
    }
    else if (op == 'Q') {
      long long int sum = getSum(segmentTree, 0, 0, n-1, left, right, n);
      printf("%lld\n", sum);
    }
  }

  return 0;
}