#include<iostream>
#include<queue>
#include<stack>

#ifndef ROOTBINARYTREE_H
#define ROOTBINARYTREE_H

template<typename T>
struct node{
    T data;
    node<T>* left;
    node<T>* right;
};
template<typename T>
class RootBinaryTree
{
    public:
        RootBinaryTree();
        RootBinaryTree(const RootBinaryTree<T>&);
        RootBinaryTree<T>& operator=(const RootBinaryTree<T>&);
        ~RootBinaryTree();

        const node<T>* getRoot() const;
        T getRootData() const;
        bool isEmpty() const;

        void create(node<T>* &);
        void create();

        void preorderTraversal() const;
        void preorderTraversal(const node<T>*) const;

        void inorderTraversal() const;
        void inorderTraversal(const node<T>*) const;

        void postorderTraversal() const;
        void postorderTraversal(const node<T>*) const;

        RootBinaryTree<T>& leftTree() const;
        RootBinaryTree<T>& rightTree() const;

        void BFS() const;
        void DFS() const;
    private:
        node<T>* root;
        void copyTree(const RootBinaryTree<T>&);
        void copyNode(node<T>* &, node<T>*&) const;
        void deleteTree(node<T>* &);
};

template<typename T>
RootBinaryTree<T>::RootBinaryTree(){
    root = NULL;
};

template<typename T>
RootBinaryTree<T>::RootBinaryTree(const RootBinaryTree<T>& tr){
    copyTree(tr);
};
template<typename T>
RootBinaryTree<T>& RootBinaryTree<T>::operator=(const RootBinaryTree<T>& tr){
    if(this != &tr){
        deleteTree();
        copyTree(tr);
    }
    return *this;
};
template<typename T>
RootBinaryTree<T>::~RootBinaryTree(){
    deleteTree(root);
};

template<typename T>
void RootBinaryTree<T>::copyTree(const RootBinaryTree<T>& tr){
    copyNode(root, tr.root);
};
template<typename T>
void RootBinaryTree<T>::copyNode(node<T>*& rt, node<T>*& copyNode) const{
    rt = NULL;
    if(copyNode){
        rt = new node<T>;
        rt->data = copyNode->data;
        copyNode(rt->left, copyNode->left);
        copyNode(rt->right, copyNode->right);
    }
};

template<typename T>
void RootBinaryTree<T>::deleteTree(node<T>*& p){
    if(p){
        deleteTree(p->left);
        deleteTree(p->right);

        delete p;
        p = NULL;
    }
};

template<typename T>
const node<T>* RootBinaryTree<T>::getRoot() const {
    return root;
};

template<typename T>
void RootBinaryTree<T>::create(node<T>* &nd){
    T x;
    char ans;
    nd = new node<T>;
    std::cout<<"Enter value:";std::cin>>x;
    nd->data = x;
    nd->left = nd->right = NULL;
    std::cout<<"Left subtree of "<<x<<' ';std::cin>>ans;

    if(ans == 'y'){
        create(nd->left);
    }

    std::cout<<"Right subtree of "<<x<<' ';std::cin>>ans;

    if(ans == 'y'){
        create(nd->right);
    }
};

template<typename T>
void RootBinaryTree<T>::create(){
    create(root);
};

template<typename T>
bool RootBinaryTree<T>::isEmpty() const {
    return root == NULL;
};

template<typename T>
RootBinaryTree<T>& RootBinaryTree<T>::leftTree() const {
    RootBinaryTree<T>& t;
    copyNode(t.root, root->left);
    return t;
};
template<typename T>
RootBinaryTree<T>& RootBinaryTree<T>::rightTree() const {
    RootBinaryTree<T>& t;
    copyNode(t.root, root->right);
    return t;
};
template<typename T>
void RootBinaryTree<T>::BFS() const{
    std::queue<node<T>* > nodeQueue;
    nodeQueue.push(root);

    while(!nodeQueue.empty()){
        node<T>* temp = nodeQueue.front();
        std::cout<<temp->data<<' ';
        nodeQueue.pop();

        if(temp->left){
            nodeQueue.push(temp->left);
        }

        if(temp->right){
            nodeQueue.push(temp->right);
        }
    }
};
template<typename T>
void RootBinaryTree<T>::DFS() const{
    std::stack<node<T>* > nodeQueue;
    nodeQueue.push(root);

    while(!nodeQueue.empty()){
        node<T>* temp = nodeQueue.top();
        std::cout<<temp->data<<' ';
        nodeQueue.pop();

        if(temp->right){
            nodeQueue.push(temp->right);
        }

        if(temp->left){
            nodeQueue.push(temp->left);
        }
    }
};

template<typename T>
void RootBinaryTree<T>::preorderTraversal() const{
    printPre(root);
};
template<typename T>
void RootBinaryTree<T>::preorderTraversal(const node<T>* p) const {
    if(p){
        std::cout<<p->data<<' ';
        print(p->left);
        print(p->right);
    }
};

template<typename T>
void RootBinaryTree<T>::inorderTraversal() const{
    printPre(root);
};
template<typename T>
void RootBinaryTree<T>::inorderTraversal(const node<T>* p) const {
    if(p){
        print(p->left);
        std::cout<<p->data<<' ';
        print(p->right);
    }
};
template<typename T>
void RootBinaryTree<T>::postorderTraversal() const{
    printPre(root);
};
template<typename T>
void RootBinaryTree<T>::postorderTraversal(const node<T>* p) const {
    if(p){
        print(p->left);
        print(p->right);
        std::cout<<p->data<<' ';
    }
};
#endif
