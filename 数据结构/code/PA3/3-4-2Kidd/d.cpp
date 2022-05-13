#include<iostream>
using namespace std;
#define lc index*2 
#define rc index*2+1
#define ln index-1
#define rn index+1
#define length(index) tree[(index)].b-tree[(index)].a
#define upgrade(index) tree[(index)].sum=tree[lc].sum+tree[rc].sum;

class pockers{
public:
	int a,b;
	int lazy;
	int sum;
	int sum0;
	pockers(){
		lazy=-1;
	}	
};

pockers* tree;
int n,m;
//wake up children
inline void push(int index){ 
	tree[index].lazy*=-1;//change to waiting mode
	tree[lc].sum=tree[lc].sum0-tree[lc].sum;
	tree[rc].sum=tree[rc].sum0-tree[rc].sum;
	if(length(lc)>1){
		tree[lc].lazy*=-1;//change to sleep mode
		tree[rc].lazy*=-1;//change to sleep mode
	}
}

void change(int i,int j,int index){
	int a=tree[index].a;
	int b=tree[index].b;
	int mi=(a+b)/2;
	if(i<=a && b<=j){  // all 
		tree[index].sum=tree[index].sum0-tree[index].sum;
		if(length(index)>1){
			tree[index].lazy*=-1;	//switch mode {waiting/sleeping}
		}
		return;
	}
	if(tree[index].lazy==1){  //init,if need to renew, push the lazy tag down layer
		push(index);
	}
	if(a<=i && j<=b){
		if(j<=mi){
			change(i,j,lc);
			upgrade(index);
			return ;
		}else if(mi<=i){
			change(i,j,rc);
			upgrade(index);
			return;
		}else{
			change(i,mi,lc);
			change(mi,j,rc);  
			upgrade(index);
			return;
		}
	}
	else if(a<=i){
		if(i<mi){
			change(i,mi,lc);
			change(mi,b,rc);
			change(b,j,rn);
			upgrade(index);
			return;
		}
		else
		{
			change(i,b,rc);
			change(b,j,rn);
			upgrade(index);
			return;
		}
	}
	else {
		if(mi<j){
			change(a,mi,lc);
			change(mi,j,rc);  
			change(i,a,ln);
			upgrade(index);
			return;
		}
		else{
			change(a,j,lc);
			change(i,a,ln);
			upgrade(index);
			return;
		}
	}
}

int check(int i,int j,int index){
	int a=tree[index].a;
	int b=tree[index].b;
	int mi=(a+b)/2;
	if(i<=a && b<=j)
		return tree[index].sum;
	if(tree[index].lazy==1){  //init,if need to renew, push the lazy tag down layer
		push(index);
	}
	if(a<=i && j<=b)
		if(j<=mi){
			return check(i,j,lc);
		}else if(mi<=i){
			return check(i,j,rc);
		}else{
			return check(i,mi,lc)+check(mi,j,rc);
		}
	else if(a<=i){
		if(i<mi)
			return check(i,mi,lc)+check(mi,b,rc)+check(b,j,rn);
		else
			return				   check(i,b,rc)+check(b,j,rn);
	}
	else {
		if(mi<j)
			return check(i,a,ln)+check(a,mi,lc)+check(mi,j,rc);
		else
			return check(i,a,ln)+check(a,j,lc);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	scanf("%d%d",&n,&m);
	tree =new pockers[4*(n+1)]();
	int k=1;
    while(k<n){
         k<<=1;
	}
	for(int i=k;i<2*k;i++){
			if(i-k<n){
			 tree[i].sum=1;
			 tree[i].sum0=1;
			 tree[i].a=i-k+1;
			 tree[i].b=i-k+2;
			}else{
			tree[i].sum=0;
			tree[i].sum0=0;
			tree[i].a=i-k+1;
			tree[i].b=i-k+2;
			}
		}
	k>>=1;
	while(k>0){
		for(int index=k;index<2*k;index++){
			 tree[index].sum=tree[lc].sum+tree[rc].sum;
			 tree[index].sum0=tree[index].sum;
			 tree[index].a=tree[lc].a;
			 tree[index].b=tree[rc].b;
		}
		k>>=1;
	}
	int a,b,sum;
	char command[2];
	for(int i=0;i<m;i++){
	scanf("%s",command);
		if(command[0]=='Q'){
			scanf("%d%d",&a,&b);
			sum=check(a,b+1,1);
			printf("%d\n",sum);
		}
		else if(command[0]=='H'){
			scanf("%d%d",&a,&b);
			change(a,b+1,1);
		}
	}
	return 0;
}