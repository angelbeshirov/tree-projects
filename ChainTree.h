#include<iostream>

#ifndef CHAINTREE_H
#define CHAINTREE_H

template<typename T>
class ChainTree
{
    public:
        ChainTree();
        ChainTree(const ChainTree&);
        ChainTree& operator=(const ChainTree&);
        ~ChainTree();

        void create(int, bool);
        void print(int);
        void resize();
        bool isEmpty() const;

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
void ChainTree<T>::print(int pos){
    if(pos == -1)return;
    print(leftIndices[pos]);
    std::cout<<values[pos]<<' ';
    print(rightIndices[pos]);
};

template<typename T>
void ChainTree<T>::create(int pos,bool left){
    T x;
    char ans;
    if(i==size-1)resize();
    std::cout<<"Node:";std::cin>>x;
    values[i] = x;
    if(pos != -1 && left){
        leftIndices[pos] = i;
    } else if(pos != -1 && !left){
        rightIndices[pos] = i;
    }
    leftIndices[i] = -1;
    rightIndices[i] = -1;

    i++;
    int currNode = i-1;
    std::cout<<"Left tree of "<<x<<" (y/n)";
    std::cin>>ans;
    if(ans=='y'){
        create(currNode,true);
    }
    std::cout<<"Right tree of "<<x<<" (y/n)";
    std::cin>>ans;
    if(ans=='y'){
        create(currNode,false);
    }
};

template<typename T>
void ChainTree<T>::resize(){
    size *=2;
    T* valHelper = new T[size+1];
    int* leftHelper = new int[size+1];
    int* rightHelper = new int[size+1];

    for(int j=0;j<i;j++){
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
}
#endif // CHAINTREE_H
