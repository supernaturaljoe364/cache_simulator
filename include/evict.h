#pragma once
#include <string>
class evictionPolicy{
//intialize constructor heree (capacity)
  public:

    virtual void onPut(const std::string& key) = 0;
    virtual void onGet(const std::string& key) = 0;
    virtual std::string evict() = 0;
    virtual void onRemove(const std::string& key) = 0;

    virtual ~evictionPolicy() = default;
};
