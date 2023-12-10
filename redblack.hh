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
  
  void fixColor(Node<T> *node);
  
  void insert(const T &value);
  Node<T> *insert(const T &value, Node<T> *node);
  
  //void remove(T value);
  //void remove(T value, Node<T> node);
  void remove(Node<T> *);


  // void find(T value);
  void preOrderPrint();
  void postOrderPrint();
  void inOrderPrint();
  
  Node<T>* findMin(Node<T>*);
  void deleteFixup(Node<T>*, Node<T>*);
  void transplant(Node<T>*, Node<T>*);

  int getSize() { return size; }
  
  

private:
  // Functions that I want to be hidden away
  void preOrderPrint(Node<T> *);
  void postOrderPrint(Node<T> *);
  void inOrderPrint(Node<T> *);

  Node<T> *find(T);
  Node<T> *find(Node<T>*, T);
  Node<T> *root;

  string color_to_string(bool);

  int size = 0;

};

template<typename T>
void RBTree<T>::rotateLeft(Node<T> *node) {
    Node<T> *rightChild = node->getRightChild();
    if(!rightChild->isNil()) {
        node->setParent(rightChild);
        rightChild->setParent(NULL);

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
    if(!leftChild->isNil()) {
        //leftChild parent = node parent
        node->setParent(leftChild);
        leftChild->setParent(NULL);
        //node parent = leftchild
        //leftchild rightchild is = to parent left
        Node<T> *temp = leftChild->getRightChild();
        leftChild->setRightChild(node);
        temp->setParent(node);
        node->setLeftChild(temp);
    }
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
      if(parent == root){
          return;
      }
      Node<T> *uncle = getUncle(current);
      Node<T> *grandparent = parent->getParent();

      //cout << "fix color loop" << endl;
      
      // If parent's color is black, stop loop, we are done.
      if (parent->getColor() == BLACK) { return; }

      // If the parent's and uncle's color are red, change them to black and grandparent to red. GP might have a red parent, violating no red to red
      else if (parent->getColor() == RED && uncle->getColor() == RED)
	{
	  parent->setColor(BLACK);
	  uncle->setColor(BLACK);
	  grandparent->setColor(RED);
	  current = grandparent; // Do not exit while loop. We must check if GP is fine to be red.
	}

      // If the parent is red and root, change parent to black and stop. (Test 4 on Wikipedia)
      else if (parent->getColor() == RED && parent == root)
	{
	  parent->setColor(BLACK);
	  return;
	}

      // The grandparent uncle parent line/triangle rotations
      else if (parent->getColor() == RED && uncle->getColor() == BLACK)
	{
	  if(uncle == grandparent->getRightChild()) {
            //triangle case
            if(current == parent->getRightChild()){
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
            if(current == parent->getLeftChild()){
	            rotateRight(parent);
                current = parent;
          //line
            } else {
	             parent->setColor(BLACK);
	            grandparent->setColor(RED);
	            rotateLeft(grandparent);
                return;
            }
	  }
	}

      
      // Can't have the loop run again, segfault for uncle/parent/grandparent. Also this covers when GP --> Current and is root (red). Test 3 on Wikipedia
      if (current == root) { return; }
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
  if (removed->getParent() == NULL)
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
void RBTree<T>::remove(Node<T> *removal)
{
  // Insert case of removal node not existing
  if (!(removal->getLeftChild()->isNil() || removal->getRightChild()->isNil()))
    {
      Node<T> *minimum = findMin(removal);
      Node<T> *minRight = minimum->getRightChild();
      transplant(minimum, minRight);

      Node<T> *nextBig = removal->getRightChild();
      minimum->setRightChild(nextBig);
      nextBig->setParent(minimum);

      transplant(removal, minimum);
      //delete fixup(minRight) if Black I THINK ALL
    }
  else if (removal->getLeftChild()->isNil()) // Right Child exists OR if both children are Nil
    {
      transplant(removal, removal->getRightChild());
      //delete fixup
    }
  else 
    {
      transplant(removal, removal->getLeftChild());
      //delete fixup
    }
  delete removal;
}

template<typename T>
void RBTree<T>::deleteFixup(Node<T> *fix, Node<T> *sibling)
{
  while (fix->getColor() == false && fix != root)
    {
      if (sibling->getColor == true)
	{
	  sibling->setColor(false); // set sibling black
	  fix->getParent()->setColor(true); // set parent red
	  //rotate parent left
	  sibling = fix->getParent()->getRight();
	}

      if (sibling->getLeftChild()->getColor() == false && sibling->getRightChild()->getColor() == false)
	{
	  sibling->setColor(true);
	  fix = fix->getParent();
	}

      if (sibling->getLeftChild()->getColor() == true && sibling->getRightChild()->getColor() == false && sibling->getColor() == false) //Sibling & sibling right are black while left is red
	{
	  sibling->getLeftChild()->setColor(false);
	  sibling->setColor(true);
	  //right rotation on sibling
	  sibling = fix->getParent()->getRight();
	}

      if (sibling->getColor() == false && sibling->getRightChild()->getColor() == true)
	{
	  bool newColor = fix->getParent()->getColor();
	  sibling->setColor(newColor);
	  fix->getParent()->setColor(false);
	  sibling->getRightChild()->setColor(false);
	  //left rotation on fix parent
	  fix = root;
	}
      fix->setColor(false);
    }
}


template<typename T>
Node<T>* RBTree<T>::findMin(Node<T> *node)
{
  if (node->getLeftChild->isNil()) { return node; }
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
  if (lock == NULL) { cout << "Could not find Node" << endl; return lock; } // Will continue program.
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
