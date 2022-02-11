#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    // TODO
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i] * PRIME_LIST[i];
    }
    sum = sum % tableSize;
    if (sum < 0) sum += tableSize;
    return sum;


}

void KeyedHashTable::ReHash()
{
    // TODO

    HashData* temp = table;
    int x = tableSize;
    tableSize = FindNearestLargerPrime(tableSize * 2);
    table = new HashData[tableSize];
    occupiedElementCount = 0;
    for (int i = 0; i < x; i++) {
        if (temp[i].key != "") {
            Insert(temp[i].key, temp[i].intArray);
        }
    }
    delete[] temp;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    // TODO
    int last = 0;
    for (int i = 0; i < PRIME_TABLE_COUNT; i++) {
        if (requestedCapacity < PRIME_LIST[i]) {
            last = PRIME_LIST[i];
            break;
        }
    }
    return last;
}

KeyedHashTable::KeyedHashTable()
{
    // TODO
    tableSize = 2;
    occupiedElementCount = 0;
    table = new HashData[tableSize];

}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    // TODO
    tableSize = FindNearestLargerPrime(requestedCapacity);
    occupiedElementCount = 0;
    table = new HashData[tableSize];
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    // TODO

    table = new HashData[other.tableSize];
    for (int i = 0; i < other.tableSize; i++) {
        table[i].intArray = other.table[i].intArray;
        table[i].key = other.table[i].key;

    }
    tableSize = other.tableSize;
    occupiedElementCount = other.occupiedElementCount;
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    // TODO
    if (this != &other) {
        delete[] table;

        this->table = new HashData[other.tableSize];
        for (int i = 0; i < other.tableSize; i++) {
            this->table[i].intArray = other.table[i].intArray;
            this->table[i].key = other.table[i].key;

        }
        this->tableSize = other.tableSize;
        this->occupiedElementCount = other.occupiedElementCount;
    }
    return *this;
}

KeyedHashTable::~KeyedHashTable()
{
    // TODO

    delete[] table;
    tableSize = 0;
    occupiedElementCount = 0;

}

bool KeyedHashTable::Insert(const std::string& key,
    const std::vector<int>& intArray)
{
    // TODO

    int h = Hash(key);
    int i = 0;
    bool x = false;
    while (table[h].key != "" && table[h].key != key) {
        h = ((i + 1) * (i + 1) - i * i + h) % tableSize;
        i++;
    }
    if (table[h].key == key) {

    }
    else {
        table[h].key = key;
        table[h].intArray = intArray;
        occupiedElementCount++;
        x = true;
    }

    if (occupiedElementCount * EXPAND_THRESHOLD >= tableSize) {
        ReHash();
    }


    return x;

}

bool KeyedHashTable::Remove(const std::string& key)
{
    // TODO
    int h = Hash(key);
    int i = 0;
    bool x = false;
    while (table[h].key != "" && table[h].key != key) {
        h = ((i + 1) * (i + 1) - i * i + h) % tableSize;
        i++;
    }
    if (table[h].key == key) {
        table[h].key = "";
        table[h].intArray.clear();
        HashData* temp = table;
        table = new HashData[tableSize];
        occupiedElementCount = 0;
        for (int i = 0; i < x; i++) {
            if (temp[i].key != "") {
                Insert(temp[i].key, temp[i].intArray);
            }
        }
        delete[] temp;
        x = true;
    }
    else {
        x = false;
    }

    return x;
}

void KeyedHashTable::ClearTable()
{
    // TODO
    for (int i = 0; i < tableSize; i++) {
        table[i].intArray.clear();
        table[i].key = "";
    }
    occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
    const std::string& key) const
{
    // TODO
    int h = Hash(key);
    int i = 0;
    bool x = false;
    while (table[h].key != "" && table[h].key != key) {
        h = ((i + 1) * (i + 1) - i * i + h) % tableSize;
        i++;
    }
    if (table[h].key == key) {
        valueOut = table[h].intArray;
        x = true;
    }
    else {
        x = false;
    }
    return x;
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if (occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for (int i = 0; i < tableSize; i++)
    {
        if (table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for (size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if ((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}