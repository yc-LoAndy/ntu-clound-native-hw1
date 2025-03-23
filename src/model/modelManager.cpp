#include "global.hpp"
#include "type.hpp"
#include "modelManager.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void ModelManager::registerUser(const vector<string> &args)
{
    /**
     * @param username [string]
     */
    if (args.size() < 1)
    {
        cout << "Error - username not specified" << endl;
        return;
    }
    string username = args[0];
    if (db.createUser(username) < 0)
    {
        cout << "Error - user already existing" << endl;
    }
    else
    {
        cout << "Success" << endl;
    }
}

void ModelManager::createListing(const vector<string> &args)
{
    /**
     * @param username [string]
     * @param title [string]
     * @param description [string]
     * @param price [double]
     * @param category [string]
     */
    if (args.size() < 5)
    {
        cout << "Error - args not enough to pack\nCREATE_LISTING <username> <title> <description> <price> <category>"
             << endl;
        return;
    }
    string username = args[0];
    string title = args[1];
    string description = args[2];
    string category = args[4];
    double price;
    try
    {
        price = stod(args[3]);
    }
    catch (const invalid_argument &e)
    {
        cout << "Error - invalid price: " << e.what() << endl;
        return;
    }

    if (!db.userExist(username))
    {
        cout << "Error - unknown user" << endl;
        return;
    }

    Listing l(title, description, price, category, username);
    listing_id lid = db.createListing(l);
    if (lid < 0)
    {
        cout << "Unknown Error [createListing]" << endl;
        return;
    }
    cout << lid << endl;
}

void ModelManager::deleteListing(const vector<string> &args)
{
    /**
     * @param username [string]
     * @param listing_id [listing_id]
     */
    if (args.size() < 2)
    {
        cout << "Error - not enough arguments to pack\n\
DELETE_LISTING <username> <listing_id>"
             << endl;
        return;
    }

    string username = args[0];
    listing_id lid;
    try
    {
        lid = (listing_id)stoi(args[1]);
    }
    catch (const invalid_argument &e)
    {
        cout << "Error - invalid listing_id: " << e.what() << endl;
        return;
    }

    int res = db.deleteListing(username, lid);
    if (res == -1)
    {
        cout << "Error - listing does not exist" << endl;
        return;
    }
    else if (res == -2)
    {
        cout << "Error - listing owner mismatch" << endl;
        return;
    }
    cout << "Success" << endl;
    return;
}

void ModelManager::getListing(const vector<string> &args)
{
    /**
     * @param usesrname [string]
     * @param listing_id [listing_id]
     */
    if (args.size() < 2)
    {
        cout << "Error - not enough arguments to pack\n\
GET_LISTING <username> <listing_id>"
             << endl;
        return;
    }

    string username = args[0];
    listing_id lid;
    try
    {
        lid = (listing_id)stoi(args[1]);
    }
    catch (const invalid_argument &e)
    {
        cout << "Error - invalid listing_id: " << e.what() << endl;
        return;
    }

    if (!db.userExist(username))
    {
        cout << "Error - unknown user" << endl;
        return;
    }

    Listing *l = db.findListing(lid);
    if (!l)
    {
        cout << "Error - not found" << endl;
        return;
    }
    cout << l->title << "|"
         << l->description << "|"
         << l->price << "|"
         << l->created_at << "|"
         << l->category << "|"
         << l->userName << endl;
}

void ModelManager::getCategory(const std::vector<std::string> &args)
{
    /**
     * @param username [string]
     * @param category [string]
     */
    if (args.size() < 2)
    {
        cout << "Error - not enough arguments to pack\n\
GET_CATEGORY <username> <category>"
             << endl;
        return;
    }

    string username = args[0];
    string category = args[1];

    if (!db.categoryExist(category))
    {
        cout << "Error - category not found" << endl;
        return;
    }

    if (!db.userExist(username))
    {
        cout << "Error - unknown user" << endl;
        return;
    }

    vector<Listing *> ls = db.getAllListing();
    sort(ls.begin(), ls.end(), [](Listing *l1, Listing *l2)
         { return l1->created_at > l2->created_at; });
    for (auto l : ls)
    {
        if (l->category == category)
            cout << l->title << "|"
                 << l->description << "|"
                 << l->price << "|"
                 << l->created_at << "|"
                 << l->category << "|"
                 << l->userName << endl;
    }
}

void ModelManager::getTopCategory(const std::vector<std::string> &args)
{
    /**
     * @param username [string]
     */
    if (args.size() < 1)
    {
        cout << "Error - username not specified" << endl;
        return;
    }
    string username = args[0];
    if (!db.userExist(username))
    {
        cout << "Error - unknown user" << endl;
        return;
    }

    unordered_map<string, int> *cmap = db.getCategoryMap();
    int maxCount = -1;
    vector<string> maxCategory;
    for (auto &[name, count] : *cmap)
    {
        if (count == maxCount)
        {
            maxCategory.push_back(name);
        }
        else if (count > maxCount)
        {
            maxCount = count;
            maxCategory.clear();
            maxCategory.push_back(name);
        }
    }
    sort(maxCategory.begin(), maxCategory.end());
    for (auto c : maxCategory)
    {
        cout << c << endl;
    }
}
