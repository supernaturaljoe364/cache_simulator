#pragma once
#include <optional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <list>

//insert key, insert value
//key-value pair stored inside a container. (std::list)

class data{
  std::string key;
  int value;

  public:
    data(const std::string& key_, const int& value_) : key(key_), value(value_) {}
};

template<typename Key, typename Value>
class lruCache{
  std::list<std::pair<Key, Value>> cacheList;
  std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> check;

  public:
    void put(const Key& key, const Value& value){

      if(cacheList.size() == 3){
        //remove the last element(rather, replace the last element)
        
        auto sl = std::next(cacheList.begin(), 2);

        cacheList.pop_back();   //remove last element
        cacheList.emplace_back(key, value);
        cacheList.splice(cacheList.begin(), cacheList, sl);           

      }
      else{
        auto it = check.find(key);

        if(it != check.end()){
          //found! so you dereference the iterator
          it->second->second = value;
          cacheList.splice(cacheList.begin(), cacheList, it->second);
        }

        else{
          //not found!, so you insert both Key-value pair, where do you insert it? (end)
          cacheList.emplace_front(key, value);
          check[key] = cacheList.begin();
          }
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
      std::cout << "LRU cache" << '\n';
      for(auto data : cacheList){
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
