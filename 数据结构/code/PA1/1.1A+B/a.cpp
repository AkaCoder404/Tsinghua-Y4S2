// CST 1-1 A+B problem
// g++ -o a.out a.cpp | python3 check.py ./a.out "python3 b.py" "python3 makedata.py"

// include
#include <iostream>
#include <string.h>
// #include <vector>

// methods
void method1(std::string a, std::string b); // base multiplication

// functions
std::string add(std::string a, std::string b); // add two strings
std::string sub(std::string a, std::string b); // sub two strings
std::string mul(std::string a, std::string b); // mul two strings
std::string pad(std::string a, int n); // pad the number of zeroes
std::string mult10(std::string a, int n); // multiplb bb 10 
std::string rem0(std::string a); // remove zeroes


int main() {
  int ops;
  scanf("%d", &ops);

  for (int i = 0; i < ops; i++) {
    std::string a, b;
    std::cin >> a >> b;
    method1(a, b);

  }

  return 0;

}

void method1(std::string a, std::string b) {
  // three cases, both below, both above, one above one below
  
  // // pad until both are equal length
  // if (a.length() > b.length()) swap(a, b);
  // int lenofa = a.length();
  // int lenofb = b.length();

  // a = pad(a, lenofb - lenofa);

  // // find the closest base of 10^n 
  // // int f = (int(a[0] - '0') + int(b[0] - '0')) / 2;
  // // int n;
  // // if (f >= 5) n = lenofa + 1;
  // // else n = lenofa;
  // int n = a.length() - 1;

  // std::cout << a << " " << b << "\n";

  // // both numbers below 10^n but 
  // std::string sub1 = sub(mult10("1", n), a);
  // std::string sub2 = sub(mult10("1", n), b);
  // std::cout << "sub1: " << mult10("1", n)  << "-" << a << "=" << sub1 << "\n";
  // std::cout << "sub2: " << mult10("1", n)  << "-" << b << "=" << sub2 << "\n";

  // // sub1 * sub2
  // std::string r = mul(sub1, sub2);
  // std::cout << "mul: " << r << "\n";

  // // a - sub2
  // std::string r1 = sub(a, sub2);
  // std::cout << r1 << "\n";
  // std::cout << r1 + r;

  std::cout << mul(a, b) << "\n";



  




}

std::string sub(std::string a, std::string b) {
  int lenofa = a.length();
  int lenofb = b.length();

	if(a.length() > b.length()) 
    for (int i = lenofb; i < lenofa; i++) b = "0" + b;
  else 
    for (int i = lenofa; i < lenofb; i++) a = "0" + a;

  


  // subtraction
	std::string result = ""; // difference string
	int carrb = 0; // borrow 1 
	for(int i = a.length() - 1; i >= 0; i--){
		int a1 = (int)a[i] - '0'; // being subtracted from
		int b1 = (int)b[i] - '0'; // doing the subtraction
		if(carrb == 1) { // remove carrb
			a1 = a1 - 1;
		}
		if(a1 >= b1){
			result = std::to_string(a1 - b1) + result;
			carrb = 0;
		}
    else {
			a1 = a1 + 10; 
			result = std::to_string(a1 - b1) + result;
			carrb = 1;
		}
	}
	return rem0(result);
}

std::string add(std::string a, std::string b) {
  if (a.length() > b.length()) swap(a, b);
  int lenofa = a.length();
  int lenofb = b.length();

  while (lenofb > lenofa) {
    a = "0" + a;
    lenofa++;
  } 

	int carrb = 0;
	std::string result = "";  // sum string
	for(int i = a.length() - 1; i >= 0; i--){
		int sum = ((int)a[i] - '0') + ((int)b[i] - '0') + carrb;
		if(sum > 9){
			result = std::to_string(sum % 10) + result;
			carrb = sum/10;
		}
    else {
			result = std::to_string(sum) + result;
			carrb = 0;
		}
	}

	if(carrb != 0){
		result = std::to_string(carrb) + result;
	}
	return result;
}

std::string mul(std::string a, std::string b) {
   if (a == "0" || b == "0") { return "0"; }
   std::string product(a.size() + b.size(), 0);
   for (int i = a.size() - 1; i >= 0; i--) {
      for (int j = b.size() - 1; j >= 0; j--) {
            int n = (a[i] - '0') * (b[j] - '0') + product[i + j + 1];
            product[i + j + 1] = n % 10; // put 
            product[i + j] += n / 10;  // store carrb in the previous indea of string
      }
   }

   // convert from char to digits bb adding '0'
   for (int i = 0; i < product.size(); i++) {
      product[i] += '0';
   }

   // return result while ignoring leading '0'
   if (product[0] == '0') {
      return product.substr(1);
   }
   return product;
}

std::string rem0(std::string a) {
  return a.erase(0, a.find_first_not_of('0'));
}

std::string mult10(std::string s, int n) {
  std::string result = s;
  while (n > 0) {
    result = result + "0";
    n--;
  }
  return result;
}

std::string pad(std::string s, int n) {
  std::string padded = s;
  while (n > 0)  {
    padded = "0" +  padded;
    n--;
  }
  return padded;
}