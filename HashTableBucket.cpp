/* Filename: HashTableBucket.cpp
 * Author: Crystal Daniel
 * Project: Project 4 - Hash Table
 * Due Date: 11/03/2025
 * Program Description: This file implements the HashTableBucket class, which represents
 * a single bucket in the hash table. Each bucket stores a key-value pair and has a type
 * indicating whether it is empty-since-start (ESS), empty-after-remove (EAR), or NORMAL.
 * The class provides constructors, accessors, mutators, and methods to manage the bucket type.
 */

#include "HashTableBucket.h"
#include <iostream>
#include <string>
#include <utility>

/* Purpose: Default constructor for HashTableBucket.
 * Behavior:
 *    Initializes the bucket type as ESS (empty-since-start), indicating
 *    the bucket has never held a key-value pair.
 */
HashTableBucket::HashTableBucket() {
    makeESS();
}

/* Purpose: Parameterized constructor for HashTableBucket.
 * Parameters:
 *    key – string key to store in the bucket
 *    value – integer value to associate with key
 * Behavior:
 *    Loads the key-value pair into the bucket and marks it as NORMAL.
 */
HashTableBucket::HashTableBucket(std::string key, const int value) {
    load(std::move(key), value);
}

/* Purpose: Loads a key-value pair into the bucket.
 * Parameters:
 *    key – string key to store
 *    value – integer value to associate
 * Behavior:
 *    Updates the bucket's key and value, then marks it as NORMAL.
 */
void HashTableBucket::load(std::string newKey, const int newValue) {
    key = std::move(newKey);
    value = newValue;
    makeNormal();
}

/* Purpose: Marks the bucket as ESS (empty-since-start).
 */
void HashTableBucket::makeESS() {
    type = BucketType::ESS;
}

/* Purpose: Marks the bucket as NORMAL (active key-value pair).
 */
void HashTableBucket::makeNormal() {
    type = BucketType::NORMAL;
}

/* Purpose: Marks the bucket as EAR (empty-after-remove).
 */
void HashTableBucket::makeEAR() {
    type = BucketType::EAR;
}

/* Purpose: Retrieves the key stored in the bucket.
 * Returns:
 *    string – the bucket's key
 */
std::string HashTableBucket::getKey() const {
    return key;
}

/* Purpose: Retrieves the value stored in the bucket.
 * Returns:
 *    int – the bucket's value
 */
int HashTableBucket::getValue() const {
    return value;
}

/* Purpose: Provides a reference to the value stored in the bucket.
 * Returns:
 *    int& – reference to the bucket's value
 * Behavior:
 *    Allows modification of the bucket's value directly.
 */
int& HashTableBucket::getValueRef() {
    return value;
}

/* Purpose: Updates the bucket's value.
 * Parameters:
 *    newValue – integer to store in the bucket
 */
void HashTableBucket::setValue(const int newValue) {
    value = newValue;
}

/* Purpose: Checks if the bucket is considered empty.
 * Returns:
 *    true if the bucket type is ESS or EAR, false otherwise
 */
bool HashTableBucket::isEmpty() const {
    return type == BucketType::ESS || type == BucketType::EAR;
}

/* Purpose: Checks if the bucket is empty since start.
 * Returns:
 *    true if bucket type is ESS, false otherwise
 */
bool HashTableBucket::isEmptySinceStart() const {
    return type == BucketType::ESS;
}

/* Purpose: Checks if the bucket is empty after removal.
 * Returns:
 *    true if bucket type is EAR, false otherwise
 */
bool HashTableBucket::isEmptyAfterRemove() const {
    return type == BucketType::EAR;
}

/* Purpose: Prints the bucket to an output stream.
 * Parameters:
 *    os – output stream (e.g., cout)
 *    bucket – HashTableBucket to print
 * Returns:
 *    Reference to the output stream
 * Behavior:
 *    Prints "<key, value>" if NORMAL, "<EAR>" if empty-after-remove,
 *    and "<ESS>" if empty-since-start.
 */
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