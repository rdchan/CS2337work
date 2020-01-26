//Rishi Chandna rdc180001
#ifndef HASHENTRY_H
#define HASHENTRY_H

template<typename T>
class HashEntry
{
    public:

        HashEntry() {
            this->key = 0;
            this->value = T();
            this->status = 's';
        }

        HashEntry(int key, T value) : HashEntry() {
            this->key = key;
            this->value = value;
        }

        void setStatus(char s) { status = s; }
        int getKey() { return key; }
        T getValue() { return value; }
        char getStatus() { return status; }
        ~HashEntry();

    protected:

    private:
        int key;
        T value;
        char status; //s is empty since start, r is empty since removal, o is occupied
};

#endif // HASHENTRY_H
