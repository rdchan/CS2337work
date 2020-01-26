//Rishi Chandna
//rdc180001
//Jiahua Fan jxf180028

#include <iostream>
#include "BST.h"
using namespace std;

int main()
{
    Node *node3 = new Node(3),*Node8 = new Node(8);
    Node* node1 = new Node(1);
    BST btree(5);
    btree.add(node3);
    btree.add(Node8);
    btree.add(node1);
    btree.BFPrint();
    cout << "height: " << btree.GetHeight() << endl;

}
