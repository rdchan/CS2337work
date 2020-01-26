#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <math.h>
#include <iostream>
#include <vector>

#define PRIME_ONE 31 //used for double hashing!
#define PRIME_TWO 11

template<typename T>
struct bucket { //hash table is made of buckets, so it has the data but some metadata too
    T* data = nullptr;
    std::string key = "";
    char status = 's';
};

template<typename T>
class HashTable
{
    public:
        HashTable() {
            SIZE_OF_TABLE = 0;
            table = nullptr;
        }

        HashTable(unsigned int size) : HashTable() {
            SIZE_OF_TABLE = size;
            table = new bucket<T>*[SIZE_OF_TABLE];
            for(unsigned int i = 0; i < SIZE_OF_TABLE; i++) {
                table[i] = nullptr;
            }
        }
        ~HashTable() {
            delete table;
        }


        bool Insert(T* value, std::string key) {

            bucket<T>* entry = new bucket<T>();
            entry->data = value;
            entry->key = key;
            entry->status = 's';

            if(table == nullptr) {
                Resize();
            }

            unsigned int attempts_made = 0;
            int hash = (HashOne(entry->key) + attempts_made * HashTwo(entry->key)) % SIZE_OF_TABLE;
            while(attempts_made < SIZE_OF_TABLE) { //don't insert it if there's no space. there should always be space though since we resize.
                                            //also used as an exit condition if I chose poor c1 and c2/quadratic couldn't find a spot
                if(table[hash] == nullptr) { //if it's empty (could check value is s or r, but either works
                    table[hash] = entry;
                    table[hash]->status = 'o';
                    //std::cout << "inserted: " << entry->key << " at " << hash << std::endl;
                    num_entries++; //increment num_entries to calculate load factor and determine resizing

                    //rehash if necessary
                    if( (double)(num_entries)/(double)(SIZE_OF_TABLE) >= max_load_factor) {
                        Resize();
                    }

                    return true;
                }
                //if it didn't work yet, try the next hash
                attempts_made++;
                hash = (HashOne(entry->key) + attempts_made * HashTwo(entry->key)) % SIZE_OF_TABLE;

            }
            std::cout << "couldn't insert" << std::endl;
            return false;
        }

        T* operator[](std::string key) {
            //std::cout << "fetching bucket with key: " << key << std::endl;
            unsigned int attempts_made = 0;
            int hash = (HashOne(key) + attempts_made * HashTwo(key)) % SIZE_OF_TABLE;
            while(attempts_made < SIZE_OF_TABLE) {

                //if the hit is marked as empty since start, return nullptr
                if(table[hash] == nullptr || table[hash]->status == 's') {
                    return nullptr;
                }

                //if we get a hit return it
                if(table[hash]->key == key) {
                  //  std::cout << "using key :" << key << ":, found hit at hash code " << hash << std::endl;
                    return table[hash]->data;
                }

                //if we haven't exited, we need to check the next possible hash.
                attempts_made++ ;
                hash = (HashOne(key) + attempts_made * HashTwo(key)) % SIZE_OF_TABLE;
            }

            std::cout << "exceeded max attempts in finding key: " << key << std::endl;
            return nullptr;
        }

        //follows logic for finding the bucket with the key, but instead of returning the data, the bucket must be cleared
        bool Erase(std::string key) {
            //std::cout << "searching for bucket with key: " << key << std::endl;
            unsigned int attempts_made = 0;
            int hash = (HashOne(key) + attempts_made * HashTwo(key)) % SIZE_OF_TABLE;

            while(attempts_made < SIZE_OF_TABLE) {

                //if the hit is marked as empty since start, we couldn't find the key to erase
                if(table[hash] == nullptr || table[hash]->status == 's') {
                    return false;
                }

                //if we get a hit remove it and return true
                if(table[hash]->key == key) {
                    table[hash]->status = 'r';
                    table[hash]->key = "";
                    table[hash]->data = nullptr;
                    num_entries--;
                    return true;
                }

                //if we haven't exited, we need to check the next possible hash.
                attempts_made++;
                hash = (HashOne(key) + attempts_made * HashTwo(key)) % SIZE_OF_TABLE;
            }

            std::cout << "exceeded max attempts in finding key to remove: " << key << std::endl;
            return false;
        }

        //TODO: clear function
        void Clear() {
            for(unsigned int i = 0; i < SIZE_OF_TABLE; i++) {
                if(table[i] != nullptr) {
                    /*
                    if(table[i]->data != nullptr) {
                        //delete table[i]->data;
                    }
                    table[i]->data = nullptr;
                    table[i]->key = "";
                    table[i]->status = 's';
                    */
                    if(table[i]->key != "") {
                        std::cout << "about to delete: " << table[i]->data << "(" << table[i]->key << ")" << std::endl;
                        delete table[i]->data;
                    }
                    table[i]->data = nullptr;
                    table[i]->key = "";
                    table[i]->status = 's';
                }

            }
            num_entries = 0;
        }

        bool isEmpty() { return num_entries = 0; }

        int size() { return SIZE_OF_TABLE; }

        int numEntries() { return num_entries; }
        //TODO: toVector function

        void copyToVector(std::vector<T*>& player_vec) {
            for(unsigned int i = 0; i < SIZE_OF_TABLE; i++) {
                if(table[i] != nullptr) {
                    player_vec.push_back(table[i]->data);
                }
            }
        }

        bucket<T>** getTable() { return table; }
    protected:

    private:
        unsigned int SIZE_OF_TABLE;
        unsigned int num_entries = 0;
        bucket<T>** table;
        const double max_load_factor = 0.5;

        int HashOne(std::string key) {
            unsigned int sum = 0;
            for(unsigned int i = 0; i < key.length(); i++) {
                sum += (int)(((int)(key.at(i))) * (pow(PRIME_ONE,key.length()-i-1))) % SIZE_OF_TABLE;

            }
            sum = sum % SIZE_OF_TABLE;
            return sum;
        }

        int HashTwo(std::string key) {
            unsigned int sum = 0;
            for(unsigned int i = 0; i < key.length(); i++) {
                sum += (int)((int(key.at(i))) * (pow(PRIME_TWO,key.length()-i-1))) % SIZE_OF_TABLE;

            }
            sum = sum % SIZE_OF_TABLE;
            return sum;
        }

        void Resize() {
            //std::cout << "called resize!" << std::endl;
            unsigned int old_size = SIZE_OF_TABLE;
            SIZE_OF_TABLE *= 2;
            if(SIZE_OF_TABLE == 0) {
                SIZE_OF_TABLE = 7;
            }
            //now we need to go to the next prime number
            while(!isPrime(SIZE_OF_TABLE)) {
                SIZE_OF_TABLE++;
            }
            //std::cout << "new size is " << SIZE_OF_TABLE << std::endl;

            HashTable<T>* new_table = new HashTable<T>(SIZE_OF_TABLE);
            for(unsigned int i = 0; i < old_size; i++) {
                if(table[i] != nullptr) {
                    new_table->Insert(table[i]->data, table[i]->key);
                }
            }
            delete [] table;
            table = new_table->getTable();
        }

        bool isPrime(unsigned int possible_prime) {
            for(int i = 2; i < sqrt(possible_prime); i++) {
                if(possible_prime % i == 0) {
                    return false;
                }
            }
            return true;
        }
};

#endif // HASHTABLE_H
