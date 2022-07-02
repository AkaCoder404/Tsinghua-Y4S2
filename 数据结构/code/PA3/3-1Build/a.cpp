#include <cstdio>
#define MAXSIZE 1005000

class Node {
  public:
  int parent;
  int nextSibling;
  int prevSibling;
  int firstChild;
  int height;
  int scale;
  Node() : parent(0), nextSibling(0), prevSibling(0), firstChild(0), height(0), scale(0){};
};

class Tree {
  public:
  Node nodes[MAXSIZE]; // array implementation

  // build tree
  void buildTree(int size) {
    for (int i = 1; i <= size; i++) {
      int numChildren; // 孩子个数
      scanf("%d", &numChildren);
      if (numChildren) { // 不等于0时
        int tmp1, tmp2;
        scanf("%d", &tmp1);
        nodes[tmp1].parent = i;                 // 第一个child父母为i
        nodes[i].firstChild = tmp1;             // i的第一个child为
        for (int j = 1; j < numChildren; j++) { // 剩下的孩子
          scanf("%d", &tmp2);
          nodes[tmp2].prevSibling = tmp1;
          nodes[tmp1].nextSibling = tmp2;
          nodes[tmp2].parent = i;
          tmp1 = tmp2;
        }
      }
    }
  }
  // get child (with rank rank) of parent
  int getChild(int parent, int rank) {
    int targetNode = nodes[parent].firstChild;
    while (rank--) {
      targetNode = nodes[targetNode].nextSibling;
    }
    return targetNode;
  }
  // get node using path
  int getNode() {
    int pathLength;
    int tmp;
    int parent = 1;
    int child;
    scanf("%d", &pathLength);
    while (pathLength-- > 0) {
      scanf("%d", &tmp);
      child = getChild(parent, tmp);
      if (child) // if more children, keep going down path
        parent = child;
      else // if no more children, break
        break;
    }
    while (pathLength-- > 0) // read remaining useless arguments if any
      scanf("%d", &tmp);
    return parent; // return searched node
  }
  // remove subtree
  void removeNode(int srcNode) {
    int parent = nodes[srcNode].parent;

    // if srcNode is the firstChild
    if (nodes[nodes[srcNode].parent].firstChild == srcNode) {
      nodes[nodes[srcNode].parent].firstChild = nodes[srcNode].nextSibling;
      nodes[nodes[srcNode].nextSibling].prevSibling = 0;
    } else { // it is not firstChild
      nodes[nodes[srcNode].prevSibling].nextSibling = nodes[srcNode].nextSibling;
      nodes[nodes[srcNode].nextSibling].prevSibling = nodes[srcNode].prevSibling;
    }

    // update scale of all ancestors
    while (parent) {
      nodes[parent].scale -= nodes[srcNode].scale;
      parent = nodes[parent].parent;
    }

    // update ancestor heights if necessary
    parent = nodes[srcNode].parent;
    int child = srcNode;
    while (parent) {
      int oldHeight = nodes[parent].height;
      update(parent);
      if (nodes[parent].height == oldHeight) // if height hasn't changed, no need to update ancestor
        break;
      parent = nodes[parent].parent;
    }

    // remove srcNode
    nodes[srcNode].parent = 0;
    nodes[srcNode].prevSibling = 0;
    nodes[srcNode].nextSibling = 0;
  }
  // move the subtree rooted at srcNode to the rank-th subtree of targetNode
  void moveSubTree(int srcNode, int targetNode, int rank) {
    nodes[srcNode].parent = targetNode;
    if (rank == 0) { // if rank is zero, insert as first child
      nodes[srcNode].nextSibling = nodes[targetNode].firstChild;
      nodes[srcNode].prevSibling = 0; //
      if (nodes[targetNode].firstChild) 
        nodes[nodes[targetNode].firstChild].prevSibling = srcNode;
      nodes[targetNode].firstChild = srcNode;
    } else { // otherise, insert at proper rank
      int currentNode = getChild(targetNode, rank - 1);
      nodes[srcNode].prevSibling = currentNode;
      nodes[srcNode].nextSibling = nodes[currentNode].nextSibling;
      if (nodes[currentNode].nextSibling)
        nodes[nodes[srcNode].nextSibling].prevSibling = srcNode;
      nodes[currentNode].nextSibling = srcNode;
    }

    // update scales and heights
    int parent = targetNode, child = srcNode;
    while (parent) { //update ancesstor 
      nodes[parent].scale += nodes[srcNode].scale;
      if (nodes[child].height >= nodes[parent].height)
        nodes[parent].height = nodes[child].height + 1;
      child = parent;
      parent = nodes[parent].parent;
    }
  }
  // maintain tree height and scale using recursion
  int height(int rank) {
    if (nodes[rank].firstChild == 0) // if has no children
      return nodes[rank].height = 0;
    else {                         // has children
      if (nodes[rank].height == 0) // if height is zero, update
        updateHeight(rank);
      return nodes[rank].height; // return height
    }
  }
  void updateHeight(int rank) {
    int max = -1;
    for (int currentNode = nodes[rank].firstChild; currentNode; currentNode = nodes[currentNode].nextSibling) {
      // recursive call for height
      max = max > height(currentNode) ? max : nodes[currentNode].height;
    }
    nodes[rank].height = max + 1;
  }
  int size(int rank) {
    if (nodes[rank].firstChild == 0) // if no children
      return nodes[rank].scale = 1;
    else {
      if (nodes[rank].scale == 0) // if children but size is zero, update
        updateScale(rank);
      return nodes[rank].scale;
    }
  }
  void updateScale(int rank) {
    int scale = 0;
    for (int currentNode = nodes[rank].firstChild; currentNode; currentNode = nodes[currentNode].nextSibling) {
      // recursive call for scale
      scale += size(currentNode);
    }
    nodes[rank].scale = scale + 1;
  }
  void update(int rank) {
    updateHeight(rank);
    updateScale(rank);
  }

} tree;

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  tree.buildTree(n);  // build tree
  tree.update(1);     // update whole tree

  // read query and print results
  int command;
  while (m--) {
    scanf("%d", &command);
    int srcNode, targetNode, rank;
    if (command == 0) { // move subtree
      srcNode = tree.getNode();
      tree.removeNode(srcNode);
      targetNode = tree.getNode();
      scanf("%d", &rank);
      tree.moveSubTree(srcNode, targetNode, rank);
    } else if (command == 1) { // query height
      targetNode = tree.getNode();
      printf("%d\n", tree.height(targetNode));
    } else if (command == 2) { // query size
      targetNode = tree.getNode();
      printf("%d\n", tree.size(targetNode));
    }
  }
  return 0;
}