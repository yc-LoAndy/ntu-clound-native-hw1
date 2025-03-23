#ifndef _APP_HPP
#define _APP_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using CommandHandler = std::function<void(std::vector<std::string>)>;

class App
{
public:
    App();
    void run();
    void registerCommand(const std::string &command, CommandHandler handler);

private:
    std::unordered_map<std::string, CommandHandler> commandMap;
};

#endif
