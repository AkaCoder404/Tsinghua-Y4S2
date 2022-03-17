#include <iostream>
#include <string>

using namespace std;
string a;

void play(int rank) {
    int left = rank;
    int right = rank;

    // if string is empty, and call rank when 0, out of range error
    char color = a.at(rank);

    printf("---------------------\n");
    cout << "ranks " << left << " " << right << "\n";
    cout << "strin " << a << "\n";
    

    while (left >= 0 && a.at(left) == color) --left;
    left += 1;
    while (right < a.size() && a.at(right) == color) ++right;


    cout << "ranksafter " << left << " " << right << "\n";

    int size = right - left;
    cout << "sizes " << size << "\n";
    printf("---------------------\n");
    if (size >= 3) {
        a.erase(left, size);

        int next = left;
        if (left - 1 >= 0) next = left - 1;
        play(next);
    }
}

int main() {
    getline(cin, a);
    int m = 0;
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

// terminate called after throwing an instance of 'std::out_of_range'
//   what():  basic_string::at: __n (which is 0) >= this->size() (which is 0)
// Aborted