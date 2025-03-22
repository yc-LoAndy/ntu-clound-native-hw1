#ifndef _MODEL_HPP
#define _MODEL_HPP

#include <string>
#include <vector>

typedef int listing_id;

typedef struct listing
{
    listing_id id;
    std::string title;
    std::string description;
    double price;
    std::string category;
    std::string userName;

} Listing;

#endif
