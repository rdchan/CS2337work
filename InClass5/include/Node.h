#ifndef NODE_H
#define NODE_H

class Node
{
private:
    int num;
    Node *right, *left, *next;


public:
    Node* getNext() { return next; }
    void setNext(Node* nex) { next = nex; }
    Node(){num=0;left=nullptr;right=nullptr; next = nullptr;}
    Node(int x){num=x;left=nullptr;right=nullptr; next = nullptr;}
    Node(Node* c){this->num=c->num; left=nullptr; right=nullptr; next = nullptr; }

    int getNum(){return num;}
    Node* getLeft(){return left;}
    Node* getRight(){return right;}

    void setNum(int x){num=x;}
    void setLeft(Node* n){left=n;}
    void setRight(Node* n){right=n;}

};
#endif // NODE_H
