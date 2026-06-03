#include <iostream>
#include <sstream>
#include <functional>
#include <limits>
#include "evict.h"
#include "cache.h"
#include "fifo.h"
#include "lru.h"
#include "lfu.h"
#include <cctype>
#include <memory>
int main(){

  int capacity;
  std::string evict;
  std::unique_ptr<evictionPolicy> policy;
  std::cout << "Enter cache capacity: ";
  std::cin >> capacity;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
  std::cout << "\n1. LRU\n2. FIFO\n3. LFU\nEnter Eviction Policy: ";
  std::cin >> evict;

  for(auto& ch : evict){
    ch = std::tolower(static_cast<unsigned char>(ch));
  }

  if(evict == "lru"){
    policy = std::make_unique<LRU>();
  }
  else if(evict == "fifo"){
    policy = std::make_unique<fifo>();
  }
  else if(evict == "lfu"){
    policy = std::make_unique<lfu>();
  }
  else{
    std::cout << "Invalid policy" << '\n';
    return 1;
  }


  Cache cache(capacity, std::move(policy));
  std::string key;
  int value;

  std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands = {
    {
      "GET", [&](std::istringstream& iss){
        iss >> key;
        std::cout << key << '\n';
        auto result = cache.get(key);

        if(result.has_value()) {
          std::cout << result.value() << '\n';
        }
      }
    },

    {
      "PUT", [&](std::istringstream& iss){
        iss >> key >> value;
        std::cout << key << " " << value << '\n';
        cache.put(key, value);


      }
    },

    {
      "DISPLAY", [&](std::istringstream& iss){
        cache.display();
      }
    }, 

    {
      "REMOVE", [&](std::istringstream& iss){
        iss >> key;
        if(key == "") cache.remove();

        else{
          iss >> key;
          cache.remove(key);
        }
       }
     },

    {
      "CONTAINS", [&](std::istringstream& iss){
        iss >> key;

        cache.contains(key);
      }
    },

    {
      "SHOW STATS", [&](std::istringstream& iss){
        cache.displayStats();
      }
    },
    {
      "EXIT", [&](std::istringstream& iss){
        std::exit(0);
      }
    }

  };

  while(true){
    std::cout << "====LRU SHIT=====\n";
    std::string input;

    std::string command; 

    std::getline(std::cin, input);
    std::istringstream iss(input);
  
    iss >> command;
    std::cout << command << '\n';

    if(commands.find(command) != commands.end()){
      commands[command](iss);
    }
    else{
      std::cout << "Invalid command." << '\n';
    }
  }
}
