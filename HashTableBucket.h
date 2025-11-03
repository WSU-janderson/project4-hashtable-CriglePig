/*
 * HashTableBucket.h
 */
#pragma once
#include <string>

enum class BucketType {NORMAL, ESS, EAR};

class HashTableBucket {
    private:
        std::string key = "SENTINEL_KEY_42"; // sentinel for ESS buckets
        int value = 0;
        BucketType type = BucketType::ESS;

    public:
        HashTableBucket();  // ESS by default
        HashTableBucket(std::string key, int value);

        void load(std::string key, int value);

        void makeESS();
        void makeNormal();
        void makeEAR();

        [[nodiscard]] std::string getKey() const;
        [[nodiscard]] int getValue() const;
        int& getValueRef();
        void setValue(int newValue);

        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] bool isEmptySinceStart() const;
        [[nodiscard]] bool isEmptyAfterRemove() const;

        friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);
};
