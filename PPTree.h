#include<iostream>
#include<queue>
#include<stack>
#include <stdlib.h>
#include<vector>
#include <time.h>

#ifndef PPTREE_H
#define PPTREE_H

using std::vector;
using std::string;
using std::cout;
using std::endl;

struct Player {
    string name;
    int coef;
    friend std::ostream& operator<<(std::ostream& os, const Player& pl){
        os<<pl.name<<" "<<pl.coef<<endl;
        return os;
    }
};

template<typename T>
struct node
{
    T data;
    node<T>* left;
    node<T>* right;
};

template<typename T>
class PPTree
{
    public:
        PPTree();
        PPTree(const PPTree<T>&);
        PPTree<T>& operator=(const PPTree<T>&);
        ~PPTree();

        void create();
        void create(vector<T>);
        void tournament(node<T>*, string);
        void tournament();
        void findpath(string);
        int whoWins(Player, Player);
        void resize();

        void createNode(int, node<T>*[], node<T>**);
        node<T>* createTree(int n);

        // Traversals
        void preorderTraversal(node<T>*);
        void preorderTraversal();
        void inorderTraversal(node<T>*);
        void inorderTraversal();
        void postorderTraversal(node<T>*);
        void postorderTraversal();

        void debug(); // prints the pos array

        int getCurrIndex() const;
        bool isEmpty() const;
        bool hasTwoChilds(int) const;
        int findFirstChild(int) const;

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
    currIndex = 0;
};

template<typename T>
bool PPTree<T>::isEmpty() const {
    return currIndex == 0;
};

template<typename T>
void PPTree<T>::create() { // not randomized creation CBT
    T x;
    char ans;
    int posToCheck = 0;
    std::queue<int> tmp;
    std::cout<<"Node:";std::cin>>x;
    pos[currIndex] = -1;
    values[currIndex] = x;
    int currNode = currIndex;
    currIndex++;
    tmp.push(currNode);

    std::cout<<"More elements?(y/n):";std::cin>>ans;
    while(ans == 'y' || ans == 'Y'){
        if(currIndex == size - 1)resize();
        posToCheck = tmp.front();
        std::cout<<"Node:";std::cin>>x;

        values[currIndex] = x;
        if(hasTwoChilds(posToCheck)){
            tmp.pop();
            posToCheck = tmp.front();
        }
        if(!hasTwoChilds(posToCheck)){
            pos[currIndex] = posToCheck;
            tmp.push(currIndex);
        }
        currIndex++;
        std::cout<<"More elements? (y/n):";std::cin>>ans;
    }
};

template<typename T>
void PPTree<T>::create(vector<T> leafs) { //randomized creation
    T x;
    int currNode;
    int posToCheck = 0;
    std::queue<int> tmp;
    srand(time(0));
    int randomNumber;

    if(!leafs.empty()){
        int randomNumber;
        if(leafs.size() == 1){
            randomNumber = 0;
        } else {
            randomNumber = rand() % (leafs.size());
        }
        x = leafs[randomNumber];
        leafs.erase(leafs.begin() + randomNumber);

        pos[currIndex] = -1;
        values[currIndex] = x;
        int currNode = currIndex;
        currIndex++;
        tmp.push(currNode);
    }

    while(!leafs.empty()){
        if(leafs.size() == 1){
            randomNumber = 0;
        } else {
            randomNumber = rand() % (leafs.size());
        }
        x = leafs[randomNumber];
        leafs.erase(leafs.begin() + randomNumber);
        if(currIndex == size - 1)resize();
        posToCheck = tmp.front();
        values[currIndex] = x;
        if(hasTwoChilds(posToCheck)){
            tmp.pop();
            posToCheck = tmp.front();
        }
        if(!hasTwoChilds(posToCheck)){
            pos[currIndex] = posToCheck;
            tmp.push(currIndex);
        }
        currIndex++;
    }
};

template<typename T>
void PPTree<T>::debug() {
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
    temp->data = values[i];
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
void PPTree<T>::preorderTraversal(node<T>* root){
    if (root != NULL)
    {
        std::cout << root->val << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
};

template<typename T>
void PPTree<T>::preorderTraversal(){
    preorderTraversal(createTree(currIndex));
};

template<typename T>
void PPTree<T>::inorderTraversal(node<T>* root){
    if (root != NULL)
    {
        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }
};

template<typename T>
void PPTree<T>::inorderTraversal(){
    inorderTraversal(createTree(currIndex));
};

template<typename T>
void PPTree<T>::postorderTraversal(node<T>* root){
    if (root != NULL)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        std::cout << root->val << " ";
    }
};

template<typename T>
void PPTree<T>::postorderTraversal(){
    postorderTraversal(createTree(currIndex));
};

template<typename T>
int PPTree<T>::getCurrIndex() const{
    return currIndex;
};

template<typename T>
bool PPTree<T>::hasTwoChilds(int posToCheck) const{
    if(posToCheck > currIndex)return false;

    int br=0;
    for(int i =0; i<currIndex;i++){
        if(posToCheck == pos[i])br++;
    }

    return br >= 2;
}

template<typename T>
int PPTree<T>::findFirstChild(int posToCheck) const{
    if(posToCheck > currIndex)return false;

    for(int i = 0; i<currIndex;i++){
        if(posToCheck == pos[i])return i;
    }
};

template<typename T>
void PPTree<T>::tournament(node<T>* nd, string nameToPrint){
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
void PPTree<T>::tournament(){
    node<T>* tour = createTree(currIndex);
    if(tour == NULL){
        std::cout<<"There are no players\n";
    } else {
        tournament(tour,"");
        cout<<"The final winner is:"<<tour->data;
    }
};

template<typename T>
void PPTree<T>::findpath(string name){
    node<T>* tour = createTree(currIndex);
    if(tour == NULL){
        std::cout<<"There are no players\n";
    } else tournament(tour, name);
};

template<typename T>
int PPTree<T>::whoWins(Player player1, Player player2){// 1 = player1 2 - player2
    int sum = player1.coef + player2.coef;
    srand(time(NULL));
    int number = rand() % sum;
    if(number <= player1.coef)return 1;
    else return 2;
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
