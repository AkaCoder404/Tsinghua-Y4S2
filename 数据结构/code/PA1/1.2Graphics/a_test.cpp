 #include<cstdio>
 #include<cstdlib>
 #include<cstring>
 #include<cctype>
 #include<iostream>
 #include<algorithm>
 using namespace std;
 const int BUF_SIZE = 30;
 char buf[BUF_SIZE], *buf_s = buf, *buf_t = buf + 1;
const int maxn = 200010;
 long long x[maxn], y[maxn];
int n, m;
bool toLeft(int num, long long _x, long long _y) {
     return (x[num] * _y + y[num] * (_x - x[num])) >= 0;
 }
int getcnt(long long _x, long long _y) {
    int l = 0, r = n + 1;
   while (l < r - 1) {
       int mid = (l + r) >> 1;
        if (!mid) break;
         if (toLeft(mid, _x, _y)) l = mid;
         else r = mid;
    }
   return l;
 }
 int main() {
    //  freopen("hahaha.in","r",stdin);
    //  freopen("hahaha.out","w",stdout);
     scanf("%d",&n);
     for (int i = 1; i <= n; ++ i)
        scanf("%lld",&x[i]);
    for (int i = 1; i <= n; ++ i)
        scanf("%lld",&y[i]);
    sort(x + 1, x + n + 1);
     sort(y + 1, y + n + 1);
     scanf("%d",&m);
     while (m --) {
         int _x, _y;
         scanf("%d%d",&_x,&_y);
         printf("%d\n", getcnt(_x, _y));
     }
     return 0;
 }