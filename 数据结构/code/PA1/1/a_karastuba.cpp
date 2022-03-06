// CST 1-1 A+B problem
// g++ -o a.out a.cpp | python3 check.py ./a.out "python3 b.py" "python3 makedata.py"

// include
#include <iostream>
#include <string.h>
#include <math.h>


// functions
std::string karatsuba(std::string x, std::string y);     // main recursive
std::string kadd(std::string x, std::string y);          // add two strings
std::string ksub(std::string x, std::string y);          // sub two strings
std::string krem(std::string str);                  // remove extra zeroes
std::string kmult10(std::string str, int n);     // multiply by 10^n

int main() {
	std::ios_base::sync_with_stdio(false); // speed up cin/cout
  int ops; // number of pairs of nums
  std::cin >> ops;

	for (int i = 0; i < ops; i++) {
    std::string x,y;
    std::cin >> x >> y;
    // remove leading zeroes and output result
    std::cout << krem(karatsuba(x,y))<< "\n";
  }

	return 0;
}

std::string karatsuba(std::string x, std::string y){
  // make sure both numbers have same digits
  if (x.length() > y.length()) swap(x, y);
  int lenofx = x.length();
  int lenofy = y.length();

  while (lenofy > lenofx) {
    x = "0" + x;
    lenofx++;
  } 

  // base case
	if(x.length() == 1 && y.length() == 1){
	  int product = ((int)x[0] - '0') * ((int)y[0] - '0');
    return std::to_string(product);
	}

  // add zeroes to beginning of strings if length is odd 
	if(x.length() % 2 !=0){
		x = "0" + x;
		y = "0" + y;
	}

  // find values of al, ar, bl, br
	std::string al, ar, bl, br, p1, p2, p3;
	int n = x.length();
	al = x.substr(0, x.length()/2);
	ar = x.substr(x.length()/2);
	bl = y.substr(0, y.length()/2);
	br = y.substr(y.length()/2);
 	
	p1 = karatsuba(al, bl);												// al * bl
	p2 = karatsuba(kadd(al, ar), kadd(bl, br));		// (al + ar) * (bl + br)
	p3 = karatsuba(ar, br);												// (ar * br)

	return kadd(kadd(kmult10(p1, n), kmult10(ksub(ksub(p2,p1), p3), n/2)), p3); 
	// ((al * bl) * 10^n + ((al + ar) * (bl + br) - (al * bl) -  (ar * br)） * 10^n/2) + (ar * br)

}

std::string kadd(std::string x, std::string y){
  // make sure they same length
  if (x.length() > y.length()) swap(x, y);
  int lenofx = x.length();
  int lenofy = y.length();

  while (lenofy > lenofx) {
    x = "0" + x;
    lenofx++;
  } 

	int carry = 0;
	std::string result = "";  // sum string
	for(int i = x.length() - 1; i >= 0; i--){
		int sum = ((int)x[i] - '0') + ((int)y[i] - '0') + carry;
		if(sum > 9){
			result = std::to_string(sum % 10) + result;
			carry = sum/10;
		}
    else {
			result = std::to_string(sum) + result;
			carry = 0;
		}
	}

	if(carry != 0){
		result = std::to_string(carry) + result;
	}
	return result;
}

std::string ksub(std::string x, std::string y){
  int lenofx = x.length();
  int lenofy = y.length();

	if(x.length() > y.length()) 
    for (int i = lenofy; i < lenofx; i++) y = "0" + y;
  else 
    for (int i = lenofx; i < lenofy; i++) x = "0" + x;

  // subtraction
	std::string result = ""; // difference string
	int carry = 0; // borrow 1 
	for(int i = x.length() - 1; i >= 0; i--){
		int a1 = (int)x[i] - '0'; // being subtracted from
		int b1 = (int)y[i] - '0'; // doing the subtraction
		if(carry == 1) { // remove carry
			a1 = a1 - 1;
		}
		if(a1 >= b1){
			result = std::to_string(a1 - b1) + result;
			carry = 0;
		}
    else {
			a1 = a1 + 10; 
			result = std::to_string(a1 - b1) + result;
			carry = 1;
		}
	}
	return krem(result);
}

std::string krem(std::string str){
  return str.erase(0, str.find_first_not_of('0'));
}

std::string kmult10(std::string str, int n){
	while(n > 0){
		str = str + "0";
		n--;
	}
	return str;
}