#include "SDL.h"
#include <iostream>
#include <cmath>

#define WIDTH 1280
#define HEIGHT 960

bool running, fullscreen;
SDL_Renderer* renderer;
SDL_Window* window;
SDL_Rect tile;
float tileScale = 1.5;
int OffsetX = 0;
int OffsetY = 0;

int ChessBoard[8][8] = { {3,-4,5,-6,7,-5,4,-3},     /* Pawn      ->   |x| = 2 */
                         {-2,2,-2,2,-2,2,-2,2},     /* Rook      ->   |x| = 3 */
                         {1,-1,1,-1,1,-1,1,-1},     /* Knight    ->   |x| = 4 */
                         {-1,1,-1,1,-1,1,-1,1},     /* Bishop    ->   |x| = 5 */
                         {1,-1,1,-1,1,-1,1,-1},     /* Queen     ->   |x| = 6 */
                         {-1,1,-1,1,-1,1,-1,1},     /* King      ->   |x| = 7 */
                         {2,-2,2,-2,2,-2,2,-2},     /* (x < 0)   ->   Black tile */
                         {-3,4,-5,6,-7,5,-4,3}      /* (x > 0)   ->   White tile */
                                            };      /* |x| = 1   ->   Empty tile */


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
    tile.w = tileScale*64;
    tile.h = tileScale*64;
    tile.x = 0;
    tile.y = 0;
    OffsetX = (WIDTH - tile.w * 8) / 2;
    OffsetY = (HEIGHT - tile.w * 8) / 2;
}

void update()
{
    if (fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if (!fullscreen) SDL_SetWindowFullscreen(window, 0);
}

void drawChessboard()
{

    for (int i = 0; i < 8; i++)
    {
        tile.y = i * tile.h + OffsetY;
        for (int k = 0; k < 8; k++)
        {
            tile.x = k * tile.w + OffsetX;
            if (ChessBoard[i][k] <0)
            {
                SDL_SetRenderDrawColor(renderer, 87, 65, 47, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 213, 196, 161, 255);
            }
            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

void draw()
{
    
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 0);
    SDL_RenderFillRect(renderer, NULL);
    drawChessboard();
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