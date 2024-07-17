#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data
class Node{
public:
    int key;
    int value;
    Node(int k, int v){
        key = k;
        value = v;
    }
};