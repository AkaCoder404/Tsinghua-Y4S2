# CST 4-1 Circuit
## Background
Our goal was to find two components, defined by 64 output pins with either a low level (0) or high level(1) signal, that had the greatest value when we find the XOR of the two components. Each component would be defined by a 64 bit value of 1 and 0, we had to find components that would give us the greatest XOR value within a certain distance, K. In this case, distance would be defined by the order of the input. For example, the 1st input would be the 1st component, and the 3rd input would be the 3rd component, and its distance from the first component is 1. 

And if there are more than one greatest combination of 2 components, we find the earliest of the elements, and output its index.

## Method 1: Brute Force
This method maintained an array containing the components as a 64 bit unsigned integer, first by reading as string and then translating it into a `uint64_t`. Then I would do a linear search forward and backward K elements from each index, and finding the other component in which would give a maximum XOR. Thus, in this algorithm, we would have to have a time complexity of O(64n * 2k) = O(n * k) where k represent the linear search range we have to check and n represents the number of elements. The space complexity is O(64n)


## Method 2: Trie + Queue (List implementation)
The concept of finding the **maximum** XOR of the bit string can also be thought of as comparing prefixes of a string, and having the first prefix character that doesn't match earlier in the bit substring can be treated as a greater maximum XOR. For example, we can compare the three bit strings

```cpp
11011 // 1st
01101 // 2nd
11000 // 3rd
```

We can see that compared to the 1st bit string, the 2nd bit string would give a bigger XOR value, because the first bit 0 doesn't match, and therefore the XOR would result in 1. On the other hand, the first bit of the third string does match, and therefore the XOR would result in 0.

So thus we can use a Trie data structures, which often is good for finding out whether a string exists in our set of strings, and find the string where the earliest bit doesn't match.

In this binary trie, each element is either one or zero, and searching through the trie until reaching a terminal node will give the corresponding element (component). In this trie, each internal node records the number of components contained in its descendants, which is used to determine the direction when finding the target node. And since the 01 of multiple components maybe the same, we have used a Queue(list data structure) linked to the final node to record the sequence of components (earlier components are at the front, later components at the end).

The algorithm can be broken down into three parts, insert, search, and delete.

### Insertion
Insertion simply requires traveling down the trie, incrementing the child count if there is overlap, or creating a new node if necessary. At the leaf node (which represents the termination of the bit string), if it doesn't exist, create the node, and enqueue the component id. Nodes are stored in an array structure, which zero and one pointing to the zero and one children nodes.

### Deletion
Like insertion, this requires traveling down the trie, decrementing hthe child count, and finaly dequeing the queue located at the leaf node.

### Search (for maximum component)
In order to maximize the XOR, the value opposite to the 01 at a corresponding position in the trie should be selected each time a direction is selected. For example, if we are traversing down the tree for 11000, and we reach the 3rd bit, if that node also contains 1 as a child, then we should choose that direction. Otherwise, keep going down the tree. 

When reaching the final node, the queue head should contain the component that satisfies the conditions. At the same time, in order to prevent the current element from being fetched, it is necessary to judge the number of the current element, if it is not equal, directly take the one after the head, otherwise, take the next one after that.

The time complexity no longer requires a linear search, and thus is simply O(64n) or O(n). And the space complexity is O(64n) or O(n).