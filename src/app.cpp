#include "app.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

using namespace std;

App::App()
{
    this->commandMap = {};
}

void App::run()
{
    string input;
    while (true)
    {
        cout << "# ";
        if (getline(cin, input))
        {
            if (input == "exit")
                break;
            if (input.empty())
                continue;

            vector commandVec = split(input);
            string command = commandVec[0];

            if (this->commandMap.find(command) == this->commandMap.end())
            {
                cout << "[Error] Command not found: " << command << endl;
                continue;
            }
            vector<string> args = slice<string>(commandVec, 1);
            this->commandMap[input](args);
        }
        else
        {
            break;
        }
    }
}

void App::registerCommand(const string &command, CommandHandler handler)
{
    if (this->commandMap.find(command) == this->commandMap.end())
    {
        string errorMsg = "command already registered";
        throw invalid_argument(errorMsg += command);
    }
    this->commandMap[command] = handler;
}
