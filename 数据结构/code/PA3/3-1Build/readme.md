# CST 3.2 Not Found

## Left Child Right Sibiling Binary Tree
I used the concept of a left-child right siblig binary tree, a multi fork tree, which is implemented using an array, where each node contains the rank of its parent, its first child, and its next and previous sibilings. Building the tree is quite easy, taking O(n) time. 

Then in order to keep track of the height and scale of each subtree, we have to constantly update height and scale of each node during each move operation. 

Also, after the tree is build, we update the height and scale of the root node, or 1. This is done recursively through DFS by reaching a leaf node and back tracking to the starting node, increasing the height by one for each layer. The root node's height of a subtree is the max height of all its children + 1. The scale is similarily implemented, counting the number of nodes for each layer. 

Thus, height and size can be obtained in O(1) time.

In order to get the node by path, we simply traverse down the tree if it is getting the firstChild (rank is 0) of the node, otherwise, we keep iterating nextSibiling to get the sibiling with the rank we need. If the nodes still exists, keep searching, otherwise, read the rest of the inputs but don't do anything with them. Thus, locating the node does not exceed the cost, which has O(cost) time.

In order to move a subtree, we first have to get the source node, remove the subtree at the source node, get the target node, and insert the subtree at the target node. Since we have implemented this in an array, where each node has information pointing to its next and previous sibiling, as well as its parent and first child, moving and inserting a subtree would be like moving it in a linked list. 

During the process of removing a subtree, we have to two things.
   1. Update the scale of ancestor nodes by subtracting the scale of the subtree
   2. Update the height and scale of ancestor nodes, but we can stop when the height no longer changes, which means that the tree is fully updated
Inserting a subtree at the target node means increasing the scale of the ancesstor node by the scale of the subtree, and we can simply increase the height by 1. Moving and cutting a subtree only takes O(1), and the operation of updating the height and scale of does not exceed the sum of the two costs, which makes this time complexity O(cost).

## Complexity
If n represents the number of nodes, then:
   Space complexity is obviously O(n)
   Time complexity is O(n + sum of all costs), which should be done within time limit. 

## Results
I recieved a 70/90. I could not figure out how to improve the algorithm.


## 参考
https://www.geeksforgeeks.org/left-child-right-sibling-representation-tree/
https://en.wikipedia.org/wiki/Left-child_right-sibling_binary_tree