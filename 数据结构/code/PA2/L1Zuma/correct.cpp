#include <iostream>
#include <list>
#include <string>
using namespace std;

void bang(list<char> & beads, int id, char bead){
    list<char>::iterator i, r, l;
    int num = 0;    /*计数*/
    i = beads.begin();
    advance(i, id);
    beads.insert(i, bead);  /*插入元素*/

    /*考虑到多次消除的可能，使用while循环进行消除*/
    while(1){
        if(beads.size() < 3)
            break;
        
        num = 0;
        r = i--;    
        /*这步操作之后r指向被插入元素以后，i指向被插入元素*/
        
        for(; r != beads.end(); r++){
            if(*r == *i)    num ++;
            else    break;
        }           /*向右判断*/

        l = i;          
        /*if(i != beads.begin()){
            l--;
            while (1){
                if(*l != *i){   l++;break;} //l需要加加
                else    num ++;
                
                if(l == beads.begin())  break;
                else    l--;    
            }
        }   //向左判断*/

        /*由流程图发现的简化方法*/
        while(l != beads.begin()){
            l--;
            if(*l != *i){   l++; break;}
            else    num++;
        }


        /*删除部分*/
        if(num > 1){
            beads.erase(l, r);
            i = r;
        }
        else
            break;
    }


    /*输出*/
    if(beads.empty())
        cout << '-' << endl;
    else{
        for(i = beads.begin(); i != beads.end(); i++)
            cout << *i;
        cout << endl;
    }
    return ;
}
int main(){
    int n, id;
    char bead;
    string initial_beads;
    list<char> beads;

    getline(cin, initial_beads);
    for(int i = 0; i < initial_beads.size(); i++){
        beads.push_back(initial_beads[i]);
    }
    /*构造初始状态*/

    cin >> n;
    while(n--){
        cin >> id >> bead;
        bang(beads, id, bead);
    }
    return 0;
}