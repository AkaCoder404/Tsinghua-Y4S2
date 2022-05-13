#include "hashtable.h"

// hashing strategies
int naive_hashing::operator()(char* str, int N){
    if(str == NULL) return 0;
    else return (str[0]+N)%N;
}

// use folding algorithm
int ascii_hashing::operator()(char* str, int N) {
    if (str == NULL) return 0;
    int len = strlen(str);
    int ans = 0;
    int shift = 7; 
    for (int i = 0; i < len; i++) {
        ans = ans + (int((unsigned char)str[i] << 7));
        ans %= N;
    }
    return ans;
}


// use djb2 algorithm at http://www.cse.yorku.ca/~oz/hash.html
int utf8_hashing::operator()(char *str, int N){
    if (str == NULL) return 0;
    int len = strlen(str);
    int ans = 5381;
    for (int i = 0; i < len; i++) {
        ans = (((ans << 5) + ans) + int((unsigned char)str[i]));
        ans %= N;
    }
    return ans;
}

// collision strategies
int linear_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    return (last_choice + 1) % table_size;
}
void linear_probe::init(){
    return;// do nothing
}


int quadratic_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    int ans;   
    if (negative) { // backward direction
        ans = (last_choice - square * square) % table_size;
        if (ans < 0 ) ans += table_size;
        square++; // increase square only when both sides have been checked
        negative = !negative;
    } else { // forward direction
        ans = (last_choice + square * square) % table_size;
        negative = !negative;
    }
    return ans;
}
void quadratic_probe::init() {
    square = 1;
    negative = false;
    return;
}

int overflow_probe::operator()(hash_entry* Table, int table_size, int last_choice) {
    int ans = table_size + counter; // overflow counter starting from end of table
    counter++;
    return ans;
}
void overflow_probe::init() {
    counter = 0; // overflow counter
    return;
}