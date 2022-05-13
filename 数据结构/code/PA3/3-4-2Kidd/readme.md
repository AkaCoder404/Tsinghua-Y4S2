# CST 3-4-2 Kidd Report

THis problem requires us to implement to track the number of flips per playing card. 

## Method 1 Brute Force using Array
This method declared an array with size of the maximum number of nodes, which was $1\leq n < 2^{31}$. This method, when getting the input command of `H`, we would iterate through index `left` to `right` and flip the cards. In this case, we would simply increase the value at that index `arr[i]` by one.

Then when recieving the input command of `Q`, we would simply iterate through the array, and add up all the sums of the values of `arr[i]` where $\\text{left} \leq i \leq \text{right}$ These two funtions, `update` and `summation`, both have a time complexity of $O(n)$. `update` for a single has a time complexity of `O(1)`, but it has to be done `n` itself

This algorithm only received 20/50, the rest were runtime error (too much memory), therefore the current speed was not the problem, but the amount of memory being used.


## Method 2 Segment Tree
According to the tip, the algorithm could be improved by implementing a Segment Tree. A segmemnt tree could be implenented in a similar way to the Huffman Encoding Tree, using an array, and where the children of a node is located at `2 * pos + 1` and `2 * pos + 2`, where `pos` is the location of the parent node. 

A segmemnt tree,

The algorithm can be split into 3 parts, `constructSegmentTree`, `getSum`, and `updateNode`, where we build the tree using the given results. In this case, building the segment tree can be ignored, because all the initial values are simply 0, and thus we just have to declare an array large enough to store the nodes. `getSum` get's the sum of the times the cards were flipped and `updateNode` flips the cards between left and right.

### Time Complexity and Space Complexity
The size of a segmemnt tree, or the space complexity, like any tree, depends on the number of nodes there are. 

The total number of leaf nodes is at least `n`,  and the total number of internal nodes is `n-1`, but generally, to build a segmemnt tree of array size `n`, we need to use a tree of `4*n` nodes. This is to account for empty leaf nodes. 

We can ignore construction because we don't need to build the tree with any specific values.

The time complexity for  `updateNode` only takes `log(n)` because as we traverse down the tree, we can see that we only need to update one index on each level, so we recursively call the update function for the node until we reach the leaf node, then it backtracks updating all the ancestor nodes.

The `getSum` function operates in a similar fashion, such that we only need `log(n)` to find the total range covering all the sums.

However, this method still requires a high space complexity, even more than the first, thus it still only received a 20/50


### Method 3 Improved Segment Tree
In this problem, clearly, the yumber of playing cards is too large, directly implementing the a segmement tree where each playing card represents a leaf node, which requires a maximum of $4n=2^{33}$ nodes, exceeds the allowable space.

Therefore, it is necessary to read all the query and left and right update/sum bounds, discretize the interval, and store the smallest interval segment in each leaf node. 

Also, during the search process, if an interval that needs to be updated or queried completely overlap with a parent node, there is no need to modify the parent's sucessor, and it can be temporarily recorded by a `tag` attribute. 


First we have to preprocess to get the smallest interval segmemnts. 
1. We store each row of inputs accordingly. 
2. Then all the endpoints of all possible smallest intervals are stored in the array of `endPoints`. Only the right endpoints of all intervals are stored since the it is a closed interval. 
3. Therefore, `left - 1` and `right` need to be stored in `endPoints` and this can be done in linear time.
4. Then we can sort `endPoints` and remove duplicates to get all the right endpoints of the smallest interval.

Then we build the tree as in any segment tree.

The function `updateNode` is used to flip all the intervals between `left` and `right` in the nodes wose rank. The `value` of the corresponding node is increased by `right - left + 1`. `updateNode`'s base case is when the interval of the node whose `rank` completely overlap with the interval `left` and `right`.

The addition of `tag` means that we don't have to traverse all child nodes, and just increase the `tag` of the parent node by one. 

If the `base` case is not met, that means the recursive termination condition is not met, and thus we must continue recursively downwards. 
1. determine whether the current node as a tag, if there is
2. add $tag \cdot (right - left + 1)$ to the `value` of the current node, then pass the `tag` to the left and right children,
3. reset the `tag` of the current node to be zero.
   
Finally, we select the part of the left and right children of the current node that overlaps with the interval for recursive modification. 

The `getSum` operation is pretty similar. If the current node overlap with the left and right interval, return `tag \cdot (right - left + 1) directly. 

Otherwise, we have to recursively go down deeper. We handle the `tag` similarily to the `updateNode` function. 

Then we recursively go down deeper until the nodes below will coincide with the current node.


### Time Complexity and Space Complexity
Since now the amount of space required is dependent on $m$, the overal space cost when building tree nodes is $O(m)$

The time complexity of this problem mainly occurs during the sorting of all the `edgePoints`, `getSum`, and `updateNode` take up $O(m\cdot \log{m}$ and , where as building the tree `constructSegmentTree` only requires `O(m)` time complexity. 
Therefore the total time complexity of this problem is $O(m\cdot \log{m}$


## Tips
1. Segment Tree
2. 参考讲义同一节中"Merge At Common Ancestors"的内容，Segment Tree 中每个内部节点保存所有 merge 到该节点的反转次数（懒惰标记）。
3. 结果可能很大，注意用 long long 存储。

## References
Segment Tree
- https://en.wikipedia.org/wiki/Segment_tree

Quick Sort
- https://www.geeksforgeeks.org/quick-sort/
