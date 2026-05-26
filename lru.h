#pragma once
#include <optional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <list>

//insert key, insert value
//key-value pair stored inside a container. (std::list)


template<typename Key, typename Value>
class lruCache{
  std::list<std::pair<Key, Value>> cacheList;
  std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> check;

  size_t capacity;
  public:


    lruCache(const int& size) : capacity(size) {};
    void put(const Key& key, const Value& value){


      if(cacheList.size() == capacity){
        //too big, remove the last element from the list and remove corresponding element from map
        
        Key lastKey = cacheList.back().first;       //end() is the iterator, back is thelement
        check.erase(lastKey);
        cacheList.pop_back();

        //last element removed, now enter the new element
        cacheList.emplace_front(key, value);
        check[key] = cacheList.begin();
        return;
      }

      auto it = check.find(key);

      if(it != check.end()){
        //found! so you dereference the iterator
        it->second->second = value;
        cacheList.splice(cacheList.begin(), cacheList, it->second);
      }

      else{
        //not found!, so you insert both Key-value pair, where do you insert it?(front)
        cacheList.emplace_front(key, value);
        check[key] = cacheList.begin();
        }
    }


    std::optional<Value> get(const Key& key){
      //retrieve key using std::unordered_map

    //if the cacheList is empty.
      auto it = check.find(key);
      if(it != check.end()){
        //found! return Value
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return it->second->second;

      }
      else {
        return std::nullopt;
      }
    }

    void display(){

      if(cacheList.empty()){
        std::cout << "List is empty!" << '\n';
      }
      else{
          std::cout << "===CACHE STORE===" << '\n';
          for(auto data : cacheList)
            std::cout << data.first << " " << data.second << '\n';
      }

    }

    void remove(){

      if(cacheList.empty()){
        std::cout << "List is empty!" << '\n';
        return;
      }
      else{
      //remove the LRU cache (the last) pop_back()
        auto last = cacheList.back().first;   //access the alst element (pair), and access the key
        check.erase(last);    //remove key from unordered_map

        cacheList.pop_back();
        std::cout << "LRU task removed." << '\n';
      }
    }
};
