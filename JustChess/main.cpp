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

#pragma region pieces_textures
int pawn_W[16][16] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int rook_W[32][32];
int knight_W[32][32];
int bishop_W[32][32];
int queen_W[32][32];
int king_W[32][32];

int pawn_B[16][16];
int rook_B[32][32];
int knight_B[32][32];
int bishop_B[32][32];
int queen_B[32][32];
int king_B[32][32];
#pragma endregion

int ChessBoard[8][8] = { {13,-14,15,-16,17,-15,14,-13},     /* Pawn_W      ->   |x| = 2 Pawn_B      ->   |x| = 12 */
                         {-12,12,-12,12,-12,12,-12,12},     /* Rook_W      ->   |x| = 3 Rook_B      ->   |x| = 13 */
                         {1,-1,1,-1,1,-1,1,-1},             /* Knight_W    ->   |x| = 4 Knight_B    ->   |x| = 14 */
                         {-1,1,-1,1,-1,1,-1,1},             /* Bishop_W    ->   |x| = 5 Bishop_B    ->   |x| = 15 */
                         {1,-1,1,-1,1,-1,1,-1},             /* Queen_W     ->   |x| = 6 Queen_B     ->   |x| = 16 */
                         {-1,1,-1,1,-1,1,-1,1},             /* King_W      ->   |x| = 7 King_B      ->   |x| = 17 */
                         {2,-2,2,-2,2,-2,2,-2},             /* (x < 0)   ->   Black tile */
                         {-3,4,-5,6,-7,5,-4,3}              /* (x > 0)   ->   White tile */
                                            };              /* |x| = 1   ->   Empty tile */


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


void drawPiece(int piece, int x, int y)
{

    switch (piece) {
        case 2:
        for (int i=0; i < tile.w; i++)
        {
            for (int k=0; k < tile.h; k++)
            {
                int x_cord = k / 6;
                int y_cord = i / 6;
                if (pawn_W[x_cord][y_cord] == 1)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawPoint(renderer, x + i, y + k);
                }
                else if (pawn_W[x_cord][y_cord] == 2)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(renderer, x + i, y + k);
                }
            }
        }
    }
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
            if (ChessBoard[i][k] == 2 || ChessBoard[i][k] == -2)
            {
                drawPiece(2, tile.x, tile.y);
            }
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