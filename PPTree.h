#include<iostream>

#ifndef PPTREE_H
#define PPTREE_H

template<typename T>
struct node
{
    T val;
    node* left;
    node* right;
};

template<typename T>
class PPTree
{
    public:
        PPTree();
        PPTree(const PPTree<T>&);
        PPTree<T>& operator=(const PPTree<T>&);
        ~PPTree();

        void create(int);
        void resize();
        void createNode(int, node<T>*[], node<T>**);
        node<T>* createTree(int n);

        void inorder(node<T>*);
        void print(); // prints the pos array

        int getLength() const;
        bool isEmpty() const;

    private:
        int* pos;
        T* values;
        int size;
        int currIndex;
        void copyTree(const PPTree<T>&);
        void deleteTree();
};

template<typename T>
PPTree<T>::PPTree(){
    size = 10;
    currIndex = 0;
    pos = new int[size];
    values = new T[size];
};

template<typename T>
PPTree<T>::PPTree(const PPTree<T>& PPTree){
    copyTree(PPTree);
};

template<typename T>
PPTree<T>& PPTree<T>::operator=(const PPTree<T>& PPTree){
    if(this != &PPTree){
        deleteTree();
        copyTree(PPTree);
    }
    return *this;
};

template<typename T>
PPTree<T>::~PPTree(){
    deleteTree();
};

template<typename T>
void PPTree<T>::copyTree(const PPTree<T>& PPTree){
    size = PPTree.size;
    currIndex = PPTree.currIndex;
    pos = new int[size];
    values = new T[size];

    for(int i = 0;i<currIndex;i++){
        pos[i] = PPTree.pos[i];
        values[i] = PPTree.values[i];
    }
};

template<typename T>
void PPTree<T>::deleteTree(){
    delete[] pos;
    delete[] values;
    pos = NULL;
    values = NULL;
};

template<typename T>
bool PPTree<T>::isEmpty() const {
    return currIndex == 0;
};

template<typename T>
void PPTree<T>::create(int parent) {
    T x;
    char ans;

    if(currIndex == size-1)resize();
    std::cout<<"Node:";std::cin>>x;

    pos[currIndex] = parent;
    values[currIndex] = x;
    int currNode = currIndex;
    currIndex++;

    std::cout<<"Left tree of "<<x<<" (y/n)";
    std::cin>>ans;
    if(ans=='y'){
        create(currNode);
    }

    std::cout<<"Right tree of "<<x<<" (y/n)";
    std::cin>>ans;
    if(ans=='y'){
        create(currNode);
    }
};

template<typename T>
void PPTree<T>::print() {
    for(int i=0;i<currIndex;i++){
        std::cout<<pos[i]<<" ";
    }
};

template<typename T>
void PPTree<T>::createNode(int i, node<T> *created[], node<T>** root)
{
    if (created[i] != NULL)
        return;

    node<T>* temp = new node<T>;
    temp->val = values[i];
    temp->left = temp->right = NULL;
    created[i] = temp;

    if (pos[i] == -1){
        *root = created[i];
        return;
    }

    if (created[pos[i]] == NULL)
        createNode(pos[i], created, root);

    node<T>* p = created[pos[i]];

    if (p->left == NULL)
        p->left = created[i];
    else
        p->right = created[i];
};

template<typename T>
node<T>* PPTree<T>::createTree(int n)
{
    node<T>* created[n];
    for (int i=0; i<n; i++)
        created[i] = NULL;

    node<T>* root = NULL;
    for (int i=0; i<n; i++)
        createNode(i, created, &root);

    return root;
};

template<typename T>
void PPTree<T>::inorder(node<T>* root){
    if (root != NULL)
    {
        inorder(root->left);
        std::cout << root->val << " ";
        inorder(root->right);
    }
};

template<typename T>
int PPTree<T>::getLength() const{
    return currIndex;
};

template<typename T>
void PPTree<T>::resize(){
    size*=2;
    int* posHelper = new int[size];
    T* valHelper = new T[size];
    for(int i=0;i<currIndex;i++){
        posHelper[i] = pos[i];
        valHelper[i] = values[i];
    }

    delete[] pos;
    delete[] values;

    pos = posHelper;
    values = valHelper;
};

#endif // PPTREE_H
