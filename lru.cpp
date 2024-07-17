#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data
class Node{
public:
    string key;
    int value;
    Node(string key, int value){
        this->key = key;
        this->value = value;
    }
};

//LRU CACHE DATA STRUCTURE
class LRUCache{
public:
    int maxSize;
    list<Node> l;
    unordered_map<string, list<Node>::iterator> m;//key to iterator of list

    LRUCache(int maxSize){
        this->maxSize = maxSize > 1 ? maxSize : 1;//if its 0-->1 
    }

    void insertKeyValue(string key, int value){
        // 2cases
        //if it is present in the hashMap-->present in the cache-->cache hit
        if(m.count(key) != 0){
            //simply update the value of key
            auto it = m[key];
            it->value = value;
        }
        else{
            //check if cache is full or not
            //if it is full remove the last or lru item from the cache
            if(l.size() == maxSize){
                Node last = l.back();
                m.erase(last.key);
                l.pop_back();
            }
            Node n(key, value);
            l.push_front(n);//becomes the head
            m[key] = l.begin();//address of the head
        }
    }

    int* getValue(string key){
        //if key is not present in the cache
        if(m.count(key) == 0){
            return NULL;
        }

        //if key is present in the cache-->cache hit, node should come to the top, address in the map will also be changed
        auto it = m[key];
        int value = it->value;

        //move this key to the front of the list
        l.push_front(*it);
        l.erase(it);
        m[key] = l.begin();
        //return value;//cant return the address of the value as it will be deleted
        return &l.begin()->value;//return the address of the value at the head
    }

    string mostRecentKey(){
        return l.front().key;
    }

};

int main(){
    LRUCache lru(3);
    lru.insertKeyValue("mango", 10);
    lru.insertKeyValue("apple", 20);
    lru.insertKeyValue("guava", 30);
    cout<<lru.mostRecentKey()<<endl;

    lru.insertKeyValue("mango", 40);
    cout<<lru.mostRecentKey()<<endl;

    int* orders = lru.getValue("mango");
    if(orders != NULL){
        cout<<"Value of mango is "<<*orders<<endl;
    }

    lru.insertKeyValue("banana", 50);

    if(lru.getValue("apple") == NULL){
        cout<<"apple doesn't exist"<<endl;
    }
    if(lru.getValue("guava") == NULL){
        cout<<"guava doesn't exist"<<endl;
    }
    if(lru.getValue("mango") == NULL){
        cout<<"mango doesn't exist"<<endl;
    }
    if(lru.getValue("banana") == NULL){
        cout<<"banana doesn't exist"<<endl;
    }

    return 0;
}