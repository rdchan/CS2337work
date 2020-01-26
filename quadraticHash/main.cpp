//Rishi Chandna rdc180001
#include <iostream>
#include "HashEntry.h"
#include "HashTable.h"

using namespace std;

int main()
{
    HashTable<int>* table = new HashTable<int>();
    /*for(int i = 1; i < 5; i++) {
        table->Insert(new HashEntry<int>(100+(i%7)*100+i*i, 100+(i%7)*100+i));
    }*/
    table->Insert(new HashEntry<int>(0, 60));
    table->Insert(new HashEntry<int>(2, 110));
    table->Insert(new HashEntry<int>(4, 364));
    table->Insert(new HashEntry<int>(5, 75));
    table->Insert(new HashEntry<int>(6, 66));
    table->Insert(new HashEntry<int>(92, 49));

    std::cout << "****" << std::endl;
    table->Print();
    delete table;
}
