#include<iostream>
#include<fstream>
#include"VecTree.h"
using namespace std;

vector<Player> readFromFile(){
    srand(time(0));
    vector<Player> testVec;
    vector<Player> realVec;
    Player player;
    ifstream object;
    object.open("participants.txt",ios::in);

    while(object>>player.name>>player.coef){
        testVec.push_back(player);
    }

    int rndNumber;
    int howManyPlayersToReallyInclude = rand() % testVec.size();

    while(howManyPlayersToReallyInclude-- >= 0){
        if(testVec.size() == 1){
            rndNumber = 0;
        } else {
            rndNumber = rand() % (testVec.size());
        }
        realVec.push_back(testVec[rndNumber]);
        testVec.erase(testVec.begin() + rndNumber);
    }
    object.close();
    return realVec;
};

void allFunctionTogether(){
    VecTree<Player> k;
    vector<Player> players = readFromFile();
    k.create(players);
    k.debug();
    k.tournament();
    cout<<endl;
    string name;
    cout<<endl;
    cout<<"Enter name to search for:";cin>>name;
    k.findpath(name);
};

int main(){
    allFunctionTogether();
}
