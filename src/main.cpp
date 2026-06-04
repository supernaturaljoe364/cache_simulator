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
#include <fstream>

int main(){

  int capacity;
  int evict;
  std::unique_ptr<evictionPolicy> policy;
  std::cout << "Enter cache capacity: ";
  std::cin >> capacity;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
  std::cout << "\n1. LRU\n2. FIFO\n3. LFU\nEnter Eviction Policy: ";
  std::cin >> evict;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  switch(evict){
    case 1:
      policy = std::make_unique<LRU>();
      break;
    
    case 2:
      policy = std::make_unique<fifo>();
      break;

    case 3:
      policy = std::make_unique<lfu>();
      break;
    
    default:
      std::cout << "Invalid option" << '\n';
  }
  


  Cache cache(capacity, std::move(policy));
  std::string key;
  int value;

  std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands = {
    {
      "GET", [&](std::istringstream& iss){
        iss >> key;
        auto result = cache.get(key);

        if(result.has_value()) {
          std::cout << result.value() << '\n';
        }
        else{
          std::cout << "Key not found!" << '\n';
        }
      }
    },

    {
      "PUT", [&](std::istringstream& iss){
        iss >> key >> value;
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
      "STATS", [&](std::istringstream& iss){
        cache.displayStats();
      }
    },
    {
      "EXIT", [&](std::istringstream& iss){
        std::exit(0);
      }
    },

    {
      "RUNTEST", [&](std::istringstream& iss){
        //open file from tests/ dir and ru
        std::ifstream readSample("sample.txt");
        if(!readSample.is_open()){
          std::cout << "File not found!" << '\n';
        }
        else{
          std::string line;
          while(std::getline(readSample, line)){
              // run each individual line and run commands accordingly
            std::string command; 

            std::istringstream iss(line);
          
            iss >> command;
            if(commands.find(command) != commands.end()){
              commands[command](iss);
            }

          }
        }
      }
    }

  };

  while(true){
    std::cout << "====CACHE SIMULATOR=====\n";
    std::string input;

    std::string command; 

    std::getline(std::cin, input);
    std::istringstream iss(input);
  
    iss >> command;

    if(commands.find(command) != commands.end()){
      commands[command](iss);
    }
    else{
      std::cout << "Invalid command." << '\n';
    }
  }
}
