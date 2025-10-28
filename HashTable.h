/**
 * HashTable.h
 */

class HashTable {
    public:
    HashTable(size_t initCapacity); // default constructor
    bool insert(std::string key, size_t value);

    bool remove(std::string key);

    bool contains(const std::string &key) const;

    std::optional<int> get(const std::string &key) const;

    int &operator[](const std::string &key);

    std::vector<std::string> keys() const;

    double alpha() const;

    size_t capacity() const;

    size_t size() const;

private:
};