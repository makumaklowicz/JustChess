#include "SDL.h"
#include <iostream>
#include <cmath>

#define WIDTH 1280
#define HEIGHT 640

bool running, fullscreen;
SDL_Renderer* renderer;
SDL_Window* window;
void input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) running = false;
    }
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_ESCAPE]) running = false;
}
void init()
{

}

void update()
{
    if (fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if (!fullscreen) SDL_SetWindowFullscreen(window, 0);
}

void draw()
{

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 0);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    running = 1;
    fullscreen = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "SDL Init Error" << std::endl;
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) std::cout << "SDL Window Create Failed" << std::endl;
    SDL_SetWindowTitle(window, "JustChess");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    init();
    while (running)
    {
        update();
        input();
        draw();

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 60;
}