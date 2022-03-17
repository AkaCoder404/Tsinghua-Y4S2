#include <iostream>
#include <string>

using namespace std;
string a;


void play(int rank) {
    int left = rank;
    int right = rank;

    // breaks when string is empty, you cannot a.at(0) on empty string
    char color = a.at(rank);

    printf("---------------------\n");
    cout << "ranks " << left << " " << right << "\n";
    cout << "strin " << a << "\n";
    
    
    // get all colors to left that are same
    while (left >= 0 && a.at(left) == color) --left;
    left += 1;

    // get all colors to right that are same
    while (right < a.size() && a.at(right) == color) ++right;

    // if amount of colors to right - amount colors to left are >= 3, we have 
    int size = right - left;
    cout << "sizes " << size << "\n";
    printf("---------------------\n");
    if (size >= 3) {

        // 
        a.erase(left, size);
        printf("Hello\n");
        play(left - 1);
    }
}

int main() {
    // initial beads
    getline(cin, a);
    int m = 0;

    // number of operations
    cin >> m;

    int rank; char color;
    for(int i = 0; i < m; ++i) {
        cin >> rank >> color;
        a.insert(a.cbegin() + rank, color);
        play(rank);
    }
    
    cout << a << endl;

    return 0;
}

// incorrect testcase
// ACCBA
// 5
// 1 B
// 0 A
// 2 B
// 4 C
// terminate called after throwing an instance of 'std::out_of_range'
//   what():  basic_string::at: __n (which is 18446744073709551615) >= this->size() (which is 0)
// Aborted