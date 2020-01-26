//Rishi Chandna
//RDC180001
#ifndef BINTREE_H
#define BINTREE_H

#include "Node.h"
#include <algorithm> //std::max for cleaner recursive height function

template<typename T>
class BinTree
{

    private:
        Node<T>* root;

        Node<T>* FindLeftmostChild(Node<T>* curr) { //recursive helper function for MinValue. helps in finding the first term
            while(curr->left) {
                return FindLeftmostChild(curr->left);
            }
            return curr;
        }

        //helper function for deleting a node.
        //starts from root, and goes down. looks for an ancestor that is a left child of a parent. that parent is the successor
        Node<T>* FindAncestorSuccessor(Node<T>* key, Node<T>* curr, Node<T>* succ) {
            //traverses down the tree from the root
            if(!curr) { return succ; } //if we reach the end of the tree, the most successive node we've found
            if(*(key->payload) < *(curr->payload)) {
                //if the key whose successor we are looking for is less than the node we're looking at
                succ = curr; //the thing we're looking at is bigger than the key, so it could be a successor
                return FindAncestorSuccessor(key, curr->left, succ); //go to the left of the tree to find a smaller value bigger than the key
            } else if (*(key->payload) > *(curr->payload)) {
                //if this node is smaller than the key, it can't be a successor.
                return FindAncestorSuccessor(key, curr->right, succ); //look for something bigger
            } else { return succ; } //if we traversed down to the key, no need to keep looking any further, return the successor
        }

    public:
        const Node<T>* getRoot() { return root;}
        BinTree() { root = nullptr;};
        ~BinTree() {delete root;};

        //for nice lazy function calls, since you can't have member variables be default arguments for some reason :(
        bool Insert(T data) {
            return Insert(data, root);
        }

        //recursively finds the leaf (or parent of single child) that should be the parent of the input data, then goes one more level to the null child
        //inserts there. uses a lookahead method, since parent pointers are gross
        bool Insert(T data, Node<T>* insert_point) {
            //inserting into empty tree should set root
            if(root == nullptr) {
                root = new Node<T>(data);
                return true;
            }

            if(insert_point == nullptr) { return false; } //shouldn't get here.
            if(*data < *(insert_point->payload)) { //check if we go left
                if(insert_point->left == nullptr) { //see if we can insert right there
                    insert_point->left = new Node<T>(data); //do so if possible
                    return true;
                } else {
                    return Insert(data, insert_point->left); //otherwise insert into left subtree recursively
                }

            } else { //same thing as before, but to the right.
                if(insert_point->right == nullptr) {
                    insert_point->right = new Node<T>(data);
                    return true;
                } else {
                    return Insert(data, insert_point->right);
                }
            }

            //no reason to get here. have it just in case?
            std::cerr << "insert error" << std::endl;
            return false;
        }

        //nice for lazy function calls since member variables can't be default arguments. too dynamic :(
        Node<T>* Search(T data) {
            return Search(data, root);
        }

        Node<T>* Search(T data, Node<T>* curr) {
            //if we went past a leaf, we didn't find it
            if(curr == nullptr) { return nullptr;}
            //see if we found it
            if(*data == *(curr->payload)) {
                return curr;
            } //if we didn't check left or right subtree accordingly.
            if(*data < *(curr->payload)) {
                return Search(data, curr->left);
            } else {
                return Search(data, curr->right);
            }

            std::cerr << "search error" << std::endl;
            return nullptr;
        }

        //helpful for deletion, also good to have.
        T FindSuccessor(T data) {
            //if the thing we are trying to find a successor for exists, go find it
            if(Search(data)) {
                return *(FindSuccessor(Search(data))->payload);
            } else {
                //if it doesn't exist to begin with, there won't be a successor
                std::cerr << "node dne error in BinTree::FindSuccessor" << std::endl;
                return -1;
            }
        }

        Node<T>* FindSuccessor(Node<T>* key) {
            //how we search for successor depends on the existence of the right subtree

            if(key->right) {
                //if it exists, go to the right subtree, and find least (leftmost) value
                return FindLeftmostChild(key->right);
            } else {
                //if it doesn't exist, then the successor is an ancestor
                return FindAncestorSuccessor(key, root, nullptr);
            }

        }


        //rip default arguments. can't be member variables :(
        bool Delete(T data) {
            return Delete(data, root, nullptr);
        }

        bool Delete(T data, Node<T>* curr, Node<T>* parent) {
            //if the node we're looking at is null, return false
            if(curr == nullptr) { return false;}

            //otherwise check if we found the thing to delete
            if(data == *(curr->payload)) {
                //if we did, how we remove it depends on its children
                //if it's a leaf node
                if(!curr->left && !curr->right) {
                    //check if the parent is null (removing the root)
                    if(parent == nullptr) {
                        //deallocate memory for curr and set root to nullptr
                        delete curr;
                        root = nullptr;
                    } else if (parent->left == curr) {
                        //if this is the parent's left child
                        delete curr;
                        parent->left = nullptr;
                    } else if (parent->right == curr) {
                        //if this is the parent's right child
                        delete curr;
                        parent->right = nullptr;
                    }

                } else if (curr->left && !curr->right) {
                    //if it has a left child but not a right child
                    if(parent == nullptr) {
                        Node<T>* left_side = curr->left;
                        curr->left = nullptr;
                        delete curr;
                        root = left_side;
                    } else if (parent->left == curr) {
                        //if this is the parent's left child
                        Node<T>* left_side = curr->left;

                        //don't recursively delete all descendants
                        curr->left = nullptr;
                        delete curr;

                        parent->left = left_side;
                    } else if (parent->right == curr) {
                        //if this is the parent's right child
                        Node<T>* right_side = curr->right;

                        //don't recursively delete all descendants
                        curr->left = nullptr;
                        delete curr;

                        parent->right = right_side;
                    }
                } else if (!curr->left && curr->right) {
                    //if it has a right child but not a left child

                    if(parent == nullptr) {
                        Node<T>* right_side = curr->right;
                        curr->right = nullptr;
                        delete curr;
                        root = right_side;
                    } else if(parent->left == curr) {
                        //if this is the parent's left child
                        Node<T>* right_side = curr->right;

                        //don't recursively delete all descendants
                        curr->left = nullptr; curr->right = nullptr;
                        delete curr;

                        parent->left = right_side;
                    } else if(parent->right == curr) {
                        Node<T>* right_side = curr->right;

                        //don't recursively delete all descendants
                        curr->left = nullptr; curr->right = nullptr;
                        delete curr;

                        parent->right = right_side;
                    }
                } else {
                    //the node we are trying to remove has two children

                    T succ_payload = *(FindSuccessor(curr)->payload);
                    Delete(succ_payload, curr, parent);
                    *(curr->payload) = succ_payload;
                }
                return true;
            } else {
                //we haven't found the key to delete yet
                if(data < *(curr->payload)) {
                    //if the key is less than the payload
                    return Delete(data, curr->left, curr);
                    //delete the data from the left subtree, with this node as the parent
                } else {
                    //otherwise it's >=
                    return Delete(data, curr->right, curr);
                    //go to the right subtree
                }
            }

            //shouldn't get here
            std::cout << "bintree delete error" << std::endl;

            return false;
        }

        bool isEmpty() {
            return root == nullptr;
        }

        int Size() {
            return Size(root);
        }

        int Size(Node<T>* curr) {
            if(curr == nullptr) { return 0;}
            //add the left side, this one (1), and the right side.
            return Size(curr->left) + 1 + Size(curr->right);
        }

        //nicely 0 indexed
        int Height() {
            return Height(root);
        }

        //1 indexed
        int Height(Node<T>* curr) {
            if(curr == nullptr) { return -1; }
            //return 1 + whichever is higher between the left and right subtrees.
            return 1+std::max(Height(curr->left),Height(curr->right));
        }

        Node<T>* MinValue() {
            return MinValue(root);
        }

        //just slide down the left side as far as possible
        Node<T>* MinValue(Node<T>* curr) {
            if(curr->left == nullptr) { return curr;}
            return MinValue(curr->left);
        }

        Node<T>* MaxValue() {
            return MaxValue(root);
        }

        //just slide down the right side as far as possible
        Node<T>* MaxValue(Node<T>* curr) {
            if(curr->right == nullptr) { return curr;}
            return MaxValue(curr->right);
        }

        void PrintTree() {
            PrintTree(root);
        }

        //inorder recursive print
        void PrintTree(Node<T>* curr) {
            if(curr == nullptr) {
                return;
            }
            PrintTree(curr->left);
            std::cout << *(curr->payload) << ":" << curr << ", "; //GOTTA OVERLOAD THE << OPERATOR FOR the payload to use this effectively
            PrintTree(curr->right);
        }

    protected:

};

#endif // BINTREE_H
