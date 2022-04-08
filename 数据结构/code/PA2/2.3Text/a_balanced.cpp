// Linked List

#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAX_LENGTH = 1e6;
char s[MAX_LENGTH];     // initial string
int pre[MAX_LENGTH];    // prefix
                        // 1 and 2 represent head and trailer nodes, respectively
                        // pre[1] represents -1
                        // pre[2] represents tails prev
int suf[MAX_LENGTH];    // suffix
                        // 1 and 2 represent head and trailer nodes, respectively
                        // suf[1] represents heads succ
                        // suf[2] represents -1 
char ch[MAX_LENGTH];    // characters / text

int idx;                // insert new character at end of current ch
// position of [] relative to index at array
int pos[2];             // pos[0] is [
                        // pos[1] is ]
// position of [] relative to length                     
int cnt[2];             // cnt[0] is [
                        // cnt[1] is ]
void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

// debugging information
void pri() {
  printf("--------------------------\n");
  printf("cha ");
  for (int i = 0; i <= idx; i++) {
    printf("%c ", (ch[i] ==  '\0' ? '_' : ch[i]));
  } 
  printf("\npre ");
  for (int i = 0; i <= idx; i++) {
    printf("%d ", pre[i]);
  } 
  printf("\n");
  printf("suf ");
  for (int i = 0; i <= idx; i++) {
    printf("%d ", suf[i]);
  } 

  printf("\npos %d %d\n", pos[0], pos[1]);
  printf("cnt %d %d\n", cnt[0], cnt[1]);
  printf("--------------------------\n");
}

int main() {
  // initalize string
  scanf("%s", s);

  // set up prefix, suffix, and char array
  idx = 2;
  pre[1] = -1;    // root 
  pre[2] = 1;     // end of prefix
  suf[1] = 2;     // start of suffix
  suf[2] = -1;    // end of suffix
  pos[0] = pos[1] = cnt[0] = cnt[1] = 1;
  
  int len = strlen(s);
  // printf("%d\n", len);
  for (int i = 0; i < len; i++) {
    ++idx;
    ch[idx] = s[i];
    pre[idx] = i == 0 ? 1 : idx - 1;
    suf[idx] = i == len - 1 ? 2 : idx + 1;
  }

  if (len > 0) {
      suf[1] = 3;             // start of suffixes
      pre[2] = idx;           // end of prefix
      pos[1] = idx;           // location of ] in terms of array pos
      cnt[1] = len + 1;       // location of ] in terms of string size
  } 

  // pri();

  
  // number of operations
  int N;
  scanf("%d", &N);

  char c, c1, c2;
  for(int i = 0; i < N; i++) {
    scanf(" %c", &c); 
    switch(c) {
      // move brackets left
      case '<': {
        scanf(" %c", &c1);
        int opt = c1 == 'L' ? 0 : 1; 
        // can't move left anymore
        if (pos[opt] == 1) {
          printf("F\n");
          break;
        }
        else {
          int u = pos[opt];                       // get pos of []
          int v = pre[u];                         // get prefix of ch at location of []
          if (suf[v] != u) swap(suf[v], pre[v]);  // 
          pos[opt] = v;                           // set pos of [] to prefix< 
          cnt[opt]--;                             // shift [] left
          printf("T\n");                           
        }
        break;
      } 
      case '>': {
        scanf(" %c", &c1);
        int opt = c1 == 'L' ? 0 : 1; 
        if (suf[pos[opt]] == 2) {             // bracket at end
          printf("F\n");
          break;
        }
        int u = suf[pos[opt]];                // get position of [] in suf 
        int v = suf[u];                       // get suffix of []
        if (pre[v] != u) swap(suf[v], pre[v]);
        pos[opt] = u;                         // set pos of [] to be suffix of suf
        cnt[opt]++;                           // shift bracket right
        printf("T\n");
        break;
      }    
      case 'I': {
        // insert new element
        scanf(" %c", &c1);                           // bracket
        scanf(" %c", &c2);                           // character
        int opt = c1 == 'L' ? 0 : 1;                 
        ++idx;                  
        ch[idx] = c2;                                // store new char at highest location
        int u = pos[opt];                            // pos of []
        int v = suf[u];                              // suffix of pos of []
        pre[idx] = u;                                // set prefix of new char to be current pos of []
        suf[idx] = v;                                // set suffix of new char to be suffix of pos of []
        suf[u] = idx;                                // set suffix of character at [] to be position of new character
        pre[v] = idx;                                // set prefix of suffix of character at [] to be position of new character
        if (cnt[opt^1] >= cnt[opt]) cnt[opt^1]++;    // 
        pos[opt] = idx;                              // 
        cnt[opt]++;                                  // shift [] to right
        if (pos[opt^1] == u) pos[opt^1] = idx;       // if pos of other bracket is at the same location, set it to be new location of shifted bracket
        printf("T\n");
        break;
      }
      case 'D': {
        scanf(" %c", &c1);
        int opt = c1 == 'L' ? 0 : 1; 
        if (suf[pos[opt]] == 2) {     // nothing to the right
          printf("F\n");
          break;
        }
        int u = pos[opt];                           // pos of [] in terms of array
        int v = suf[u];                             // suffix of u
        int w = suf[v];                             // suffix of v (suffix suffix of u)
        if (pre[w] != v) swap(suf[w], pre[w]);    
        if (cnt[opt^1] > cnt[opt]) cnt[opt^1]--;
        if (pos[opt^1] == v) pos[opt^1] = u;
        suf[u] = w;                                 // set suffix of deleted location to suffix suffix
        pre[w] = u;                                 // set prefix of suffix suffix to point to deleted nocation
        printf("T\n");
        break;
      }
      case 'R': {
        // reverse the string
        // [ to the right of ], no reverse
        if (cnt[1] - cnt[0] <= 0) {
          printf("F\n");
          break;
        }
        // [ overlap ], reverse but doesn't do anything
        else if (cnt[1] - cnt[0] == 1) {
          printf("T\n");
          break;
        }

        // else reverse
        else { 
          // flip end nodes [] prev and succ 
          int a = pos[0];                 // pos of [ in terms of array
          int b = suf[a];                 // suffix of [ at pos of [
          int c = pos[1];                 // pos of ] in terms of array
          int d = suf[c];                 // suffix of ] at pos pf [
          swap(pre[b], suf[b]);           // swap the pre and suf of ch at [, starting suc of [
          swap(pre[c], suf[c]);           // swap the pre and suf of ch at ]
          // printf("\na = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
          // pri();
          suf[a] = c;                     // set [ successor to be tail
          pre[c] = a;                     // set tai's prev to be [
          suf[b] = d;                     // set head's succ to be b
          pre[d] = b;                     // set ] prev to be had
          pos[1] = b;                     // pos of ] set to loc of pos [ 
          printf("T\n");
          // pri();
        }
         break;  
      }
      case 'S': {  
        int u = 1; 
        while (true) {
          if (pre[suf[u]] != u) {
            // swap pref and suf to point in reverse direction unless already in the right direction
            // printf("swap(%d,%d) at (%d, %d)\n", pre[suf[u]], suf[suf[u]], suf[u], u);
            swap(pre[suf[u]], suf[suf[u]]);
            // printf("swap(%d,%d) at (%d, %d)\n", pre[suf[u]], suf[suf[u]], suf[u], u);
            // pri();
          }
          u = suf[u];           // next suffix
          if (u == 2) break;    // when reach end 
          printf("%c", ch[u]);   
        }
        printf("\n");
        // pri();
        break;
      } 
      case '\n': break;
    }
  }
  return 0;
}