#pragma once
#include "evict.h"
#include <string>
#include <unordered_map>

class lfu : public evictionPolicy{
  
  std::unordered_map<std::string, int> lfuMap;

  public:
    void onPut(const std::string& key) override;
    void onGet(const std::string& key) override;
    void onRemove(const std::string& key) override;
    std::string evict() override;
};
