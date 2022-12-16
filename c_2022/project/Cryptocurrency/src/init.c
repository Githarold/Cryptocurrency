/**
 @file      init.c
 @brief     무한 루프 진입 전 객체 및 SDL 요소 초기화를 위한 함수 정의
 @author    이승헌, 이태겸
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

    app.font = TTF_OpenFont("./ttf/KoPubWorld Dotum Bold.ttf", 22);
    
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
    memset(&chart, 0, sizeof(Entity));
    memset(&chart_kkori, 0, sizeof(Entity));
    memset(&layout, 0, sizeof(Entity));
    memset(&search, 0, sizeof(Entity));
    memset(&position_picture, 0, sizeof(Entity));
    memset(&profit_picture, 0, sizeof(Entity));
    memset(&coin_price_board, 0, sizeof(Text));
    memset(&left_money_board, 0, sizeof(Text));
    memset(&buy_price_board, 0, sizeof(Text));
    memset(&liquidation_money_board, 0, sizeof(Text));
    memset(&rate_of_return_board, 0, sizeof(Text));
    memset(&profits_board, 0, sizeof(Text));
    
    
    

    return;
}

void InitChart(void) {
    for(int i = 0 ; i < 40 ; i++)       // 차트를 구성하는 모든 객체에 대해 초기화
    {
        chart[i].pos.x = i*20;
        chart[i].pos.y = CHART_HEIGHT/2;
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");
        chart[i].pos.w = 20;
        chart[i].pos.h = 0;

        chart_kkori[i].pos.x = chart[i].pos.x + 10;
        chart_kkori[i].pos.y = CHART_HEIGHT/2;
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/greenline.png");
        chart_kkori[i].pos.w = 1;
        chart_kkori[i].pos.h = 0;

        chart_volume[i].pos.x = i*20;
        chart_volume[i].pos.y = SCREEN_HEIGHT;
        chart_volume[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");
        chart_volume[i].pos.w = 20;
        chart_volume[i].pos.h = 0;
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

    return;
}

void InitBoard(void)
{
    coin_price_board.color.r = 255; 
    coin_price_board.color.g = 255;
    coin_price_board.color.b = 255;
    coin_price_board.color.a = 255;
    coin_price_board.pos.x = 550;
    coin_price_board.pos.y = 9;

    left_money_board.color.r = 255;     
    left_money_board.color.g = 255;
    left_money_board.color.b = 255;
    left_money_board.color.a = 255;
    left_money_board.pos.x = 890;
    left_money_board.pos.y = 167;

    buy_price_board.color.r = 255;
    buy_price_board.color.g = 255;
    buy_price_board.color.b = 255;
    buy_price_board.color.a = 255;
    buy_price_board.pos.x = 865;
    buy_price_board.pos.y = 640;
    buy_price_board.pos.w = 80;
    buy_price_board.pos.h = 25;

    liquidation_money_board.color.r = 255;
    liquidation_money_board.color.g = 255;
    liquidation_money_board.color.b = 255;
    liquidation_money_board.color.a = 255;
    liquidation_money_board.pos.x = 865;
    liquidation_money_board.pos.y = 678;
    liquidation_money_board.pos.w = 80;
    liquidation_money_board.pos.h = 25;

    rate_of_return_board.color.r = 255;
    rate_of_return_board.color.g = 255;
    rate_of_return_board.color.b = 255;
    rate_of_return_board.color.a = 255;
    rate_of_return_board.pos.x = 1019;
    rate_of_return_board.pos.y = 640;
    rate_of_return_board.pos.w = 70;
    rate_of_return_board.pos.h = 25;

    profits_board.color.r = 255;
    profits_board.color.g = 255;
    profits_board.color.b = 255;
    profits_board.color.a = 255;
    profits_board.pos.x = 1019;
    profits_board.pos.y = 678;
    profits_board.pos.w = 70;
    profits_board.pos.h = 25;

    position_picture.pos.x = 845;
    position_picture.pos.y = 320;
    position_picture.pos.w = 200;
    position_picture.pos.h = 120;

    // profit_picture.pos.x = SCREEN_WIDTH / 2;
    // profit_picture.pos.y = SCREEN_HEIGHT / 2;
    profit_picture.pos.x = 300;
    profit_picture.pos.y = 300;
    profit_picture.texture = IMG_LoadTexture(app.renderer, "./gfx/pepe0.png");


    return;
}

void InitSearchCoin(void)
{
    search.texture = IMG_LoadTexture(app.renderer, "./gfx/search.png");
    search.pos.x = 0;
    search.pos.y = 0;
    search.pos.w = 290;
    search.pos.h = 50;

    return;
}