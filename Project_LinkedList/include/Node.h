//Rishi Chandna
//rdc180001
#ifndef NODE_H
#define NODE_H

#include <string>

template<typename T> //used for templated payload data. could use player explicitly, but want reusable classes
class Node
{

    private:
        T* payload; //member variable for holding the player or whatever else
        Node<T>* next; //member variable for pointing to the next node in the singly linked list
    public:


        Node() {
            this->next = nullptr;
            this->payload = new T();
        }

        //can be kinda sketchy if the template used doesn't have a constructor that takes in a string
        //be careful with using this constructor outside of a Player type
        Node(std::string name) {
            this->next = nullptr;
            this->payload = new T(name);
            dynamic_pointer_exists = true;
        }

        Node(T data) { //uses static object of the data
            this->next = nullptr;
            this->payload = new T(data);
            dynamic_pointer_exists = true; //used for cleanup
        }

        Node(T* data) { //accepts a pointer to the data.
            this->next = nullptr;
            this->payload = data;
        }

        ~Node() {
            if(dynamic_pointer_exists) {
                delete payload;
            }
            delete next;
        }

        T* getPayload() { return payload; }
        Node<T>* getNext() { return next; }
        void setNext(Node<T>* new_node) { next = new_node; }
    protected:

    private:
        bool dynamic_pointer_exists = false; //used for knowing when cleanup is necessary

};

#endif // NODE_H
