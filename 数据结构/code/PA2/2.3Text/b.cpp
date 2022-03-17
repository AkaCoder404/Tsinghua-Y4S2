#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;
#define N 10000000
int pre[N], suf[N];
char ch[N], st[N];
int idx, pos[2], cnt[2];

inline void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

void Insert(int opt, char c) {
    ++idx;
    ch[idx] = c;
    int u = pos[opt], v = suf[u];
    pre[idx] = u; suf[idx] = v;
    suf[u] = idx; pre[v] = idx;
    if (cnt[opt^1] >= cnt[opt]) cnt[opt^1]++;
    pos[opt] = idx; cnt[opt]++;
    if (pos[opt^1] == u) pos[opt^1] = idx;
    puts("T");
}

void LMove(int opt) {
    if (pos[opt] == 1) {
        puts("F");
        return ;
    }
    int u = pos[opt], v = pre[u];
    if (suf[v] != u) swap(suf[v], pre[v]);
    pos[opt] = v; cnt[opt]--;
    puts("T");
} 

void RMove(int opt) {
    if (suf[pos[opt]] == 2) {
        puts("F");
        return ;
    }
    int u = suf[pos[opt]], v = suf[u];
    if (pre[v] != u) swap(suf[v], pre[v]);
    pos[opt] = u; cnt[opt]++;
    puts("T");  
}

void Delete(int opt) {
    if (suf[pos[opt]] == 2) {
        puts("F");
        return ;
    }
    int u = pos[opt], v = suf[u], w = suf[v];
    if (pre[w] != v) swap(suf[w], pre[w]);
    if (cnt[opt^1] > cnt[opt]) cnt[opt^1]--;
    if (pos[opt^1] == v) pos[opt^1] = u;
    suf[u] = w; pre[w] = u;
    puts("T");
}

void Reverse() {
    if (cnt[1] - cnt[0] <= 0) {
        puts("F");
        return ;
    }
    if (cnt[1] - cnt[0] == 1) {
        puts("T");
        return ;
    }
    int a = pos[0], b = suf[a], c = pos[1], d = suf[c];
    swap(pre[b], suf[b]); swap(pre[c], suf[c]);
    suf[a] = c; pre[c] = a; suf[b] = d; pre[d] = b;
    pos[1] = b;
    puts("T");
}

void Show() {
    int u = 1;
    while (true) {
        if (pre[suf[u]] != u) swap(pre[suf[u]], suf[suf[u]]);
        u = suf[u];
        if (u == 2) break;
        putchar(ch[u]);
    }
    putchar('\n');
}

void Build() {
    scanf("%s",st);
    idx = 2;
    pre[1] = -1; suf[1] = 2;
    pre[2] = 1; suf[2] = -1;
    pos[0] = pos[1] = cnt[0] = cnt[1] = 1;
    int len = strlen(st);
    for (int i = 0; i < len; i++) {
        ++idx;
        ch[idx] = st[i];
        pre[idx] = i == 0 ? 1 : idx - 1;
        suf[idx] = i == len - 1 ? 2 : idx + 1;
    }
    if (len > 0) {
        suf[1] = 3; pre[2] = idx; 
        pos[1] = idx; cnt[1] = len + 1;
    } 
}

inline int Dir() {
    getchar();
    return getchar() == 'L' ? 0 : 1;
}

int main() {
    // freopen("editor.in", "r", stdin);
    // freopen("editor.out", "w", stdout);
    Build();
    int m;
    scanf("%d",&m);
    for (int i = 1; i <= m; i++) {
        getchar(); 
        char opt = getchar();
        while (opt != '<' && opt != '>' && !(opt >= 'A' && opt <= 'Z')) opt = getchar(); 
        if (opt == '<') LMove(Dir());
        else if (opt == '>') RMove(Dir());
        else if (opt == 'I') {
            int d = Dir();
            char c = ' ';
            while (c < 33 || c > 126) c = getchar();
            Insert(d, c);
        }
        else if (opt == 'D') Delete(Dir());
        else if (opt == 'R') Reverse();
        else if (opt == 'S') Show();
    }
    return 0;
}
