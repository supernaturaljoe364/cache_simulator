#include "lfu.h"
#include <climits>
#include <iostream>


void lfu::onPut(const std::string& key){
  //if it exists, increment frequency
  auto it = lfuMap.find(key);
  if(it != lfuMap.end()){
    lfuMap[key] += 1;
  }
  //if it doesn't exist, initialize freq to 1
  else lfuMap[key] = 1;

  return;
}

void lfu::onGet(const std::string& key){
  //accessed, so incremement frequency
  lfuMap[key] += 1;
  return;
} 

void lfu::onRemove(const std::string& key){
  //erase key from map
  auto it = lfuMap.find(key);
  if(it != lfuMap.end()){
    lfuMap.erase(key);
    std::cout << key << " removed from map" << '\n';
  }
  else{
    std::cout << "Key not found!" << '\n';
  }
}

std::string lfu::evict(){
  //remove the one with the lowest frequency
  //remove_if and remove cannot be used as they are designed for sequential containers
  //traverse through the map
  int minVal = INT_MAX;
  std::string minKey;
  for(const auto& kv : lfuMap){
    if(kv.second < minVal){
      minVal = kv.second;
      minKey = kv.first;
    }
  }

  //lowerst element foudn!, now remove taht element
  lfuMap.erase(minKey);
  std::cout << minKey << " erased via lfu" << '\n';
  return minKey;

}


