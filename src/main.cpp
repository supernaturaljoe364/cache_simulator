#include <iostream>
#include "lru.h"
#include <sstream>
#include <functional>
#include <limits>
#include <fstream>

int main(){

  std::cout << "===LRU CACHE===" << '\n';
  int capacity;
  std::cout << "Enter cache capacity: ";
  std::cin >> capacity;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  lruCache<std::string, std::string> lru(capacity);

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
        std::string value;
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
    std::cout << "\n";
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
