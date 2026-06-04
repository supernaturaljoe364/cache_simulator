#include "fifo.h"
#include <iostream>

void fifo::onPut(const std::string& key){
  //add key onto the queue<std::String>

  auto it = queueMap.find(key);
  if(it == queueMap.end()){
    //key not found! add to deque
    queue.emplace_back(key);
    //map the key to last (since push_back is done)
    queueMap[key] = queue.end();
    std::cout << key << " pushed onto queue (FIFO)" << '\n';

  }
  else{
      std::cout << "Element already exists!" << '\n';
  }
  
}

void fifo::onGet(const std::string& key){
  //do nothing. 
}

void fifo::onRemove(const std::string& key){
  //remove means 
  auto it = queueMap.find(key);
  if(it != queueMap.end()){
    //key found! 
    queue.erase(it->second);
    queueMap.erase(it);
    std::cout << key << " removed from the queue." << '\n';
  }
}

std::string fifo::evict(){
  //remove the first element
  
  std::string firstElement = queue.front();
  queue.pop_front();
  queueMap.erase(queueMap.begin());

  std::cout << firstElement << "(1st) removed fromt queue(FIFO)" << '\n';
  return firstElement;
}



