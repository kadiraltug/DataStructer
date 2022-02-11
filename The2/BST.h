#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);
    
        
private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    
    void copy(BSTNode<T>*& node, BSTNode<T>* obj) {
    /* TODO */
    
    
        if (obj != NULL) {
            node = new BSTNode<T>(obj->data, NULL, NULL);
            copy(node->left, obj->left);
            copy(node->right, obj->right);
        }
    
    
    }
    
    bool contains(BSTNode<T>* p,BSTNode<T>* node) const {
    /* TODO */
        if (p == NULL) {
            return false;
        }
        else {
            if (p->data == node->data) {
                return true;
            }
            else if (p->data < node->data) {
                contains(p->right, node);
            }
            else if (p->data>node->data)
            {
                contains(p->left, node);
            }
        }

    }
    
    void insert(BSTNode<T>*& node,const T& data) {
    /* TODO */
        if (node == NULL) {
            node = new BSTNode<T>(data, NULL, NULL);
        }
        else if(data<node->data){
            insert(node->left, data);
        }
        else if (data > node->data) {
            insert(node->right,data);
        }
    }
    
    void remove(BSTNode<T>*& node, const T& data) {
    /* TODO */
        if(node==NULL){
                
        }
        if (search(data) == NULL) {
    
        }
        else {
            if (node->data < data) {
                remove(node->right, data);
            }
            else if (node->data > data) {
                remove(node->left, data);
            }
            
            else {
                if(node->left!=NULL&&node->right!=NULL){
                    node->data=findMin(node->right)->data;
                    remove(node->right,node->data);
                }
                else{
                    BSTNode<T>* old=node;
                    node=(node->right!=NULL)? node->right :node->left;
                    
                    delete old;
                }
                
                
            }
        }
    }
    
    
    BSTNode<T>* findMin(BSTNode<T>* node) {
        BSTNode<T>* current=node;
        while (current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }
    
    void removeAllNodes(BSTNode<T>*& node) {
    /* TODO */
        if (node) {
            removeAllNodes(node->left);
            
            removeAllNodes(node->right);
            
            delete node;
        }
        
    }
    
    BSTNode<T>* search(BSTNode<T>* node,const T& data) const {
        if (node == NULL) {
            return NULL;
        }
        else {
            if (node->data == data) {
                return node;
            }
            else if (node->data < data) {
                search(node->right, data);
            }
            else if (node->data > data)
            {
                search(node->left, data);
            }
        }
    }
    
    BSTNode<T>* getSuccessor(BSTNode<T>* p, BSTNode<T>* node, TraversalPlan tp) const {
        if (tp == inorder) {
            /* TODO */
            BSTNode<T>* temp = NULL;
            if(node->right!=NULL){
                temp=node->right;
                while(temp->left!=NULL){
                    temp=temp->left;
                }
                return temp;
            }
            else{
                BSTNode<T>* q = p;
                
                while (q->data != node->data) {
                    if (node->data < q->data) {
                        temp = q;
                        q = q->left;
                    }
                    else {
                        q = q->right;
                    }
                }
                return temp;
            }
        }
        else if (tp == preorder) {
            /* TODO */
            BSTNode<T>* temp = NULL;
            if(node->left!=NULL){
                return node->left;
            }
            else if(node->left==NULL&&node->right!=NULL){
                return node->right;
            }
            else{
                BSTNode<T>* q = p;
                temp=q;
                while (q->data != node->data){
                    if (q->left!=NULL&&q->right!=NULL&&node->data<temp->data){
                        temp=q->right;
                    }
                    if(node->data<q->data){
                        q=q->left;
                    }
                    else{
                        q=q->right;
                    }
                }
                if(temp==p){
                    temp=NULL;
                }
                return temp;
            }
            
        }
        else if (tp == postorder) {
           
            BSTNode<T>* temp = NULL;
            BSTNode<T>* q = p;
            if(node==q){
                return NULL;
            }
            else{
                while(q->data!=node->data){
                    if(node->data<q->data){
                        temp=q;
                        q=q->left;
                    }
                    else{
                        temp=q;
                        q=q->right;
                    }
                }
                BSTNode<T>* temp2=temp->right;
                if(temp2!=NULL){
                    if(temp2->data!=node->data){
                        while((temp2->left!=NULL||temp2->right!=NULL)){
                            if(temp2->left!=NULL){
                                temp2=temp2->left;
                            }
                            else{
                                temp2=temp2->right;
                            }
                        }
                    }
                    else{
                        temp2=temp;
                    }
                    
                    return temp2;
                }
                else{
                    return temp;
                }
                
            }
        }
    }
    
    
    void oper(BSTNode<T>* q) {
        if (q != NULL) {
            this->insert(q->data);
            oper(q->left);
            oper(q->right);
        }
    }
    
    
    void print(BSTNode<T> *node, TraversalPlan tp) const {
    
        // check if the node is NULL?
        if (node == NULL)
            return;
    
        if (tp == inorder) {
            // first, output left subtree and comma (if needed).
            print(node->left, inorder);
            if (node->left) {
                std::cout << "," << std::endl;
            }
    
            // then, output the node.
            std::cout << "\t" << node->data;
    
            // finally, output comma (if needed) and the right subtree.
            if (node->right) {
                std::cout << "," << std::endl;
            }
            print(node->right, inorder);
        } else if (tp == preorder) {
            
            std::cout << "\t" << node->data;
            
            if (node->left) {
                std::cout << "," << std::endl;
            }
            print(node->left, preorder);
            if (node->right) {
                std::cout << "," << std::endl;
            }
            print(node->right, preorder);
        } else if (tp == postorder) {
            
            
            print(node->left, postorder);
            
            if (node->left) {
                std::cout << "," << std::endl;
            }
    
            // then, output the node.
            print(node->right, postorder);
    
            // finally, output comma (if needed) and the right subtree.
            if (node->right) {
                std::cout << "," << std::endl;
            }
            
            
            std::cout << "\t" << node->data;
        }
    }
    

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    /* TODO */
    root=NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    
    if (obj.getRoot() == NULL) {
        root = NULL;
    }
    else {
        BSTNode<T>* p=obj.getRoot();
        copy(root, p);
    }
}



template<class T>
BST<T>::~BST() {
    /* TODO */
    removeAllNodes();
    
    
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    /* TODO */
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    /* TODO */
    if (root == NULL) {
        return true;
    }
    return false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    /* TODO */
    return contains(root, node);
}


template<class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    insert(root,data);
}

template<class T>
void BST<T>::remove(const T &data) {
    /* TODO */
    remove(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    /* TODO */
    if(root==NULL){
        
    }
    else{
    removeAllNodes(root);
    root=NULL;
    }
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    /* TODO */
    return search(root, data);
}



template<class T>
BSTNode<T>* BST<T>::getSuccessor(BSTNode<T>* node, TraversalPlan tp) const {
    
    if (tp == inorder) {
        /* TODO */
        
        
        return getSuccessor(root, node, tp);
        
        

    }
    else if (tp == preorder) {
        /* TODO */
        
        return getSuccessor(root, node, tp);


    }
    else if (tp == postorder) {
        /* TODO */
        getSuccessor(root, node, tp);
    }
}



template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
        
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    if (this != &rhs) {
        this->removeAllNodes();
        BSTNode<T>* p = rhs.getRoot();
        oper(p);
    }
    return *this;
}







