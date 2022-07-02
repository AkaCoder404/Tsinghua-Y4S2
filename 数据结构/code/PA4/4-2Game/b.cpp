#include<cstdio>
#include<iostream>
#define maxn 1000
const int MAXV=1000;
const int INF=0x3fffffff;
 
using namespace std;

int N,M,C1,C2;
int graph[maxn][maxn];//存储顶点间边的信息
int difficulty[maxn];
int verWeight[maxn] ;//顶点权重 

//先求最短距离
bool vis[MAXV]={false};//表示已经访问过的节点，初始值都是为false，未访问; 如果为true，则表示已访问 
int d[MAXV] ; //dis中保留的是 源点到目标城市的访问距离 ，初始的情况下，距离都是最大值 

int pre[MAXV];//到顶点v的前驱节点 
int way[MAXV];//令起点s到顶点u的最短路径条数为num[u] 

void dijkstra(int s){
	fill(d,d+MAXV,INF);//fill函数将整个d数组赋值为INF 
	fill(way,way+MAXV,0);//将从源点到顶点的路径条数设置为0
		 
	d[s] = 0; //起点到自身的距离为0
	way[s] = 1;//起点到自身的路径为1 
	int i,j;
	for(i = 0;i< N; i++){
		int u = -1, MIN= INF ;//当前最短路径的这个顶点 	
		for(j = 0;j < N;j++){//第一层 for 循环是用于寻找当前尚未遍历节点中最短的那个路径
			//vis[j] == false => 尚未遍历 
			//最短路径 d[j] < MIN ，然后执行更新操作 
			if(vis[j] == false && d[j] < MIN){ //更新 MIN 值 			
				u = j;
				MIN = d[j];													
			}
		}
		
		if(u == -1)	return;
		vis[u] = true; //对节点u标记为已访问 
		for(int v = 0; v < N;v++){
			//如果节点v尚未访问 
			//并且有 u->v 的边
			//并且 d[u]+graph[u][v] < d[v] 
			if(vis[v] == false && graph[u][v]!=INF ){
				if(d[u]+graph[u][v] == d[v]) way[v] += way[u] ;//说明到v的最短路径有多条 
				if(d[u]+graph[u][v] < d[v]) {
					d[v] = d[u] + graph[u][v];//优化 d[v] 这个距离					
					pre[v] = u;//计算前驱节点
					way[v] = way[u];//如果最短路径相同，则可以单纯的复制即可 
				}				
			}
		}
	}
}

int main(){
  scanf("%d %d", &N, &M);
	fill(graph[0],graph[0]+MAXV*MAXV,INF);//初始化图G	

  for(int i = 0; i < N; i++) { // 便之间的权重
    scanf("%d", &difficulty[i]);
  }
	
	// int i,j;
	int ver1,ver2; 
	int weight;
	for(int i = 0; i< M;i++){
    scanf("%d %d", &ver1, &ver2);
		graph[ver1 - 1][ver2 - 1] = difficulty[ver1 - 1];//输入边之间的权重 	
	}
	
	dijkstra(0);
	for(int i = 0;i< N;i++){
		cout << d[i] <<" ";
	}cout <<"\n";
	
	cout<<"===========\n";
	for(int i = 0;i < N;i++) {
		cout <<i + 1<<"predecessor node is："<< pre[i] + 1<<"\n";
	}
	
	
	cout<<"===========\n";
	for(int i = 0;i < N;i++) {
		cout <<i + 1<<"has the path："<< way[i] + 1<<"\n";
	}

  printf("%d\n%d", d[N-1] + difficulty[N-1], way[N-1]);

}
