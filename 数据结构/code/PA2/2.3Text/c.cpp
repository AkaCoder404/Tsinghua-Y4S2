#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXL=1e5;
int N;
char s[MAXL+10];
int len;

int tcnt;
struct T{int pre,next;char c;} text[MAXL*11+10];
void del(int x)
{
    text[text[x].pre].next=text[x].next;
    text[text[x].next].pre=text[x].pre;
    text[0].pre=-1;
}
void add(int x,char c)
{
    ++tcnt;
    text[tcnt].pre=x;
    text[tcnt].next=text[x].next;
    text[text[x].next].pre=tcnt;
    text[x].next=tcnt;
    text[tcnt].c=c;
    text[0].pre=-1;
}



struct C
{
    int pos;
    void pri(bool t){printf("%s\n",t?"T":"F");}
    void move(bool l)
    {
        if(l)
        {
            if(text[pos].pre!=-1)
            {
                pos=text[pos].pre;
                pri(true);
            }else pri(false);
        }else 
            if(text[pos].next)
            {
                pos=text[pos].next;
                pri(true);
            }else pri(false);
    }
    void insert(char c)
    {
        add(pos,c);
        pos=text[pos].next;
        pri(true);
    }
    void rm()
    {
            if(text[pos].next)
            {
                del(text[pos].next);
                pri(true);
            }else pri(false);
    }

} L,R;


void rev() {
  int front = text[L.pos].next;
  int back = R.pos;
  
  while (front != back && text[front].next != back && text[back].pre != front) {
    char temp = text[front].c;
    text[front].c = text[back].c;
    text[back].c = temp;
    front = text[front].next;
    back = text[back].pre;
  }

}

int main()
{
    // freopen("editor.in","r",stdin);
    // freopen("editor.out","w",stdout);
    int i;
    scanf("%s",s);
    len=strlen(s);
    for(i=0;i<len;i++) 
        add(i,s[i]);
    L.pos=0,R.pos=len;

    scanf("%d",&N);
    while(N--)
    {
        char c;
        do c=getchar(); 
        while(c<33||c>126);
        if(c=='<'||c=='>') 
        {
            bool left=c=='<'?1:0;
            do c=getchar(); while(c<33||c>126);
            if(c=='L') L.move(left);
            else R.move(left);
        }else if(c=='I')
        {
            do c=getchar(); while(c<33||c>126);
            if(c=='L')
            {
                do c=getchar(); while(c<33||c>126);
                L.insert(c);
            }else 
            {
                do c=getchar(); while(c<33||c>126);
                R.insert(c);
            }
        }else if(c=='D')
        {
            do c=getchar(); while(c<33||c>126);
            if(c=='L') L.rm();
            else R.rm();
        }else if (c=='R') {
          // rev();
        }
   
        
        else if(c=='S')
        {
            for(i=text[0].next;i;i=text[i].next)
                putchar(text[i].c);
            printf("\n");
        }
    }
    return 0;
}
