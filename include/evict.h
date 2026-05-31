#pragma once
#include <string>
#include <optional>
#include <unordered_map>
#include <list>
#include <utility>

class evictionPolicy{
//intialize constructor heree (capacity)
  public:
    std::list<std::pair<std::string, int>> cacheList;
    std::unordered_map<std::string, std::list<std::pair<std::string, int>>::iterator> check;

    virtual void put(const std::string& key, const int& value) = 0;
    virtual std::optional<int> get(const std::string& key) = 0;
    virtual void remove() = 0;
};
