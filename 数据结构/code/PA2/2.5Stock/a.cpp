// Description
// "The general trend of the world is that
// if it is divided for a long time, it must be united,
// and if it is united for a long time,
// it must be divided."
// The same is true for the stock market:
// new shares are continuously issued,
// and old shares are withdrawn one after another.

// The period between issuance and exit is called the active period of the stock.

// https://en.wikipedia.org/wiki/Queap

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <cstdlib> // atoi
#include <iostream>

int DAYS = 0;

#define MAX_ROW_LENGTH 256
#define MAX_DATA 1e8
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct Investment {
  int days;
  int amount;
  Investment() {
    this->days = -1;
    this->amount = -1;
  }
  Investment(int days, int amount) : days(days), amount(amount) {}
};

template <class T>
class Stack {
  public:
  // bool empty(); // check if stack is empty
  // void push(T); // push onto stack
  // T pop();      // pop the last element
  // T top();      // get the last element

  Stack() {
    capacity = MAX_DATA;
    stack = new T[capacity];
    loc = 0;
  }

  ~Stack() { delete[] stack; }

  bool empty() {
    if (loc == 0)
      return true;
    else
      return false;
  }

  void push(T value) {
    stack[++loc] = value;
  }

  T top() {
    return stack[loc];
  }

  T pop() {
    if (!empty())
      return stack[loc--];
    else
      return Investment();
  }

  private:
  T *stack;
  int loc;
  int capacity;
};

// template <class T>
// Stack<T>::~Stack() {
//   delete[] stack;
// }

// template <class T>
// bool Stack<T>::empty() {
//   if (loc == 0)
//     return true;
//   else
//     return false;
// }

// template <class T>
// void Stack<T>::push(T value) {
//   stack[++loc] = value;
// }

// template <class T>
// T Stack<T>::pop() {
//   if (!empty())
//     return stack[loc--];
//   else
//     return Investment();
// }

// template <class T>
// T Stack<T>::top() {
//   return stack[loc];
// }

template <class T>
class Queap {
  public:
  Queap();
  void enqueap(T); // add value to top
  T dequeap();     // remove value from bottom
  T min();         // get the min of stack
  T max();         // get max of stack
  private:
  Stack<T> s1;  // beg of stack (basicly flip of s2 to pop from front)
  Stack<T> s11; // priority min, min at top
  Stack<T> s2;  // end of stack
  Stack<T> s22; // priority min, min at top of stack
  Stack<T> stack_inv;
};

template <class T>
Queap<T>::Queap() {}

template <class T>
void Queap<T>::enqueap(T value) {
  s2.push(value);
  // s22.push(MIN(value.amount, s22.empty() ? value.amount : s22.top().amount);
  s22.push(s22.empty() ? value : (value.amount < s22.top().amount ? value : s22.top()));
}

template <class T>
T Queap<T>::dequeap() {
  if (s1.empty()) {
    while (!s2.empty()) {
      T temp = s2.top();
      s22.pop();
      s1.push(s2.pop());
      s11.push(s11.empty() ? temp : (temp.amount < s11.top().amount ? temp : s11.top()));
    }
  }
  s11.pop();
  return s1.pop();
}

template <class T>
T Queap<T>::min() {
  if (s1.empty()) {
    while (!s2.empty()) {
      T temp = s2.top();
      s1.push(s2.pop());
      s22.pop();
      s11.push(s11.empty() ? temp : (temp.amount < s11.top().amount ? temp : s11.top()));
    }
  }
  T temp = (s22.empty() ? s11.top() : s22.top());
  return s11.top().amount < temp.amount ? s11.top() : temp;
}

template <class T>
T Queap<T>::max() {
  return Investment();
}

int main() {
  int N;
  // https://stackoverflow.com/questions/42257456/fgets-doesnt-work-in-the-loop
  // https://stackoverflow.com/questions/4214314/get-a-substring-of-a-char
  // char buffer[100];
  // fgets(buffer, 100, stdin);
  // sscanf(buffer, "%i", &N);
  // scanf("%d", &N);
  std::cin >> N;
  std::cin.ignore();
  N = N << 1; // 2 * N

  Queap<Investment> q;                        // create queap
  Investment *current = new Investment(0, 0); // current holding
  int money = 0;

  // char *row = (char *)malloc(sizeof(char) + MAX_ROW_LENGTH);
  for (int i = 0; i < N; i++) {
    // use fgets to get entire line
    // fgets(row, MAX_ROW_LENGTH, stdin);
    // if ((strlen(row) > 0) && (row[strlen(row) - 1] == '\n'))
    //   row[strlen(row) - 1] = '\0';

    // // printf("string [%s]\n", row);

    // // find position of first space
    // int posn = -1;
    // char *space_ptr = (strchr(row, ' '));
    // if (space_ptr != NULL)
    //   posn = space_ptr - row;
    // // printf("pos %d\n", posn);

    int D = -1; // days
    int X = -1; // value
    // int len = strlen(row);
    // // if first space doesn't exist, then there is only one character
    // if (posn == -1) {
    //   char subrow[posn];
    //   memcpy(subrow, &row[0], len);
    //   subrow[len] = '\0';
    //   // printf("subrow %s\n", subrow);

    //   D = atoi(subrow);
    //   // printf("Input 1 [%d]\n", D);

    // }
    // // if first space exists, then there are two
    // else {
    //   // read first character
    //   char subrow[posn];
    //   memcpy(subrow, &row[0], posn);
    //   subrow[posn] = '\0';
    //   // printf("subrow %s\n", subrow);

    //   D = atoi(subrow);
    //   // printf("Input 1 [%d]\n", D);
    //   // read second character
    //   int len_of_second = strlen(row) - posn;
    //   char subsubrow[len_of_second];
    //   memcpy(subsubrow, &row[posn + 1], len_of_second);
    //   subsubrow[len_of_second] = '\0';
    //   X = atoi(subsubrow);
    //   // printf("Input 2 [%d]\n", X);
    // }

    char name[256];
    // std::cin.ignore();
    std::cin.getline(name, 256);
    std::cin.ignore();

    int posn = -1;
    int len = strlen(name);
    char *space_ptr = (strchr(name, ' '));
    if (space_ptr != NULL)
      posn = space_ptr - name;

    if (posn == -1) {
      char subrow[posn];
      memcpy(subrow, &name[0], len);
      subrow[len] = '\0';
      D = atoi(subrow);
    }
    else {
      // read first character
      char subrow[posn];
      memcpy(subrow, &name[0], posn);
      subrow[posn] = '\0';
      // printf("subrow %s\n", subrow);

      D = atoi(subrow);
      // printf("Input 1 [%d]\n", D);
      // read second character
      int len_of_second = strlen(name) - posn;
      char subsubrow[len_of_second];
      memcpy(subsubrow, &name[posn + 1], len_of_second);
      subsubrow[len_of_second] = '\0';
      X = atoi(subsubrow);
      // printf("Input 2 [%d]\n", X);
    }

    // printf("Inputs %d, %d\n", D, X);

    // dequeue
    if (X == -1) {
      // remove earliest invested
      DAYS += D;
      Investment temp = q.dequeap();
      // printf("pop %d, %d\n", temp.days, temp.amount);
      // printf("average money after pop %d\n", money);
      // if earliest invested is one being currently invested
      // pick next smallest investment to switch to
      if (current->days == temp.days) {
        // printf("popped current investment %d %d on days %d to %d\n", current->days, current->amount, current->days, DAYS);
        money += (DAYS - current->days) * current->amount;
        *current = q.min();
        current->days = DAYS;
        // printf("new min investment day %d amount %d\n", current->days, current->amount);
        // update money

      }
      // otherwise
      else {
      }
    } else {
      DAYS += D;
      // insert new investment into stack
      Investment temp = Investment(DAYS, X);
      q.enqueap(temp); // add tostack
      // printf("current investment %d %d on day %d to %d at $%d\n", current->days, current->amount, current->days, DAYS, money);
      // if new investment has higher holding than current investment, this is new investment
      if (temp.amount >= current->amount) {
        // update current money = days past until current change unless nothing currently invesed
        money += current->amount == -1 ? 0 : (DAYS - current->days) * current->amount;
        *current = temp;

        // printf("average money before update $%d, new current %d, %d\n", money, current->days, current->amount);
        
      }
    }
  }
  // free(row);
  money += (DAYS - current->days) * current->amount;
  // printf("money %d days %d\n", money, DAYS);

  printf("%d", money);
  return 0;
}

// 2*100 + 7*200 + 4*150 + 8*300 + 2*200