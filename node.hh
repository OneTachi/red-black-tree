#ifndef NODE_HH
#define NODE_HH
#include <stddef.h>

using namespace std;

template<typename T>
class Node
{
public:
  // Constructors -- All assume Node will be Red. All Pointers will be assigned to NUlL unless specified
  Node(){};
  Node(Node *parent, Node *leftChild, Node *rightChild, T value = NULL) { rightChild = rightChild; leftChild = leftChild; parent = parent; value = value; }
  Node(Node *parent, T value = NULL) { parent = parent; value = value; }

  // Returns corresponding pointer to node
  Node *getLeftChild() { return leftChild; } ;
  Node *getRightChild() { return rightChild; };
  Node *getParent() { return parent; };

  // Set corresponding pointers
  void setLeftChild(Node *child) { leftChild = child; };
  void setRightChild(Node *child) { rightChild = child; };
  void setParent(Node *node) { parent = node; };

  void setColor(bool is_red) { red = is_red; };
  
private:
  bool red = true;
  T value = NULL;
  Node *parent = NULL;
  Node *leftChild = NULL;
  Node *rightChild = NULL;
};

template<typename T>
class Nil : public Node
{
  Nil(Node* parent) { setParent(parent); setColor(false); }
}


#endif
