#include "cache.h"
#include <optional>
#include <iostream>


std::optional<int> Cache::get(const std::string& key){

  data.totalRequests++;
  auto it = cacheData.find(key);
  if(it != cacheData.end()){
    //key found!! now extract value using policy
    data.hits++;
    policy->onGet(key);
    return it->second;
  }
  else{
    //key not found!, add to cacheData map and

    data.misses++;
    return std::nullopt;
  }
}

void Cache::put(const std::string& key, int value){

  auto it = cacheData.find(key);
  if(it != cacheData.end()){
    //key found!, update value.

    it->second = value;
    policy->onPut(key);

    std::cout << "Value updated for existing Key" << '\n';
  }

  else{
      //input new key.
      if(cacheData.size() == capacity){
        std::cout << "Cache is full. An element is removed via Eviction Policy" << '\n';
        data.evictions++;
        std::string evictedIt = policy->evict();
        cacheData.erase(evictedIt);
      }
      cacheData[key] = value;
      policy->onPut(key);

      std::cout << "Key added to list." << '\n';
  }
}

void Cache::remove(){
    //eviction policy stuff
  if(cacheData.empty()){
    std::cout << "List is empty!" << '\n';
  }
  else{
    data.evictions++;
    std::string evictedIt = policy->evict();
    cacheData.erase(evictedIt);
    std::cout << "Evicted from Cache" << '\n';
  }
}

void Cache::remove(const std::string& key){
  data.totalRequests++;
  if(cacheData.empty()){
    std::cout << "List is empty" << '\n';
  }
  else{

    auto it = cacheData.find(key);
    if(it != cacheData.end()){
      //key found! remove
      data.hits++;
      policy->onRemove(key);
      cacheData.erase(key);
      std::cout << key << " erased from cache" << '\n';
    }
    else{
      //key not found!
      data.misses++;
    }
  }
}

void Cache::display() const{
  if(cacheData.empty()){
    std::cout << "List is empty" << '\n';
  }
  else{
    std::cout << "===CACHE===\n\n";
    for(const auto& data : cacheData){
      std::cout << data.first << " " << data.second << '\n';
    }
  }
}

void Cache::contains(const std::string& key) const{
  auto it = cacheData.find(key);
  if(it != cacheData.end()){
    //key found!
    std::cout << key << " is present in the list" << '\n';
  }
  else std::cout << key << " is not present in the list" << '\n';
}

void Cache::displayStats() const{
  std::cout << "===CACHE SIMULATOR STATS===" << '\n';
  std::cout << "Total Requests: "  << data.totalRequests << '\n';
  std::cout << "Hits: " << data.hits << '\n';
  std::cout << "Misses: " << data.misses << '\n';
  std::cout << "Evictions: " << data.evictions << '\n';
  
  if(data.totalRequests == 0){
    std::cout << "Hit Rate: 0.0%" << '\n';
    std::cout << "Miss Rate: 0.0%" << '\n';
  }
  else{
    std::cout << "Hit Rate: " << (static_cast<float>(data.hits) / (data.totalRequests)) * 100 << "%" << '\n';
    std::cout << "Miss Rate: " << (static_cast<float>(data.misses)/ (data.totalRequests)) * 100 << "%" <<'\n';
  }
  
}


