/**
 @file      init.c
 @brief     무한 루프 진입 전 객체 및 SDL 요소 초기화를 위한 함수 정의
 @author    이승헌
*/
#include "init.h"

void InitSDL(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[ERROR] in InitSDL(): %s", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow("YoungAndRich", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    return;
}

void InitTTF(void) {
    if (TTF_Init() < 0) {
        printf("[ERROR] in InitTTF(): %s", SDL_GetError());
        exit(1);
    }

    app.font = TTF_OpenFont("./ttf/LiberationSans-Regular.ttf", 20);

    return;
}

void QuitSDL(int flag) {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    QuitTTF();
    SDL_Quit();
    exit(flag);

    return;
}

void QuitTTF(void) {
    TTF_CloseFont(app.font);
    TTF_Quit();

    return;
}

void InitMemorySet(void) {
    memset(&app, 0, sizeof(App));

    return;
}

void InitChart(void) {
    for( int i = 0 ; i < 60 ; i++)
    {
        chart[i].pos.x = i*20;
        chart[i].pos.y = CHART_HEIGHT/2;
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");
        chart[i].pos.w = 20;
        
        chart_kkori[i].pos.x = chart[i].pos.x + 10;
        chart_kkori[i].pos.w = 1;
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/greenline.png");
        chart_kkori[i].pos.y = CHART_HEIGHT/2;

        chart_volume[i].pos.x = i*20;
        chart_volume[i].pos.y = SCREEN_HEIGHT;
        chart_volume[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");
        chart_volume[i].pos.w = 20;
    }

    return;
}

void InitLayout(void)
{
    layout.texture = IMG_LoadTexture(app.renderer, "./gfx/layout.png");
    layout.pos.x = 0;
    layout.pos.y = 0;
    layout.pos.h = SCREEN_HEIGHT;
    layout.pos.w = SCREEN_WIDTH;
}