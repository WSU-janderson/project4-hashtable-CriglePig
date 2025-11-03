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
        size_t m_capacity; // the amount of spaces for buckets in the table
        size_t m_size; // the amount of buckets in the table
        std::vector<HashTableBucket> table; // a vector that holds buckets
        std::vector<size_t> offsets; // pseudo-random probe offsets

        void resize();

        void generateOffsets(size_t seed = 0);

        [[nodiscard]] int hash(const std::string& key) const;

        [[nodiscard]] bool isNormalKeyFound(const std::string& key, size_t index) const;

    public:
        static constexpr size_t DEFAULT_INITIAL_CAPACITY = 8;

        HashTable(size_t initCapacity = DEFAULT_INITIAL_CAPACITY); // default constructor

        bool insert(const std::string& key, int value);

        bool remove(const std::string& key);

        [[nodiscard]] bool contains(const std::string& key) const;

        [[nodiscard]] std::optional<int> get(const std::string& key) const;

        [[nodiscard]] std::vector<std::string> keys() const;

        [[nodiscard]] double alpha() const;

        [[nodiscard]] size_t capacity() const;

        [[nodiscard]] size_t size() const;

        int& operator[](const std::string& key);

        friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);

        [[nodiscard]] std::string printMe() const;
};
