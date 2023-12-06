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
  Node(Node<T> *mom){ this->nil = true; this->parent = mom;}
  Node(const T &value){ this->value = value; rightChild = new Node<T>(this); leftChild = new Node<T>(this);}
  Node(Node *parent, Node *leftChild, Node *rightChild, T value = NULL) { cout << "BC" << endl; rightChild = rightChild; leftChild = leftChild; parent = parent; value = value; }
  Node(Node *parent, T value) { parent = parent; value = value; rightChild = new Node<T>(this); leftChild = new Node<T>(this);}

  // Returns corresponding pointer to node

  
  Node *getLeftChild() { return leftChild; } ;
  Node *getRightChild() { return rightChild; };
  Node *getParent() { return parent; };
  T getValue(){return value;}

  // Set corresponding pointers
  void setLeftChild(Node *child) { leftChild = child; };
  void setRightChild(Node *child) { rightChild = child; };
  void setParent(Node *node) { parent = node; };

  bool getColor() { return red; }
  void setColor(bool is_red) { red = is_red; };

  // Check if Node is Nil
  bool isNil(){return nil;};
  
  
private:
  bool red = true;
  bool nil = false;
  T value;
  Node *parent = NULL;
  Node *leftChild = NULL;
  Node *rightChild = NULL;
};
#endif
