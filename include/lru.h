#pragma once
#include "evict.h"
#include <list>
#include <unordered_map>

class LRU : public evictionPolicy{
  std::list<std::string> order;
  std::unordered_map<std::string, std::list<std::string>::iterator> check;    //doesnt know about value

  public:
    void onPut(const std::string& key) override;
    void onGet(const std::string& key) override;
    void onRemove(const std::string& key) override;
    std::string evict() override;
};
