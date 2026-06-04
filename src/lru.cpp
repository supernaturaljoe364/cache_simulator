#include <iostream>
#include <unordered_map>
#include <list>
#include "lru.h"

//insert key, insert value
//key-value pair stored inside a container. (std::list)

void LRU::onPut(const std::string& key){
  //only care about order.
  auto it = check.find(key);
  if(it == check.end()){
    //key not found! insert new key!

    order.push_front(key);
    check[key] = order.begin();
    std::cout << key << " inserted into the list(LRU)" << '\n';
  } 
  else{
    order.splice(order.begin(), order, it->second);
    check[key] = order.begin();
    std::cout << key << " order updated. (LRU)" << '\n';
  }
  return;
}

void LRU::onGet(const std::string& key){
  //retrieve key using std::unordered_map

  auto it = check.find(key);
  order.splice(order.begin(), order, it->second);
  check[key] = order.begin();
}

std::string LRU::evict(){
  //evict the least recently used. (the last one)
  //return the key at end()? (they cannot actually access the value. so let cacheData remove)
  auto lruString = order.back();
  check.erase(lruString);
  order.pop_back();
  std::cout << "Evicted from LRU." << '\n';
  return lruString;
}
void LRU::onRemove(const std::string& key){
  
    auto it = check.find(key);

    if(it == check.end())
        return;

    order.erase(it->second);

    check.erase(it);
}
