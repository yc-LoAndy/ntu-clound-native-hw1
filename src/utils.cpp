#include "utils.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

vector<string> split(string &str)
{
    vector<string> v;
    string token;
    bool inQuote = false;
    string currentArg;

    for (size_t i = 0; i < str.size(); i++)
    {
        char ch = str[i];

        if (ch == '\'')
        {
            inQuote = !inQuote; // Toggle quote state
            if (!inQuote)
            { // Closing quote
                v.push_back(currentArg);
                currentArg.clear();
            }
        }
        else if (ch == ' ' && !inQuote)
        {
            if (!currentArg.empty())
            {
                v.push_back(currentArg);
                currentArg.clear();
            }
        }
        else
        {
            currentArg += ch;
        }
    }

    if (!currentArg.empty())
    {
        v.push_back(currentArg);
    }

    if (inQuote)
    {
        cout << "Warning: quote not enclosed" << endl;
    }

    return v;
}

string getCurrentDateTime()
{
    time_t now = time(nullptr);
    tm *local_time = localtime(&now);

    ostringstream oss;
    oss << (local_time->tm_year + 1900) << "-"
        << setw(2) << setfill('0') << (local_time->tm_mon + 1) << "-"
        << setw(2) << setfill('0') << local_time->tm_mday << " "
        << setw(2) << setfill('0') << local_time->tm_hour << ":"
        << setw(2) << setfill('0') << local_time->tm_min << ":"
        << setw(2) << setfill('0') << local_time->tm_sec;

    return oss.str();
}
