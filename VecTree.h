#include<iostream>
#include<queue>
#include<stack>
#include <stdlib.h>
#include<vector>
#include <time.h>

#ifndef VECTREE_H
#define VECTREE_H

struct Player {
    std::string name;
    int coef;
    friend std::ostream& operator<<(std::ostream& os, const Player& pl){
        os<<pl.name<<" "<<pl.coef<<std::endl;
        return os;
    }
};

template<typename T>
struct node {
    T data;
    int left;
    int right;
};

template<typename T>
class VecTree
{
    public:
        void setLeft(int, T);
        void setRight(int, T);
        void create();
        void inorderTraversal(int);
        bool isEmpty() const;

    private:
        std::vector<node<T>*> nodes;
};

template<typename T>
void VecTree<T>::setLeft(int indx, T data){
    int leftIndx = nodes.size();
    nodes[indx].left = leftIndx;
    node<T>* temp = new node<T>();
    temp->data = data;
    temp->left = -1;
    temp->right = -1;
    nodes.push_back(temp);
};

template<typename T>
void VecTree<T>::setRight(int indx, T data){
    int rightIndx = nodes.size();
    nodes[indx].right = rightIndx;
    node<T>* temp = new node<T>();
    temp->data = data;
    temp->left = -1;
    temp->right = -1;
    nodes.push_back(temp);
};

template<typename T>
void VecTree<T>::create(){
    T x;
    char ans;
    node<T>* nd = new node<T>;
    std::cout<<"Enter value:";std::cin>>x;
    nd->data = x;
    nd->left = nd->right = -1;
    nodes.push_back(nd);
    /*if(pos != -1 && left){
        nodes[pos]->left = nodes.size()-1;
    } else if(pos != -1 && !left) {
        nodes[pos]->right = nodes.size()-1;
    }*/

    std::cout<<"Left subtree of "<<x<<' ';std::cin>>ans;
    //int currNode = pos + 1;
    if(ans == 'y'){
        //create(currNode,true);
    }

    std::cout<<"Right subtree of "<<x<<' ';std::cin>>ans;

    if(ans == 'y'){
        //create(currNode,false);
    }
};

template<typename T>
void VecTree<T>::inorderTraversal(int index){
    if(nodes[index]->left != -1)
        inorderTraversal(nodes[index]->left);
    std::cout<<nodes[index]->data<<" ";
    if(nodes[index]->right != -1)
        inorderTraversal(nodes[index]->right);
};

template<typename T>
bool VecTree<T>::isEmpty() const {
    return nodes.empty();
};
#endif // VECTREE_H
