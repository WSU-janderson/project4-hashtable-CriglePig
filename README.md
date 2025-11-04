[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

---
# Time Complexity Analysis

## insert()
The `insert()` function first checks for duplicates with `contains()`, then may `resize()` the table and generate new
probe offsets, each potentially **O(n)**, and finally probes for an empty bucket, averaging **O(1)**. Overall,
`insert()` has **O(1)** average time under normal load factors but **O(n)** worst-case time due to resizing, offset
generation, or full-table probing.

## remove()
The `remove()` function computes the hash of the key and probes the table using the pseudo-random offsets until it
finds the key or hits an empty-since-start bucket. Each probe is **O(1)**, so on average `remove()` is **O(1)**. In
the worst case, it may need to examine every bucket, giving **O(n)** worst-case time.

## contains()
The `contains()` function calculates the hash of the key and probes the table using pseudo-random offsets until the
key is found or an empty-since-start bucket is reached. Each probe is **O(1)**, so `contains()` has **O(1)** average
time. In the worst case, it could examine all buckets, resulting in **O(n)** worst-case time.

## get()
The `get()` function works similarly to `contains()`, probing the table until it finds the key or an empty-since-start
bucket. Average-case time is **O(1)**, but in the worst case it may need to check every bucket, giving **O(n)**.

## operator\[]()
The bracket operator `operator[]()` also probes for the key using pseudo-random offsets and returns a reference to the
value. Average-case time is **O(1)**, but worst-case time is **O(n)** if the key is at the end of the probe sequence
or not present.