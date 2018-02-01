#include<iostream>
#include<queue>
#include<stack>
#include <stdlib.h>
#include<vector>
#include <time.h>

#ifndef VECTREE_H
#define VECTREE_H

using std::string;
using std::vector;
using std::cout;
using std::endl;

struct Player {
    std::string name;
    int coef;
    friend std::ostream& operator<<(std::ostream& os, const Player& pl){
        os<<pl.name<<" "<<pl.coef<<endl;
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
        void create(vector<T>);

        bool hasLeft(int) const;
        bool hasRight(int) const;
        int whoWins(Player, Player) const;

        void preorderTraversal(int);
        void preorderTraversal();
        void inorderTraversal(int);
        void inorderTraversal();
        void postorderTraversal(int);
        void postorderTraversal();

        bool isEmpty() const;
        void debug() const;
        vector<node<T>* > copyVector() const;

        void tournament(int, string);
        void tournament();
        void findpath(string);


    private:
        vector<node<T>*> nodes;
};

template<typename T>
void VecTree<T>::setLeft(int indx, T data) {
    int leftIndx = nodes.size();
    nodes[indx]->left = leftIndx;
    node<T>* temp = new node<T>();
    temp->data = data;
    temp->left = -1;
    temp->right = -1;
    nodes.push_back(temp);
};

template<typename T>
void VecTree<T>::setRight(int indx, T data) {
    int rightIndx = nodes.size();
    nodes[indx]->right = rightIndx;
    node<T>* temp = new node<T>();
    temp->data = data;
    temp->left = -1;
    temp->right = -1;
    nodes.push_back(temp);
};

template<typename T>
void VecTree<T>::create() {
    T x;
    std::queue<int> tmp;
    char ans;
    node<T>* nd = new node<T>;
    cout<<"Enter value:";std::cin>>x;
    nd->data = x;
    nd->left = nd->right = -1;
    tmp.push(nodes.size());
    nodes.push_back(nd);
    cout<<"More elements? y/n:";std::cin>>ans;
    while(ans == 'y' || ans == 'Y'){
        cout<<"Enter value:";std::cin>>x;
        int pos = tmp.front();
        tmp.push(nodes.size());
        if(nodes[pos]->left == -1){
            setLeft(pos,x);
        }
        else if(nodes[pos]->right == -1){
            setRight(pos,x);
        }
        if(nodes[pos]->left != -1 && nodes[pos]->right != -1){
            tmp.pop();
        }
        cout<<"More elements? y/n:";std::cin>>ans;
    }
};

template<typename T>
void VecTree<T>::create(vector<T> st) {
    std::queue<int> que;
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
        nd->left = nd->right = -1;
        que.push(nodes.size());
        nodes.push_back(nd);

    }

    while(!st.empty()){

        if(st.size() == 1){
            randomNumber = 0;
        } else {
            randomNumber = rand() % (st.size());
        }
        x = st[randomNumber];
        st.erase(st.begin() + randomNumber);

        int pos = que.front();
        que.push(nodes.size());
        if(nodes[pos]->left == -1){
            setLeft(pos,x);
        }
        else if(nodes[pos]->right == -1){
            setRight(pos,x);
        }
        if(nodes[pos]->left != -1 && nodes[pos]->right != -1){
            que.pop();
        }
    }
};

template<typename T>
bool VecTree<T>::hasLeft(int pos) const {
    return nodes[pos]->left != -1;
};

template<typename T>
bool VecTree<T>::hasRight(int pos) const {
    return nodes[pos]->right != -1;
};

template<typename T>
void VecTree<T>::tournament(int pos, string nameToPrint) {
    if(nodes[pos]->left != -1){
        if(hasLeft(nodes[pos]->left))tournament(nodes[pos]->left, nameToPrint);
    }
    if(nodes[pos]->right != -1){
        if(hasLeft(nodes[pos]->right))tournament(nodes[pos]->right, nameToPrint);
    }
    if(nodes[pos]->right != -1){
        if(nameToPrint == "" || nameToPrint == nodes[nodes[pos]->left]->data.name || nameToPrint == nodes[nodes[pos]->right]->data.name){
            cout<<" Currently "<<nodes[nodes[pos]->left]->data.name<<" with coefficient "
                <<nodes[nodes[pos]->left]->data.coef<<" and "<<nodes[nodes[pos]->right]->data.name<<" with coefficient "
                    <<nodes[nodes[pos]->right]->data.coef<<" are playing\n";
        }
        int result = whoWins(nodes[nodes[pos]->left]->data, nodes[nodes[pos]->right]->data);
        if(result == 2){
            if(nameToPrint == "" || nameToPrint == nodes[nodes[pos]->left]->data.name || nameToPrint == nodes[nodes[pos]->right]->data.name){
                nodes[nodes[pos]->left]->data = nodes[nodes[pos]->right]->data;
                cout<<" The winner is "<<nodes[nodes[pos]->left]->data<< "\n";
            } else nodes[nodes[pos]->left]->data = nodes[nodes[pos]->right]->data;
            nodes[nodes[pos]->right] = NULL;
        } else {
            if(nameToPrint == "" || nameToPrint == nodes[nodes[pos]->left]->data.name || nameToPrint == nodes[nodes[pos]->right]->data.name){
                cout<<" The winner is "<<nodes[nodes[pos]->left]->data<< "\n";
            }
            nodes[nodes[pos]->right] = NULL;
        }
    }
    if(nodes[pos]->left != -1){
        if(nameToPrint == "" || nameToPrint == nodes[pos]->data.name || nameToPrint == nodes[nodes[pos]->left]->data.name){
            cout<<" Currently "<<nodes[pos]->data.name<<" with coefficient "<<nodes[pos]->data.coef<<" and "<<nodes[nodes[pos]->left]->data.name
            <<" with coefficient "<<nodes[nodes[pos]->left]->data.coef<<" are playing\n";
        }
        int result = whoWins(nodes[pos]->data, nodes[nodes[pos]->left]->data);
        if(result == 2){

            if(nameToPrint == "" || nameToPrint == nodes[pos]->data.name || nameToPrint == nodes[nodes[pos]->left]->data.name){
                nodes[pos]->data = nodes[nodes[pos]->left]->data;
                cout<<" The winner is "<<nodes[pos]->data<< "\n";
            } else nodes[pos]->data = nodes[nodes[pos]->left]->data;
            nodes[nodes[pos]->left] = NULL;
        } else {
            if(nameToPrint == "" || nameToPrint == nodes[pos]->data.name || nameToPrint == nodes[nodes[pos]->left]->data.name){
                cout<<" The winner is "<<nodes[pos]->data<< "\n";
            }
            nodes[nodes[pos]->left] = NULL;
        }
    }
};

template<typename T>
void VecTree<T>::tournament() {
    vector<node<T>*> nodesCopy = copyVector();

    node<T>* m;
    if(nodes.size() == 0){
        cout<<"There are no players\n";
    } else {
        tournament(0,"");
        for(int i=0;i<nodes.size();i++){
            if(nodes[i]){
                m = nodes[i];
                break;
            }
        }
        nodes.clear();
        nodes.push_back(m);
        cout<<"The final winner is:"<<nodes[0]->data.name;
    }
    nodes = nodesCopy;
};

template<typename T>
void VecTree<T>::findpath(string name) {
    vector<node<T>* > nodesCopy = copyVector();
    if(nodes.size() == 0){
        cout<<"There are no players\n";
    } else tournament(0, name);
    nodes = nodesCopy;
};

/*
    Used to avoid any memory sharing that might occur
*/
template<typename T>
vector<node<T>* > VecTree<T>::copyVector() const {
    vector<node<T>* > newVector;
    for(int i=0;i<nodes.size();i++){
        node<T>* newNode = new node<T>;
        newNode->data = nodes[i]->data;
        newNode->left = nodes[i]->left;
        newNode->right = nodes[i]->right;
        newVector.push_back(newNode);
    }
    return newVector;
};

template<typename T>
int VecTree<T>::whoWins(Player player1, Player player2) const {// 1 = player1 2 - player2
    int sum = player1.coef + player2.coef;
    srand(time(NULL));
    int number = rand() % sum;
    if(number <= player1.coef)return 1;
    else return 2;
};

template<typename T>
void VecTree<T>::inorderTraversal(int index) {
    if(nodes[index]->left != -1)
        inorderTraversal(nodes[index]->left);
    cout<<nodes[index]->data<<" ";
    if(nodes[index]->right != -1)
        inorderTraversal(nodes[index]->right);
};

template<typename T>
void VecTree<T>::preorderTraversal() {
    preorderTraversal(0);
};

template<typename T>
void VecTree<T>::preorderTraversal(int index) {
    cout<<nodes[index]->data<<" ";
    if(nodes[index]->left != -1)
        preorderTraversal(nodes[index]->left);
    if(nodes[index]->right != -1)
        preorderTraversal(nodes[index]->right);
};

template<typename T>
void VecTree<T>::inorderTraversal() {
    inorderTraversal(0);
};

template<typename T>
void VecTree<T>::postorderTraversal(int index) {
    if(nodes[index]->left != -1)
        postorderTraversal(nodes[index]->left);
    if(nodes[index]->right != -1)
        postorderTraversal(nodes[index]->right);
    cout<<nodes[index]->data<<" ";
};

template<typename T>
void VecTree<T>::postorderTraversal() {
    postorderTraversal(0);
};

template<typename T>
bool VecTree<T>::isEmpty() const {
    return nodes.empty();
};

template<typename T>
void VecTree<T>::debug() const {
    for(int i=0;i<nodes.size();i++){
        cout<<"Nd"<<nodes[i]->data<<" "<<nodes[i]->left<<" "<<nodes[i]->right<<endl;
    }
}
#endif // VECTREE_H
