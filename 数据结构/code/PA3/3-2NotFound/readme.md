# CST 3-2 Not Found Report

The goal of this lab is to find the the lexographically smallest binary string not preset in the given string given a data set of $o$ and $1$


## Method 1 Brute Force
Lexographically create substrings and see whether or not they exists in the given string. 

## Method 2 Suffix Trie 
1. Create suffix tree from given string
2. BFS through Suffix Tree, find first missing transition and track that node.
3. Backtrack through tree reverse and print out everything

This achieved a 25/50
1-3 Accepted
4 Runtime Error (trap 14)
5-6 Accepted
7 Memory Limit Exceeded
8 Time Limit Exceeded
9-10 Runtme Error (trap 14)

## Method 3 Compressed Binary Suffix Tree



## Tips
1. 如何将输入数据存下来？
2. 答案的长度不会太大，可以枚举，但是之后如何判断？
3. 如何减少判断答案所需要的空间？

## Resources
Trie https://en.wikipedia.org/wiki/Ukkonen%27s_algorithm
Suffix Tree

Bitmaps
- https://en.wikipedia.org/wiki/Bit_array#Basic_operations
- https://layerlab.org/2018/06/07/My-bitmap.html