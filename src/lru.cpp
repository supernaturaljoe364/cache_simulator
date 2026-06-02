#pragma once
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <list>
#include "lru.h"
#include "cache.h"

//insert key, insert value
//key-value pair stored inside a container. (std::list)
Data data;

void LRU::onPut(const std::string& key){
  //only care about order.
  auto it = check.find(key);
  order.splice(order.begin(), order, it->second);
  
}

void LRU::onGet(const std::string& key){
  //retrieve key using std::unordered_map

  auto it = check.find(key);
  order.splice(order.begin(), order, it->second);
  return;
}

std::string LRU::evict(){
  //evict the least recently used. (the last one)
  //return the key at end()? (they cannot actually access the value. so let cacheData remove)
  auto lruString = order.back();
  order.pop_back();


  std::cout << "Evicted from LRU." << '\n';
  return lruString;
}
void LRU::onRemove(const std::string& key){
  //remove from the orderlist (the last one LRU)
  //
  auto it = check.find(key);
  
  if(it != check.end()){
    //key found! remove it
    order.erase(it->second);

    auto removeString = order.back();
    check.erase(removeString);
    std::cout << key << " removed from list (LRU)." << '\n';
  }
}
