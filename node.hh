#ifndef NODE_HH
#define NODE_HH
#include <stddef.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

template<typename T>
class Node
{
public:
  // Constructors -- All assume Node will be Red. All Pointers will be assigned to NUlL unless specified
  Node(){this->nil = true;};
  Node(Node<T> *mom){ nil = true;  parent = mom;}
  Node(const T &value){ this->value = value; rightChild = new Node<T>(this); leftChild = new Node<T>(this);}
  Node(Node *parent, Node *leftChild, Node *rightChild, T value = NULL) { ; rightChild = rightChild; leftChild = leftChild; parent = parent; value = value; }
  Node(Node *parent, T value) { parent = parent; value = value; rightChild = new Node<T>(this); leftChild = new Node<T>(this);}

  // Returns corresponding pointer to node

  
  Node *getLeftChild() { return leftChild; } ;
  Node *getRightChild() { return rightChild; };
  Node *getParent() { cout<< parent << endl; return parent; };
  T getValue(){return value;}

  // Set corresponding pointers
  void setLeftChild(Node *child) { leftChild = child; child->setParent(this); };
  void setRightChild(Node *child) { rightChild = child; child->setParent(this); };
  void setParent(Node *node) { parent = node; };

  void incrementDegree() { degree++; }
  void decrementDegree() { degree--; }

  bool getColor() { return red; }
  void setColor(bool is_red) { red = is_red; };

  // Check if Node is Nil
  bool isNil(){return nil;};
  
  
private:
  bool red = true;
  bool nil = false;
  T value;
  Node *parent;
  Node *leftChild;
  Node *rightChild;
  int degree = 1;
};
#endif
