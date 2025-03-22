#include "db.hpp"
#include <type.hpp>
#include <vector>
#include <string>
#include <unordered_map>

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

listing_id DB::createListing(Listing &listing)
{
    if (!this->userExist(listing.userName))
        return -1;
    listing.id = this->nextListingId++;
    this->userListingMap[listing.userName][listing.id] = listing;
    return listing.id;
}

int DB::deleteListing(const std::string &userName, listing_id listingId)
{
    size_t res = this->userListingMap[userName].erase(listingId);
    return (res == 0) ? -1 : 0;
}

unordered_map<listing_id, Listing> DB::findUserListings(const std::string &name)
{
    if (!this->userExist(name))
        return {};
    return this->userListingMap.at(name);
}

bool DB::categoryExist(const std::string &name)
{
    return this->categoryMap.find(name) != this->categoryMap.end();
}

int DB::createCategory(const std::string &name)
{
    if (this->categoryExist(name))
        return -1;

    this->categoryMap[name] = 0;
    return 0;
}

int DB::deleteCategory(const std::string &name)
{
    size_t res = this->categoryMap.erase(name);
    return (res == 0) ? -1 : 0;
}

string DB::getLargestCategory()
{
    int maxCount = -1;
    string maxCategory = "";
    for (auto &[name, count] : this->categoryMap)
    {
        if (count > maxCount)
        {
            maxCount = count;
            maxCategory = name;
        }
    }
    return maxCategory;
}
