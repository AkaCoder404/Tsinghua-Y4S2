// CST 1-2 Graphics
// tips 
// 1. 对于每条线段，可以用向量叉积的 ToLeft 测试来判断其在线段的左边还是右边。通过二分查找，可以高效的查找点在哪个区域内，从而确定交点的数目。

// includes
#include <iostream>

// struct
struct Point {
  int x, y;
};


// methods
// sort from least to greatest, then check one by one using toLeft rule O(n * n) -> pass 50% test
void method1(int n, int m, int *x, int *y, Point *points); 
// functions
// checks whether a point is to the left of a line using vector cross product
bool toLeft(int ax, int ay, int bx, int by, int cx, int cy); 
// quicksort
int partition(int *arr, int start, int end);
void quicksort(int *arr, int start, int end);
// void swap(int a, int b);

int main() {
  int n;  // num of axis points
  int m;  // num of query points
 
  // x and y axis points
  scanf("%d", &n);
  int x[n];
  int y[n];
  for (int i = 0; i < n; i++) scanf("%d", &x[i]);
  for (int i = 0; i < n; i++) scanf("%d", &y[i]);

  // query points
  scanf("%d", &m);
  Point query[m];
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &(query[i].x), &(query[i].y));
  }

  // int x1[m];
  // int y1[m];
  // for (int i = 0; i < m; i++) scanf("%d", &x1[i]);
  // for (int i = 0; i < m; i++) scanf("%d", &y1[i]);

  method1(n, m, x, y, query);
  return 0;
}

bool toLeft(int ax, int ay, int bx, int by, int cx, int cy) {
  // int value = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
  // printf("value %d\n", value);
  // printf("check (%d,%d) - (%d,%d) with (%d, %d)\n", ax, ay, bx, by, cx, cy);
  // + for points on left, - for points on right
  return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax) >   0 ? false : true; 
}

void method1(int n, int m, int *x, int *y, Point *points) {
  quicksort(x, 0, n - 1); // sort x axis
  quicksort(y, 0, n - 1); // sort y axis

  // check for each line whether it is to left or right
  int count;
  for (int i = 0; i < m; i++) {
    count = 0;
    for (int j = 0; j < n; j++) {
      // line (x, 0) - (0, y) and line (0, 0) - (cx, cy)
      if (toLeft(x[j], 0, 0, y[j], points[i].x, points[i].y)) {
        count++;
        if (count == n) printf("%d \n", n);
      }
      else {
        printf("%d \n",  count);
        break;
      }
    }
  }
}


int partition(int *arr, int start, int end) {
  int pivot = arr[start];
  int count = 0;
  for (int i = start + 1; i <= end; i++) {
    if (arr[i] <= pivot)
        count++;
  }
  // giving pivot element its correct position
  int pivotIndex = start + count;
  std::swap(arr[pivotIndex], arr[start]);

  // sorting left and right parts of the pivot element
  int i = start, j = end;
  while (i < pivotIndex && j > pivotIndex) {
    while (arr[i] <= pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }
    if (i < pivotIndex && j > pivotIndex) {
      std::swap(arr[i++], arr[j--]);
    }
  }
  return pivotIndex;
}
 
void quicksort(int *arr, int start, int end) {
    // base case
    if (start >= end) return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // sorting the left part
    quicksort(arr, start, p - 1);
 
    // Sorting the right part
    quicksort(arr, p + 1, end);
}
 