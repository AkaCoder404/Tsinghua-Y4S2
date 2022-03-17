// CST 1-1 A+B problem
// g++ -o a.out a.cpp | python3 check.py ./a.out "python3 b.py" "python3 makedata.py"

// include
#include <iostream>
#include <string.h>
#include <math.h>
const double PI =  3.14159265358979323846;

struct Complex{ 
  double x;
  double y;
  Complex() { 
    x = 0; 
    y = 0; 
  }
  Complex(double x, double y) {    
    this->x = x;
    this->y = y;
  }
};

// overload operators
Complex operator+(Complex a, Complex b) {
  return Complex(a.x + b.x, a.y + b.y); 
}

Complex operator-(Complex a, Complex b) {
  return Complex(a.x - b.x, a.y - b.y); 
}

Complex operator*(Complex a, Complex b) {
  return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); 
}

/**
 * FFT 
 * @param a n-length coefficient vector a [a_0,a_1,...,a_(n-1)]
 * @param n omega, primitive nth root of unity omega, n is a power of 2
 * @return vector of values of polynomial for the nth roots of unity 
 */
void fft(int n, Complex * a) {
  // base case 
  if(n <= 1 ) return; 
  int mid = n >> 1;     // n * 2^1

  // divide into even and odd numbers
  Complex a_even[mid];    // even numbers
  Complex a_odd[mid];    // odd numbers

  for (int i = 0; i < mid;i++) {
    a_even[i] = a[i << 1];            // i * 2^1
    a_odd[i] = a[(i << 1) + 1];      // i * 2^1 + 1
  }

  // recursive calls with omega^2 as n/2th root of unity
  fft(mid, a_even);
  fft(mid, a_odd);

  Complex w1(cos(PI/mid),sin(PI/mid));   // e^(-j*2*pi/(2*n))
  Complex w(1,0);   
  Complex x;

  for (int i = 0; i < mid;i++) {
    x = w * a_odd[i];              // combine step, x = omega^i
    a[i] = a_even[i] + x;
    a[i + mid] = a_even[i] - x;     // because of reflective prop.
    w = w * w1;
  }
}

/**
 * IFT
 * @param a n-length coefficient vector
 * @param n 
 * @return inverse fft 
 */
void ifft(int n , Complex * a) {
  if(n<=1) return;

  int mid = n >> 1;
  Complex a_even[mid];
  Complex a_odd[mid];

  for (int i = 0; i < mid; i++){
    a_even[i] = a[i << 1];
    a_odd[i] = a[(i<<1) + 1];
  }

  ifft(mid, a_even);
  ifft(mid, a_odd);

  // performing inverse fft
  Complex w1(cos(PI/mid),-sin(PI/mid));
  Complex w(1,0);
  Complex x;

  for (int i = 0; i < mid;i++){
    x = w * a_odd[i];
    a[i] = a_even[i] + x;
    a[i + mid] = a_even[i] -x;
    w = w * w1;
  } 
}

std::string multiply(std::string num1, std::string num2) {
  int n = num1.size();
  int m = num2.size();

  // handle the numbers as complex values
  Complex a[100000];
  Complex b[100000];

  // convert to ints
  // for(int i = 0; i < n; i++) a[i].x = num1[i] - '0';
  // for(int i = 0; i < m; i++) b[i].x = num2[i] - '0';

  // higher base ie 100
  int base100n = n % 2 == 0 ? n/2 : n / 2 + 1;
  int base100m = m % 2 == 0 ? m/2 : m / 2 + 1;
  
  // if odd, first digit is by itself
  if (n % 2 == 1) {
    a[0].x = (num1[0] - '0'); 
    for(int i = 1, j = 1; i < n; i+=2, j++) {
      int temp = (num1[i] - '0') * 10 + (num1[i + 1] - '0');
      printf("temp %d\n", temp);
      a[j].x = (num1[i] - '0') * 10 + (num1[i + 1] - '0');
    }
    // is even
  } else {
    for(int i = 0, j = 0; i < n; i +=2, j++ ) {
      a[j].x = (num1[i] - '0') * 10 + (num1[i + 1] - '0');
    }
  }

  if (m % 2 == 1) {
    b[0].x = (num2[0] - '0');
    for(int i = 1, j = 0; i < m; i+=2, j++) {
      b[j].x = (num2[i] - '0') * 10 + (num2[i + 1] - '0');
    }
    // is even
  } else {
    for(int i = 0, j = 0; i < m; i +=2, j++ ) {
      b[j].x = (num2[i] - '0') * 10 + (num2[i + 1] - '0');
    }
  }

  printf("size of num1 %d\n", n);
  for(int i = 0; i < base100n; i++) {
    printf("%f ", a[i].x);
  }

  printf("\n");
  printf("size of num2 %d\n", n);
  for(int i = 0; i < base100m; i++) {
    printf("%f ", a[i].x);
  }

  n = base100n;
  m = base100m;


  int k = 1;
  while( k <= (n+m)) k <<= 1; // coefficent vector length of 2n

  // do fft on both arrays
  fft(k,a);
  fft(k,b);

  // pairwise product of the vector elements A * B = IFFT(FFT(A) * FFT(B))
  for(int i = 0; i <= k; i++){
      a[i] = a[i] * b[i];
  }

  // do ift on result to get coefficients back
  ifft(k,a);

  // processing carry 
  std::string result = "";
  int carry = 0;
  int result_length = n + m;
  int temp_result[result_length]; n--; m--;

  // account for rounding error
  for(int i = result_length - 2; i >= 0; i--) {
    temp_result[result_length - 2 - i] = a[i].x/k + 0.5;
  }

  // handle carries
  // for (int i = 0; i <= result_length - 2; i++){
  //   result += std::to_string(((temp_result[i]) + carry) % 10);
  //   carry = ((temp_result[i]) + carry) / 10;
  // }
  printf("result\n");
  for(int i = 0; i <= result_length - 2; i++) {
    printf("%d ", temp_result[i]);
  }
  printf("\n");

   // handle carries
  for (int i = 0; i <= result_length - 2; i++){
    result += std::to_string(((temp_result[i]) + carry) % 100);
    carry = ((temp_result[i]) + carry) / 100;
  }
  

  // add last carry 
  if(carry) { result += std::to_string(carry); }
  return result;
}

int main() {
  int n; 
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string x, y;
    std::cin >> x >> y;
    std::string result = multiply(x, y);
    // result is backwords, so reverse it
    for(int i = result.length() - 1; i >= 0 ; i--) {
      std::cout << result[i];
    }
    std::cout << "\n";
  }
}