#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <SDL2/SDL.h>

using namespace std;

//*********************************************************************************************************
int s[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};

const int SCREEN_WIDTH = 954;
const int SCREEN_HEIGHT = 654;
const string WINDOW_TITLE = "*-P-*-U-*-Z-*-Z-*-L-*-E-*";

void moveNumber();
const char *NUMBER[10] = {"number//0.bmp", "number//1.bmp", "number//2.bmp", "number//3.bmp", "number//4.bmp", "number//5.bmp",
                          "number//6.bmp", "number//7.bmp", "number//8.bmp", "number//9.bmp"};

const char *GAME_LV[8][10] = {
    {"image//result.bmp", "image//img_1.bmp", "image//img_2.bmp", "image//img_3.bmp", "image//img_4.bmp", "image//img_5.bmp",
     "image//img_6.bmp", "image//img_7.bmp", "image//img_8.bmp", "image//img_9.bmp"},

    {"img_game_1//akali.bmp", "img_game_1//img_1.bmp", "img_game_1//img_2.bmp", "img_game_1//img_3.bmp", "img_game_1//img_4.bmp",
     "img_game_1//img_5.bmp", "img_game_1//img_6.bmp", "img_game_1//img_7.bmp", "img_game_1//img_8.bmp", "img_game_1//img_9.bmp"},

    {"img_game_2//oggy.bmp", "img_game_2//img_1.bmp", "img_game_2//img_2.bmp", "img_game_2//img_3.bmp", "img_game_2//img_4.bmp",
     "img_game_2//img_5.bmp", "img_game_2//img_6.bmp", "img_game_2//img_7.bmp", "img_game_2//img_8.bmp", "img_game_2//img_9.bmp"},

    {"img_game_3//ac.bmp", "img_game_3//img_1.bmp", "img_game_3//img_2.bmp", "img_game_3//img_3.bmp", "img_game_3//img_4.bmp",
     "img_game_3//img_5.bmp", "img_game_3//img_6.bmp", "img_game_3//img_7.bmp", "img_game_3//img_8.bmp", "img_game_3//img_9.bmp"},

    {"img_game_4//picalong.bmp", "img_game_4//img_1.bmp", "img_game_4//img_2.bmp", "img_game_4//img_3.bmp", "img_game_4//img_4.bmp",
     "img_game_4//img_5.bmp", "img_game_4//img_6.bmp", "img_game_4//img_7.bmp", "img_game_4//img_8.bmp", "img_game_4//img_9.bmp"},

    {"img_game_5//moon.bmp", "img_game_5//img_1.bmp", "img_game_5//img_2.bmp", "img_game_5//img_3.bmp", "img_game_5//img_4.bmp",
     "img_game_5//img_5.bmp", "img_game_5//img_6.bmp", "img_game_5//img_7.bmp", "img_game_5//img_8.bmp", "img_game_5//img_9.bmp"},

    {"img_game_6//doremon.bmp", "img_game_6//img_1.bmp", "img_game_6//img_2.bmp", "img_game_6//img_3.bmp", "img_game_6//img_4.bmp",
     "img_game_6//img_5.bmp", "img_game_6//img_6.bmp", "img_game_6//img_7.bmp", "img_game_6//img_8.bmp", "img_game_6//img_9.bmp"},

    {"img_game_7//pikachu.bmp", "img_game_7//img_1.bmp", "img_game_7//img_2.bmp", "img_game_7//img_3.bmp", "img_game_7//img_4.bmp",
     "img_game_7//img_5.bmp", "img_game_7//img_6.bmp", "img_game_7//img_7.bmp", "img_game_7//img_8.bmp", "img_game_7//img_9.bmp"},
};

SDL_Event k;
SDL_Renderer *renderer;
SDL_Window *window;

void logSDLError(std::ostream &os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window *&window, SDL_Renderer *&renderer);
void quitSDL(SDL_Window *window, SDL_Renderer *renderer);
void waitUntilKeyPressed();
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

///**********************************************************************************************
void playGame(int &change_time);
int leverGame;
int time_move = 0;

void printPuzzle()
{
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (s[y][x] != 9)
            {
                SDL_Texture *piece = loadTexture(GAME_LV[leverGame][s[y][x]], renderer);
                renderTexture(piece, renderer, 400 + 152 * x, 100 + 152 * y, 150, 150);
                SDL_Texture *image = loadTexture(GAME_LV[leverGame][0], renderer);
                renderTexture(image, renderer, 100, 100, 200, 200);

                SDL_DestroyTexture(piece);
                SDL_DestroyTexture(image);
            }
        }
    }
}

void printPicture()
{
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            SDL_Texture *piece = loadTexture(GAME_LV[leverGame][s[y][x]], renderer);
            renderTexture(piece, renderer, 400 + 152 * x, 100 + 152 * y, 150, 150);
            SDL_Texture *image = loadTexture(GAME_LV[leverGame][0], renderer);
            renderTexture(image, renderer, 100, 100, 200, 200);

            SDL_Delay(100);
            SDL_DestroyTexture(piece);
            SDL_DestroyTexture(image);
        }
    }
}

bool checkStop()
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            if (s[y][x] != 3 * y + x + 1)
                return 0;
    return 1;
}

int nineRow()
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            if (s[y][x] == 9)
                return y;
}

int nineCol()
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            if (s[y][x] == 9)
                return x;
}

void swapNumber(int x, int y)
{
    int i = nineRow();
    int j = nineCol();
    int temp = s[i][j];
    s[i][j] = s[i + x][j + y];
    s[i + x][j + y] = temp;
}

void turnUp()
{
    if (nineRow() < 2)
    {
        swapNumber(1, 0);
    }
}

void turnDown()
{
    if (nineRow() > 0)
    {
        swapNumber(-1, 0);
    }
}

void turnLeft()
{
    if (nineCol() < 2)
    {
        swapNumber(0, 1);
    }
}

void turnRight()
{
    if (nineCol() > 0)
    {
        swapNumber(0, -1);
    }
}

void autoExchange(int &change_time)
{
    srand((unsigned int)time(0));
    for (int i = 0; i <= change_time; i++)
    {
        int r = rand() % 4;
        if (r == 0)
            turnUp();
        if (r == 1)
            turnDown();
        if (r == 2)
            turnLeft();
        if (r == 3)
            turnRight();
    }
    change_time += 5;
}

void arrowKey()
{
    int m = nineRow();
    int n = nineCol();

    SDL_WaitEvent(&k);
    if (k.type == SDL_KEYDOWN)
    {
        if (k.key.keysym.sym == SDLK_LEFT)
            turnLeft();
        if (k.key.keysym.sym == SDLK_RIGHT)
            turnRight();
        if (k.key.keysym.sym == SDLK_DOWN)
            turnDown();
        if (k.key.keysym.sym == SDLK_UP)
            turnUp();
        if (nineRow() != m || nineCol() != n)
            time_move++;
    }

    SDL_Delay(65);
}

void moveNumber()
{
    if (time_move < 100)
    {
        SDL_Texture *hundred = loadTexture(NUMBER[0], renderer);
        SDL_Texture *ten = loadTexture(NUMBER[time_move / 10], renderer);
        SDL_Texture *unit = loadTexture(NUMBER[time_move % 10], renderer);

        renderTexture(hundred, renderer, 100, 350);
        renderTexture(ten, renderer, 171, 350);
        renderTexture(unit, renderer, 242, 350);
        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(hundred);
        SDL_DestroyTexture(ten);
        SDL_DestroyTexture(unit);
    }
    if (time_move >= 100)
    {
        SDL_Texture *hundred = loadTexture(NUMBER[time_move / 100], renderer);
        SDL_Texture *ten = loadTexture(NUMBER[time_move / 10 % 10], renderer);
        SDL_Texture *unit = loadTexture(NUMBER[time_move % 10], renderer);

        renderTexture(hundred, renderer, 100, 350);
        renderTexture(ten, renderer, 171, 350);
        renderTexture(unit, renderer, 242, 350);
        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(hundred);
        SDL_DestroyTexture(ten);
        SDL_DestroyTexture(unit);
    }
}

void startGame()
{
    SDL_Texture *start_img = loadTexture("basic_img//start.bmp", renderer);
    renderTexture(start_img, renderer, 0, 0);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(start_img);
    waitUntilKeyPressed();
}

void playGame(int &change_time)
{
    autoExchange(change_time);
    leverGame = rand() % 8;
    while (1)
    {
        if (checkStop())
        {
            printPicture();
            moveNumber();
            SDL_Texture *cont = loadTexture("basic_img//continue.bmp", renderer);
            renderTexture(cont, renderer, 20, 450, 370, 150);
            SDL_RenderPresent(renderer);
            waitUntilKeyPressed();
            // SDL_Delay(1000);
            srand(time(0));
            leverGame = rand() % 8;
            time_move = 0;
            autoExchange(change_time);

            // playGame(change_time);
        }
        moveNumber();
        arrowKey();

        SDL_RenderPresent(renderer);
        SDL_PollEvent(&k);
        if (time_move == 999)
        {
            SDL_Texture *lose = loadTexture("basic_img//loser.bmp", renderer);
            renderTexture(lose, renderer, 0, 0);
            SDL_RenderPresent(renderer);

            while (true)
            {
                SDL_PollEvent(&k);
                if (k.type == SDL_KEYDOWN && k.key.keysym.sym == SDLK_LEFT)
                {
                    time_move = 0;
                    playGame(change_time);
                }
                if (k.type == SDL_KEYDOWN && k.key.keysym.sym == SDLK_RIGHT)
                    return;
            }

            SDL_DestroyTexture(lose);
        }

        if ((k.type == SDL_KEYDOWN && k.key.keysym.sym == SDLK_ESCAPE) || k.type == SDL_QUIT)
        {
            SDL_Texture *quit = loadTexture("basic_img//you_quit.bmp", renderer);
            renderTexture(quit, renderer, 250, 250);
            SDL_RenderPresent(renderer);
            while (true)
            {
                SDL_PollEvent(&k);
                if (k.type == SDL_KEYDOWN && k.key.keysym.sym == SDLK_LEFT)
                    break;
                if (k.type == SDL_KEYDOWN && k.key.keysym.sym == SDLK_RIGHT)
                    return;
            }
        }
        SDL_Texture *background = loadTexture("basic_img//back_ground.bmp", renderer);

        if (background == nullptr)
        {
            SDL_DestroyTexture(background);
            quitSDL(window, renderer);
        }

        renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_DestroyTexture(background);
        printPuzzle();
        SDL_RenderPresent(renderer);
    }
}

///********************************************************************************************************************************************************

int main(int argc, char *argv[])
{
    initSDL(window, renderer);
    SDL_Texture *background = loadTexture("basic_img//back_ground.bmp", renderer);
    if (background == nullptr)
    {
        SDL_DestroyTexture(background);
        quitSDL(window, renderer);
    }

    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_DestroyTexture(background);
    SDL_RenderPresent(renderer);

    // ********** Play ***********
    srand(time(0));
    startGame();
    int change_time = 10;
    playGame(change_time);
    // ********** All ***********
    SDL_RenderPresent(renderer);

    quitSDL(window, renderer);
    return 0;
}

///********************************************************* Ket thuc ham main ****************************************************************************

void logSDLError(std::ostream &os, const std::string &msg, bool fatal) // ghi lại lỗi xuất hiện trong SDL
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window *&window, SDL_Renderer *&renderer) // khởi tạo SDL
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window *window, SDL_Renderer *renderer) // thoát khỏi SDL
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren) // tải một hình ảnh từ file và tạo một texture SDL
{

    SDL_Texture *texture = nullptr;

    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

    if (loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);

        if (texture == nullptr)
        {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    }
    else
    {
        logSDLError(std::cout, "LoadBMP");
    }
    return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}