//
// Created by aghoy on 12/3/2023.
//

#ifndef REDBLACK_HH
#define REDBLACK_HH
#include "node.hh"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stddef.h>
#include <stdlib.h>

using namespace std;

const bool RED = true;
const bool BLACK = false;

template<typename T>
class RBTree{
public:
  //Constructors
  RBTree(){root = NULL;}
  RBTree(T value){this->root = Node<T>(value); size = 1; }
  RBTree(Node<T>* node){this->root = node; size = 1; }

  //Functions
  Node<T> *getRoot(){ return root;}
  Node<T> *getUncle(Node<T> *nibling);
  
  void rotateLeft(Node<T>*);
  void rotateRight(Node<T>*);
  void rotateDirection(bool, Node<T>*);
  
  void fixColor(Node<T> *node);
  
  void insert(const T &value);
  Node<T> *insert(const T &value, Node<T> *node);
  
  //void remove(T value);
  //void remove(T value, Node<T> node);
  void remove(T value);


  // void find(T value);
  void preOrderPrint();
  void postOrderPrint();
  void inOrderPrint();

  int getSize() { return size; }
  
  

private:
  // Functions that I want to be hidden away
  void preOrderPrint(Node<T> *);
  void postOrderPrint(Node<T> *);
  void inOrderPrint(Node<T> *);

  Node<T> *find(T);
  Node<T> *find(Node<T>*, T);
  Node<T> *root;
  void remove(Node<T> *);

  Node<T>* findMin(Node<T>*);
  void transplant(Node<T>*, Node<T>*);

  void burn_branch(Node<T> *);
  void swap_nodes(Node<T> *, Node<T> *);
  void isolate_branch(Node<T> *);
  void cut_branch(Node<T> *);
  
  void complex_remove(Node<T>*);

  string color_to_string(bool);

  int size = 0;

};

template<typename T>
void RBTree<T>::rotateLeft(Node<T> *node) {
    Node<T> *rightChild = node->getRightChild();
    Node<T> *parent = node->getParent();
    if(!rightChild->isNil()) {
        node->setParent(rightChild);
        rightChild->setParent(parent);
        if(node == root){
            root = rightChild;
        }
        if(parent != NULL){
            if(parent->direction(node) == RIGHT)
                parent->setRightChild(rightChild);
            else
                parent->setLeftChild(rightChild);
        }
        //cout << "root:" << root->getValue() << endl;
        Node<T> *temp = rightChild->getLeftChild();
        rightChild->setLeftChild(node);
        temp->setParent(node);
        node->setRightChild(temp);
    }
}

template<typename T>
void RBTree<T>::rotateRight(Node<T> *node ) {
    //check if left exists
    Node<T> *leftChild = node->getLeftChild();
    Node<T> *parent = node->getParent();
    if(!leftChild->isNil()) {
        //leftChild parent = node parent
        node->setParent(leftChild);
        leftChild->setParent(parent);
        if(node == root){
            root = leftChild;
        }
        if(parent != NULL){
            if(parent->direction(node) == RIGHT)
                parent->setRightChild(leftChild);
            else
                parent->setLeftChild(leftChild);
        }
        //cout << "root:" << root->getValue() << endl;
        //node parent = leftchild
        //leftchild rightchild is = to parent left
        Node<T> *temp = leftChild->getRightChild();
        leftChild->setRightChild(node);
        temp->setParent(node);
        node->setLeftChild(temp);
    }
}

template<typename T>
void RBTree<T>::rotateDirection(bool dir, Node<T> *node)
{
  if (dir == RIGHT) { rotateRight(node); }
  else { rotateLeft(node); }
}


template<typename T>
Node<T>* RBTree<T>::getUncle(Node<T>* nibling) {
    Node<T> *nibParent = nibling->getParent();
    if(nibParent == NULL) {
        return NULL;
    }
    Node<T> *grandparent = nibParent->getParent();
    if(nibParent == grandparent->getLeftChild()){
        return grandparent->getRightChild();
    } else {
        return grandparent->getLeftChild();
    }
}

//TODO: finish fixColor, write delete and print
template<typename T>
void RBTree<T>::fixColor(Node<T> *node) {
  // Note: Inserting first node into root case is already covered in insert(T).
  
  Node<T> *current = node; // This will be the node we track.

  while (current->getColor() == RED) //We will continue our loop till current is black.
    {
      Node<T> *parent = current->getParent();
      Node<T> *grandparent = NULL;
      Node<T> *uncle = NULL;
      if(parent != root){
          grandparent = parent->getParent();
          uncle = getUncle(current);
      }
      //cout << "root:" << root->getValue() << endl;

      // If parent's color is black, stop loop, we are done.
      if (parent->getColor() == BLACK) { return; }

      else if (parent->getColor() == RED && parent == root)
      {
          parent->setColor(BLACK);
          return;
      }

      // If the parent's and uncle's color are red, change them to black and grandparent to red. GP might have a red parent, violating no red to red
      else if (parent->getColor() == RED && uncle->getColor() == RED)
	{
        //cout << "root:" << root->getValue() << endl;
        //cout << "uncle:" << uncle->getValue() << endl;
	  parent->setColor(BLACK);
	  uncle->setColor(BLACK);
	  grandparent->setColor(RED);
	  current = grandparent; // Do not exit while loop. We must check if GP is fine to be red.
	}
      // The grandparent uncle parent line/triangle rotations
      else if (parent->getColor() == RED && uncle->getColor() == BLACK) {
          if (uncle == grandparent->getRightChild()) {
              //triangle case
              if (current == parent->getRightChild()) {
                  rotateLeft(parent);
                  current = parent;
                  //line case
              } else {
                  parent->setColor(BLACK);
                  grandparent->setColor(RED);
                  rotateRight(grandparent);
                  return;
              }
              //uncle on left
          } else {
              //triangle
              if (current == parent->getLeftChild()) {
                  rotateRight(parent);
                  current = parent;
                  //line
              } else {
                  parent->setColor(BLACK);
                  grandparent->setColor(RED);
                  //cout << "root:" << root->getValue() << endl;
                  rotateLeft(grandparent);
                  //cout << "root:" << root->getValue() << endl;
                  return;
              }
          }
      }



      // Can't have the loop run again, segfault for uncle/parent/grandparent. Also this covers when GP --> Current and is root (red). Test 3 on Wikipedia
      if (current == root) {
          return;
      }
        //cout << current->getRightChild()->getLeftChild()->getValue() << endl;
    }
}

template<typename T>
void RBTree<T>::insert(const T &value){
    if(root == NULL) {
      root = new Node<T>(value);
      root->setColor(BLACK); // Set Root to black immediately (this is just one case covered.)
    }
    else {
      fixColor(insert(value, root));
    }
    size++;
  
}

template<typename T>
Node<T>* RBTree<T>::insert(const T &value, Node<T> *node) {
  
  if(value < node->getValue())
    {
      if(node->getLeftChild()->isNil()) {
	node->setLeftChild(new Node<T>(value));
	return node->getLeftChild();
      }
      else
	{
	  return insert(value, node->getLeftChild());
	}
    }
  else if (value == node->getValue())
    {
      node->incrementDegree();
      return node;
    }
  else
    {
      if(node->getRightChild()->isNil()) {
	node->setRightChild(new Node<T>(value));
	return node->getRightChild();
      }
      else
	{
	  return insert(value, node->getRightChild());
	}
  }
}

template<typename T>
void RBTree<T>::preOrderPrint()
{
  if (root == NULL) { cout << "Root NULL, stopping print" << endl; exit(0); }
  preOrderPrint(root);
}

template<typename T>
void RBTree<T>::preOrderPrint(Node<T> *node)
{
  cout << node->getValue() << " " << color_to_string(node->getColor()) << " " << node->getDegree() << endl;
  if (!node->getLeftChild()->isNil())
    {
      preOrderPrint(node->getLeftChild());
    }
  if (!node->getRightChild()->isNil())
    {
      preOrderPrint(node->getRightChild());
    }
}

template<typename T>
void RBTree<T>::postOrderPrint()
{
    cout << "root:" << root->getValue() << endl;
  if (root == NULL) { cout << "Root NULL, stopping print" << endl; exit(0); }
  postOrderPrint(root);
}

template<typename T>
void RBTree<T>::postOrderPrint(Node<T> *node)
{
  if (!node->getLeftChild()->isNil())
    {
      postOrderPrint(node->getLeftChild());
    }
  if (!node->getRightChild()->isNil())
    {
      postOrderPrint(node->getRightChild());
    }
  cout << node->getValue() << " " << color_to_string(node->getColor()) << " " << node->getDegree() << endl;
}

template<typename T>
void RBTree<T>::inOrderPrint()
{
  if (root == NULL) { cout << "Root NULL, stopping print" << endl; exit(0); }
  inOrderPrint(root);
}

template<typename T>
void RBTree<T>::inOrderPrint(Node<T> *node)
{
   
  if (!node->getLeftChild()->isNil())
    {
      inOrderPrint(node->getLeftChild());
    }
  cout << node->getValue() << " " << color_to_string(node->getColor()) << " " << node->getDegree() << endl;
  if (!node->getRightChild()->isNil())
    {
      inOrderPrint(node->getRightChild());
    }
}



template<typename T>
void RBTree<T>::transplant(Node<T> *removed, Node<T> *successor)
{
  if (removed == root)
    {
      root = successor;
    }
  else if (removed->getParent()->getLeftChild == removed)
    {
      removed->getParent()->setLeftChild(successor); // Set removed's parent's left child to successor
    }
  else
    {
      removed->getParent()->setRightChild(successor); // Set removed's parent's left child to successor
    }
  successor->setParent(removed->getParent()); // Set Successors parent as the removed node's parent
}

template<typename T>
void RBTree<T>::remove(T key)
{
  Node<T> *del = find(key);
  if (del == NULL) { return; }

  Node<T> *leftChild = del->getLeftChild();
  Node<T> *rightChild = del->getRightChild();
  
  // If removed node is root with no children, delete it. Update root
  if (del == root && size == 1) 
    {
      cut_branch(del);
      root = NULL;
      return;
    }
  // If removed node has no children and red, delete it. Put Nil Node back
  if (del->has_no_children() && del->getColor() == RED)
    {
      burn_branch(del);
      return;
    }
  // If removed node has no children and is black, we have to do more to conserve red-black tree properties.
  if (del->has_no_children() && del->getColor() == BLACK)
    {
      complex_remove(del);
    }
  // If removed node has 2 children
  if (!(leftChild->isNil() || rightChild->isNil()))
    {
      Node<T> *successor = findMin(del->getRightChild());
      swap_nodes(successor, del);
      remove(successor); 
      return;
    }
  // Single child case. Must be a black with a red child. So swap nodes and then delete
  else if (!leftChild->isNil())
    {
      swap_nodes(del, leftChild);
      burn_branch(leftChild);
      return;
    }
  else if (!rightChild->isNil())
    {
      swap_nodes(del, rightChild);
      burn_branch(rightChild);
      return;
    }  
}

template<typename T>
void RBTree<T>::remove(Node<T> *del)
{
  Node<T> *leftChild = del->getLeftChild();
  Node<T> *rightChild = del->getRightChild();
  if (del->has_no_children()) { burn_branch(del); }
    // Single child case. Must be a black with a red child. So swap nodes and then delete
  else if (!leftChild->isNil())
    {
      swap_nodes(del, leftChild);
      burn_branch(leftChild);
      return;
    }
  else if (!rightChild->isNil())
    {
      swap_nodes(del, rightChild);
      burn_branch(rightChild);
      return;
    }  
  
}


/**
 * Utility function to combine two steps.
 */
template<typename T>
void RBTree<T>::burn_branch(Node<T> *burning_point)
{
  isolate_branch(burning_point);
  cut_branch(burning_point);
}

/**
 * Swaps the location of two nodes within the tree
 */
template<typename T>
void RBTree<T>::swap_nodes(Node<T> *n, Node<T> *m)
{
  T temp = n->getValue();
  n->setValue(m->getValue());
  m->setValue(temp);
}

/**
 * Snaps connection between parent node and child node
 */
template<typename T>
void RBTree<T>::isolate_branch(Node<T> *cut)
{
  Node<T> *stem = cut->getParent();
  if (stem->getRightChild() == cut) { stem->setRightChild(new Node<T>(stem)); }
  else if (stem->getLeftChild() == cut) { stem->setLeftChild(new Node<T>(stem)); }
}


/**
 * Deletes an entire subtree/subtree including the root of the subtree/tree.
 * DOES subtract size
 */
template<typename T>
void RBTree<T>::cut_branch(Node<T> *node)
{
  if (node->getLeftChild() != NULL) { cut_branch(node->getLeftChild()); }
  if (node->getRightChild() != NULL) { cut_branch(node->getRightChild()); }
  if (!node->isNil()) { size--; } // If its an actual node, subtract from size.
  delete node;
}

template<typename T>
void RBTree<T>::complex_remove(Node<T> *node)
{
  // Wrap in some while loop
  Node<T> *current = node;
  Node<T> *parent = current->getParent();
  bool dir = parent->direction(current);
  Node<T> *sibling = parent->child_in_direction(!dir);
  Node<T> *close_nephew = sibling->child_in_direction(dir);
  Node<T> *distant_nephew = sibling->child_in_direction(!dir);

  // Deletion complete case.
  if (current == root)
    {
      return;
    }
  // If sibling and sibling children are colored black
  else if (parent->getColor() == BLACK && sibling->getColor() == BLACK && close_nephew->getColor() == BLACK && distant_nephew->getColor() == BLACK)
    {
      sibling->setColor(RED);
      current = parent;
    }
  
  //
  //  else if (sibling->getColor() == RED )

  
}


template<typename T>
Node<T>* RBTree<T>::findMin(Node<T> *node)
{
  if (node->getLeftChild()->isNil()) { return node; }
  return findMin(node->getLeftChild());
}

/**
 * Will attempt to find a node given a key.
 * If it does not find a node, it will print that out BUT continue the program passing NULL as return.
 */
template<typename T>
Node<T>* RBTree<T>::find(T key)
{
  if (root == NULL) { cout << "Root is null, canceling find and program." << endl; exit(0); }

  Node<T>* lock = find(root, key);
  if (lock == NULL) { cout << "Could not find Node: " << key << endl; return lock; } // Will continue program.
  return lock;
}

/**
 * This is the recursive function that will find a node based on a key
 */
template<typename T>
Node<T>* RBTree<T>::find(Node<T> *node, T key)
{
  if (node->isNil()) { return NULL; } // Key not found
  
  T lock = node->getValue();
  if (lock == key) { return node; } // Found node, return.
  else if (key > lock) { return find(node->getRightChild(), key); } // Use BST property, check right.
  else { return find(node->getLeftChild(), key); } // Must be smaller if not two other cases, 
}

template<typename T>
string RBTree<T>::color_to_string(bool color)
{
  if (color == RED) { return "RED"; }
  return "BLACK";
}

#endif //REDBLACK_HH
