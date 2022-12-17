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
    if(strcmp(coin_data.candle_date_time_kst, coin_data.candle_date_time_kst_check))            // 1분마다 초기화되는 문자열과 실시간으로 초기화되는 문자열을 비교하여 시간이 지났음을 파악
    {
        i++;
        strcpy(coin_data.candle_date_time_kst_check, coin_data.candle_date_time_kst);           // coin_data.candle_date_time_kst_check 는 1분마다 초기화되는 값
        FixChart();                                                                             // coin_data.candle_date_time_kst 는 실시간으로 초기화되는 값
        SDL_Delay(100); 
        
    }
    return;
}

void DefineChartHeight(void)
{   
    if(coin_data.trade_coef < coin_data.opening_coef)                                       // 시작가보다 현재가가 낮을 때 (음봉)
    {
        chart[i].pos.y = 600 - coin_data.opening_coef;                                      // 높이 중심 300을 기준으로 대칭시킴
                                                                                            // 음봉인 경우 시작가 > 현재가 이므로 시작가를 기준으로 막대를 표현할 사각형을 그려야함
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");                // 
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/greenline.png");      // 해당 가격, 거래량 봉의 색을 파란색으로 지정
        chart_volume[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");         // 
        coin_price_board.color.b = 225;                                                     // 우측 상단에 표시할 코인의 가격의 색을 파란색으로 지정                              
        coin_price_board.color.r = 0;                                                       //
        coin_price_board.color.g = 0;                                                       //
    }
    else if(coin_data.trade_coef > coin_data.opening_coef)                                  // 시작가보다 현재가가 높을 때 (양봉)
    {
        chart[i].pos.y = 600 - coin_data.trade_coef;                                        // 높이 중심 300을 기준으로 대칭시킴
                                                                                            // 양봉인 경우 시작가 < 현재가 이므로 현재가를 기준으로 막대를 표현할 사각형을 그려야함
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");                  //
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/redline.png");        // 해당 가격, 거래량 봉의 색을 빨간색으로 지정
        chart_volume[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");           //
        coin_price_board.color.b = 0;                                                       // 우측 상단에 표시할 코인의 가격의 색을 빨간색으로 지정                              
        coin_price_board.color.r = 225;                                                     //
        coin_price_board.color.g = 0;                                                       //
    }
    else
    {
        chart[i].pos.y = 600 - coin_data.trade_coef;                                        // 가격변동 없을 때 (차트상으로는 양봉으로 취급)
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/redline.png");
        chart_volume[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");
        coin_price_board.color.b = 255;                                                     // 우측 상단에 표시할 코인의 가격의 색을 흰색으로 지정                              
        coin_price_board.color.r = 255;                                                     //
        coin_price_board.color.g = 255;                                                     //
    }

    chart[i].pos.h = abs(round(coin_data.trade_coef - coin_data.opening_coef));         // 가격 막대 봉의 높이를 abs(현재가 - 시작가)로 지정

    if(chart[i].pos.h == 0)             // 가격변동이 없을 때 높이가 0이 되어 차트에서 보이지 않게 됨을 방지
    {
        chart[i].pos.h = 1;
    }

    chart_kkori[i].pos.y = 600 - coin_data.high_coef;           // 높이 중심 300을 기준으로 대칭시킴
    chart_kkori[i].pos.h = abs(round(coin_data.high_coef - coin_data.low_coef));        // 가격 꼬리 봉의 높이를 abs(최고가 - 최저가)로 지정

    chart_volume[i].pos.h = coin_data.candle_acc_trade_volume_coef;         // 거래량 차트의 높이는 get_info에서 변환한 거래량 값을 이용
    chart_volume[i].pos.y = SCREEN_HEIGHT - chart_volume[i].pos.h;

    if(coin_data.candle_acc_trade_volume_high <= coin_data.candle_acc_trade_volume)     // 새로운 거래량이 갱신되었을 때 이 거래량 값이 거래량 차트의 높이가 되므로 이전의 거래량 값들을 변환해줌
    {
        for(int j = 0 ; j < i ; j++)
        {
            chart_volume[j].pos.h = chart_volume[j].pos.h * coef_chart / coef_chart_before;     // 거래량의 경우 계수를 곱해 값을 조정한 다음 차트에 표현하게 됨
                                                                                                // 이전에 곱한 계수로 나누고 새로 갱신된 계수를 곱해주어 최신화
            chart_volume[j].pos.y = SCREEN_HEIGHT - chart_volume[j].pos.h;
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
    for (int i = 0; i < 40 ; i++) 
    {
        RenderChart(&(chart[i]));                   // 
        RenderChart(&(chart_kkori[i]));             // 차트를 구성하는 chart 구조체 40개를 모두 렌더링(실시간 최신화)
        RenderChart(&(chart_volume[i]));            //
    }
    RenderBoard(&left_money_board);                 // 기존에 설정한 글꼴을 그대로 사용할 TEXT 구조체 변수 2개는 이때 렌더링해줌
    RenderBoard(&coin_price_board);
    
    return;
}

void DrawPositionPicture(void)
{
    position_picture.pos.w = 200;                   // 렌더링할 이미지의 너비와 높이
    position_picture.pos.h = 120;                   //
    if(short_long_flag)     // long
    {
        position_picture.texture = IMG_LoadTexture(app.renderer, "./gfx/long.png");         
    }
    else                    // short
    {
        position_picture.texture = IMG_LoadTexture(app.renderer, "./gfx/short.png");
    }
    RenderChart(&position_picture);
}

void DrawProfitPicture(void)
{
    if((picture_percent > -10) && (picture_percent < 10))
    {
        profit_picture.texture = IMG_LoadTexture(app.renderer, "./gfx/pepe0.png");
    }
    else if((picture_percent > 10) && (picture_percent < 20))
    {
        profit_picture.texture = IMG_LoadTexture(app.renderer, "./gfx/pepe+10.png");
    }
    else if(picture_percent > 20)
    {
        profit_picture.texture = IMG_LoadTexture(app.renderer, "./gfx/pepe+20.png");
    }
    else if((picture_percent < -10) && (picture_percent > -20))
    {
        profit_picture.texture = IMG_LoadTexture(app.renderer, "./gfx/pepe-10.png");
    }
    else if(picture_percent < -20)
    {
        profit_picture.texture = IMG_LoadTexture(app.renderer, "./gfx/pepe-20.png");
    }
    SDL_SetTextureAlphaMod(profit_picture.texture, 255 - draw_count);                   // 이미지의 알파값 설정
    SDL_SetTextureBlendMode(profit_picture.texture, SDL_BLENDMODE_BLEND);               // 설정한 알파값을 투명도로 사용 
    RenderPosPic(&profit_picture);
    draw_count = draw_count + 10;                                                       // flag가 on(1)인 동안 draw_count가 증가하며 투명도 증가 

    if(draw_count == 250)                                                               // draw_count가 250이 되면 flag가 off(0)되고 이미지 렌더링을 멈춤 
    {
        draw_flag = 0;
        draw_count = 0;
    }
    
    return;
}

void DrawPositionInfo(void)
{
    if (buy_price > coin_data.trade_price)           // 매수가 > 현재가의 경우
    {
        if (short_long_flag)                         // Long 포지션의 경우 매수가 > 현재가 일때 손실 
        {
            rate_of_return_board.color.r = 0;        //
            rate_of_return_board.color.b = 225;      //
            rate_of_return_board.color.g = 0;        //
                                                     // position 구역에 들어갈 텍스트 색을 파란색으로 지정 
            profits_board.color.r = 0;               //
            profits_board.color.b = 225;             //
            profits_board.color.g = 0;               //
        }
        else                                         // Short 포지션의 경우 매수가 > 현재가 일때 수익 
        {
            rate_of_return_board.color.r = 225;      // 
            rate_of_return_board.color.b = 0;        //
            rate_of_return_board.color.g = 0;        //
                                                     // position 구역에 들어갈 텍스트 색을 붉은색으로 지정 
            profits_board.color.r = 225;             //
            profits_board.color.b = 0;               //
            profits_board.color.g = 0;               //
        }
    }
    else if (buy_price < coin_data.trade_price)      // 매수가 < 현재가의 경우
    {
        if (short_long_flag)                         // Long 포지션의 경우 매수가 < 현재가 일때 수익 
        {
            rate_of_return_board.color.r = 225;      //
            rate_of_return_board.color.b = 0;        //
            rate_of_return_board.color.g = 0;        //
                                                     // position 구역에 들어갈 텍스트 색을 붉은색으로 지정 
            profits_board.color.r = 225;             //
            profits_board.color.b = 0;               //
            profits_board.color.g = 0;               //
        }
        else                                         // Short 포지션의 경우 매수가 < 현재가 일때 손실
        {
            rate_of_return_board.color.r = 0;        //
            rate_of_return_board.color.b = 225;      //
            rate_of_return_board.color.g = 0;        //
                                                     // position 구역에 들어갈 텍스트 색을 푸른색으로 지정 
            profits_board.color.r = 0;               //
            profits_board.color.b = 225;             //
            profits_board.color.g = 0;               //
        }
    }
    else                                               // 현재가 = 매수가 인 경우 두 포지션 모두 손실이나 수익 없음
    {
        rate_of_return_board.color.r = 255;            //
        rate_of_return_board.color.b = 255;            //
        rate_of_return_board.color.g = 255;            //
                                                       // position 구역에 들어갈 텍스트 색을 흰색으로 지정 
        profits_board.color.r = 255;                   //
        profits_board.color.b = 255;                   //
        profits_board.color.g = 255;                   //
    }
    RenderPositionBoard(&buy_price_board);
    RenderPositionBoard(&liquidation_money_board);
    RenderPositionBoard(&rate_of_return_board);
    RenderPositionBoard(&profits_board);
    return;
}

void RenderPositionBoard(Text *object) 
{
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

void RenderPosPic(Entity *object)
{
    SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w),
                     &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));
}

void FixChart(void)
{
    if(i == 38)
    {             
        for(int j = 0 ; j < 39 ; j++)
        {
            chart[j] = chart[j+1];                  // n번째 봉에 n+1번째 봉의 정보를 저장 
            chart[j].pos.x -= 20;                   // x축으로 -20만큼 평행이동 
            chart_kkori[j] = chart_kkori[j+1];
            chart_kkori[j].pos.x -= 20;
            chart_volume[j] = chart_volume[j+1];
            chart_volume[j].pos.x -= 20;
        }
        i--;                                        // 더 이상 i가 증가하면 안 되므로 빼줌
    }
}