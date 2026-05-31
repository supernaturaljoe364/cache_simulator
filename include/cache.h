#pragma once
#include <unordered_map>
#include <memory>
#include "evict.h"


struct Data{
  size_t totalRequests = 0;   //size_t cannot be -ve.
  size_t hits = 0;
  size_t misses = 0;
  size_t evictions = 0;
  size_t hitMiss = 0;
};

class Cache{
  
  std::unordered_map<std::string, int> cacheData;
  std::unique_ptr<evictionPolicy> cachePolicy;

};


