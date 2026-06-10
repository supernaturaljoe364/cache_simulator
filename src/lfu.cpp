#include "lfu.h"
#include <iterator>
#include <climits>


void lfu::onPut(const std::string& key){
//insert key. chech if it exxists
  auto it = keyMap.find(key);
  if(it != keyMap.end()){
    onGet(key);      
  }
  else{
      //not found! 
      minFreq = 1;
      Node node;
      node.key = key;
      node.freq = minFreq;

      freqMap[minFreq].push_front(node);

      keyMap[key] = freqMap[minFreq].begin();
  }
}

void lfu::onGet(const std::string& key){
  //accessed, so incremement frequency
  auto it = keyMap.find(key);
  if(it != keyMap.end()){

    auto listIter = it->second;
    int curFreq = listIter->freq;

    Node node = *(it->second);
    freqMap[curFreq].erase(listIter);

    if(freqMap[curFreq].empty()){
      freqMap.erase(curFreq);

      if(minFreq == curFreq){
        ++minFreq;
      }
    }

    node.freq++;
    freqMap[node.freq].push_front(node);
    keyMap[key] = freqMap[node.freq].begin();
  } 
}
void lfu::onRemove(const std::string& key){
  //erase key from map
  auto it = keyMap.find(key);
  if(it != keyMap.end()){
    
    //remove element from both freqMap and keyMap
    //remoev from freqMap via freq 

    auto removeFreq = it->second->freq;

    keyMap.erase(key);

    freqMap[removeFreq].erase(it->second);
    //remove from keyMap via key
  }
}

std::string lfu::evict(){

  //return the key from keyMap
  //remove it from both freqMap and keyMap (the LFU)
  
  //remove the element with LFU via minFreq and if tie, remove via LRU (last element of DLL)
  if(freqMap[minFreq].size() == 0){
    minFreq++;
  }

  auto lastElement = std::prev(freqMap[minFreq].end());
  std::string lastKey = lastElement->key;
  keyMap.erase(lastKey);
  freqMap[minFreq].erase(lastElement);

  return lastKey;
}


