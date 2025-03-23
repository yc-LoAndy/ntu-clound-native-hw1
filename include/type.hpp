#ifndef _MODEL_HPP
#define _MODEL_HPP

#include "utils.hpp"
#include <string>
#include <vector>

typedef int listing_id;

struct Listing
{
    listing_id id = -1;
    std::string title;
    std::string description;
    double price;
    std::string category;
    std::string userName;
    std::string created_at;

    Listing()
        : id(-1), title(""), description(""), price(0.0), category(""), userName(""), created_at(getCurrentDateTime()) {}

    Listing(
        std::string title,
        std::string description,
        double price,
        std::string category,
        std::string userName)
        : id(-1), title(title), description(description), price(price), category(category), userName(userName), created_at(getCurrentDateTime()) {}
};

#endif
