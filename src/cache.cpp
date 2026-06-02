#include "cache.h"
#include <optional>
#include <iostream>

std::optional<int> Cache::get(const std::string& key){
  auto it = cacheData.find(key);
  if(it != cacheData.end()){
    //key found!! now extract value using policy

    policy->onGet(key);
    return it->second;
  }
  else{
    //key not found!, add to cacheData map and
    return std::nullopt;
  }
}

void Cache::put(const std::string& key, const int& value){
  if(cacheData.size() == capacity){
    //eviction policy stuff
    std::string evictedValue = policy->evict();
    cacheData.erase(evictedValue);
    //now add new key, value pair.
    cacheData[key] = value;
    policy->onPut(key);
    
  }
  else{
    
    auto it = cacheData.find(key);
    if(it != cacheData.end()){
      //key found!, update value.

      it->second = value;
      policy->onPut(key);

      std::cout << "Value updated for existing Key" << '\n';
    }
    else{
      //input new key.
      cacheData[key] = value;
      policy->onPut(key);

      std::cout << "Key added to list." << '\n';
    }
  }

}

void Cache::remove(){
    //eviction policy stuff

  if(cacheData.empty()){
    std::cout << "List is empty!" << '\n';
  }
  else{
    std::string evictedIt = policy->evict();
    cacheData.erase(evictedIt);
    std::cout << "Evicted from Cache" << '\n';
  }
}

void Cache::remove(const std::string& key){
  if(cacheData.empty()){
    std::cout << "List is empty" << '\n';
  }
  else{
    cacheData.erase(key);
    std::cout << key << " erased from cache" << '\n';
    policy->onRemove(key);
  }
}
