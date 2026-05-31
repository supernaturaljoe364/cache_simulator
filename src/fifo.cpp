#include <iostream>
#include <optional>
#include <unordered_map>
#include <list>
#include "fifo.h"

void fifo::put(const std::string& key, const int& value){
  //add to list
  auto it = check.find(key);
  if(it != check.end()){
    //found! change the value of the existing key
    it->second->second = value;
    //now place the pair onto the front of the list
    return;
  }
  else{
    //not found!, push at the end of the list.
    if(fifoCache.size() == 3){
      //remove front
      fifoCache.pop_front();
      std::string firstElementIterator = fifoCache.front().first;
      check.erase(firstElementIterator);

      //then add a new to the back
      fifoCache.emplace_back(key, value);
      check[key] = fifoCache.end();
      return;
    }
    else{

      fifoCache.emplace_back(key, value);     
      check[key] = fifoCache.end();     //have list iterator placed at the end.H
      return;
    }
  }

}

std::optional<int> fifo::get(const std::string& key){
  //get value from key using unordered_map
  auto it = check.find(key);
  if(it != check.end()){
    //key found! extract value     
    return it->second->second;
  }
  else return std::nullopt;
}

void fifo::display() const{
  //display the cacheList
  for(const auto& pair : fifoCache){
    std::cout << pair.first << " " << pair.second << '\n';
  }
}

void fifo::remove(){
  //remove the first one
  if(fifoCache.empty()){
    std::cout << "List is empty!" << '\n';
  }
  else{

    fifoCache.pop_front();
    std::string firstElementIterator = fifoCache.front().first;
    check.erase(firstElementIterator);

    //removed element from both cacheList and map
    std::cout << "Element removed" << '\n';
  }
}

void fifo::remove(const std::string& key){
  //search and remove
  if(fifoCache.empty()){
    std::cout << "List is empty!" << '\n';
  }
  else{

    auto it = check.find(key);
    if(it != check.end()){
      //key found! now remove it
      fifoCache.erase(it->second);   //erase element so it->second
      check.erase(key);

      std::cout << "Element removed" << '\n';
    }
  }
}

