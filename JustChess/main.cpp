#include "SDL.h"
#include <iostream>
#include <cmath>

//Window resolution
#define WIDTH 1280
#define HEIGHT 960

bool running, fullscreen;
SDL_Renderer* renderer;
SDL_Window* window;
SDL_Rect tile;
float tileScale = 1.75;
int OffsetX = 0;
int OffsetY = 0;
bool selected = false;

#pragma region pieces_textures
int pawn[16][16] = 
{
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
int rook[16][16]=
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0},
{0,0,0,1,2,1,0,1,2,2,2,2,1,0,0,0},
{0,0,0,1,2,1,1,1,2,2,2,2,1,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int knight[16][16]=
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,1,2,2,2,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,1,2,1,2,2,2,2,2,1,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,1,2,2,1,1,1,2,2,2,2,1,0,0,0},
{0,0,0,1,1,0,0,1,2,2,2,2,1,0,0,0},
{0,0,0,0,0,0,1,2,2,2,2,2,1,0,0,0},
{0,0,0,0,0,1,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int bishop[16][16]=
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,0,0,1,2,2,2,0,1,0,0,0,0,0},
{0,0,0,0,1,2,2,2,0,1,2,1,0,0,0,0},
{0,0,0,0,1,2,2,2,1,2,2,1,0,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int queen[16][16]=
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0},
{0,0,1,2,1,0,1,2,2,1,0,1,2,1,0,0},
{0,0,1,2,2,1,2,2,2,2,1,2,2,1,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int king[16][16]=
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0},
{0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,0},
{0,0,1,2,2,2,1,0,0,1,2,2,2,1,0,0},
{0,0,1,2,0,1,2,1,1,2,1,0,2,1,0,0},
{0,0,1,2,0,0,1,2,2,1,0,0,2,1,0,0},
{0,0,1,2,1,0,0,2,2,0,0,1,2,1,0,0},
{0,0,0,1,2,1,1,2,2,1,1,2,1,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
#pragma endregion

int ChessBoard[8][8] = { {13,  14,  15, 16,  17, 15,  14, 13},             /* Pawn_W      ->   |x| = 2 Pawn_B      ->   |x| = 12 */
                         {12,  12,  12, 12,  12, 12,  12, 12},             /* Rook_W      ->   |x| = 3 Rook_B      ->   |x| = 13 */
                         { 1,   1,  1,   1,  1,   1,  1,   1},             /* Knight_W    ->   |x| = 4 Knight_B    ->   |x| = 14 */
                         { 1,   1,  1,   1,  1,   1,  1,   1},             /* Bishop_W    ->   |x| = 5 Bishop_B    ->   |x| = 15 */
                         { 1,   1,  1,   1,  1,   1,  1,   1},             /* Queen_W     ->   |x| = 6 Queen_B     ->   |x| = 16 */
                         { 1,   1,  1,   1,  1,   1,  1,   1},             /* King_W      ->   |x| = 7 King_B      ->   |x| = 17 */
                         { 2,   2,  2,   2,  2,   2,  2,   2},             /* (x < 0)   ->   Black tile */
                         { 3,   4,  5,   6,  7,   5,  4,   3}              /* (x > 0)   ->   White tile */
                                                                };             /* |x| = 1   ->   Empty tile */

int ChessBoardToDraw[8][8] = { 0 };


void input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) running = false;
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_MouseButtonEvent& b=e.button;
            if (b.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                mouseX = (int)((mouseX-OffsetX) / tile.w);
                mouseY = (int)((mouseY-OffsetY) / tile.h);
                ChessBoardToDraw[mouseY][mouseX] = 16;
            }
            if (b.button == SDL_BUTTON_RIGHT)
            {
                memcpy(ChessBoardToDraw, ChessBoard, sizeof(ChessBoard));
            }
        }
    }
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_ESCAPE]) running = false;
}
void init()
{
    memcpy(ChessBoardToDraw, ChessBoard, sizeof(ChessBoard));
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
    int color;
    int texture[16][16] = { 0 };
    if(piece>10)
    {
        color = 2;
    }
    else
    {
        color = 1;
    }
    if (piece == 12 || piece == 2) { memcpy(texture, pawn, sizeof(pawn)); }
    if (piece == 13 || piece == 3) { memcpy(texture, rook, sizeof(rook)); }
    if (piece == 14 || piece == 4) { memcpy(texture, knight, sizeof(knight)); }
    if (piece == 15 || piece == 5) { memcpy(texture, bishop, sizeof(bishop)); }
    if (piece == 16 || piece == 6) { memcpy(texture, queen, sizeof(queen)); }
    if (piece == 17 || piece == 7) { memcpy(texture, king, sizeof(king)); }

    switch (color) {
        case 1:
        for (int i=0; i < tile.w; i++)
        {
            for (int k=0; k < tile.h; k++)
            {
                int scaled_x_cord = k / (tile.w/16);
                int scaled_y_cord = i / (tile.h/16);
                if (texture[scaled_x_cord][scaled_y_cord] == 1)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawPoint(renderer, x + i, y + k);
                }
                else if (texture[scaled_x_cord][scaled_y_cord] == 2)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(renderer, x + i, y + k);
                }
            }
        }
        break;

        case 2:
            for (int i = 0; i < tile.w; i++)
            {
                for (int k = 0; k < tile.h; k++)
                {
                    int scaled_x_cord = k / (tile.w / 16);
                    int scaled_y_cord = i / (tile.h / 16);
                    if (texture[scaled_x_cord][scaled_y_cord] == 1)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                        SDL_RenderDrawPoint(renderer, x + i, y + k);
                    }
                    else if (texture[scaled_x_cord][scaled_y_cord] == 2)
                    {
                        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 0);
                        SDL_RenderDrawPoint(renderer, x + i, y + k);
                    }
                }
            }
            break;
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

            if (k%2==0)
            {
                if (i % 2 == 0)
                {
                    SDL_SetRenderDrawColor(renderer, 213, 196, 161, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 87, 65, 47, 255);
                }
            }
            else
            {
                if (i % 2 == 1)
                {
                    SDL_SetRenderDrawColor(renderer, 213, 196, 161, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 87, 65, 47, 255);
                }
            }
            SDL_RenderFillRect(renderer, &tile);
            if (ChessBoardToDraw[i][k] != 1 )
            {
                drawPiece(ChessBoardToDraw[i][k], tile.x, tile.y);
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