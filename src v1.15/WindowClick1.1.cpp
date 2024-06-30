#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "font.h"
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 100;
const int BUTTON_X = 0;
const int BUTTON_Y = 0;
extern unsigned char Font_ttf[];
extern unsigned int Font_ttf_len;

std::string textToRender;
int buttonpress = 0;
int ms;
bool isMouseOverButton(int x, int y) {
    return x >= BUTTON_X && x <= BUTTON_X + BUTTON_WIDTH && y >= BUTTON_Y && y <= BUTTON_Y + BUTTON_HEIGHT;
}
SDL_Texture* renderText(const std::string &message, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer) {
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}

int main(int argc, char* argv[]) {
if (TTF_Init() != 0) {
    std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    SDL_Quit();
    return 1;
}
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_Window *win = SDL_CreateWindow("Click!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       100, 100,
                                       SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(win);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_RWops *rw = SDL_RWFromConstMem(Font_ttf, Font_ttf_len);
TTF_Font *font = TTF_OpenFontRW(rw, 1, 24); // Replace with your font file path and size
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                return 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (isMouseOverButton(x, y)) {
                    running = false;
                    buttonpress = 1;
                }
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_Rect buttonRect = { BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
        SDL_RenderFillRect(renderer, &buttonRect);

SDL_Color textColor = {0, 0, 0};
        SDL_Texture *textTexture = renderText("Start", font, textColor, renderer);
        if (textTexture != nullptr) {
            int texW = 0;
            int texH = 0;
            SDL_QueryTexture(textTexture, nullptr, nullptr, &texW, &texH);
            SDL_Rect renderQuad = {(BUTTON_WIDTH - texW) / 2 + BUTTON_X, (BUTTON_HEIGHT - texH) / 2 + BUTTON_Y, texW, texH};
            SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
            SDL_DestroyTexture(textTexture);
        }

        SDL_RenderPresent(renderer);
        buttonpress = 0;

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

while(buttonpress = 1){
     
    buttonpress = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }


    std::srand(std::time(nullptr));


    int screenWidth = 0;
    int screenHeight = 0;
    SDL_DisplayMode dm;
    if (SDL_GetCurrentDisplayMode(0, &dm) == 0) {
        screenWidth = dm.w;
        screenHeight = dm.h;
    } else {
        std::cerr << "SDL_GetCurrentDisplayMode failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    int windowX = std::rand() % (screenWidth - 100);
    int windowY = std::rand() % (screenHeight - 100);


    Uint32 startTime = SDL_GetTicks();
    SDL_Window *win = SDL_CreateWindow("Click!",
                                       windowX, windowY,
                                       100, 100,
                                       SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(win);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_RWops *rw = SDL_RWFromConstMem(Font_ttf, Font_ttf_len);
TTF_Font *font = TTF_OpenFontRW(rw, 1, 24); // Replace with your font file path and size
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    bool running = true;
    bool buttonPressed = false;
    Uint32 buttonPressTime = 0;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                return 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (!buttonPressed && isMouseOverButton(event.button.x, event.button.y)) {
                    running = false;
                    buttonpress = 1;
                    buttonPressed = true;
                    buttonPressTime = SDL_GetTicks();
                    std::cout << (buttonPressTime - startTime) << std::endl;
                    ms = (buttonPressTime - startTime);
                   

                }
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect buttonRect = { BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
        SDL_RenderFillRect(renderer, &buttonRect);
    std::string textToRender = std::to_string(ms);

SDL_Color textColor = {0, 0, 0};
        SDL_Texture *textTexture = renderText(textToRender, font, textColor, renderer);
        if (textTexture != nullptr) {
            int texW = 0;
            int texH = 0;
            SDL_QueryTexture(textTexture, nullptr, nullptr, &texW, &texH);
            SDL_Rect renderQuad = {(BUTTON_WIDTH - texW) / 2 + BUTTON_X, (BUTTON_HEIGHT - texH) / 2 + BUTTON_Y, texW, texH};
            SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
            SDL_DestroyTexture(textTexture);
        }

        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();


}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();



    return 0;
}
