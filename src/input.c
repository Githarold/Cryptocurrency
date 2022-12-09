/**
 @file      input.c
 @brief     키보드 입력 발생 시 처리하는 함수 정의
 @author    이태겸
 */

#include "input.h"

void GetInput(void) {
    SDL_Event event;

    // SDL_PollEvent() 함수는 이벤트 큐에 남아 있는 이벤트를 가져옴
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // 창닫기 버튼을 누른 경우
            case SDL_QUIT:
                SDL_DestroyTexture(layout.texture);
                for (i=0 ; i<60 ; i++)
                {
                    SDL_DestroyTexture(chart[i].texture);
                    SDL_DestroyTexture(chart_kkori[i].texture);
                }
                QuitSDL(0);
                break;
            // 마우스 이벤트 발생
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;
                    // 마우스로 검색창을 클릭했을 시, 티커를 검색하게 해주는 함수를 실행한다.
                    if ((mouse_x < 800) && (mouse_y < 50)) {
                        make_url();
                        printf("%s\n%s\n", ticker, url);
                    }
                }
                // SDL_GetMouseState(&mouse_x, &mouse_y);
                printf("%d %d\n", mouse_x, mouse_y);
                break;
            case SDL_MOUSEWHEEL:
                if(event.wheel.y > 0)
                {
                    // scroll up, 차트 창이 나타내는 가격 범위가 줄어들어야함 -> 최대 최소 퍼센트값 감소
                    max_min_percent -= 0.1;
                    if (max_min_percent < 1)
                    {
                        max_min_percent = 1;
                    }
                }
                else if(event.wheel.y < 0)
                {
                    // scroll down// 차트 창이 나타내는 가격 범위가 늘어나야함 -> 최대 최소 퍼센트값 증가
                    max_min_percent += 0.1;
                    if (max_min_percent > 7)
                    {
                        max_min_percent = 7;
                    }
                }
            default:
                break;
        }
    }

    return;
}