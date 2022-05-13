#include <cstdio>
#include <stdlib.h>

class TreeNode {
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;

  int sum;

  TreeNode() {}
  ~TreeNode() {}
};

class SegmentTree {
  public:
    int size;
    int capacity;
    int *array;
};

SegmentTree* createSegmentTree (int capacity) {
  SegmentTree* segmentTree = (SegmentTree*)malloc(sizeof(SegmentTree));
  segmentTree->size = 0;
  segmentTree->capacity = capacity;
  // segmentTree->array = (TreeNode**)malloc(segmentTree->capacity * sizeof(TreeNode*));
  // segmentTree->array = (int)malloc(segmentTree->capacity * sizeof(int));

  // number of internal nodes (N - 1, given that it is FBT) and leaf nodes (N)
  // total nodes = (2N - 1)
  segmentTree->array = new int[2 * capacity - 1];
  return segmentTree;
}

// number of space needed is (smallest power of 2 >= (2N-1)), there can be vacant spaces
// height of segment tree ceiling(log_2(N+1))
// size of array = (2^h - 1) -> formula
int constructSegmentTree(SegmentTree* segmentTree, int pos, int arr[], int l, int r) {
  // when we have reached leaf node
  if (l == r) {
    segmentTree->array[pos] = arr[l];
    return arr[l];
  }
  // if not leaf node
  int mid = (l + r) / 2;
  segmentTree->array[pos] = constructSegmentTree(segmentTree, 2 * pos + 1, arr, l, mid) + 
    constructSegmentTree(segmentTree, 2 * pos + 2, arr, mid + 1, r); 

  return segmentTree->array[pos];
}

// find range sum
// sl and sr is range of current node
// l and r is the target range
int getSum(SegmentTree* segmentTree, int pos, int sl, int sr, int l, int r) {


  // three cases
  // 1. total overlap -> return sum
  // 2. no overlap -> return 0
  // 3. partial overlap -> keep searching left + right
  // 

  // total overlap
  if (l <= sl && r >= sr)         
    return segmentTree->array[pos];
  
  // no overlap
  if (sr < l || sl > r)
   return 0;

  // partial overlap
  int mid = (sl + sr) / 2; 
  return getSum(segmentTree, 2 * pos + 1, sl, mid, l, r) 
      + getSum(segmentTree, 2 * pos + 2, mid + 1, sr, l, r);
}

// currentNode in index tree
void updateLeafNode(SegmentTree* segmentTree, int currentNode, int sl, int sr, int pos, int diff) {
  // 1. update array          0(1)
  // 2. update segment array   log(n)
    // top down traverse

  if (sl > pos || sr < pos) // if pos is not within range of node
    return;

  segmentTree->array[currentNode] += diff;

  // top down traverse update sums until reach target pos (if lead node)
  if (sl != sr) {
    int mid = (sl + sr) / 2;
    updateLeafNode(segmentTree, 2 * currentNode + 1, sl, mid, pos, diff);
    updateLeafNode(segmentTree, 2 * currentNode + 2, mid + 1, sl, pos, diff);
  }
}


int main() {

  // int arr[8] = {2, 3, -1, 3, -2, 4, 8, 10};
  int arr[7] = {0, 0, 0, 0, 0, 0, 0};

  // construction = 2N-1 -> O(n)
  // query -> O(log N)
  // update -> O(log N)

  // segment tree is useful only if updates are frequent (otherwise directly use array)
  SegmentTree* segmentTree = createSegmentTree(7);
  int result = constructSegmentTree(segmentTree, 0, arr, 0, 6);
  int sum = getSum(segmentTree, 0, 0, 6, 0, 6);
  printf("%d\n", sum);

  // updateLeafNode(segmentTree, 0, 0, 7, 3, 5); 
  // updateLeafNode(segmentTree, 0, 0, 7, 0, 5);
  for (int i = 2; i <= 4; i++) {
    updateLeafNode(segmentTree, 0, 0, 7, i, 1);
  } 

  for (int i = 0; i < 2 * 7 - 1; i++) {
    printf("%d ", segmentTree->array[i]);
  }
  int sum2 = getSum(segmentTree, 0, 0, 7, 0, 7);
  printf("\n%d\n", sum2);



}