#pragma once
#include <unordered_map>
#include <memory>
#include "evict.h"
#include <optional>
struct Data{
  size_t totalRequests = 0;   //size_t cannot be -ve.
  size_t hits = 0;
  size_t misses = 0;
  size_t evictions = 0;
};

class Cache{
  size_t capacity;

  std::unordered_map<std::string, int> cacheData;
  std::unique_ptr<evictionPolicy> policy;

  Data data;
  public:
  Cache(size_t capacity_, std::unique_ptr<evictionPolicy> policy_)  :
    capacity(capacity_), policy(std::move(policy_)) {};



  std::optional<int> get(const std::string& key);
  void put(const std::string& key,  int value);
  void remove();
  void remove(const std::string& key);
  void display() const;
  void contains(const std::string& key) const;
  void displayStats() const;
};



