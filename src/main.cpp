#include "modelManager.hpp"
#include <app.hpp>

int main()
{
    App app;

    app.registerCommand("REGISTER", &ModelManager::registerUser);
    app.registerCommand("CREATE_LISTING", &ModelManager::createListing);
    app.registerCommand("DELETE_LISTING", &ModelManager::deleteListing);
    app.registerCommand("GET_LISTING", &ModelManager::getListing);
    app.registerCommand("GET_CATEGORY", &ModelManager::getCategory);
    app.registerCommand("GET_TOP_CATEGORY", &ModelManager::getTopCategory);

    app.run();
    return 0;
}
