#include <cstdio>
#define MAX 1049000
#define LENGTH 24

unsigned int nodes[MAX] = {0};
char buffer[LENGTH + 5];
int bufferTail = 0;
int rankList[LENGTH + 24];
int rankTail = 0;

void search(){
    // Find the first node with 0, backtrack up to find the corresponding string, and output in reverse order
    for(int i = 1; i < (1 << (LENGTH + 1)) - 1; i++)
        if((nodes[i >> 5] & ((unsigned int) 1 << (i % 32))) == 0) break;
    char stack[LENGTH + 5];
    int stackTail = 0;
    while(i > 0){
        stack[stackTail++] = i % 2 == 0 ? '1' : '0';
        i = (i - 1) >> 1;
    }
    for(int i = stackTail - 1; i >= 0; i--)
        putchar(stack[i]);
    putchar('\n');
}

int main(){
    int rank = 0;
    while(true){
        // Insert the node whose length is before the last 24, and calculate the rank by right shift recursion
        char chr = fgetc(stdin);
        if(chr == '\n') break;
        buffer[bufferTail++ % LENGTH] = chr;
        int left = bufferTail - LENGTH, right = bufferTail;
        rank <<= 1;
        if(chr == '1') rank++;
        rank &= ((1 << LENGTH) - 1);
        if(left > 0){
            int tmp = (1 << LENGTH) - 1 + rank;
            nodes[tmp >> 5] |= (1 << (tmp - ((tmp >> 5) << 5)));
        }
    }
    for(int i = bufferTail - LENGTH > 0 ? bufferTail - LENGTH : 0; i < bufferTail; i++){
        // Process the last 24 characters individually and insert them one by one, this part takes very little time
        int left = i, right = bufferTail;
        rank = 0;
        for(int j = left; j < right; j++)
            rank = buffer[j % LENGTH] == '0' ? (rank << 1) + 1 : (rank << 1) + 2;
        nodes[rank >> 5] |= (1 << (rank - ((rank >> 5) << 5)));
        rankList[rankTail++] = rank;
    }
    // Update all the nodes on the previous path of the leaf nodes on the 24th layer, which takes a long time
    for(int i = (1 << LENGTH) - 1; i < (1 << (LENGTH + 1)) - 1; i++){
        rank = i;
        if((nodes[rank >> 5] & (1 << (rank - ((rank >> 5) << 5)))) > 0){
            rank = (i - 1) >> 1;
            while(rank > 0 && (nodes[rank >> 5] & (1 << (rank - ((rank >> 5) << 5)))) == 0){
                nodes[rank >> 5] |= (1 << (rank - ((rank >> 5) << 5)));
                rank = (rank - 1) >> 1;
            }
        }
    }
    // Update the last 24 nodes, the end point is not on the leaf node, the time is short
    for(int i = 0; i < rankTail; i++){
        rank = (rankList[i] - 1) >> 1;
        while(rank > 0 && (nodes[rank >> 5] & (1 << (rank - ((rank >> 5) << 5)))) == 0){
            nodes[rank >> 5] |= (1 << (rank - ((rank >> 5) << 5)));
            rank = (rank - 1) >> 1;
        }
    }
    // Find the lexicographically smallest node and print the result.
    search();
    return 0;
}