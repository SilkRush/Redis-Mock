/**
 * @file store.h
 * @brief Command Center of the server that understands the command
 *
 * @author Abhishek Regmi
 * @date 05/26/2026
 */

#ifndef STORE_H
#define STORE_H

#include <string>
#include <unordered_map>

class Store
{
private:
    std::unordered_map<std::string, std::string> _store;

public:
    void set(const std::string &key, const std::string &value)
    {
        _store[key] = value;
    }

    std::string get(const std::string &key)
    {
        if (_store.count(key))
        {
            return _store[key];
        }
        return "";
    }

    bool del(const std::string &key)
    {
        if (_store.count(key))
        {
            _store.erase(key);
            return true;
        }
        return false;
    }

    bool exists(const std::string &key)
    {
        if (_store.count(key))
        {
            return true;
        }
        return false;
    }
};

#endif