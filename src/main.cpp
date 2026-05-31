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
  LRU lru;

  std::string key;
  int value;

  std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands = {
    {
      "GET", [&](std::istringstream& iss){
        iss >> key;
        std::cout << key << '\n';
        auto result = lru.get(key);

        if(result.has_value()) {
          std::cout << result.value() << '\n';
        }
      }
    },

    {
      "PUT", [&](std::istringstream& iss){
        iss >> key >> value;
        std::cout << key << " " << value << '\n';
        lru.put(key, value);


      }
    },

    {
      "DISPLAY", [&](std::istringstream& iss){
        lru.display();
      }
    }, 

    {
      "REMOVE", [&](std::istringstream& iss){
        iss >> key;
        if(key == "") lru.remove();

        else{
          iss >> key;
          lru.remove(key);
        }
       }
     },

    {
      "CONTAINS", [&](std::istringstream& iss){
        iss >> key;

        lru.contains(key);
      }
    },

    {
      "SHOW STATS", [&](std::istringstream& iss){
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
    std::cout << command << '\n';

    if(commands.find(command) != commands.end()){
      commands[command](iss);
    }
    else{
      std::cout << "Invalid command." << '\n';
    }
  }
}
