//Rishi Chandna
//rdc180001
//Jiahua Fan jxf180028

#include "BST.h"
#include "Queue.h"
#include <iostream>

#include <algorithm>

bool BST::search(int x)
{
  Node* ptr = root;
  while (ptr)
  {
    if (ptr->getNum() == x)
        return true;
    else if (x < ptr->getNum())
        ptr = ptr->getLeft();
    else
        ptr = ptr->getRight();
  }
  return false;

}

void BST::BFPrint() {
    Queue* q = new Queue();
    q->Push(root);
    while(!q->isEmpty()) {
        //print front of queue
        Node* print = q->Pop();

        std::cout << print->getNum() << ", ";
        //add front of queue's children to queue
        q->Push(print->getLeft());
        q->Push(print->getRight());
    }
}

void BST::add(Node* n)
{
    if (!root)
        root = n;
    else
    {
        Node *ptr = root;
        while(true)
        {
            if (n->getNum() < ptr->getNum())
            {
                if (ptr->getLeft())
                    ptr = ptr->getLeft();
                else
                {
                    ptr->setLeft(n);
                    break;
                }
            }
            else
            {
                if (ptr->getRight())
                    ptr = ptr->getRight();
                else
                {
                    ptr->setRight(n);
                    break;
                }
            }
        }
    }
}


Node* BST::deleteNode(int x)
{

    Node* parent = nullptr, *cur = root;

    while (cur)
    {
        if (cur->getNum() == x)
        {
            //if 0 children
            if (!cur->getLeft() && !cur->getRight())
            {
                Node* hold = new Node(cur);
                //if inside the tree
                if (parent)
                {
                    //check which child of the parent
                    if(parent->getLeft() == cur)
                        parent->setLeft(nullptr);
                    else
                        parent->setRight(nullptr);
                }
                else
                    root = nullptr;

                delete cur;
                return hold;
            }
            // check for 2 children
            else if(cur->getLeft() && cur->getRight())
            {
                Node* hold = cur;
		Node* temp = new Node(hold);
                parent = cur;
                cur = cur->getLeft();
                // move to the rightmost child of left subtree
                while (cur->getRight())
                {
                    parent = cur;
                    cur = cur->getRight();
                }
                //copying the data
                hold->setNum(cur->getNum());

                //link cur's parent to cur's child
                if (parent == hold)
                    parent->setLeft(cur->getLeft());
                else
                    parent->setRight(cur->getLeft());

                delete cur;
                return temp;
            }
            //has 1 child
            else
            {
                if (parent)
                {
                    //check if cur is left child
                    if (parent->getLeft() == cur)
                        //assign parent left to cur's child
                        parent->setLeft(cur->getLeft() ? cur->getLeft() : cur->getRight());
                    else
                        //assign parent right to cur's child
                        parent->setRight(cur->getLeft() ? cur->getLeft() : cur->getRight());
                }
                else
                    root = cur->getLeft() ? cur->getLeft() : cur->getRight();

                Node* hold = new Node(cur);
                delete cur;
                return hold;
            }


        }
        else
        {
            parent = cur;
            if (x < cur->getNum())
                cur = cur->getLeft();
            else
                cur = cur->getRight();
        }
    }



}

int BST::GetHeight(Node* cur) {
    if(cur == nullptr) { return 0; }
    return std::max(GetHeight(cur->getLeft()), GetHeight(cur->getRight())) + 1;
}
int BST::GetHeight() {
    return GetHeight(root);
}
