//Rishi Chandna
//rdc180001
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream> //cout for lame print function that prints the address of each node.

template<typename T>
class LinkedList
{
    private:


        //ListFindInsertionPosition is used for sort.
        //searches the list for the insertion position and returns the list node after which the current node should be inserted.
        //If the current node should be inserted at the head
            //ListFindInsertionPosition return null.
        Node<T>* head; //probably should be private but then defining friend functions in here requires an inclusion of Player
        Node<T>* tail;

        Node<T>* FindInsertionPosition(T* data) {
            Node<T>* beforeIter = nullptr;
            Node<T>* iter = this->head;
            while(iter != nullptr && (*(iter->getPayload()) < (*data) )) {
                beforeIter = iter;
                iter = iter->getNext();
            }
            return beforeIter;
        }

    public:

        LinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        ~LinkedList() {
            delete head; //sets of chain reaction type deal and deletes all nodes
        }

        Node<T>* getHead() { return head;}
        Node<T>* getTail() { return tail;}
        void append(T data) { //accepts a static object of the data

            //Create a new node of the templated type, with next pointer nullptr
            Node<T>* new_node = new Node<T>(data);

            //If list’s head pointer is null
            if(this->head == nullptr) {
                //Set the list’s head pointer and tail pointer to the new node
                this->head = new_node;
                this->tail = new_node;
            //Otherwise
            } else {
                //set tail->next to the new node
                tail->setNext(new_node);
                //set the list's tail pointer to the new node
                tail = new_node;
            }
        };

        void append(T* data) { //accepts a pointer to the data
            //Create a new node of the templated type, with next pointer nullptr
            Node<T>* new_node = new Node<T>(data);

            //If list’s head pointer is null
            if(this->head == nullptr) {
                //Set the list’s head pointer and tail pointer to the new node
                this->head = new_node;
                this->tail = new_node;
            //Otherwise
            } else {
                //set tail->next to the new node
                tail->setNext( new_node );
                //set the list's tail pointer to the new node
                tail = new_node;
            }
        }

        void append(Node<T>* new_node) { //accepts a node pointer
            //If list’s head pointer is null
            if(this->head == nullptr) {
                //Set the list’s head pointer and tail pointer to the new node
                this->head = new_node;
                this->tail = new_node;
            //Otherwise
            } else {
                //set tail->next to the new node
                tail->next = new_node;
                //set the list's tail pointer to the new node
                tail = new_node;
            }
        }

        void prepend(T data) {

            //Create a new node of the templated type, with next pointer nullptr
            Node<T>* new_node = new Node<T>(data);

            //If list’s head pointer is null (list is empty)
            if(this->head == nullptr) {
                //Set the list’s head pointer and tail pointer to the new node
                this->head = new_node;
                this->tail = new_node;
            } else {
                //set new_node's next pointer to the list’s head pointer
                new_node->next = this->head;

                //Set the list’s head pointer to the new node
                this->head = new_node;
            }

        };

        void prepend(T* data) { //accepts a pointer to the data
        //Create a new node of the templated type, with next pointer nullptr
            Node<T>* new_node = new Node<T>(data);

            //If list’s head pointer is null (list is empty)
            if(this->head == nullptr) {
                //Set the list’s head pointer and tail pointer to the new node
                this->head = new_node;
                this->tail = new_node;
            } else {
                //set new_node's next pointer to the list’s head pointer
                new_node->next = this->head;

                //Set the list’s head pointer to the new node
                this->head = new_node;
            }
        }

        void prepend(Node<T>* new_node) { //accepts a pointer to a node
            //If list’s head pointer is null (list is empty)
            if(this->head == nullptr) {
                //Set the list’s head pointer and tail pointer to the new node
                this->head = new_node;
                this->tail = new_node;
            } else {
                //set new_node's next pointer to the list’s head pointer
                new_node->setNext(this->head);

                //Set the list’s head pointer to the new node
                this->head = new_node;
            }
        }
        bool remove(T data) {

            //case when empty
            if(this->head == nullptr) { return false; }

            //case when removing head
            if(this->head->payload == data) {

                Node<T>* new_head = this->head->getNext();
                delete this->head;
                this->head = this->head->getNext();
                return true;
            }

            //for removing a middle element or the tail...
            //Create a node pointer to traverse the list, set it to the head
            Node<T>* iter = this->head;
            //While the pointer’s next’s templated data object isn’t equal to the parameter passed in
            while(!(iter->getNext()->getPayload() == data)) {
                //Set the pointer to the pointer’s next node field
                iter = iter->getNext();

                //If the pointer is now nullptr (reached the end of the list)
                    //Return false
                if(iter == nullptr) { return false; }
            }
            //We are now at the node right before the node to be deleted. iter->next is getting deleted
            //If the pointer’s next’s next’s field is nullptr, that means we are removing the tail
            if(iter->getNext()->getNext() == nullptr) {
                //Deallocate memory for this pointer’s next pointer.
                delete iter->getNext();
                //this pointer is now the tail, so set its next to null
                iter->next = nullptr;
                //Set the tail field of the list to the node this pointer is pointing to
                this->tail = iter;
                //Return true
                return true;
            } else {
                //in this scenario, we are removing something. we are removing iter->next

                //Create a new pointer to the same address as this pointer’s next field
                Node<T>* to_delete = iter->getNext();

                //Set this pointer’s next field to this pointer’s next’s next’s field
                iter->setNext( iter->getNext()->getNext() );

                //Deallocate memory for the new pointer
                delete to_delete;

                //Return true
                return true;
            }
        };

        bool search(T data) {
            //if head pointer is null
                //return false
            if(this->head == nullptr) { return false; }

            //Create a node pointer to traverse the list, set it to the head
            Node<T>* iter = this->head;

            //While the pointer’s next’s templated data object isn’t equal to the parameter passed in
            while(!(iter->getNext()->payload == data)) { //requires overload of == operator in the template typename object

                //Set the pointer to the pointer’s next node field
                iter = iter->getNext();

                //If the pointer is now nullptr (reached the end of the list)
                    //Return false
                if(iter == nullptr) { return false; }
            }
            //since we exited the while, it means that iter->next->payload is the data that we were searching for
            //Return true
            return true;

        };

        void print() {
            //Prints to console
            //Create a node pointer to traverse the list, set it to the head
            Node<T>* iter = this->head;

            //While the pointer isn’t nullptr
            while(iter != nullptr) {
                //Print the contents of the node pointed at by the pointer

                std::cout << (iter->getPayload()) << std::endl;

                //Set the pointer to the pointer’s next node field
                iter = iter->getNext();
            }
            //exit
        };

        //tries to insert new_node after the location node. returns bool if it was successful or not.
        //NOTE: doesn't actually check if location exists.
        bool insertAfter(Node<T>* location, Node<T>* new_node) {

            if(this->head == nullptr) { //list is empty
                this->head = new_node;
                this->tail = new_node;
                return true;
            } else if (this->tail == location) {
                this->tail->setNext(new_node);
                this->tail = new_node;
                new_node->setNext(nullptr);
                return true;
            } else {
                new_node->setNext(location->getNext());
                location->setNext(new_node);
                return true;
            }
        }


        //NOTE: also doesn't check if location exists.
        bool removeAfter(Node<T>* location) {

            //special case for removing the head
            if(location == nullptr && this->head != nullptr) {
                Node<T>* new_head = this->head->getNext();
                delete head;
                this->head = new_head;
            } else if( location->getNext() != nullptr) { //make sure we aren't trying to remove something after the tail
                Node<T>* successor_node = location->getNext()->getNext();
                location->setNext(successor_node);

                //if we removed the tail..
                if(successor_node == nullptr) {
                    this->tail = location;
                }
            }
            return true;
        }

        //requires the typename to have a defined < operator
        void sort() {

            if(this->head == nullptr) { return;}
            if(this->head->getNext() == nullptr) { return; }
            Node<T>* beforeCurrent = this->head;
            Node<T>* current = this->head->getNext();
            Node<T>* afterCurrent = current->getNext();
            Node<T>* position;
            //For node : list
            while(current != nullptr) {
                afterCurrent = current->getNext();
                position = FindInsertionPosition(current->getPayload());

                if(position == beforeCurrent) {
                    beforeCurrent = current;
                } else {
                    removeAfter(beforeCurrent);
                    if(position == nullptr) {
                        prepend(current);
                    } else {
                        insertAfter(position, current);
                    }
                }
                current = afterCurrent;
            }
        };

        bool isEmpty() {return this->head == nullptr;  }

        //not often used, but could be helpful to someone else.
        int length() {
            //Set length to 0
            int length = 0;

            //Set node pointer to the head pointer
            Node<T>* iter = this->head;

            //While our node pointer isn’t nullptr
            while(iter != nullptr) {
                //Increment length
                length++;

                //Set node pointer to it’s next field
                iter = iter->getNext();
            }
            //Return length
            return length;
        };

    protected:


};

#endif // LINKEDLIST_H
