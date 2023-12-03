#ifndef NODE_HH
#define NODE_HH

using namespace std;

template<typename T>
class Node
{
public:
  // Constructors -- All assume Node will be Red. All Pointers will be assigned to NUlL unless specified
  Node(){}
  Node(*Node parent, *Node leftChild, *Node rightChild, T value = NULL) { this.rightChild = rightchild; this.leftChild = leftChild; this.parent = parent; this.value = value; }
  Node(*Node parent, T value = NULL) { this.parent = parent; this.value = value; }

  // Returns corresponding pointer to node
  *Node leftChild() { return leftChild; } 
  *Node rightChild() { return rightChild; }
  *Node parent() { return parent; }

  // Set corresponding pointers
  void setLeftChild(*Node child) { leftChild = child; }
  void setRightChild(*Node child) { rightChild = child; }
  void setParent(*Node node) { parent = node; }

  void setColor(bool is_red) { red = is_red; }
  
private:
  boolean red = true;
  T value = NULL;
  *Node parent = NULL;
  *Node leftChild = NULL;
  *Node rightChild = NULL;
};


#endif
