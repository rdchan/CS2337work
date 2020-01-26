#include <iostream>

using namespace std;


template<typename T>
class Stack {
    private:
        struct Node {
            T* data;
            Node* next;
        };
        Node* head = nullptr;
    public:
        void Push(T* data) {
            Node* new_head = new Node;
            new_head->data = data;
            new_head->next = head;
            head = new_head;
        }

        T* Pop() {
            T* item = new T;
            *item = *(head->data);
            Node* old_head = head;
            head = head->next;
            delete old_head;
            return item;
        }

        T* Peek() {
            return head->data;
        }

};
int main()
{
    cout << "Hello world!" << endl;
    Stack<int> stacc;
    stacc.Push(new int(5));
    stacc.Push(new int(8));
    cout << "should be 8: " << *(stacc.Peek()) << std::endl;
    cout << "still 8: " << *(stacc.Pop()) << endl;
    cout << "now 5: " << *(stacc.Pop()) << endl;
    return 0;
}
