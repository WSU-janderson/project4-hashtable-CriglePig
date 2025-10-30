/*
 * HashTableBucket.h
 */

#include <string>

enum class BucketType {NORMAL, ESS, EAR};

class HashTableBucket {
    private:
        std::string key;
        int value;
        BucketType type;

    public:
        HashTableBucket();  // ESS by default
        HashTableBucket(std::string key, size_t value);

        void load(std::string key, size_t value);

        void makeESS();
        void makeNormal();
        void makeEAR();

        std::string getKey() const;
        size_t getValue() const;
        void setValue(size_t newValue);

        bool isEmpty() const;
        bool isEmptySinceStart() const;
        bool isEmptyAfterRemove() const;

        friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);
};
