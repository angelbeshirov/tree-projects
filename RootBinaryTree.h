#include<iostream>
#include<queue>
#include<stack>
#include <stdlib.h>
#include<vector>
#include <time.h>

#ifndef ROOTBINARYTREE_H
#define ROOTBINARYTREE_H

using std::vector;
using std::string;

template<typename T>
struct node{
    T data;
    node<T>* left;
    node<T>* right;
};

struct Player {
    std::string name;
    int coef;
    friend std::ostream& operator<<(std::ostream& os, const Player& pl){
        os<<pl.name<<" "<<pl.coef<<std::endl;
        return os;
    }
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

        void create();
        void create(vector<T>);
        void tournament(node<T>*, string);// "" = all matches
        void tournament();
        void findpath(string name);

        int whoWins(Player, Player);

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
        void copyNode(node<T>* &, node<T>*) const;
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
void RootBinaryTree<T>::copyNode(node<T>*& rt, node<T>* toCopyNode) const{
    rt = NULL;
    if(toCopyNode){
        rt = new node<T>;
        rt->data = toCopyNode->data;
        copyNode(rt->left, toCopyNode->left);
        copyNode(rt->right, toCopyNode->right);
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
void RootBinaryTree<T>::create(){
    T x;
    std::queue<node<T>* > tmp;
    char ans;
    node<T>* nd = new node<T>;
    std::cout<<"Enter value:";std::cin>>x;
    nd->data = x;
    nd->left = nd->right = NULL;
    root = nd;
    tmp.push(nd);
    std::cout<<"More elements? y/n:";std::cin>>ans;
    while(ans == 'y' || ans == 'Y'){
        std::cout<<"Enter value:";std::cin>>x;
        node<T>* tmp1 = tmp.front();
        if(!tmp1->left){
            tmp1->left = new node<T>;
            tmp1->left->left = tmp1->left->right = NULL;
            tmp1->left->data = x;
            tmp.push(tmp1->left);
        }
        else if(!tmp1->right){
            tmp1->right = new node<T>;
            tmp1->right->left = tmp1->right->right = NULL;
            tmp1->right->data = x;
            tmp.push(tmp1->right);
        }
        if(tmp1->left && tmp1->right){
            tmp.pop();
        }
        std::cout<<"More elements? y/n:";std::cin>>ans;
    }
};

template<typename T>
void RootBinaryTree<T>::create(std::vector<T> st){
    std::queue<node<T>* > que;
    T x;
    srand(time(0));
    node<T>* nd = new node<T>;
    int randomNumber;

    if(!st.empty()){
        int randomNumber;
        if(st.size() == 1){
            randomNumber = 0;
        } else {
            randomNumber = rand() % (st.size());
        }
        x = st[randomNumber];
        st.erase(st.begin() + randomNumber);
        nd->data = x;
        nd->left = nd->right = NULL;
        root = nd;
        que.push(nd);
    }

    while(!st.empty()){

        if(st.size() == 1){
            randomNumber = 0;
        } else {
            randomNumber = rand() % (st.size());
        }
        x = st[randomNumber];
        st.erase(st.begin() + randomNumber);

        node<T>* nod = que.front();
        if(!nod->left){
            nod->left = new node<T>;
            nod->left->left = nod->left->right = NULL;
            nod->left->data = x;
            que.push(nod->left);
        }
        else if(!nod->right){
            nod->right = new node<T>;
            nod->right->left = nod->right->right = NULL;
            nod->right->data = x;
            que.push(nod->right);
        }
        if(nod->left && nod->right){
            que.pop();
        }
    }
};

template<typename T>
void RootBinaryTree<T>::tournament(node<T>* nd, string nameToPrint){
    if(nd->left){
        if(nd->left->left)tournament(nd->left, nameToPrint);
    }
    if(nd->right){
        if(nd->right->left)tournament(nd->right, nameToPrint);
    }
    if(nd->right){
        if(nameToPrint == "" || nameToPrint == nd->left->data.name || nameToPrint == nd->right->data.name){
            std::cout<<" Currently "<<nd->left->data.name<<" with coefficient "
                <<nd->left->data.coef<<" and "<<nd->right->data.name<<" with coefficient "
                    <<nd->right->data.coef<<" are playing\n";
        }
        int result = whoWins(nd->left->data, nd->right->data);
        if(result == 2){
            if(nameToPrint == "" || nameToPrint == nd->left->data.name || nameToPrint == nd->right->data.name){
                nd->left->data = nd->right->data;
                std::cout<<" The winner is "<<nd->left->data<< "\n";
            } else nd->left->data = nd->right->data;
            delete nd->right;
            nd->right = NULL;
        } else {
            if(nameToPrint == "" || nameToPrint == nd->left->data.name || nameToPrint == nd->right->data.name){
                std::cout<<" The winner is "<<nd->left->data<< "\n";
            }
            delete nd->right;
            nd->right = NULL;
        }
    }
    if(nd->left){
        if(nameToPrint == "" || nameToPrint == nd->data.name || nameToPrint == nd->left->data.name){
            std::cout<<" Currently "<<nd->data.name<<" with coefficient "<<nd->data.coef<<" and "<<nd->left->data.name<<" with coefficient "<<nd->left->data.coef<<" are playing\n";
        }
        int result = whoWins(nd->data, nd->left->data);
        if(result == 2){

            if(nameToPrint == "" || nameToPrint == nd->data.name || nameToPrint == nd->left->data.name){
                nd->data = nd->left->data;
                std::cout<<" The winner is "<<nd->data<< "\n";
            } else nd->data = nd->left->data;
            delete nd->left;
            nd->left = NULL;
        } else {
            if(nameToPrint == "" || nameToPrint == nd->data.name || nameToPrint == nd->left->data.name){
                std::cout<<" The winner is "<<nd->data<< "\n";
            }
            delete nd->left;
            nd->left = NULL;
        }
    }
};

template<typename T>
void RootBinaryTree<T>::tournament(){
    node<T>* tour;
    copyNode(tour, this->root);
    if(tour == NULL){
        std::cout<<"There are no players\n";
    } else {
        tournament(tour,"");
        std::cout<<"The final winner is:"<<tour->data;
    }
};

template<typename T>
void RootBinaryTree<T>::findpath(string name){
    node<T>* tour;
    copyNode(tour, this->root);
    if(tour == NULL){
        std::cout<<"There are no players\n";
    } else tournament(tour, name);
};

template<typename T>
int RootBinaryTree<T>::whoWins(Player player1, Player player2){// 1 = player1 2 - player2
    int sum = player1.coef + player2.coef;
    srand(time(NULL));
    int number = rand() % sum;
    if(number <= player1.coef)return 1;
    else return 2;
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
        std::cout<<temp->data;
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
        std::cout<<temp->data;
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
        std::cout<<p->data;
        preorderTraversal(p->left);
        preorderTraversal(p->right);
    }
};

template<typename T>
void RootBinaryTree<T>::inorderTraversal() const{
    inorderTraversal(root);
};

template<typename T>
void RootBinaryTree<T>::inorderTraversal(const node<T>* p) const {
    if(p){
        inorderTraversal(p->left);
        std::cout<<p->data;
        inorderTraversal(p->right);
    }
};

template<typename T>
void RootBinaryTree<T>::postorderTraversal() const{
    postorderTraversal(root);
};

template<typename T>
void RootBinaryTree<T>::postorderTraversal(const node<T>* p) const {
    if(p){
        postorderTraversal(p->left);
        postorderTraversal(p->right);
        std::cout<<p->data;
    }
};

#endif
