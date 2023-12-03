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
    Node<T> getRoot(){ return root;}
    Node<T> getUncle(Node<T> nibling);
    void rotateLeft(Node<T>*);
    void rotateRight(Node<T>*);
    void fixColor(Node<T> *node);
    void insert(T value);
    Node<T> insert(T value, Node<T> *node);
    void remove(T value);
    void remove(T value, Node<T> node);


    void find(T value);

private:
    Node<T> *root;

};

template<typename T>
void RBTree<T>::rotateLeft(Node<T> *node) {
    Node<T> rightChild = node->getRightChild();
    Node<T> temp = rightChild.getLeftChild();
    rightChild->setLeftChild(node);
    node->setRightChild(temp);
}

template<typename T>
void RBTree<T>::rotateRight(Node<T> *node ) {
    Node<T> leftChild = node->getLeftChild();
    Node<T> temp = leftChild.getRightChild();
    leftChild->setRightChild(node);
    node->setLeftChild(temp);
}

template<typename T>
Node<T> RBTree<T>::getUncle(Node<T> nibling) {
    Node<T> nibParent = nibling->getParent();
    if(nibParent == NULL){
        return NULL;
    }
    Node<T> grandparent = nibParent->getParent();
    if(nibParent == grandparent.getLeftChild()){
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
    }
    Node<T> uncle = getUncle(node);
    Node<T> currParent = node->getParent();
    if(uncle->getColor()){
        uncle->setColor(false);
        currParent->setColor(false);
        currParent->getParent()->setColor(true);
    } else {
        //if uncle is on the right
        if(uncle == currParent.getParent()->getRightChild()){
            //triangle case
            if(node == currParent.getRightChild()){

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
Node<T> RBTree<T>::insert(T value, Node<T> *node){
    if(value < node->value){
        if(node->getLeftChild()->isNil()) {
            node->setLeftChild(new Node<T>(value));
            return node->getLeftChild();
        }
        else
            insert(value, node->getLeftChild());
    } else {
        if(node->getRightChild()->isNil()) {
            node->setRightChild(new Node<T>(value));
            return node->getRightChild();
        }
        else
            insert(value, node->getRightChild());
    }
}

#endif //REDBLACK_HH
