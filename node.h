#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node {
public:
    const int x, y;
    T data;
    Node* next;
    Node* down;

    void KillNext(){
        if(next!= nullptr){
            this->next->KillNext();
        }
        else{
            delete(this);
        }
    }

    void KillDown(){
        if(down!= nullptr){
            this->down->KillDown();
        }
        else{
            delete(this);
        }
    }
};

#endif