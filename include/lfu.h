#pragma once
#include "evict.h"
#include <string>
#include <unordered_map>
#include <list>

struct Node{
  std::string key;
  size_t freq;
};

class lfu : public evictionPolicy{
  
  std::unordered_map<int, std::list<Node>> freqMap;
  std::unordered_map<std::string, std::list<Node>::iterator> keyMap;
  size_t minFreq;


  public:
    void onPut(const std::string& key) override;
    void onGet(const std::string& key) override;
    void onRemove(const std::string& key) override;
    std::string evict() override;
};
