# CST4-8 Process Schedule

## Background 
The goal of this experiment was to implment a process scheduler that would always run the process with the max priority at a given time. 

A `process` object kept track of the process' id, priority, creation time, and execution time. 

## Method 1: Brute Force Method
The brute force method requires doing a linear search throughout all processes to find the one with the maximum priority as long as the creation time is currently less than the current time and that the execution time is zero (the process has finished executing). This linear search takes O(n) time, and if the time it takes to finish all processes is T, then the total time complexity is $O(T * n)$. The space complexity is simply $O(n)$

## Method 2: Priority Queue
By implementing a priority queue, we check the process with the max priority with O(1) time complexity. 

The priority queue is implemented using a binary heap tree (array implementation), where each process represents a node on the heap. Two important parts is the `minHeapify`, `insertMinHeap`, and `extractMin` function. The left child is denoted at 2 * idx + 1, and the right child is denoted at 2 * idx + 2

`minHeapify` builds the heap, which the tree has to satisfy the heap invariant, which means that every element's parent is less than itself, or that the child is always greater than its parent. Building the heap generally takes O(n) time complexity. In our casee, the process with the current priority is at the top. 

`insertMinHeap` is simply handles inserting a new process into the heap, and makes the heap invariant still stays true. This generally takes O(log(n)) time.

`extractMin` simply removes the node at the top of the heap, and calls `minHeapify` to rebuild the tree.

### Implementation
First, we store all the processes in an array. 

For every unit of time, we first check if there are processes that have been created within the current time, if it has, then we simply add it to our minHeap. Then, we peek the minheap to see if the current processes' priority is greater than or less than the process with max priority. If it is less than, then we switch out the process with the current max. Then we decrement the current proccesses'execution time by 1. 

If the execution time of the current proccess is 0, we extract that process, print out the id and current time, and set the current processes to be the max priority of proccesses in heap, and increment the time.

If the execution time of current processes is not zero, we simply increment the time, and redo the previous parts.

Since we use pointers, the space complexity is still O(n).

## References
https://en.wikipedia.org/wiki/Priority_queue
https://www.geeksforgeeks.org/priority-queue-using-array-in-c/