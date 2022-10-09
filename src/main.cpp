#include "controllers/App.hpp"

int main()
{
    // Create new app instance
    auto *app = new App;
    // Begin the main game loop and capture the return code of the game
    const int ret = app->beginGameLoop();
    // Dispose of app instance
    delete app;
    return ret;
}
