//Rishi Chandna
//RDC180001
#ifndef NODE_H
#define NODE_H

#include "BinTree.h"
#include "Payload.h"
template<typename T>
class BinTree;

//nothing really interesting in here. holds a payload, and a left and right child.
//for inheritance to handle trig terms also, holds a Payload pointer. that's kinda interesting
template<typename T>
class Node
{
    public:
        Node() { payload = nullptr; left = nullptr; right = nullptr; }

        Node(T* input) : Node(){
            payload = input;
        }

        Node(T input) : Node() {
            payload = new T(input);
        }

        ~Node(){delete left; delete payload; delete right; };

        //some accessors because friend functions that aren't in classes are hard.
        T getPayload() const { return *payload; }
        Node<T>* getLeft() const { return left; }
        Node<T>* getRight() const { return right; }

        friend class BinTree<T>;
    protected:

    private:
        Node<T>* left;
        Node<T>* right;
        T* payload;

};

#endif // NODE_H
