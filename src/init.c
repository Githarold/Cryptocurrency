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
    memset(&chart, 0, sizeof(App));
    memset(&chart_kkori, 0, sizeof(App));
    memset(&layout, 0, sizeof(App));
    memset(&coin_price_board, 0, sizeof(App));
    memset(&left_money_board, 0, sizeof(App));
    memset(&buy_money_board, 0, sizeof(App));
    memset(&liquidation_money_board, 0, sizeof(App));
    memset(&rate_of_return_board, 0, sizeof(App));
    memset(&profits_board, 0, sizeof(App));


    return;
}
// extern Entity chart_kkori[30];
// extern Entity chart_volume[30];
// extern Entity layout;

// extern Text coin_price_board;
// extern Text left_money_board;
// extern Text buy_money_board;
// extern Text liquidation_money_board;
// extern Text rate_of_return_board;
// extern Text profits_board;

void InitChart(void) {
    for(int i = 0 ; i < 30 ; i++)
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
}

void InitScoreBoard(void)
{
    coin_price_board.color.r = 0;
    coin_price_board.color.g = 0;
    coin_price_board.color.b = 0;
    coin_price_board.color.a = 255;
    coin_price_board.pos.x = 900;
    coin_price_board.pos.y = 175;

    // left_money_board.color.r = 0;
    // left_money_board.color.g = 0;
    // left_money_board.color.b = 0;
    // left_money_board.color.a = 255;

    // buy_money_board.color.r = 0;
    // buy_money_board.color.g = 0;
    // buy_money_board.color.b = 0;
    // buy_money_board.color.a = 255;

    // liquidation_money_board.color.r = 0;
    // liquidation_money_board.color.g = 0;
    // liquidation_money_board.color.b = 0;
    // liquidation_money_board.color.a = 255;

    // rate_of_return_board.color.r = 0;
    // rate_of_return_board.color.g = 0;
    // rate_of_return_board.color.b = 0;
    // rate_of_return_board.color.a = 255;

    // profits_board.color.r = 0;
    // profits_board.color.g = 0;
    // profits_board.color.b = 0;
    // profits_board.color.a = 255;


    return;
}