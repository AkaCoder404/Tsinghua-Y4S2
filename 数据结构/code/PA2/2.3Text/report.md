# PA2 报告

## 2.3 ⑨的完美文本编辑器

The core idea is to use a data structure that store characters and its relative position to in the document. 

### 方法一: 链表

This method is perhaps the most obvious one. Use a linked list where each node contains information regarding the next character, its previous character, and its successor character. Meanwhile use two pointers to keep track of the location of ‘[’ and ‘]’ in the text. Inserting characters is as easy as inserting a new node, and deleting a character is as easy as removing a node. Shifting the left or right bracket is also simple. Reversing part of the text was reversing all nodes (or just their values) of the characters between the two brackets. This was relatively easy to implement.

The implementation received a 15/50 on the 50% test. The rest of the cases were time limit exceeded. 

### 方法二：数组，Show 时后做 Reverse

It is simple to see that the bottleneck of this task lies in the reverse. Meaning, the test cases calls the reverse function many times throughout. For example, removing the reverse implementation of the first method gave me all wrong answers, but non of the test cases received time limit exceeded. Thus, we need to find a way to reduce the amount of times reverse is called. We also implemented an array based on the given tip. 
> 💡 使用数组集中存放链表节点可以提高效率

In order to implement this, we used three arrays `pre[], suf[], ch[]` to keep track of the location of the characters previous character, the location of the characters successor character, and the character at a specific index, respectively. We also keep track of the locations of the brackets using `pos[], cnt[]` representing the actual location with regards to the index, and the relative position. 

For example, with an input, abcde, we get 

```cpp
cha _ _  _ a b c d e 
pre 0 -1 7 1 3 4 5 6 
suf 0 3 -1 4 5 6 7 2 
pos 1 7
cnt 1 6
```

Here, the prefix of the character a, is `pre[3]`, which is 1 (or the character at `pre[1]` which is -1, in this case represents the a empty head, or the empty head of a linked list, thus showing that a has no previous),and the successor is `suf[3]` which is 4 (or the character at `ch[4]` which is b).

For the basic operations such as delete, insert, and shift brackets, it is relatively easy to understand. For example, every time we insert a new operation, we add it to the end of the array, and update the prefix and suffix arrays to point to this new character. 

For example, for the command `I L f`

```cpp
cha _ _  _ a b c d e f 
pre 0 -1 7 8 3 4 5 6 1 
suf 0 8 -1 4 5 6 7 2 3 
pos 8 7
cnt 2 7
```

Since at this moment, the text is as such

```cpp
[abcde]
```

and inserting at the left most bracket would give us

```cpp
[fabcde]
```

We insert f at the right most position of the array. And we update its `pre[], suf[]`

The prefix of f is the prefix of what a was, and the successor is a. Deleting an element simply re adjusts the prefix and suffix array without deleting an array character. 

The main difference lies in the ‘reverse’ and ‘show’ commands. Implementing a reverse during ‘show’ greatly improves the time complexity because it is called less. And the ‘reverse’ command simply sets up the prefix and suffix of the characters at the end (first and last) to do the reversing. 

Using abcde in the input, calling reverse results in

```cpp
cha _ _  _ a b c d e 
pre 0 -1 3 4 5 6 7 1 
suf 0 7 -1 2 3 4 5 6 
pos 1 3
cnt 1 6
```

As we can see, it sets the prefix of ‘a’ to point to ‘b’, and the suffix of ‘a’ to point ‘e’. The same logic is done for ‘e’. Thus, when show is called, we simply swap the prefix’s and suffixes when necessary. 

This implementation received a 85/90 on the 90 percent test, with the last test case being time limit exceeded. I did not know how to improve this algorithm any further.