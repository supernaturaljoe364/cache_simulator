#pragma once
#include <optional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <list>

//insert key, insert value
//key-value pair stored inside a container. (std::list)

struct Data{
  size_t totalRequests = 0;   //size_t cannot be -ve.
  size_t hits = 0;
  size_t misses = 0;
  size_t evictions = 0;
  size_t hitMiss = 0;
};

template<typename Key, typename Value>
class lruCache{
  std::list<std::pair<Key, Value>> cacheList;
  std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> check;

  size_t capacity;
  Data data;

  public:
    lruCache(const int& size) : capacity(size) {};

    void put(const Key& key, const Value& value){
      
      //adding elements

      data.totalRequests++;
      auto it = check.find(key);

      if(it != check.end()){
        //found! so you dereference the iterator
        data.hits++;
        data.hitMiss++;
        it->second->second = value;
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return;
      }

      else{
        if(cacheList.size() == capacity){
          //too big, remove the last element from the list and remove corresponding element from map
          data.evictions++;
          Key lastKey = cacheList.back().first;       //end() is the iterator, back is thelement
          check.erase(lastKey);
          cacheList.pop_back();

          //last element removed, now enter the new element
          cacheList.emplace_front(key, value);
          check[key] = cacheList.begin();
          return;
        }
        else{
          //not found!, so you insert both Key-value pair, where do you insert it?(front)
          cacheList.emplace_front(key, value);
          check[key] = cacheList.begin();
          return;
        }
      }

    }


    std::optional<Value> get(const Key& key){
      //retrieve key using std::unordered_map

       data.totalRequests++; //increment counter (number of times i've accesed)
    //if the cacheList is empty.
      auto it = check.find(key);
      if(it != check.end()){
        //return Value (cache hit!)
        data.hits++;
        data.hitMiss++;
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return it->second->second;

      }
      else {
        data.misses++;
        data.hitMiss++;
        return std::nullopt;
      }
    }

    void display() const{

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
      data.totalRequests++;
      if(cacheList.empty()){
        std::cout << "List is empty!" << '\n';
        return;
      }
      else{
      //remove the LRU cache (the last) pop_back()
        auto last = cacheList.back().first;   //access the alst element (pair), and access the key
        cacheList.pop_back();
        check.erase(last);    //remove key from unordered_map

        std::cout << "LRU task removed." << '\n';
      }
    }

    void remove(const Key& key){
      data.totalRequests++;
      if(cacheList.empty()){
        std::cout << "List is empty!" << '\n';
        return;
      }
      else{
        
        auto it = check.find(key);

        if(it != check.end()){
          //key found! now remove it
          data.hits++;
          data.hitMiss++;
          cacheList.erase(it->second);
          check.erase(it);
          std::cout << "LRU task removed." << '\n';
        }
        else{
          data.misses++;
          data.hitMiss++;
          std::cout << "Key not found!" << '\n';
        }

      }

    }

    bool contains(const Key& key){
      data.totalRequests++;
      return check.find(key) != check.end();
    }

    void displayStats() const {
      std::cout << "===LRU CACHE STATS===" << '\n';
      std::cout << "Total Requests: "  << data.totalRequests << '\n';
      std::cout << "Hits: " << data.hits << '\n';
      std::cout << "Misses: " << data.misses << '\n';
      std::cout << "Evictions: " << data.evictions << '\n';
      std::cout << "Hit Rate: " << (static_cast<float>(data.hits) / (data.hitMiss)) * 100 << "%" << '\n';
      std::cout << "Miss Rate: " << (static_cast<float>(data.misses)/ (data.hitMiss)) * 100 << "%" <<'\n';

      //technically don't need a variable for miss if calculatign hit;
    }
};
