#ifndef _MODEL_MANAGER_HPP
#define _MODEL_MANAGER_HPP

#include <string>
#include <vector>

class ModelManager
{
public:
    static void registerUser(const std::vector<std::string> &args);
    static void createListing(const std::vector<std::string> &args);
    static void deleteListing(const std::vector<std::string> &args);
    static void getListing(const std::vector<std::string> &args);
    static void getCategory(const std::vector<std::string> &args);
    static void getTopCategory(const std::vector<std::string> &args);
};

#endif
