#include "fifo.h"

void fifo::onPut(const std::string& key){
  //add key onto the queue<std::String>

  auto it = queueMap.find(key);
  if(it == queueMap.end()){
    //key not found! add to deque
    queue.emplace_back(key);
    //map the key to last (since push_back is done)
    queueMap[key] = queue.end();

  }
  else{
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
  }
}

std::string fifo::evict(){
  //remove the first element
  
  std::string firstElement = queue.front();
  queue.pop_front();
  queueMap.erase(firstElement);

  return firstElement;
}



