/**
 @file      draw_chart.c
 @brief     차트 구현 함수를 정의한 소스파일
 @author    이태겸
 */

#include "draw_chart.h"

void ClearWindow(void) 
{
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    SDL_RenderClear(app.renderer);

    return;
}

void RenderLayout(Entity *object)
{
    SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w), &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, NULL);

    return;
}

void ShowWindow(void)
{
    SDL_RenderPresent(app.renderer);
    
    return;
}

void checktime(void)
{
    if(strcmp(coin_data.candle_date_time_kst, coin_data.candle_date_time_kst_check))
    {
        i++;
        strcpy(coin_data.candle_date_time_kst_check, coin_data.candle_date_time_kst);
        SDL_Delay(100);     
    }

    return;
}

void DefineChartHeight(void)
{   
    if(coin_data.trade_coef < coin_data.opening_coef)           // 시작가보다 현재가가 낮을 때 (음봉)
    {
        chart[i].pos.y = 600 - coin_data.opening_coef;
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/greenline.png");
        chart_volume[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");
        coin_price_board.color.b = 225;
        coin_price_board.color.r = 0;
    }
    else if(coin_data.trade_coef > coin_data.opening_coef)      // 시작가보다 현재가가 높을 때 (양봉)
    {
        chart[i].pos.y = 600 - coin_data.trade_coef; 
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/redline.png");
        chart_volume[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");
        coin_price_board.color.b = 0;
        coin_price_board.color.r = 225;
    }
    else
    {
        chart[i].pos.y = 600 - coin_data.trade_coef;            // 가격변동 없을 때 (차트상으로는 양봉으로 취급)
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/redline.png");
        chart_volume[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");
        coin_price_board.color.b = 0;
        coin_price_board.color.r = 0;
    }

    chart[i].pos.h = abs(round(coin_data.trade_coef - coin_data.opening_coef));   
    chart_kkori[i].pos.h = abs(round(coin_data.high_coef - coin_data.low_coef)); 

    if(chart[i].pos.h == 0)
    {
        chart[i].pos.h = 1;
    }

    chart_kkori[i].pos.y = 600 - coin_data.high_coef; 
    // printf("%-8.2f %-10.2f %d\n", coin_data.trade_coef, coin_data.trade_price, i);      ##########################################################가격 디버그
    
    chart_volume[i].pos.h = coin_data.candle_acc_trade_volume_coef;
    chart_volume[i].pos.y = SCREEN_HEIGHT - chart_volume[i].pos.h;

    if(coin_data.candle_acc_trade_volume_high <= coin_data.candle_acc_trade_volume)
    {
        for(int j = 0 ; j < i ; j++)
        {
            chart_volume[j].pos.h = chart_volume[j].pos.h * coef_chart / coef_chart_before;
            chart_volume[j].pos.y = SCREEN_HEIGHT - chart_volume[j].pos.h;

    // printf("%d    %d     %.2f\n", chart_volume[i].pos.h, chart_volume[i].pos.y, coin_data.candle_acc_trade_volume_coef);  #####################거래량 디버그
    // chart_volume[i].pos.h = abs(round(SCREEN_HEIGHT - coin_data.candle_acc_trade_volume_coef))

    // printf("%.2f  %.2f  %d  %d zzzz\n", coin_data.trade_price, 600 - coin_data.trade_coef, chart[i].pos.y, chart[i].pos.h);              // 12/6 
    // printf("%d  %d  %d  %d  가격 : %.2f\n", chart[i].pos.h, chart[i].pos.x, chart[i].pos.y, chart[i].pos.w, coin_data.trade_price);
        }
    }

    return;
}

void RenderChart(Entity *object)
{
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));    //이미지를 Dst만큼의 사각형에 출력

    return;
}

void DrawChart(void)
{
    RenderLayout(&layout);
    for (int i = 0; i < 30 ; i++) 
    {
        RenderChart(&(chart[i]));
        RenderChart(&(chart_kkori[i]));
        RenderChart(&(chart_volume[i]));
    }
    RenderBoard(&left_money_board);
    RenderBoard(&coin_price_board);

    
    return;
}

void DrawPositionInfo(void)
{
    if(buy_price > coin_data.trade_price)   // 가격 하락 
    {
        rate_of_return_board.color.r = 0;
        rate_of_return_board.color.b = 255;

        profits_board.color.r = 0;
        profits_board.color.b = 225;
    }
    else if(buy_price < coin_data.trade_price)      // 가격 상승
    {
        rate_of_return_board.color.r = 225;
        rate_of_return_board.color.b = 0;

        profits_board.color.r = 255;
        profits_board.color.b = 0;
    }
    else
    {
        rate_of_return_board.color.r = 0;
        rate_of_return_board.color.b = 0;

        profits_board.color.r = 0;
        profits_board.color.b = 0;
    }
    RenderPositionBoard(&buy_price_board);
    RenderPositionBoard(&liquidation_money_board);
    RenderPositionBoard(&rate_of_return_board);
    RenderPositionBoard(&profits_board);
    // printf("info\n");
    return;
}

void RenderPositionBoard(Text *object) 
{

    // SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w),
    //                  &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));    

    return;
}

void RenderBoard(Text *object) 
{

    SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w),
                     &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));    

    return;
}
