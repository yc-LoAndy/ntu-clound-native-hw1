#ifndef _DB_HPP
#define _DB_HPP

#include "type.hpp"
#include <string>
#include <unordered_map>

class DB
{
private:
    listing_id nextListingId;

    std::unordered_map<std::string, int> categoryMap;
    std::unordered_map<std::string, std::unordered_map<listing_id, Listing>> userListingMap;

public:
    DB() : nextListingId(0) {}

    // User
    bool userExist(const std::string &name);
    int createUser(const std::string &name);

    // Listing
    listing_id createListing(Listing &listing);
    int deleteListing(const std::string &userName, listing_id listingId);
    std::unordered_map<listing_id, Listing> findUserListings(const std::string &name);

    // Category
    bool categoryExist(const std::string &name);
    int createCategory(const std::string &name);
    int deleteCategory(const std::string &name);
    std::string getLargestCategory();
};

#endif
