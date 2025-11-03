/*
 * HashTable.h
 */
#pragma once
#include <vector>
#include <optional>
#include <string>
#include "HashTableBucket.h"

class HashTable {
    private:
        size_t capacity; // the amount of spaces for buckets in the table
        size_t size; // the amount of buckets in the table
        std::vector<HashTableBucket> table; // a vector that holds buckets
        std::vector<size_t> offsets; // pseudo-random probe offsets

        void resize();

        void generateOffsets(size_t seed = 0);

        [[nodiscard]] int hash(const std::string& key) const;

        [[nodiscard]] bool isNormalKeyFound(const std::string& key, size_t index) const;

    public:
        HashTable(size_t initCapacity = 8); // default constructor

        bool insert(const std::string& key, int value);

        bool remove(const std::string& key);

        [[nodiscard]] bool contains(const std::string& key) const;

        [[nodiscard]] std::optional<int> get(const std::string& key) const;

        [[nodiscard]] std::vector<std::string> keys() const;

        [[nodiscard]] double alpha() const;

        [[nodiscard]] size_t getCapacity() const;

        [[nodiscard]] size_t getSize() const;

        int& operator[](const std::string& key);

        friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);

        [[nodiscard]] std::string printMe() const;
};
