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
    void fixColor(Node<T> *node);
    void insert(T value);
    void insert(T value, Node<T> *node);
    void remove(T value);
    void remove(T value, Node<T> node);

    void find(T value);

private:
    Node<T> *root;

};

template<typename T>
Node<T> RBTree<T>::getUncle(Node<T> nibling) {
    Node<T> nibParent = nibling.getParent();
    if(nibParent == NULL){
        return NULL;
    }
    if(nibParent == )
}

//TODO: finish fixColor, write delete and print
template<typename T>
void RBTree<T>::fixColor(Node<T> *node) {
    if(node == root){
        node->setColor(false);
        return;
    }
    if()
}

template<typename T>
void RBTree<T>::insert(T value){
    if(root == NULL) {
        root = new Node<T>(value);
        root->setColor(false);
    }
    else
        insert(value, root);
}

template<typename T>
void RBTree<T>::insert(T value, Node<T> *node){
    if(value < node->value){
        if(node->getLeftChild()->isNil())
            getRoot().setLeftChild(new Node<T>(value));
        else
            insert(value, node->getLeftChild());
    } else {
        if(node->getRightChild()->isNil())
            getRoot().setRightChild(new Node<T>(value));
        else
            insert(value, node->getRightChild());
    }
}

#endif //REDBLACK_HH
