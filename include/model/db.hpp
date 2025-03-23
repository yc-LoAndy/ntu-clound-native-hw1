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
    std::unordered_map<listing_id, Listing> listingMap;
    std::unordered_map<std::string, std::vector<listing_id>> userListingMap;

public:
    DB() : nextListingId(100001) {}

    // User
    bool userExist(const std::string &name);
    int createUser(const std::string &name);

    // Listing
    bool listingExist(listing_id listingId);
    listing_id createListing(Listing &listing);
    int deleteListing(const std::string &userName, listing_id listingId);
    Listing *findListing(listing_id listingId);
    std::vector<Listing *> getAllListing();

    // Category
    bool categoryExist(const std::string &name);
    std::unordered_map<std::string, int> *getCategoryMap();
};

#endif
