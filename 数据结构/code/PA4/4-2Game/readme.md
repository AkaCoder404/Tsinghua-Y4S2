# CST 4-2 Game
The purpose of this lab was to implement a shortest path finding algorithm to not only find the shortest path length, but also how many paths have that minimum solution. 

## Method 1: Dijkstra's using 2D Matrix
The first path finding algorithm for a directed graph with no negative weights was dijkstra's path finding algorithm. The most basic implementation uses a 2D matrix to store the paths between the two vertices. The values in the 2D matrix represent the weight between the two vertices, and thus matrix entries of zero state that there is no path between the two vertices. 

The weight of the edges is not directly stated in the problem, instead each level, or vertices has a certain "weight". Thus, we can instead treat outgoing edges as having a weight equal to the "weight" of the vertice is going from. 

Thus, djikstra's algorithm will give us the shortest path from the source node to every node in the graph. However, in this case, the only ones we are interested in is the source node and destination node of N. Thus the total time spent on level 1 to level N is equal to shortest path length + the time it takes to complete the final level.

In order to keep track of the number of shortest paths, we simply have to keep track of the number of shortest paths of the precursor nodes. If the new distance is the same, there are multiple shortest paths to v through u, then we will add the number paths to u and number paths to v together. Otherwise, if the new updated distance is less to v through u is less, we can copy the number of shortest paths to u into v.

The time complexity of djikstra's path finding algorithm for a 2D matrix is O(n^2), where n represents the number of vertices

This only received a 20/50, with a runtime error (signal 11), which probably suggest that there is a memory limit error, thus using a 2D matrix wastes too much space. 


## Method 2: Dijkstra's using Adjacency List
The concept of shortest path and find the number of shortest paths is the same as the matrix representation. In the previous method, we had to maintain two sets of information  about which vertices are already included in the shortest path tree and which ones are not. However, that would take O(V^2) time, this would perform extremely poorly for graphs with relatively few edges compared to nodes. 

With an adjacency list however, all the vertices can be traversed in O(V+E) time using a BFS algorithm. While traversing all vertices using BFS, we use a min heap to store the vertices that have not yet been finalized. The minheap is used as a priority queue to get the minimum distance vertex from the set of not included vertices. 

The time complexity of operations for extract-min are O(logV) for min heap. The dijkstra algorithm is pretty much the same as the 2D matrix, however, instead of looking through all possible vertices, and, it only takes O(1) time to find the next minimum distance, instead of the normal O(n) time.

The time complexity of using adjacency list representation with a min heap reduces the time complexity to O((V+E)logV), where V is the number of vertices and E is the number of edges.


## References 
- Dijkstra's Algorithm - https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
- Graph Representations - https://www.geeksforgeeks.org/graph-and-its-representations/
- Adjacency List for Graphs - https://www.youtube.com/watch?v=k1wraWzqtvQ&ab_channel=mycodeschool
