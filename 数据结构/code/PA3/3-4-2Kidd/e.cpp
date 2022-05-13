#include <cstdio>
#include <cstring>
#define MAX 200010
#define ENDPOINTS_MAX 400010
#define NODES_MAX 6400160


// quicksort taken from geeks for geeks 
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
char inputOp[MAX];
int inputLeft[MAX];
int inputRight[MAX];
int inputLen = 0;
int endPoints[ENDPOINTS_MAX];
int endPointsLen = 0;

int nodeLeft[NODES_MAX];
int nodeRight[NODES_MAX];
long long value[NODES_MAX];
long long tag[NODES_MAX];

void constructSegmentTree(int left, int right, int rank) {
  if (left > 0) {
    nodeLeft[rank] = endPoints[left - 1] + 1;
  } else {
    nodeLeft[rank] = 1;
  }
  nodeRight[rank] = endPoints[right - 1];
  if (right - left > 1) {
    int mid = (left + right) >> 1;
    int twoTimesRank = (rank << 1);
    constructSegmentTree(left, mid, twoTimesRank + 1);
    constructSegmentTree(mid, right, twoTimesRank + 2);
  }
  return;
}

void updateNode(int left, int right, int rank) {
  int twoTimesRank = (rank << 1);
  if (nodeLeft[rank] == left && nodeRight[rank] == right) {
    tag[rank] += 1;
    return;
  }
  value[rank] += (right - left + 1);
  // update tag
  if (tag[rank]) {
    long long currentTag = tag[rank];
    value[rank] += currentTag * (long long)(nodeRight[rank] - nodeLeft[rank] + 1);
    tag[twoTimesRank + 1] += currentTag;
    tag[twoTimesRank + 2] += currentTag; 
    tag[rank] = 0;
  }
  if (right >= nodeLeft[twoTimesRank + 2]) {
    updateNode((nodeLeft[twoTimesRank + 2] > left ? nodeLeft[twoTimesRank + 2] : left), right, twoTimesRank + 2);
  }
  if (left <= nodeRight[twoTimesRank + 1]) {
    updateNode(left, (nodeRight[twoTimesRank + 1] < right ? nodeRight[twoTimesRank + 1] : right), twoTimesRank + 1);
  }
  return;
}

long long getSum(int left, int right, int rank) {
  int twoTimesRank = (rank << 1);
  if (value[rank] == 0 && tag[rank] == 0) {
    return 0;
  }

  // if total overlap
  if (left == nodeLeft[rank] && right == nodeRight[rank]) {
    return tag[rank] * (long long)(right - left + 1) + value[rank];
  }

  // update tag
  if (tag[rank] > 0) {
    long long currenttag = tag[rank];
    value[rank] += currenttag * (long long)(nodeRight[rank] - nodeLeft[rank] + 1);
    tag[twoTimesRank + 1] += currenttag;
    tag[twoTimesRank + 2] += currenttag;
    tag[rank] = 0;
  }
  // if partial overlap
  long long res = 0;
   if (right >= nodeLeft[twoTimesRank + 2]) {
    res += getSum((nodeLeft[twoTimesRank + 2] > left ? nodeLeft[twoTimesRank + 2] : left), right, twoTimesRank + 2);
  }
  if (left <= nodeRight[twoTimesRank + 1]) {
    res += getSum(left, (nodeRight[twoTimesRank + 1] < right ? nodeRight[twoTimesRank + 1] : right), twoTimesRank + 1);
  }
  return res;
}

int main() {
  int n, m;
  scanf("%d %d\n", &n, &m);
  for (int i = 0; i < m; i++) {
    char op;
    int left, right;
    scanf("%c %d %d", &op, &left, &right);
    getchar();
    if (op == 'Q') {
      inputOp[inputLen] = 'Q';
    } else if (op == 'H') {
      inputOp[inputLen] = 'H';
    }
      inputLeft[inputLen] = left;
      inputRight[inputLen] = right;
      inputLen++;
    endPoints[endPointsLen++] = left - 1;
    endPoints[endPointsLen++] = right;
  }
  endPoints[endPointsLen++] = n;

  quickSort(endPoints, 0, endPointsLen);

  // remove duplicates
  int memory = 0;
  int tempendPointsLen = 0;
  for (int i = 0; i < endPointsLen; i++) {
    if (endPoints[i] != memory) {
      memory = endPoints[i];
      endPoints[tempendPointsLen++] = endPoints[i];
    }
  }
  // build segement tree
  constructSegmentTree(0, endPointsLen, 0);

  for (int i = 0; i < inputLen; i++) {
    if (inputOp[i] == 'H') {
      updateNode(inputLeft[i], inputRight[i], 0);
    } else {
      printf("%lld\n", getSum(inputLeft[i], inputRight[i], 0));
    }
  }
  return 0;
}