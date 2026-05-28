#include <iostream>
#include "lru.h"
#include <sstream>
#include <functional>
#include <limits>

int main(){

  int capacity;
  std::cout << "Enter cache capacity: ";
  std::cin >> capacity;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  lruCache<std::string, int> lru(capacity);

  std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands = {
    {
      "GET", [&](std::istringstream& iss){
        std::string key;
        iss >> key;
        auto result = lru.get(key);

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
        std::string key;
        int value;
        iss >> key >> value;
        lru.put(key, value);

        std::cout << "Key, Value entered." << '\n';
      }
    },

    {
      "DISPLAY", [&](std::istringstream& iss){
        lru.display();
      }
    }, 

    {
      "REMOVE", [&](std::istringstream& iss){
        std::string key;
        iss >> key;
        if(key == ""){
          lru.remove();
        } 

        else{
          lru.remove(key);
        }
       }
     },

    {
      "CONTAINS", [&](std::istringstream& iss){
        std::string key;
        iss >> key;

        if(lru.contains(key)) std::cout << "True\n";
        else std::cout << "False" << '\n';
      }
    },

    {
      "STATS", [&](std::istringstream& iss){
        lru.displayStats();
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
    if(commands.find(command) != commands.end()){
      commands[command](iss);
    }
    else{
      std::cout << "Invalid command." << '\n';
    }
  }
  return 0;
}
