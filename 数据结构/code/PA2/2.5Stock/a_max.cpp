#include "stdio.h"
#include "string.h"
#include <cstdlib> // atoi
#include <iostream>

long long int DAYS = 0;
#define MAX_DATA 1e6

struct Investment {
  long long int days;
  long long int amount;
  Investment() {
    this->days = -1;
    this->amount = -1;
  }
  Investment(long long int days, long long int amount) : days(days), amount(amount) {}
};

struct Stack {
  // public:
  Stack() {
    capacity = MAX_DATA;
    stack = new Investment[capacity];
    loc = 0;
  }

  ~Stack() { delete[] stack; }

  bool empty() {
    if (loc == 0)
      return true;
    else
      return false;
  }

  void push(Investment value) {
    stack[++loc] = value;
  }

  Investment top() {
    return stack[loc];
  }

  Investment pop() {
    if (!empty())
      return stack[loc--];
    else
      return Investment();
  }

  // private:
  Investment *stack;
  long long int loc;
  long long int capacity;
};

struct Queap {
  Queap() {
    // while (!s1.empty())
    //   s1.pop();
    // while (!s11.empty())
    //   s11.pop();
    // while (!s2.empty())
    //   s2.pop();
    // while (!s22.empty())
    //   s22.pop();
  }

  void enqueap(Investment value) {
    s2.push(value);
    s22.push(s22.empty() ? value : (value.amount > s22.top().amount ? value : s22.top()));
  }

  Investment dequeap() {
    if (s1.empty()) {
      while (!s2.empty()) {
        Investment temp = s2.top();
        s22.pop();
        s1.push(s2.pop());
        s11.push(s11.empty() ? temp : (temp.amount > s11.top().amount ? temp : s11.top()));
      }
    }
    s11.pop();
    return s1.pop();
  }

  Investment max() {
    if (s1.empty()) {
      while (!s2.empty()) {
        Investment temp = s2.top();
        s1.push(s2.pop());
        s22.pop();
        s11.push(s11.empty() ? temp : (temp.amount > s11.top().amount ? temp : s11.top()));
      }
    }
    Investment temp = (s22.empty() ? s11.top() : s22.top());
    return s11.top().amount > temp.amount ? s11.top() : temp;
  }

  // private:
  Stack s1;  // beg of stack (basicly flip of s2 to pop from front)
  Stack s11; // priority min, min at top
  Stack s2;  // end of stack
  Stack s22; // priority min, min at top of stack
};

int main() {
  long long int N;
  Queap q;
  Investment *current = new Investment(0, 0); // current holding
  long long int money = 0;
  long long int days_head = 0;

  std::cin >> N;
  std::cin.ignore();
  N = N << 1; // 2 * N

  char name[100];
  for (long long int i = 0; i < N; i++) {
    long long int D = -1; // days
    long long int X = -1; // value
    std::cin.getline(name, 100);

    long long int posn = -1;
    long long int len = strlen(name);
    char *space_ptr = (strchr(name, ' '));
    if (space_ptr != NULL)
      posn = space_ptr - name;

    if (posn == -1) {
      char subrow[posn];
      memcpy(subrow, &name[0], len);
      subrow[len] = '\0';
      D = atoi(subrow);
    } else {
      // read first character
      char subrow[posn];
      memcpy(subrow, &name[0], posn);
      subrow[posn] = '\0';

      D = atoi(subrow);
      long long int len_of_second = strlen(name) - posn;
      char subsubrow[len_of_second];
      memcpy(subsubrow, &name[posn + 1], len_of_second);
      subsubrow[len_of_second] = '\0';
      X = atoi(subsubrow);
    }

    // dequeue
    if (X == -1) {
      // remove earliest invested
      DAYS += D;
      Investment temp = q.dequeap();
      // printf("pop %d, %d\n", temp.days, temp.amount);
      // printf("average money after pop %d\n", money);

      // if popped element is current day, get new max holding
      if (current->days == temp.days) {
        // printf("popped current investment %d %d on days %d to %d\n", current->days, current->amount, current->days, DAYS)
        money +=  (DAYS - current->days) * current->amount;
        days_head += (DAYS - current->days);
        *current = q.max();
        current->days = DAYS; // reset new start day
        // printf("new min investment day %d amount %d\n", current->days, current->amount);
      }
    } else {
      DAYS += D;
      // add new investment to queue
      Investment temp = Investment(DAYS, X);
      q.enqueap(temp); 
      // printf("current investment %d %d on day %d to %d at $%d\n", current->days, current->amount, current->days, DAYS, money);

      // if new queue is higher, get highest holding
      if (temp.amount >= current->amount) {
        money += current->amount == -1 ? 0 : (DAYS - current->days) * current->amount;
        days_head += (DAYS - current->days);
        *current = temp;
        // printf("average money before update $%d, new current %d, %d\n", money, current->days, current->amount);

      }
    }
  }

  // acount for last one
  money += (DAYS - current->days) * current->amount;
  days_head += (DAYS - current->days);
  // printf("%d\n", money);
  printf("%lld\n", money/days_head * DAYS);
  // printf("%d\n", DAYS);
  // printf("%d\n", days_head);
  return 0;
}


// 7 * 100 + 7 * 200 + 9 * 150 + 9 * 100 + 8 * 300 + 8 * 200
// 7 + 7 + 9 + 9 + 8 + 8