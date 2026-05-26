/**
 * @file command.h
 * @brief Command management system that see the command and call right method
 *
 * @author Abhishek Regmi
 * @date 05/26/2026
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <algorithm>

#include "store.h"

std::string handle(const std::vector<std::string> &parts, Store &store)
{
    if (parts.empty())
    {
        return "-ERR empty command\r\n";
    }
    std::string command = parts[0];
    if (command.empty())
    {
        return "-ERR empty command\r\n";
    }
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    if (command == "SET")
    {
        if (parts.size() < 3)
        {
            return "-ERR wrong number of arguments\r\n";
        }
        store.set(parts[1], parts[2]);
        return "+OK\r\n";
    }
    else if (command == "GET")
    {
        if (parts.size() < 2)
        {
            return "-ERR wrong number of arguments\r\n";
        }
        std::string result = store.get(parts[1]);
        if (!store.exists(parts[1]))
        {
            return "$-1\r\n";
        }
        return "$" + std::to_string(result.length()) + "\r\n" + result + "\r\n";
    }
    else if (command == "DEL")
    {
        if (parts.size() < 2)
        {
            return "-ERR wrong number of arguments\r\n";
        }
        bool result = store.del(parts[1]);
        if (result)
        {
            return ":1\r\n";
        }
        return ":0\r\n";
    }
    else if (command == "EXISTS")
    {
        if (parts.size() < 2)
        {
            return "-ERR wrong number of arguments\r\n";
        }
        bool result = store.exists(parts[1]);
        if (result)
        {
            return ":1\r\n";
        }
        return ":0\r\n";
    }
    else
    {
        return "-ERR unknown command\r\n";
    }
}

#endif