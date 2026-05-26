#include <iostream>
#include "lru.h"
#include <optional>

int main(){

  int capacity;
  std::cout << "Enter cache capacity: " << '\n';
  std::cin >> capacity;
  lruCache<std::string, int> lru(capacity);
  
  std::string key;
  int value;
  int ch;
  do{
    std::cout << "===LRU CACHE===" << '\n';
    std::cout << "1. GET\n2. PUT\n3. DISPLAY\n4. REMOVE\n5. EXIT\nEnter choice: ";
    std::cin >> ch;

    if(ch == 1){

      std::cout << "Enter key: ";
      std::cin >> key;
      
      auto it = lru.get(key);
      if(it.has_value()){
        std::cout << "Value is: " << it.value() << '\n';
      }
      else{
        std::cout << "Key not found!" << '\n';
      }
    }
    else if(ch == 2){
      std::cout << "Enter key,value : ";
      std::cin >> key >> value;

      lru.put(key, value);
    }
    else if(ch == 3){
      lru.display();
    }
    else if(ch == 5){
      break;
    }
    else if(ch == 4){
      lru.remove();
    }
    else{
      std::cout << "Invalid input." << '\n';
    }
  }while(ch != 5);
}
