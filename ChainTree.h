#include<iostream>
#include<queue>
#include<stack>
#include <stdlib.h>
#include<vector>
#include <time.h>

#ifndef CHAINTREE_H
#define CHAINTREE_H

using std::vector;
using std::string;

struct Player {
    std::string name;
    int coef;
    friend std::ostream& operator<<(std::ostream& os, const Player& pl){
        os<<pl.name<<" "<<pl.coef<<std::endl;
        return os;
    }
};

template<typename T>
class ChainTree
{
    public:
        ChainTree();
        ChainTree(const ChainTree&);
        ChainTree& operator=(const ChainTree&);
        ~ChainTree();

        void create();
        void create(vector<T>);
        void tournament(int, string);// "" = all matches
        void tournament();
        void findpath(string name);
        int whoWins(Player, Player);
        void refactor(int);

        void preorderTraversal() const;
        void preorderTraversal(int) const;

        void inorderTraversal() const;
        void inorderTraversal(int) const;

        void postorderTraversal() const;
        void postorderTraversal(int) const;

        void resize();
        bool isEmpty() const;

        void debug();

    private:
        T* values;
        int* leftIndices;
        int* rightIndices;
        int i;
        int size;
        void copy(const ChainTree&);
        void deleteTree();
};

template<typename T>
ChainTree<T>::ChainTree(){
    size = 10;
    i=0;
    values = new T[size];
    leftIndices = new int[size];
    rightIndices = new int[size];
};

template<typename T>
ChainTree<T>::ChainTree(const ChainTree<T>& ct){
    copy(ct);
};

template<typename T>
ChainTree<T>& ChainTree<T>::operator=(const ChainTree<T>& ct){
    if(this != &ct){
        deleteTree();
        copy(ct);
    }
    return *this;
};

template<typename T>
ChainTree<T>::~ChainTree(){
    deleteTree();
};

template<typename T>
void ChainTree<T>::copy(const ChainTree<T>& ct){
    size = ct.size;
    i = ct.i;
    values = new T[size];
    leftIndices = new int[size];
    rightIndices = new int[size];

    for(int i=0;i<ct.i;i++){
        values[i] = ct.values[i];
        leftIndices[i] = ct.leftIndices[i];
        rightIndices[i] = ct.rightIndices[i];
    }
};

template<typename T>
void ChainTree<T>::deleteTree(){
    delete[] values;
    delete[] leftIndices;
    delete[] rightIndices;
    values = NULL;
    leftIndices = NULL;
    rightIndices = NULL;
};

template<typename T>
void ChainTree<T>::preorderTraversal() const{
    preorderTraversal(0);
};

template<typename T>
void ChainTree<T>::preorderTraversal(int pos) const{
    if(pos == -1)return;
    std::cout<<values[pos];
    preorderTraversal(leftIndices[pos]);
    preorderTraversal(rightIndices[pos]);
};

template<typename T>
void ChainTree<T>::inorderTraversal() const{
    inorderTraversal(0);
};

template<typename T>
void ChainTree<T>::inorderTraversal(int pos) const{
    if(pos == -1)return;
    inorderTraversal(leftIndices[pos]);
    std::cout<<values[pos];
    inorderTraversal(rightIndices[pos]);
};

template<typename T>
void ChainTree<T>::postorderTraversal() const{
    postorderTraversal(0);
};

template<typename T>
void ChainTree<T>::postorderTraversal(int pos) const{
    if(pos == -1)return;
    postorderTraversal(leftIndices[pos]);
    postorderTraversal(rightIndices[pos]);
    std::cout<<values[pos];
};

template<typename T>
void ChainTree<T>::create(){
    T x;
    char ans;
    std::queue<int> tmp;
    std::cout<<"Node:";std::cin>>x;
    values[i] = x;
    leftIndices[i] = -1;
    rightIndices[i] = -1;
    i++;
    int currNode = i-1;
    tmp.push(currNode);
    std::cout<<"More elements?:";std::cin>>ans;
    while(ans == 'y' || ans == 'Y'){
        if(i == size - 1)resize();
        std::cout<<"Node:";std::cin>>x;
        values[i] = x;
        leftIndices[i] = -1;
        rightIndices[i] = -1;
        i++;
        currNode = i-1;
        int posToCheck = tmp.front();
        if(leftIndices[posToCheck] == -1){
            leftIndices[posToCheck] = currNode;
            tmp.push(currNode);
        }
        else if(rightIndices[posToCheck] == -1){
            rightIndices[posToCheck] = currNode;
            tmp.push(currNode);
        }
        if(leftIndices[posToCheck] != -1 && rightIndices[posToCheck] != -1){
            tmp.pop();
        }
        std::cout<<"More elements? y/n:";std::cin>>ans;
    }
};

template<typename T>
void ChainTree<T>::create(vector<T> leaves){
    T x;
    int currNode;
    std::queue<int> que;
    srand(time(0));
    int randomNumber;

    if(!leaves.empty()){
        int randomNumber;
        if(leaves.size() == 1){
            randomNumber = 0;
        } else {
            randomNumber = rand() % (leaves.size());
        }
        x = leaves[randomNumber];
        leaves.erase(leaves.begin() + randomNumber);
        values[i] = x;
        leftIndices[i] = -1;
        rightIndices[i] = -1;
        i++;
        currNode = i - 1;
        que.push(currNode);
    }
    while(!leaves.empty()){
        if(leaves.size() == 1){
            randomNumber = 0;
        } else {
            randomNumber = rand() % (leaves.size());
        }
        x = leaves[randomNumber];
        leaves.erase(leaves.begin() + randomNumber);
        if(i == size - 1)resize();
        values[i] = x;
        leftIndices[i] = -1;
        rightIndices[i] = -1;
        i++;
        currNode = i - 1;
        int posToCheck = que.front();
        if(leftIndices[posToCheck] == -1){
            leftIndices[posToCheck] = currNode;
            que.push(currNode);
        }
        else if(rightIndices[posToCheck] == -1){
            rightIndices[posToCheck] = currNode;
            que.push(currNode);
        }
        if(leftIndices[posToCheck] != -1 && rightIndices[posToCheck] != -1){
            que.pop();
        }
    }
};

template<typename T>
void ChainTree<T>::tournament(int pos, string nameToPrint){
    if(leftIndices[pos] != -1){
        if(leftIndices[leftIndices[pos]] != -1)tournament(leftIndices[pos], nameToPrint);
    }
    if(rightIndices[pos] != -1){
        if(leftIndices[rightIndices[pos]] != -1)tournament(rightIndices[pos], nameToPrint);
    }
    if(rightIndices[pos] != -1){
        if(nameToPrint == "" || nameToPrint == values[leftIndices[pos]].name || nameToPrint == values[rightIndices[pos]].name){
            std::cout<<" Currently "<<values[leftIndices[pos]].name<<" with coefficient "
                <<values[leftIndices[pos]].coef<<"  and "<<values[rightIndices[pos]].name<<" with coefficient "
                    <<values[rightIndices[pos]].coef<<"  are playing\n";
        }
        int result = whoWins(values[leftIndices[pos]], values[rightIndices[pos]]);
        if(result == 2){
            if(nameToPrint == "" || nameToPrint == values[leftIndices[pos]].name || nameToPrint == values[rightIndices[pos]].name){
                values[leftIndices[pos]] = values[rightIndices[pos]];
                std::cout<<" The winner is "<<values[leftIndices[pos]].name<< "\n";
                refactor(rightIndices[pos]);
            } else {
                values[leftIndices[pos]] = values[rightIndices[pos]];
                refactor(rightIndices[pos]);
            }
        } else {
            if(nameToPrint == "" || nameToPrint == values[leftIndices[pos]].name || nameToPrint == values[rightIndices[pos]].name){
                std::cout<<" The winner is "<<values[leftIndices[pos]]<< "\n";
            }
            refactor(rightIndices[pos]);
        }
    }
    if(leftIndices[pos] != -1){
        if(nameToPrint == "" || nameToPrint == values[pos].name || nameToPrint == values[leftIndices[pos]].name){
            std::cout<<" Currently "<<values[pos].name<<" with coefficient "<<values[pos].coef<<"  and "<<values[leftIndices[pos]].name<<" with coefficient "<<values[leftIndices[pos]].coef<<"  are playing\n";
        }
        int result = whoWins(values[pos], values[leftIndices[pos]]);
        if(result == 2){

            if(nameToPrint == "" || nameToPrint == values[pos].name || nameToPrint == values[leftIndices[pos]].name){
                values[pos] = values[leftIndices[pos]];
                std::cout<<" The winner is "<<values[pos]<< "\n";
                refactor(leftIndices[pos]);
            } else {
                values[pos] = values[leftIndices[pos]];
                refactor(leftIndices[pos]);
            }
        } else {
            if(nameToPrint == "" || nameToPrint == values[pos].name || nameToPrint == values[leftIndices[pos]].name){
                std::cout<<" The winner is "<<values[pos].name<< "\n";
            }
            refactor(leftIndices[pos]);
        }
    }
};

template<typename T>
void ChainTree<T>::refactor(int index){
    T* valHelper = new T[size+1];
    int* leftHelper = new int[size+1];
    int* rightHelper = new int[size+1];
    for(int j=0; j<index; j++){
        valHelper[j]=values[j];
        leftHelper[j]=leftIndices[j];
        rightHelper[j]=rightIndices[j];
    };

    for(int j = index + 1; j < size; j++){
        valHelper[j]=values[j];
        leftHelper[j]=leftIndices[j];
        rightHelper[j]=rightIndices[j];
    };
    deleteTree();
    values = valHelper;
    leftIndices = leftHelper;
    rightIndices = rightHelper;
    i--;
};

template<typename T>
void ChainTree<T>::tournament(){
    if(i == 0){
        std::cout<<"There are no players\n";
    } else {
        int sizeCopy = size;
        int iCopy = i;
        T* valuesCopy = new T[size];
        int* leftIndicesCopy = new int[size];
        int* rightIndicesCopy = new int[size];

        for(int j=0;j<i;j++){
            valuesCopy[j] = values[j];
            leftIndicesCopy[j] = leftIndices[j];
            rightIndicesCopy[j] = rightIndices[j];
        }
        tournament(0,"");
        std::cout<<"The winner is:" << values[i-1] ;

        size = sizeCopy;
        i = iCopy;
        for(int j=0;j<i;j++){
            values[j] = valuesCopy[j];
            leftIndices[j] = leftIndicesCopy[j];
            rightIndices[j] = rightIndicesCopy[j];
        }
    }
};

template<typename T>
int ChainTree<T>::whoWins(Player player1, Player player2){// 1 = player1 2 - player2
    int sum = player1.coef + player2.coef;
    srand(time(NULL));
    int number = rand() % sum;
    if(number <= player1.coef)return 1;
    else return 2;
};

template<typename T>
void ChainTree<T>::findpath(string name){
    if(i == 0){
        std::cout<<"There are no players\n";
    } else {
        int sizeCopy = size;
        int iCopy = i;
        T* valuesCopy = new T[size];
        int* leftIndicesCopy = new int[size];
        int* rightIndicesCopy = new int[size];

        for(int j=0;j<i;j++){
            valuesCopy[j] = values[j];
            leftIndicesCopy[j] = leftIndices[j];
            rightIndicesCopy[j] = rightIndices[j];
        }

        tournament(0,name);

        size = sizeCopy;
        i = iCopy;
        for(int j=0;j<i;j++){
            values[j] = valuesCopy[j];
            leftIndices[j] = leftIndicesCopy[j];
            rightIndices[j] = rightIndicesCopy[j];
        }
    }
};

template<typename T>
void ChainTree<T>::resize(){
    size *=2;
    T* valHelper = new T[size+1];
    int* leftHelper = new int[size+1];
    int* rightHelper = new int[size+1];

    for(int j=0; j<i; j++){
        valHelper[j]=values[j];
        leftHelper[j]=leftIndices[j];
        rightHelper[j]=rightIndices[j];
    }
    deleteTree();
    values = valHelper;
    leftIndices = leftHelper;
    rightIndices = rightHelper;
};

template<typename T>
bool ChainTree<T>::isEmpty() const{
    return i == 0;
};
#endif // CHAINTREE_H
