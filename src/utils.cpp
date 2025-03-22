#include "utils.hpp"
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

vector<string> split(string &str)
{
    string s;
    stringstream ss(str);
    vector<string> v;
    while (getline(ss, s, ' '))
    {
        v.push_back(s);
    }
    return v;
}
