/**
 @file      input.c
 @brief     키보드 입력 발생 시 처리하는 함수 정의
 @author    이승헌, 이태겸
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
                // 사용한 Texture 변수들 반환
                SDL_DestroyTexture(layout.texture);
                SDL_DestroyTexture(left_money_board.texture);
                SDL_DestroyTexture(coin_price_board.texture);
                SDL_DestroyTexture(buy_price_board.texture);
                SDL_DestroyTexture(liquidation_money_board.texture);
                SDL_DestroyTexture(rate_of_return_board.texture);
                SDL_DestroyTexture(profits_board.texture);
                SDL_DestroyTexture(chart_volume->texture);
                SDL_DestroyTexture(layout.texture);
                SDL_DestroyTexture(search.texture);
                SDL_DestroyTexture(position_picture.texture);
                SDL_DestroyTexture(profit_picture.texture);

                for (i = 0 ; i < 40 ; i++)
                {
                    SDL_DestroyTexture(chart[i].texture);
                    SDL_DestroyTexture(chart_kkori[i].texture);                    
                }

                // 사용한 Surface 변수들 반환
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
                // 왼쪽 마우스 버튼 클릭 시, 좌표를 받아온다.
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;
                    printf("x : %d, y : %d\n ",mouse_x, mouse_y);
                    // 마우스로 검색창을 클릭했을 시, 티커를 검색하게 해주는 함수를 실행한다.
                    if ((mouse_x < 500) && (mouse_y < 50))
                    {
                        close_position();           // 포지션 청산
                        make_url();                 // 티커를 다시 받아 url 가공
                        InitChart();                // Chart를 다시 그린다
                    }
                    // 투자 비율 10% 선택한 경우
                    else if ((mouse_x > 800) && (mouse_y > 228) && (mouse_x < 875) && (mouse_y < 260))
                    {
                        trade_rate = 0.1;
                        trade_rate_on_flag = 1;     // 투자 비율 선택 완료
                    }
                    // 투자 비율 25% 선택한 경우
                    else if ((mouse_x > 875) && (mouse_y > 228) && (mouse_x < 950) && (mouse_y < 260))
                    {
                        trade_rate = 0.25;
                        trade_rate_on_flag = 1;     // 투자 비율 선택 완료
                    }
                    // 투자 비율 50% 선택한 경우
                    else if ((mouse_x > 950) && (mouse_y > 228) && (mouse_x < 1025) && (mouse_y < 260))
                    {
                        trade_rate = 0.5;
                        trade_rate_on_flag = 1;     // 투자 비율 선택 완료
                    }
                    // 투자 비율 100% 선택한 경우
                    else if ((mouse_x > 1025) && (mouse_y > 228) && (mouse_x < 1100) && (mouse_y < 260))
                    {
                        trade_rate = 1.0;
                        trade_rate_on_flag = 1;     // 투자 비율 선택 완료
                    }
                    // 2배 포지션을 선택한 경우
                    else if ((mouse_x > 800) && (mouse_y > 490) && (mouse_x < 875) && (mouse_y < 520))
                    {
                        leverage = 2;
                        leverage_on_flag = 1;       // 배율 선택 완료
                    }
                    // 10배 포지션을 선택한 경우
                    else if ((mouse_x > 875) && (mouse_y > 490) && (mouse_x < 950) && (mouse_y < 520))
                    {
                        leverage = 10;
                        leverage_on_flag = 1;       // 배율 선택 완료
                    }
                    // 25배 포지션을 선택한 경우
                    else if ((mouse_x > 950) && (mouse_y > 490) && (mouse_x < 1025) && (mouse_y < 520))
                    {
                        leverage = 25;
                        leverage_on_flag = 1;       // 배율 선택 완료
                    }
                    // 100배 포지션을 선택한 경우
                    else if ((mouse_x > 1025) && (mouse_y > 490) && (mouse_x < 1100) && (mouse_y < 520))
                    {
                        leverage = 100;
                        leverage_on_flag = 1;       // 배율 선택 완료
                    }                    
                    // Short 포지션을 선택한 경우
                    else if ((mouse_x > 964) && (mouse_y > 536) && (mouse_x < 1076) && (mouse_y < 584))
                    {
                        // 현재 포지션을 보유중이 아니며, 투자비율과 배율 모두 선택했을 때만 포지션 진입
                        if (!in_position_flag && trade_rate_on_flag && leverage_on_flag)
                        {
                            short_long_flag = 0;                    // Short 포지션임을 나타냄
                            open_position(trade_rate, leverage);    // 입력받은 투자 비율과 배율로 포지션 진입
                            trade_rate_on_flag = 0;                 // 사용한 플래그 초기화
                            leverage_on_flag = 0;
                        }
                    }
                    // Long 포지션을 선택한 경우
                    else if ((mouse_x > 825) && (mouse_y > 536) && (mouse_x < 938) && (mouse_y < 584))
                    {
                        // 현재 포지션을 보유중이 아니며, 투자비율과 배율 모두 선택했을 때만 포지션 진입                        
                        if (!in_position_flag && trade_rate_on_flag && leverage_on_flag)
                        {
                            short_long_flag = 1;                    // Long 포지션임을 나타냄
                            open_position(trade_rate, leverage);    // 입력받은 투자 비율과 배율로 포지션 진입
                            trade_rate_on_flag = 0;                 // 사용한 플래그 초기화
                            leverage_on_flag = 0;
                        }                        
                    }
                    // 포지션 청산 버튼을 클릭한 경우 포지션 청산 진행
                    else if ((mouse_x > 860) && (mouse_y > 722) && (mouse_x < 1046) && (mouse_y < 760))
                    {
                        if(in_position_flag)
                        {
                            draw_flag = 1;
                        }
                        close_position();
                        // DrawProfitPicture();
                        
                    }
                }
                break;
                
            default:
                break;
        }
    }

    return;
}