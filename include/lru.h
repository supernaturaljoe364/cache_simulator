#pragma once
#include <optional>
#include <unordered_map>
#include <utility>
#include <list>
#include <cctype>
#include <iostream>

//insert key, insert value
//key-value pair stored inside a container. (std::list)

struct Data{
  size_t totalRequests = 0;   //size_t cannot be -ve.
  size_t hits = 0;
  size_t misses = 0;
  size_t evictions = 0;
  size_t hitMiss = 0;
};

class LRU{
  std::list<std::pair<std::string, int>> cacheList;
  std::unordered_map<std::string, std::list<std::pair<std::string, int>>::iterator> check;

  size_t capacity;
  Data data;

  public:
    void put(const std::string& key, const int& value);
    std::optional<int> get(const std::string& key);
    void display() const;
    void remove();
    void remove(const std::string& key);
    bool contains(const std::string& key);
    void displayStats() const; 
};
