#include <iostream>

struct Node {
  Node *prev;
  Node *next;
  char c;
  int relative_pos;
  Node() {
    this->prev = nullptr;
    this->next = nullptr;
  }
  Node(Node *prev, Node *next, char c, int relative_pos) : prev(prev), next(next), c(c), relative_pos(relative_pos) {}
};

int main() {
  const int MAX_LENGTH = 1e7;
  int LEN = 0;
  std::string s;
  
  std::cin >> s;
  LEN = s.size();

  // initalize string
  Node *L = new Node(nullptr, nullptr, -1, -1 * MAX_LENGTH);
  Node *R = L;
  for (int i = 0; i < LEN; i++) {
    R->next = new Node(R, nullptr, s[i], i);
    R = R->next;
  }
  R->next = new Node(R, nullptr, -1, MAX_LENGTH);
  R = R->next;

  // keep track of head tail to print
  Node *head = L;
  Node *tail = R;
  L = L->next;
  long long int N;
  std::cin >> N;

  char c, c1, c2;
  for (int i = 0; i < N; i++) {
    Node *front = L;
    Node *back = R->prev;
    bool is_reverse = false;
    std::cin >> c;
    if (c == '<') {
      std::cin >> c1;
      // move LEFT left
      if (c1 == 'L') {
        if (L->prev != nullptr) {
          L = L->prev;
          std::cout << "T\n";
        } else {
          std::cout << "F\n";
        }
      }
      // move RIGHT left
      else {
        if (R->prev != nullptr) {
          R = R->prev;
          std::cout << "T\n";
        } else
          std::cout << "F\n";
      }
    } else if (c == '>') {
      std::cin >> c1;
      // move LEFT right
      if (c1 == 'L') {
        if (L->next != nullptr) {
          L = L->next;
          std::cout << "T\n";
        } else {
          std::cout << "F\n";
        }

      }
      // move RIGHT right
      else {
        if (R->next != nullptr) {
          R = R->next;
          std::cout << "T\n";
        } else
          std::cout << "F\n";
      }
    } else if (c == 'I') {
      std::cin >> c1 >> c2;
      // insert at LEFT
      if (c1 == 'L') {
        if (L == tail) {
          // insert before the tail
          Node *temp = new Node(L->prev, L, c2, L->prev->relative_pos + 1); // set new node's prev to be tails' prev, and new nodes next to be tail
          L->prev->next = temp;                                             // set tail's prev's next to be new node
          L->prev = temp;                                                   // set tail's prev to be new node
                                                                            // keep pointer on tail
        } else {
          // add node in front
          Node *temp = new Node(L->prev, L, c2, L->prev->relative_pos + 1); // set new node with next and prev
          L->prev->next = temp;                                             // current nodes prev's next is new node
          L->prev = temp;                                                   // current nodes prev is new node
                                                                            // make pointer the added node
        }

      }
      // insert at RIGHT
      else {
        if (R == tail) {
          Node *temp = new Node(R->prev, R, c2, R->prev->relative_pos + 1);
          R->prev->next = temp;
          R->prev = temp;
        } else {
          Node *temp = new Node(R->prev, R, c2, R->prev->relative_pos + 1);
          R->prev->next = temp;
          R->prev = temp;
        }
      }
      std::cout << "T\n";
    } else if (c == 'D') {
      std::cin >> c1;
      // delete at LEFT
      if (c1 == 'L') {
        if (L != head && L != tail) {
          L->prev->next = L->next;
          L->next->prev = L->prev;
          L = L->next;
          std::cout << "T\n";
        } else
          std::cout << "F\n";
      }
      // deletes at RIGHT
      else {
        if (R != head && R != tail) {
          R->prev->next = R->next;
          R->next->prev = R->prev;
          R = R->next;
          std::cout << "T\n";
        } else
          std::cout << "F\n";
      }
    } else if (c == 'R') {
      is_reverse = false;
      while (front != nullptr && back != nullptr && front->relative_pos <= back->relative_pos && front != back) {

        is_reverse = true;
        std::swap(front->c, back->c);
        front = front->next;
        back = back->prev;
      }
      if (is_reverse)
        std::cout << "T\n";
      else
        std::cout << "F\n";
    } else if (c == 'S') {
      for (auto i = head->next; i != tail; i = i->next) {
        std::cout << i->c;
      }
      std::cout << "\n";
    }
  }
  return 0;
}