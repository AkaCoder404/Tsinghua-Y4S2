#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

// https://www.1024sou.com/article/521263.html

string sn = "9873007613";
string sm = "87300676513";
int K = 5;
int m = 11;
int n = 10;
int F[10000][10000];

#define Min(a,b) ((a)>(b)?(a)=(b):0)
void Solve(){
	F[0][100]=0;
	for(int i=1;i<=K;i++)F[0][100+i]=i;
	for(int i=1;i<=K;i++)F[i][100-i]=i;
	for(int i=1;i<=n;i++){
		for(int j=max(1,i-K),je=min(m,i+K);j<=je;j++){
			F[i][j-i+100]=(sn[i]==sm[j]?F[i-1][j-i+100]:i+j);
			if(abs(j-i+1)<=K)Min(F[i][j-i+100],F[i-1][j-i+1+100]+1);
			if(abs(j-1-i)<=K)Min(F[i][j-i+100],F[i][j-1-i+100]+1);
		}
	}
	if(F[n][m-n+100]<=K)
	cout<<F[n][m-n+100]<<'\n';
	else cout<<"-1\n";
}

int main() {
  Solve();
}