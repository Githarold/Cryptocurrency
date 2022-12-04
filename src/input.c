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
                QuitSDL(0);
                break;
            // 마우스 이벤트 발생
            case SDL_MOUSEBUTTONUP:
                SDL_GetMouseState(&mouse_x, &mouse_y);
                break;
            default:
                break;
        }
    }

    return;
}