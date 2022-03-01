// CST 1-1 A+B problem
// g++ -o a.out a.cpp | python3 check.py ./a.out "python3 b.py" "python3 makedata.py"

// include
#include <iostream>
#include <string.h>



// methods
void method1();  // long long int -> not large enough
void method2();  // char array base 10 -> O (m * n) -> time limit exceeded
void method3();  // karastuba method -> errors & time limit exceed 5/50

int main() {
  int ops; // number of operations
  scanf("%d", &ops);

  for (int i = 0; i < ops; i++) {
    // method1();
    // method2();
    method3();
  }
  return 0;
}

// unsigned long long int method
void method1() {
  long long int a;
  long long int b;
  scanf("%lld %lld", &a, &b);
  printf("%lld\n", a * b);
}
// char array (base 10)
void method2() { 
  char a[100000] = "";
  char b[100000] = "";
  char sum[100000] = "";
  scanf("%s %s", a, b);

  size_t lenofa = strlen(a);
  size_t lenofb = strlen(b);
  // printf("length of a %ld, length of b %ld", lenofa, lenofb);

  // if equal length
  int carry;
  int len_of_sum;

  for (int i = lenofa - 1; i >= 0; i--) {
    // printf("%d", int(a[i] - '0'));
    char temp_sum[100000]; 
    carry = 0;
    if (int(a[i] - '0') == 0) continue;
    for (int j = lenofb - 1; j >= 0; j--) { 
      int mult = int(a[i] - '0') * int(b[j] - '0') + carry; // prod of two nums + carry
      // printf("%d = %d * %d + %d\n", mult, int(a[i] - '0'), int(b[j] - '0'), carry);
      carry = int(mult / 10);  // calculate carry for next multiplication
      int mod = mult % 10;     // calculate ones digit 
      // printf("sum[%ld] = %d \n", lenofb - (j + 1), mod);
      temp_sum[lenofb - (j + 1)] = mod; // place the ones digit in sum
    }
    // if carry is not zero
    temp_sum[lenofb] = carry;
    len_of_sum = (carry == 0 ? lenofb : lenofb + 1);
    // add to total sum
    // for(int j = 0; j < len_of_sum; j++) printf("%d", temp_sum[j]);
    // printf("\n");

    carry = 0;
    for (int j = lenofa - (i + 1), k = 0; j < (lenofa - (i + 1) + len_of_sum); k++, j++) {
      int add = int(sum[j]) + int(temp_sum[k]) + carry;
      // printf("%d = %d + %d + %d\n", add, int(sum[j]), int(temp_sum[k]), carry);
      carry = int(add / 10);   // calculate carry for next addition
      int mod = add % 10; // calculate addition
      sum[j] = mod;
    }
    sum[(lenofa - (i + 1) + len_of_sum)] = carry; // add carry to the end 
    // printf("sum %d : ", i);
    // for(int i = 0; i < lenofa + lenofb; i++) printf("%d",sum[i]);
    // printf("\n");
    
  }
  // printf("carry %d\n", carry);
  int total_len_of_sum = lenofa + len_of_sum + (carry == 0 ? 0 : 1);
  for(int i = total_len_of_sum - 2; i >=0; i--) printf("%d",sum[i]);
  printf("\n");
}

void reverse(std::string& str, int len) {
  int n = len-1;
  for(int i = 0 ; i < (len / 2); i++){
    std::swap(str[i] ,str[n]);
    n = n - 1;
  }
}

std::string ksum(std::string a, std::string b) {
  if (a.length() > b.length()) 
    swap(a, b);

  int lenofa = a.length();
  int lenofb = b.length();

  // reverse for easy addition
  reverse(a, lenofa);
  reverse(b, lenofb);

  // find the sum
  int carry = 0;
  std::string sum_str = "";

  for (int i = 0; i < lenofa; i++) {
    int sum = ((a[i] - '0') + (b[i] - '0') + carry);
    sum_str.push_back(sum % 10 + '0');
    carry = sum / 10;
  } 

  for (int i = lenofa; i < lenofb; i++) {
    int sum = ((b[i] - '0') + carry);
    sum_str.push_back(sum % 10 + '0');
    carry = sum / 10;
  }
  
  if (carry) sum_str.push_back(carry + '0');
  
  reverse(sum_str, sum_str.length());
  return sum_str;
}

std::string kdif(std::string a, std::string b) {
  int lenofa = a.length();
  int lenofb = b.length();

  reverse(a, lenofa);
  reverse(b, lenofb);


  int carry = 0;
  std::string dif_str = "";
  for(int i = 0; i < lenofb; i++) {
    int dif = ((a[i] - '0') - (b[i] - '0') - carry);
    
    if (dif < 0) {
      dif = dif + 10;
      carry = 1;
    }
    else carry = 0;
    dif_str.push_back(dif + '0');
  }

  // sub remaining digits of larger number
  for (int i = lenofb; i < lenofa; i++) {
    int sub = ((a[i] - '0') - carry);

    // If the sub value is -ve,
    // then make it positive
    if (sub < 0) {
        sub = sub + 10;
        carry = 1;
    }
    else carry = 0;

    dif_str.push_back(sub + '0');
  }

  reverse(dif_str, dif_str.length());

  return dif_str;

}

std::string krem(std::string str) {
  return str.erase(0, str.find_first_not_of('0'));
}   

std::string kmultiply(std::string a, std::string b) {
  // make sure both numbers have same digits
  if (a.length() > b.length()) swap(a,b);
  int lenofa = a.length();
  int lenofb = b.length();

  while (lenofb > lenofa) {
    a = "0" + a;
    lenofa++;
  } 

  // base case (last step of recursion)
  if (lenofa == 1 && lenofb == 1) {
    int mult = ((int)a[0] - '0') * ((int)b[0] - '0');
    return std::to_string(mult);
  }

  // add zeroes to the beginning of strings when length is odd
  if (a.length() % 2 != 0) {
    a = "0" + a;
    b = "0" + b;
    lenofa++;
  }

  // find values of Al, Ar, Bl, and Br, where 
  // Al contain leftmost n/2 digits of A
  // Ar contain rightmost n/2 digits of A
  // same for Bl and BR
  // thus A * B = (Al * 10n/2 + Ar) * (Bl * 10n/2 + Br)
  // therefore A * B = 10n*Al*Bl + 
  //                   10n/2*((Al + Ar)*(Bl + Br) – Al*Bl – Ar*Br) + 
  //                   Ar*Br

  std::string al, ar, bl, br;
  // int n = a.length();
  // al = a.substr(0, a.length()/2);
	// ar = a.substr(a.length()/2);
	// bl = b.substr(0, b.length()/2);
	// br= b.substr(b.length()/2);

  
  for (int i = 0; i < lenofa / 2; i++) {
    al += a[i];
    bl += b[i];
    ar += a[lenofa / 2 + i];
    br += b[lenofa / 2 + i];
  }

  // recursion !!!
  // 
  std::string al_bl = kmultiply(al, bl);
  std::string ar_br = kmultiply(ar, br);
  std::string r = kdif(kmultiply(ksum(al, ar), ksum(bl, br)), ksum(al_bl, ar_br));
  
  // multiply by 10^n
  for(int i = 0; i < lenofa; i++) 
    al_bl = al_bl + "0";

  // multiply by 10^(n/2)
  for(int i = 0; i < lenofa / 2; i++)
    r = r + "0";

  std::string ans = ksum(al_bl, ksum(ar_br, r)); 
  // remove leading zeroes
  return krem(ans);
}

// karastuba multiplication base 10
void method3() {
  std::string a= "", b = "";
  std::cin >> a >> b;
  std::cout << kmultiply(a, b) << "\n";
}

