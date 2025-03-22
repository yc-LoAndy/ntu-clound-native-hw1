#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <vector>
#include <string>

std::vector<std::string> split(std::string &str);

template <typename T>
std::vector<T> slice(const std::vector<T> &arr, int start = 0, int end = -1)
{
    if (start < 0)
        start = 0;
    if ((long unsigned int)end > arr.size())
        end = arr.size();
    if (end == -1)
        end = arr.size();
    if (start > end)
        start = end;

    std::vector<T> result;
    for (int i = start; i < end; i++)
        result.push_back(arr[i]);
    return result;
}

#endif
