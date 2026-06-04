# Cache Simulator

A cache simulator written in modern C++20 that supports multiple eviction policies through a polymorphic policy-based architecture.

## Features

* FIFO (First-In First-Out) eviction policy
* LRU (Least Recently Used) eviction policy
* LFU (Least Frequently Used) eviction policy
* Configurable cache capacity
* Cache hit/miss statistics
* Eviction tracking
* File-based workload processing
* Runtime benchmarking using `std::chrono`

## Architecture

The project separates cache storage from eviction logic.

<pre>
Cache
  |
  +--> EvictionPolicy
          |
          +--> FIFO
          +--> LRU
          +--> LFU  
</pre>


### Cache

Responsible for:

* Key-value storage
* Cache capacity management
* Statistics collection
* Request processing

### EvictionPolicy

Abstract base class defining the eviction interface:

* `onGet()`
* `onPut()`
* `onRemove()`
* `evict()`

Implemented policies:

* FIFO
* LRU
* LFU

This allows new eviction strategies to be added without modifying the cache implementation.

## Technologies Used

* C++20
* STL Containers
* `std::unordered_map`
* `std::list`
* Smart Pointers (`std::unique_ptr`)
* Runtime Polymorphism
* `std::chrono`

### Build

```
cmake -B build
cmake --build build
```

### Run

```
./cache_sim
```

## Sample Benchmark Output


![example-(2).png](jb-image:img_1780581780703_519176a518f87)

The screenshot below shows the results of a benchmark run using a workload of 10,000 commands from `sample.txt`. The simulator records request count, cache hits, misses, evictions, and overall hit/miss rates.

## Concepts Practiced

* Object-Oriented Design
* Inheritance and Interfaces
* Runtime Polymorphism
* Smart Pointer Ownership
* Hash Tables
* Iterator-Based Data Structures
* Cache Eviction Algorithms
* Basic Performance Benchmarking



