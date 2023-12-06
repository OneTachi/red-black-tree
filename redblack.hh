//
// Created by aghoy on 12/3/2023.
//

#ifndef REDBLACK_HH
#define REDBLACK_HH
#include "node.hh"

using namespace std;

template<typename T>
class RBTree{
public:
  //Constructors
  RBTree(){root = NULL;}
  RBTree(T value){this->root = Node<T>(value);}
  RBTree(Node<T>* node){this->root = node;}

  //Functions
  Node<T> *getRoot(){ return root;}
  Node<T> *getUncle(Node<T> *nibling);
  
  void rotateLeft(Node<T>*);
  void rotateRight(Node<T>*);
  
  void fixColor(Node<T> *node);
  
  void insert(T value);
  Node<T> *insert(T value, Node<T> *node);
  
  //void remove(T value);
  //void remove(T value, Node<T> node);
  void remove(Node<T> *);


  // void find(T value);
  void preOrderPrint();
  Node<T>* findMin(Node<T>*);
  void deleteFixup(Node<T>*, Node<T>*);
  void transplant(Node<T>*, Node<T>*);
  
  

private:
  void preOrderPrint(Node<T> *);
  Node<T> *root;

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
    if(node == root){
        node->setColor(false);
        return;
    } else if(!node->getParent()->getColor()){
        return;
    }
    Node<T> *uncle = getUncle(node);
    Node<T> *currParent = node->getParent();
    if(uncle->getColor()){
        uncle->setColor(false);
        currParent->setColor(false);
        currParent->getParent()->setColor(true);
        fixColor(currParent->getParent());
    } else {
        //if uncle is on the right
        if(uncle == currParent->getParent()->getRightChild()){
            //triangle case
            if(node == currParent->getRightChild()){
                rotateLeft(currParent);
                fixColor(currParent);
            //line case
            } else {
                currParent->setColor(false);
                currParent->getParent()->setColor(true);
                rotateRight(currParent->getParent());
            }
        //uncle on left
        } else {
            //triangle
            if(node == currParent->getLeftChild()){
                rotateRight(currParent);
                fixColor(currParent);

            } else {
                currParent->setColor(false);
                currParent->getParent()->setColor(true);
                rotateLeft(currParent->getParent());
            }
        }
    }
}

template<typename T>
void RBTree<T>::insert(T value){
    if(root == NULL) {
        root = new Node<T>(value);
        root->setColor(false);
    }
    else {
        fixColor(insert(value, root));
    }
}

template<typename T>
Node<T>* RBTree<T>::insert(T value, Node<T> *node){
  if(value < node->getValue())
    {
      if(node->getLeftChild()->isNil()) {
	node->setLeftChild(new Node<T>(value));
	return node->getLeftChild();
      }
      else
	return insert(value, node->getLeftChild());
    } else {
    if(node->getRightChild()->isNil()) {
      node->setRightChild(new Node<T>(value));
      return node->getRightChild();
    }
    else
      return insert(value, node->getRightChild());
  }
}

template<typename T>
void RBTree<T>::preOrderPrint()
{
  preOrderPrint(root);
}

template<typename T>
void RBTree<T>::preOrderPrint(Node<T> *node)
{
  cout << node->getValue() << endl;
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

#endif //REDBLACK_HH
