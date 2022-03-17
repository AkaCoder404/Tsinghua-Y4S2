#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_LENGTH = 1e7;
char s[MAX_LENGTH];  // initial string
int LEN = 0;


struct Node {
  Node* prev;
  Node* next;
  char c;
  int relative_pos;
  Node() {
    this->prev = nullptr;
    this->next = nullptr;
  }
  Node(Node *prev, Node* next, char c, int relative_pos) : prev(prev), next(next), c(c), relative_pos(relative_pos) {}
};


int main() {
  scanf("%s", s);
  LEN = strlen(s);

  // initalize string
  Node *L = new Node(nullptr, nullptr, -1, -1 * MAX_LENGTH);
  Node *R = L;
  for(int i = 0; i < LEN; i++) {
    R->next = new Node(R, nullptr, s[i], i);
    R = R->next;
  }   
  R->next = new Node(R, nullptr, -1, MAX_LENGTH);
  R = R->next;

  // keep track of head tail to print
  Node* head = L;
  Node* tail = R;
  L = L->next;
  // number of operations
  long long int N;
  scanf("%lld", &N);

  char c, c1, c2; // https://stackoverflow.com/questions/20530556/scanf-not-waiting-for-input
  for (int i = 0; i < N; i++) {
    Node* front = L;
    Node* back = R->prev;
    bool is_reverse = false;
    scanf(" %c", &c); // scanf buggy?
    switch(c) {
      case '<': 
        scanf(" %c", &c1);
        // move LEFT left
        if (c1 == 'L') {
          if (L->prev != nullptr) {
            L = L->prev;  
            printf("T\n");
          }
          else {
            printf("F\n");
          }      
        }
        // move RIGHT left
        else { 
          if (R->prev != nullptr) {
            R = R->prev;
            printf("T\n");
          }
          else printf("F\n");
        } 
        break;
      case '>':
        scanf(" %c", &c1);
        // move LEFT right
        if (c1 == 'L') { 
          if (L->next != nullptr) {
             L = L->next; 
             printf("T\n");
          } 
          else {printf("F\n"); }
          
        }
        // move RIGHT right
        else { if (R->next != nullptr) {
 R = R->next;
 printf("T\n");
        } else printf("F\n");
        }
        break;
      case 'I':
        scanf(" %c", &c1);
        scanf(" %c", &c2);
        // insert at LEFT
        if (c1 == 'L')  {
          if (L == tail) {
            // insert before the tail
            Node *temp = new Node(L->prev, L, c2, L->prev->relative_pos + 1);    // set new node's prev to be tails' prev, and new nodes next to be tail
            L->prev->next = temp;                     // set tail's prev's next to be new node
            L->prev = temp;                           // set tail's prev to be new node
                                                      // keep pointer on tail
          }
          else {
            // add node in front
            Node *temp = new Node(L->prev, L, c2, L->prev->relative_pos + 1); // set new node with next and prev
            L->prev->next = temp;       // current nodes prev's next is new node
            L->prev = temp;             // current nodes prev is new node
                                    // make pointer the added node                                
          }
        
        }
        // insert at RIGHT
        else {
          if (R == tail) {
            Node *temp = new Node(R->prev, R, c2, R->prev->relative_pos + 1);
            R->prev->next = temp;
            R->prev = temp;
          }
          else {
            Node *temp = new Node(R->prev, R, c2, R->prev->relative_pos + 1);
            R->prev->next = temp;
            R->prev = temp; 
          }
         
        }
        printf("T\n");
        break;
      case 'D':
        scanf(" %c", &c1);
        // delete at LEFT
        if (c1 == 'L') {
          if (L != head && L != tail) {
            L->prev->next = L->next;
            L->next->prev = L->prev;
            L = L->next;
            printf("T\n");
          }
          else printf("F\n");
        }
        // deletes at RIGHT
        else {
           if (R != head && R != tail) {
            R->prev->next = R->next;
            R->next->prev = R->prev;
            R = R->next;
            printf("T\n");
          }
          else printf("F\n");
        }
        break;
      case 'R':
       is_reverse = false;
        while (front != nullptr && back != nullptr && front->relative_pos <= back->relative_pos && front != back
          
        ) {
          // swap c values
          is_reverse = true;
          // printf("front %c @ %d back %c @ %d \n", front->c,  front->relative_pos, back->c, back->relative_pos);
          std::swap(front->c, back->c);
          front = front->next;
          back = back->prev;
        }
        if (is_reverse) printf("T\n");
        else printf("F\n");
        break;
        // break;
      case 'S':
        // show
        for (auto i = head->next; i != tail; i = i->next) {
          printf("%c", i->c);
        }
        printf("\n");
        break;
      case '\n': break; 
    }
    // printf("L->%c R->%c\n", L->c, R->c);
  }
  // std::cout << L->c << " " << R->c << "\n";
  //   // printf("L %c R %c\n", L->c, R->c);
  // for (auto i = head->next; i != tail; i = i->next) {
  //   printf("%c", i->c);
  // }
   
   return 0;

  
}