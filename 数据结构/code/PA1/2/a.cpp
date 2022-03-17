// CST 1-2 Graphics
// tips 
// 1. 对于每条线段，可以用向量叉积的 ToLeft 测试来判断其在线段的左边还是右边。通过二分查找，可以高效的查找点在哪个区域内，从而确定交点的数目。

// includes
#include <iostream>

// struct
struct Point {
  long long int x, y;
  Point() {
    this->x = 0;
    this->y = 0;
  }
  Point(long long int x, long long int y) : x(x) , y(y) {}
};


// methods
// sort from least to greatest, then check one by one using toLeft rule O(n * n) -> pass 50% test
void method1(long long int n, long long int m, long long int *x, long long int *y, Point *Points); 
// functions
// checks whether a Point is to the left of a line using vector cross product
bool toLeft(long long int ax, long long int ay, long long int bx, long long int by, long long int cx, long long int cy); 
long long int partition(long long int *arr, long long int start, long long int end);
void quicksort(long long int *arr, long long int start, long long int end);

// binary search 
long long int binarySearch(long long int *x, long long int *y, Point c, long long int start, long long int end) {
  // if (end - start > 0) {
  //   long long int mid = (start + end) / 2;
    
  //   // if right of current line, and left of line on the right, it is true
  //   if (toLeft(x[mid], 0, 0, y[mid], c.x, c.y) && !toLeft(x[mid+1], 0, 0, y[mid+1], c.x, c.y)) return mid;
  //   // if right of current line and still right of line on the right, search more right
  //   else if (toLeft(x[mid], 0, 0, y[mid], c.x, c.y)) return binarySearch(x, y, c, mid + 1, end);
  //   // else if it is not right, search lower
  //   // if (toLeft(x[mid], 0, 0, y[mid], c.x, c.y)) return binarySearch(x, y)
  //   return binarySearch(x, y, c, start, mid);
  //   // if it is false, look at lower half until its true
  // }

  // return -1;

  // if (start < end - 1) {
  //   long long int mid = (start + end) >> 1;
  //   if (!mid) return start;
  //   if (toLeft(x[mid], 0, 0, y[mid], c.x, c.y)) return binarySearch(x, y, c, mid + 1, end);
  //   else return binarySearch(x, y, c, start, mid);
  // }
  // return start;

  while (start < end - 1) {
    long long int mid = (start + end) >> 1;
    if (!mid) break;
    if (toLeft(x[mid], 0, 0, y[mid], c.x, c.y)) start = mid;
    else end = mid;
  }
  return start;

}

int main() {
  long long int n;  // num of axis Points
  long long int m;  // num of query Points
 
  // x and y axis Points
  scanf("%lld", &n);
  long long int x[n + 1];
  long long int y[n + 1];
  for (long long int i = 1; i < n + 1; i++) scanf("%lld", &x[i]);
  for (long long int i = 1; i < n + 1; i++) scanf("%lld", &y[i]);

  // query Points
  scanf("%lld", &m);
  Point query[m];
  for (long long int i = 0; i < m; i++) {
    scanf("%lld%lld", &(query[i].x), &(query[i].y));
  }

  method1(n, m, x, y, query);
  return 0;
}

bool toLeft(long long int ax, long long int ay, long long int bx, long long int by, long long int cx, long long int cy) {
  // long long int value = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
  // printf("value %lld\n", value);
  // printf("check (%lld,%lld) - (%lld,%lld) with (%lld, %lld)\n", ax, ay, bx, by, cx, cy);
  // + for Points on left, - for Points on right
  // return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax) >  0 ? false : true;  
   return (ax * cy + by * (cx - ax)) >= 0;
  
}



void method1(long long int n, long long int m, long long int *x, long long int *y, Point *Points) {
  quicksort(x, 1, n); // sort x axis
  quicksort(y, 1, n); // sort y axis


  // linear search O(m*n)
  // check for each line whether the Point it is to left or right
  // long long int count;
  // for (long long int i = 0; i < m; i++) {
  //   count = 0;
  //   for (long long int j = 0; j < n; j++) {
  //     // line (x, 0) - (0, y) and line (0, 0) - (cx, cy)
  //     if (toLeft(x[j], 0, 0, y[j], Points[i].x, Points[i].y)) {
  //       count++;
  //       if (count == n) printf("%lld \n", n);
  //     }
  //     else {
  //       printf("%lld \n",  count);
  //       break;
  //     }
  //   }
  // }

  // use binary search
  long long int count = 0;
  for (long long int i = 0; i < m; i++) {
    // check last case
    // if (toLeft(x[n - 1], 0, 0, y[n - 1], Points[i].x, Points[i].y)) { 
    //   printf("%lld \n", n);
    //   continue;
    // }
    count = binarySearch(x, y, Points[i], 0, n + 1);
    printf("%lld \n", count);
  }


}

long long int partition(long long int *arr, long long int start, long long int end) {
  long long int pivot = arr[start];
  long long int count = 0;
  for (long long int i = start + 1; i <= end; i++) {
    if (arr[i] <= pivot)
        count++;
  }
  // giving pivot element its correct position
  long long int pivotIndex = start + count;
  std::swap(arr[pivotIndex], arr[start]);

  // sorting left and right parts of the pivot element
  long long int i = start, j = end;
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
 
void quicksort(long long int *arr, long long int start, long long int end) {
    // base case
    if (start >= end) return;
 
    // partitioning the array
    long long int p = partition(arr, start, end);
 
    // sorting the left part
    quicksort(arr, start, p - 1);
 
    // Sorting the right part
    quicksort(arr, p + 1, end);
}
  