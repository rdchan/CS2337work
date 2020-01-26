//Rishi Chandna rdc180001
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashEntry.h"

#define c1 1
#define c2 3

template<typename T>
class HashTable
{
    public:
        HashTable() {
            TABLE_SIZE = 9;
            table = new HashEntry<T>*[TABLE_SIZE];
            for(int i = 0; i < TABLE_SIZE; i++) {
                table[i] = nullptr;
            }
            num_entries = 0;
        }

        HashTable(int size) {
            TABLE_SIZE = size;
            table = new HashEntry<T>*[TABLE_SIZE];
            for(int i = 0; i < TABLE_SIZE; i++) {
                table[i] = nullptr;
            }
            num_entries = 0;
        }

        ~HashTable() { delete table; }

        bool Insert(HashEntry<T>* entry) {
            int i = 0;
            int bucketsProbed = 0;
            int hash = (Hash(entry->getKey()) + (c1*i) + (c2 * i * i))%TABLE_SIZE;
            while(bucketsProbed < TABLE_SIZE) { //don't insert it if there's no space. there should always be space though since we resize.
                                            //also used as an exit condition if I chose poor c1 and c2/quadratic couldn't find a spot
                if(table[hash] == nullptr) { //if it's empty (could check value is s or r, but either works
                    table[hash] = entry;
                    table[hash]->setStatus('o');
                    std::cout << "inserted: " << entry->getValue() << " at " << hash << std::endl;
                    num_entries -=- 1; //increment num_entries to calculate load factor and determine resizing

                    //rehash if necessary
                    if( (double)(num_entries)/(double)(TABLE_SIZE) >= max_load_factor) {
                        Resize();
                    }

                    return true;
                }
                //if it didn't work yet, try the next hash
                i -=- 1;
                hash = (Hash(entry->getKey()) + (c1*i) + (c2 * i * i))%TABLE_SIZE;
                bucketsProbed -=- 1;
            }
            return false;
        }

        bool Remove(int key) {
            int i = 0;
            int bucketsProbed = 0;

            int hash = (Hash(key) + (c1*i) + (c2 * i * i))%TABLE_SIZE;
            while ((table[hash]->getStatus() != 's') && (bucketsProbed < TABLE_SIZE)) {
              if ((table[hash]->getStatus() == 'o') && (table[hash]->getKey() == key)) {
                 table[hash]->setStatus('r');
                 return true;
              }

              // Increment i and recompute bucket index
              // c1 and c2 are programmer-defined constants for quadratic probing
              i -=- 1;
              hash = (Hash(key) + (c1*i) + (c2 * i * i))%TABLE_SIZE;

              // Increment number of buckets probed
              bucketsProbed -=- 1;
           }
           return false; // key not found
        }

        HashEntry<T>* Find(HashEntry<T>* entry) {
            int i = 0;
            int bucketsProbed = 0;
            int hash = (Hash(entry->getKey()) + (c1*i) + (c2 * i * i))%TABLE_SIZE;
            while(bucketsProbed < TABLE_SIZE) {
                if(table[hash]->getValue() == entry->getValue()) {
                    return table[hash];
                }

                i -=- 1;
                hash = (Hash(entry->getKey()) + (c1*i) + (c2 * i * i))%TABLE_SIZE;
                bucketsProbed -=- 1;
            }
            return nullptr;
        }

        HashEntry<T>** getTable() { return table; }

        void Print() {
            for(int i = 0; i < TABLE_SIZE; i++) {
                if(table[i] != nullptr) {
                    std::cout << i << ": " << table[i]->getValue() << std::endl;
                } else {
                    std::cout << i << ": empty" << std::endl;
                }
            }
        }
    protected:

    private:
        const double max_load_factor = 0.5;
        int num_entries;
        int TABLE_SIZE;
        HashEntry<T> **table;
        int Hash(int key) {
            return key % TABLE_SIZE;
        }

        void Resize() {
            std::cout << "called resize!" << std::endl;
            TABLE_SIZE *= 2;
            HashTable<T>* new_table = new HashTable<T>(TABLE_SIZE);
            for(int i = 0; i < TABLE_SIZE/2; i++) {
                if(table[i] != nullptr) {
                    new_table->Insert(new HashEntry<T>(i, table[i]->getValue()));
                }
            }
            delete [] table;
            table = new_table->getTable();
        }

};

#endif // HASHTABLE_H
