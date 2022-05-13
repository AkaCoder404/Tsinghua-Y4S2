# Report CST 3-8 Huffman

The purpose of this is to implement the Huffman algorithm to create the shortest binary encoding of a text. 

## Method 1
I used the huffman alogrithm with a minheap tree structure to improve the efficiency of getting the minimum node. 

The Huffman Algorithm is defined as such: 
1. find unique characters and their frequencies among the text
2. create a leaf node for each unique character and build a min heap of all the nodes (which allows access of minimum node, so we don't need linear search for smallest node) which stores the character and the freq
3. extract the two nodes with the minimum frequency from the min heap
4. create a new internal node that has a frequency of the sum of the two gotten from step 3 and add this node to the min heap.
5. repeat steps 3 and 4 until one remaining node is left, this is the root node of the fully encoded huffman tree

The min heap data structure is implemented using an array, where the parent node is at index $n$, and child nodes are at $2n+1$ and $2n+2$.


### Time Complexity
The time complexity is $O(n\log{n})$ where n is the number of unique characters. Since there are $n$ nodes, then the number of times the `extractMin` is called is $2(n-1)$ times. While `extractMin` takes $O\log{n}$ time because it calls `minHeapify`.

This was able to achieve 90 points on the 90% test, so no further improvements were made


## Resources
huffman algorithm - https://www.youtube.com/watch?v=dM6us854Jk0&ab_channel=CSBreakdown
how to create a min heap - https://www.youtube.com/watch?v=oAYtNV6vy-k&ab_channel=YusufShakeel
