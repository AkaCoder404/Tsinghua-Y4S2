#include <iostream>
#include <string>

using namespace std;
string a;

void play(int rank) {
    printf("---------------------\n");
    cout << "rank " << rank << "\n";
    int left = rank;
    int right = rank;
    char color = a.at(rank);

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
        // makes sure that doesn't continue if left is smaller than size of string
        if (left < a.size()) {
            play(left);
        }
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