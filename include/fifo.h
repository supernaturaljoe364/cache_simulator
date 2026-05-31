#pragma once
#include <string>
#include <unordered_map>
#include <list>
#include <optional>     //either return type of std::string or other
class fifo{
  //cannot use std::queue since it doesn't have any sorting-based operations
  std::list<std::pair<std::string, int>> fifoCache;
  std::unordered_map<std::string, std::list<std::pair<std::string, int>>::iterator> check;

  public:
    void put(const std::string& key, const int& value);
    void display() const;
    std::optional<int> get(const std::string& key);
    void displayStats() const; 
    bool contains(const std::string& key);
    void remove(const std::string& key);
    void remove();
};
