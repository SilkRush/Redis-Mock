/**
 * @file parser.h
 * @brief It takes raw bytes that server received and returns the list of command parts
 *
 * @author Abhishek Regmi
 * @date 05/26/2026
 */

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

std::vector<std::string> parse(const std::string &raw)
{
    std::vector<std::string> result;
    if (raw[0] != '*' || raw.empty())
    {
        return result;
    }

    std::size_t start = 0;
    std::size_t end = 0;
    // Search for "\r\n" starting from the position start
    while ((end = raw.find("\r\n", start)) != std::string::npos)
    {
        // Break line into length as start and (end -start)
        //  Break line into every place of newline
        std::string line = raw.substr(start, end - start);

        // If line is not a token like $ or * that gives the byte data
        if (line[0] != '$' && line[0] != '*')
        {
            result.push_back(line);
        }
        start = end + 2;
    }

    return result;
}

#endif