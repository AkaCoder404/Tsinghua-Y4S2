#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 1e7;
char s[MAX_LENGTH]; // initial string
char r[MAX_LENGTH]; // results
int LEN = 0;
int COUNT = 0;      // 
int R_COUNT = 0;    // 
int RIGHT;
int LEFT;

        //10000000
// 1 < x < 3200000
// 1 < N < 4000000

void add(int x, char c); //  add character
void del(int x); // delete character
void rev(); // reverse characters
void pri(bool t); // print true false

struct T {
  int prev;
  int next;
  char c;
} text[MAX_LENGTH];

struct Bracket {
  int pos = 0;
  int global_pos = 0;
  void move_left() {
    if (text[pos].prev != -1) { // can still move left
      pos = text[pos].prev;
      global_pos--;
      pri(true);
    } 
    else pri(false);
  }

  void move_right() {
    if (text[pos].next) { // can still move right 
      pos = text[pos].next;
      global_pos++;
      pri(true);
    }
    else pri(false);
  };

  // insert new character
  void insert(char c) {
    add(pos, c);
    pos = text[pos].next;
    global_pos++;
    pri(true);
  }

  // remove character to the right
  void remove() {
    if(text[pos].next) {
      del(text[pos].next);
      pri(true);
    }
    else pri(false);
  };

} L, R;

void add(int x, char c) {
  ++COUNT;
  text[COUNT].prev = x;                 // new char's prev is inserted position
  text[COUNT].next = text[x].next;      // next char is at inserted positions next char
  text[text[x].next].prev = COUNT;      // insrted positions next char's previous position is new char
  text[x].next = COUNT;                 // insterted positions next char is new char
  text[COUNT].c = c;                    // set new char
  text[0].prev = -1;                    // 

  // save relative pos
}


void del(int x) {
  text[text[x].prev].next = text[x].next;  // deleted position's prev's next is set to deleted position's next
  text[text[x].next].prev = text[x].prev;   // deleted position's next's prev is set to deleted position's prev
  text[0].prev = -1;
}

void rev() {
}

void pri(bool t) {
  // printf("%s\n", t ? "T" : "F");
  r[R_COUNT++] = t ? 'T' : 'F';
}


int main() {

  // initial string
  scanf("%s", s);
  LEN = strlen(s);
  for (int i = 0; i < LEN; i++) {
    add(i, s[i]);
  }
  L.pos = 0;
  R.pos = LEN;
  L.global_pos = 0;
  R.global_pos = LEN;

  // number of operations
  long long int N;
  scanf("%lld", &N);
  // printf("%lld", N);

  char c, c1, c2; // https://stackoverflow.com/questions/20530556/scanf-not-waiting-for-input
  for (int i = 0; i < N; i++) {
    // printf("i = %d \n", i);
    scanf(" %c", &c); // scanf buggy?
    bool overlap = L.pos == R.pos ? true : false;
    switch(c) {
      case '<': 
        scanf(" %c", &c1);
        // move LEFT left
        if (c1 == 'L') {
          L.move_left();
          
        }
        // move RIGHT left
        else {
          R.move_left();        
        } 
        break;
      case '>':
        scanf(" %c", &c1);
        // move LEFT right
        if (c1 == 'L') L.move_right();
        // move RIGHT right
        else R.move_right();

        break;
      case 'I':
        scanf(" %c", &c1);
        scanf(" %c", &c2);
        // insert at LEFT
        if (c1 == 'L')  {
          L.insert(c2);  
          if (overlap) R.pos = L.pos;
        }
        // insert at RIGHT
        else {
          R.insert(c2);
          if (overlap) L.pos = R.pos;
        }
        break;
      case 'D':
        scanf(" %c", &c1);
        // delete at LEFT
        if (c1 == 'L') {
          L.remove();
          if (overlap) L.pos = R.pos;
        }
        // deletes at RIGHT
        else {
          R.remove();
          if (overlap) R.pos = L.pos;
        }

        break;
      case 'R':
        // reverse

  //        for(int i = 0; i <= COUNT ;i++) {
  //   printf("%c", text[i].c);
  // }
        rev();
        // else pri(false);

  //       printf("L %d R %d\n", L.pos, R.pos);
  //       printf("L %d R %d\n", L.global_pos, R.global_pos);
  //        for(int i = 0; i <= COUNT ;i++) {
  //   printf("%c", text[i].c);
  // }
        
        break;
      case 'S':
        // show
        for(int i = text[0].next; i; i = text[i].next) 
          printf("%c", text[i].c);
        printf("\n");
        break;
      case '\n': break;
    }
   
  }

  // for (int i = 0; i < R_COUNT; i++) {
  //   printf("%c\n", r[i]);
  // }
  // printf("L %d, R %d\n", L.pos, R.pos );

  // for(int i = 0; i <= COUNT ;i++) {
  //   printf("%c", text[i].c);
  // }
  return 0;
}


