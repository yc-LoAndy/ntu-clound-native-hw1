#include "db.hpp"
#include "type.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool DB::userExist(const std::string &name)
{
    return this->userListingMap.find(name) != this->userListingMap.end();
}

int DB::createUser(const string &name)
{
    if (this->userExist(name))
        return -1;
    this->userListingMap[name] = {};
    return 0;
}

bool DB::listingExist(listing_id listingId)
{
    return this->listingMap.find(listingId) != this->listingMap.end();
}

listing_id DB::createListing(Listing &listing)
{
    if (!this->userExist(listing.userName))
        return -1;
    listing.id = this->nextListingId++;
    this->listingMap[listing.id] = listing;
    this->userListingMap[listing.userName].push_back(listing.id);
    this->categoryMap[listing.category]++;
    return listing.id;
}

int DB::deleteListing(const std::string &userName, listing_id listingId)
{
    if (!this->listingExist(listingId))
        return -1; // listing doesn't exist
    vector<listing_id> userListings = this->userListingMap[userName];
    vector<listing_id>::iterator it = find(
        userListings.begin(), userListings.end(), listingId);
    if (it == userListings.end())
        return -2; // listing not belongs to user

    string cat = this->listingMap[listingId].category;
    this->userListingMap[userName].erase(it);
    this->listingMap.erase(listingId);
    this->categoryMap[cat]--;
    return 0;
}

Listing *DB::findListing(listing_id listingId)
{
    if (this->listingMap.find(listingId) == this->listingMap.end())
        return nullptr;
    return &this->listingMap[listingId];
}

vector<Listing *> DB::getAllListing()
{
    vector<Listing *> v;
    for (auto &[lid, listing] : this->listingMap)
    {
        v.push_back(&listing);
    }
    return v;
}

bool DB::categoryExist(const std::string &name)
{
    return this->categoryMap.find(name) != this->categoryMap.end();
}

unordered_map<std::string, int> *DB::getCategoryMap()
{
    return &this->categoryMap;
}
