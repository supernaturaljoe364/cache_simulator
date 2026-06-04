# Cache Simulator

Cache Simulator written in Modern C++20. 
Stores key-value pairs with a configurable capacity and supports multiple eviction policies (LRU, LFU, FIFO) through a polymorphic policy architecture.

Built to compare eviction strategy performance under artificial workloads.

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
## Commands

```
PUT apple 10
GET apple
REMOVE banana
REMOVE               ----> Removes element via eviction policy
CONTAINS banana
DISPLAY
RUNTEST              ----> RUNS 10000 commands from sample.txt (see screenshow below)
STATS

```
## Sample Benchmark Output


<img width="427" height="182" alt="sample_output" src="https://github.com/user-attachments/assets/40a8240a-26f7-4282-b939-01fb35f2ec29" />


The screenshot below shows the results of a benchmark run adopting LRU policy, using a workload of 10,000 commands from `sample.txt`. The simulator records request count, cache hits, misses, evictions, and overall hit/miss rates.

## Concepts Practiced

* Object-Oriented Design
* Inheritance and Interfaces
* Runtime Polymorphism
* Smart Pointer Ownership
* Hash Tables
* Iterator-Based Data Structures
* Cache Eviction Algorithms
* Basic Performance Benchmarking



