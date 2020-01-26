#include "Queue.h"

void Queue::Push(Node* in) {
    if(in == nullptr) { return; }
    if(head == nullptr) {
                head = in;
                tail = in;
                return;
            } else {
                tail->setNext(in);
                tail = in;
            }

}

Node* Queue::Pop() {
            if(head != nullptr) {
                Node* to_return = head;
                if(head->getNext()) {
                    head = head->getNext();
                } else {
                    head = nullptr;
                }
                return to_return;
            }
            return nullptr;
        }
