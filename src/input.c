/**
 @file      input.c
 @brief     키보드 입력 발생 시 처리하는 함수 정의
 @author    이태겸
 */

#include "input.h"

void GetInput(void) {
    SDL_Event event;

    // SDL_PollEvent() 함수는 이벤트 큐에 남아 있는 이벤트를 가져옴
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // 창닫기 버튼을 누른 경우
            case SDL_QUIT:
                SDL_DestroyTexture(layout.texture);
                for (i=0 ; i<40 ; i++)
                {
                    SDL_DestroyTexture(chart[i].texture);
                    SDL_DestroyTexture(chart_kkori[i].texture);                    
                }
                SDL_DestroyTexture(left_money_board.texture);
                SDL_DestroyTexture(coin_price_board.texture);
                SDL_DestroyTexture(buy_price_board.texture);
                SDL_DestroyTexture(liquidation_money_board.texture);
                SDL_DestroyTexture(rate_of_return_board.texture);
                SDL_DestroyTexture(profits_board.texture);
                
                SDL_DestroyTexture(chart_volume->texture);
                SDL_DestroyTexture(layout.texture);

                SDL_FreeSurface(left_money_board.surface);
                SDL_FreeSurface(coin_price_board.surface);
                SDL_FreeSurface(buy_price_board.surface);
                SDL_FreeSurface(liquidation_money_board.surface);
                SDL_FreeSurface(rate_of_return_board.surface);
                SDL_FreeSurface(profits_board.surface);
                QuitSDL(0);
                break;

            // 마우스 이벤트 발생
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;
                    printf("x = %d, y = %d\n", mouse_x, mouse_y);
                    // 마우스로 검색창을 클릭했을 시, 티커를 검색하게 해주는 함수를 실행한다.
                    if ((mouse_x < 500) && (mouse_y < 50))
                    {
                        close_position();
                        make_url();
                        InitChart();
                    }
                    // 투자 비율 10% 선택한 경우
                    else if ((mouse_x > 800) && (mouse_y > 228) && (mouse_x < 875) && (mouse_y < 260))
                    {
                        trade_rate = 0.1;
                        trade_rate_on_flag = 1;
                    }
                    // 투자 비율 25% 선택한 경우
                    else if ((mouse_x > 875) && (mouse_y > 228) && (mouse_x < 950) && (mouse_y < 260))
                    {
                        trade_rate = 0.25;
                        trade_rate_on_flag = 1;
                    }
                    // 투자 비율 50% 선택한 경우
                    else if ((mouse_x > 950) && (mouse_y > 228) && (mouse_x < 1025) && (mouse_y < 260))
                    {
                        trade_rate = 0.5;
                        trade_rate_on_flag = 1;
                    }
                    // 투자 비율 100% 선택한 경우
                    else if ((mouse_x > 1025) && (mouse_y > 228) && (mouse_x < 1100) && (mouse_y < 260))
                    {
                        trade_rate = 1.0;
                        trade_rate_on_flag = 1;
                    }
                    // 2배 포지션을 선택한 경우
                    else if ((mouse_x > 800) && (mouse_y > 490) && (mouse_x < 875) && (mouse_y < 520))
                    {
                        leverage = 2;
                        leverage_on_flag = 1;
                    }
                    // 10배 포지션을 선택한 경우
                    else if ((mouse_x > 875) && (mouse_y > 490) && (mouse_x < 950) && (mouse_y < 520))
                    {
                        leverage = 10;
                        leverage_on_flag = 1;
                    }
                    // 25배 포지션을 선택한 경우
                    else if ((mouse_x > 950) && (mouse_y > 490) && (mouse_x < 1025) && (mouse_y < 520))
                    {
                        leverage = 25;
                        leverage_on_flag = 1;
                    }
                    // 100배 포지션을 선택한 경우
                    else if ((mouse_x > 1025) && (mouse_y > 490) && (mouse_x < 1100) && (mouse_y < 520))
                    {
                        leverage = 100;
                        leverage_on_flag = 1;
                    }                    
                    // Short 포지션을 선택한 경우
                    else if ((mouse_x > 964) && (mouse_y > 536) && (mouse_x < 1076) && (mouse_y < 584))
                    {
                        if (!in_position_flag && trade_rate_on_flag && leverage_on_flag)
                        {
                            short_long_flag = 0;
                            open_position(trade_rate, leverage);
                            trade_rate_on_flag = 0;
                            leverage_on_flag = 0;
                        }
                    }
                    // Long 포지션을 선택한 경우
                    else if ((mouse_x > 825) && (mouse_y > 536) && (mouse_x < 938) && (mouse_y < 584))
                    {
                        if (!in_position_flag && trade_rate_on_flag && leverage_on_flag)
                        {
                            short_long_flag = 1;
                            open_position(trade_rate, leverage);
                            trade_rate_on_flag = 0;
                            leverage_on_flag = 0;
                        }                        
                    }
                    // 포지션 청산을 선택한 경우
                    else if ((mouse_x > 830) && (mouse_y > 737) && (mouse_x < 1075) && (mouse_y < 764))
                    {
                        close_position();
                    }
                }
                break;
            
            default:
                break;
        }
    }

    return;
}