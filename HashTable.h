/*
 * HashTable.h
 */

#include "HashTableBucket.h"

class HashTable {
    private:
        size_t capacity; // the amount of spaces for buckets in the table
        size_t size; // the amount of buckets in the table
        std::vector<HashTableBucket> table; // a vector that holds buckets

        void resize();

        int hash(const std::string& key) const;

        bool isNormalKeyFound(const std::string& key, size_t index) const;

    public:
        HashTable(size_t initCapacity = 8); // default constructor

        bool insert(const std::string& key, int value);

        bool remove(const std::string& key);

        bool contains(const std::string& key) const;

        std::optional<int> get(const std::string& key) const;

        int& operator[](const std::string& key);

        std::vector<std::string> keys() const;

        double alpha() const;

        size_t getCapacity() const;

        size_t getSize() const;
};
