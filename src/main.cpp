#include <raylib.h>
#include <cstring>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include "Game.hpp"

int screenWidth = 1280;
int screenHeight = 720;
bool fullscreen = false;
bool borderless = false;
Game* game;
double currentTime = 0.0;
double previousTime = 0.0;

void GameLoop();

int main(int argc, char* argv[])
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);

#if defined(PLATFORM_WEB)
    InitWindow(screenWidth, screenHeight, "Test Game");
    
    game = new Game();
    game->Init();
    
    emscripten_set_main_loop(GameLoop, 0, 1);
#else
    InitWindow(screenWidth, screenHeight, "Test Game");
    SetWindowState(FLAG_VSYNC_HINT);

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--fullscreen") == 0 || strcmp(argv[i], "-f") == 0)
        {
            fullscreen = true;
        }
        if (strcmp(argv[i], "--borderless") == 0 || strcmp(argv[i], "-b") == 0)
        {
            borderless = true;
        }
    }

    if (borderless)
    {
        SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED);
        SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
        SetWindowPosition(0, 0);
    } else if (fullscreen)
    {
        SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
        SetWindowState(FLAG_VSYNC_HINT | FLAG_FULLSCREEN_MODE);
    }

    /*if (fullscreen)
    {
        int monitorWidth = GetMonitorWidth(0);
        int monitorHeight = GetMonitorHeight(0);

        InitWindow(monitorWidth, monitorHeight, "Test Game");

        SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
        //SetWindowState(FLAG_VSYNC_HINT | FLAG_FULLSCREEN_MODE);
    } else
    {
        InitWindow(screenWidth, screenHeight, "Test Game");
        SetWindowState(FLAG_VSYNC_HINT);
    }*/
    //SetTargetFPS(60);

    //SetExitKey(KEY_NULL);
    SetExitKey(KEY_ESCAPE);

    game = new Game();
    game->Init();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        GameLoop();
    }
#endif

    delete game;

    CloseWindow();

    return 0;
}

void GameLoop()
{
    game->Update(GetFrameTime());
    game->Render();
}