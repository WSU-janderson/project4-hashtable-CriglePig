/*
 * HashTableBucket.cpp
 */

#include "HashTableBucket.h"
#include <iostream>
#include <string>
#include <utility>

/**
* The default constructor can simply set the bucket type to ESS.
 *
*/
HashTableBucket::HashTableBucket() {
    makeESS();
}

/**
* A parameterized constructor could initialize the key and value, as
* well as set the bucket type to NORMAL.
*/
HashTableBucket::HashTableBucket(std::string key, int value) {
    load(std::move(key), value);
}

/**
* A load method could load the key-value pair into the bucket, which
* should then also mark the bucket as NORMAL.
*/
void HashTableBucket::load(std::string key, int value) {
    this->key = std::move(key);
    this->value = value;
    makeNormal();
}

void HashTableBucket::makeESS() {
    type = BucketType::ESS;
}

void HashTableBucket::makeNormal() {
    type = BucketType::NORMAL;
}

void HashTableBucket::makeEAR() {
    type = BucketType::EAR;
}

std::string HashTableBucket::getKey() const {
    return key;
}

int HashTableBucket::getValue() const {
    return value;
}

int& HashTableBucket::getValueRef() {
    return value;
}

void HashTableBucket::setValue(const int newValue) {
    value = newValue;
}

bool HashTableBucket::isEmpty() const {
    return type == BucketType::ESS || type == BucketType::EAR;
}

bool HashTableBucket::isEmptySinceStart() const {
    return type == BucketType::ESS;
}

bool HashTableBucket::isEmptyAfterRemove() const {
    return type == BucketType::EAR;
}

std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    if (bucket.type == BucketType::NORMAL) {
        os << "<" << bucket.key << ", " << bucket.value << ">";
    } else if (bucket.type == BucketType::EAR) {
        os << "<EAR>";
    } else {
        os << "<ESS>";
    }
    return os;
}