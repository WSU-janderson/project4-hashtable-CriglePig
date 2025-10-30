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
        HashTableBucket(std::string key, int value);

        void load(std::string key, int value);

        void makeESS();
        void makeNormal();
        void makeEAR();

        std::string getKey() const;
        int getValue() const;
        int& getValueRef();
        void setValue(int newValue);

        bool isEmpty() const;
        bool isEmptySinceStart() const;
        bool isEmptyAfterRemove() const;

        friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);
};
