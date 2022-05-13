#include <cstdio>
#include <iostream>
#include <math.h>

struct SegmentTree {
  public:
    // long long int capacity;
    long long int *array;
    // SegmentTree() {}
    // ~SegmentTree() {}
};

SegmentTree* createSegmentTree(long long int capacity) {
  SegmentTree* segmentTree = (SegmentTree*)malloc(sizeof(SegmentTree));
  // segmentTree->capacity = capacity;

  // //Height of segment tree 
	long long int x = (long long int)(ceil(log2(capacity))); 

	// //Maximum size of segment tree 
	long long int max_size = 2*(long long int)pow(2, x) - 1; 

	// // Allocate memory 
	// // int *st = new int[max_size]; 
  

  segmentTree->array = new long long int[max_size]();
  return segmentTree;
}

int constructSegmentTree(SegmentTree* segmentTree, long long int pos, long long int arr[], int l, int r) {
  // if leaf node 
  if (l == r) {
    segmentTree->array[pos] = arr[l];
    return arr[l];
  }
 
  // parent = (i - 1) / 2
  // if not leaf node 
  // long long int mid = (l + r) / 2; // split through middle
  long long int mid = l + (r - l) / 2;
  segmentTree->array[pos] = constructSegmentTree(segmentTree, 2 * pos + 1, arr, l, mid) 
    + constructSegmentTree(segmentTree, 2 * pos + 2, arr, mid + 1, r);
  
  return segmentTree->array[pos];
}

// current pos contains sum from sl to sr
long long int getSum(SegmentTree* segmentTree, long long int pos, int sl, int sr, int l, int r, int n) {
  // if (l < 0 || r > n - 1 || l > r) {
  //   printf("error");
  //   return  -1;
  // }

  // total overlap
  if (l <= sl && r >= sr) 
    return segmentTree->array[pos];

  // no overlap
  if (sr < l || sl > r) 
    return 0;

  // partial overlap
  // long long int mid = (sl + sr) / 2;
  long long int mid = sl + (sr - sl) / 2;
  return getSum(segmentTree, 2 * pos + 1, sl, mid, l, r, n) 
    + getSum(segmentTree, 2 * pos + 2, mid + 1, sr, l, r, n);
}

void updateNode(SegmentTree* segmentTree, int currentNode, int sl, int sr, int pos, int diff, int n) {

  // check for erroneous input
  // if (pos < 0 || pos > n - 1) {
  //   std::cout << "Invalid";
  // }
  // if target updaet is not within range of node, return  
  // printf("%d %d %d ", sl, sr, pos);
  if (sl > pos || sr < pos) 
    return;

  // update current sum
  // printf("update %lld with +%d\n", segmentTree->array[currentNode], diff);
  segmentTree->array[currentNode] += diff;
  // printf("updating %d\n", currentNode);
  // top down traverse and update sums until reach target pos (if lead node)
  if (sl != sr) {
    // long long int mid = (sl + sr) / 2;
    long long int mid = sl + (sr - sl) / 2;
    updateNode(segmentTree, 2 * currentNode + 1, sl, mid, pos, diff, n);
    updateNode(segmentTree, 2 * currentNode + 2, mid + 1, sr, pos, diff, n);
  }
}


int main() {
  long long int n = 0;
  int m;
  scanf("%lld %d", &n, &m);

  SegmentTree* segmentTree = createSegmentTree(n);
  // int result = constructSegmentTree(segmentTree, 0, new long long int[n](), 0, n - 1);


  char op;
  long long int left, right;
  for (int i = 0; i < m; i++) {
    // scanf(" %c %lld %lld", &op, &left, &right);
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