/**
 @file      defs.h
 @brief     데이터타입 및 상수 정의
 @author    이승헌
*/

#ifndef DEFS_H
#define DEFS_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "curl/curl.h"
#include "json-c/json.h"
#include "time.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_rect.h"

#define BUFF_SIZE 1024      // 문자열 버퍼 크기
#define SCREEN_WIDTH 640    // 화면 너피(픽셀)
#define SCREEN_HEIGHT 480   // 화면 높이(픽셀)

/* 구조체 정의 */
/**
 @brief  App: 프로그램 전체적으로 관리해야 하는 요소를 모아 놓은 구조체
*/
typedef struct {
    SDL_Renderer *renderer; /**< 렌더링 관리를 위한 구조체*/
    SDL_Window *window;     /**< 창 관리를 위한 구조체*/
    TTF_Font *font;         /**< 폰트 관리를 위한 구조체*/
} App;

/**
 @brief  Text: 게임 내에 문자열을 표시할 경우 문자열을 나타내는 구조체(스코어보드)
*/
typedef struct {
    SDL_Rect pos;           /**< 직사각형 객체의 상태를 나타내기 위한 구조체*/
    SDL_Color color;        /**< 글씨 색깔을 저장하는 구조체*/
    SDL_Surface *surface;   /**< 폰트 렌더링을 위해 필요한 구조체*/
    SDL_Texture *texture;   /**< 텍스쳐를 담고 있는 구조체 (문자열을 surface로 만들고,
                                그 후 texture에 저장)*/
} Text;

/**
 @brief  Data : 코인의 가격, 변동량, 거래량 등의 정보가 담겨있는 구조체
*/
typedef struct {
    unsigned long price;            // 가격 정보
    unsigned long fluctate_rate;    // 최근 24시간 변동률
    unsigned long units_traded;     // 00시 기준 거래량
    unsigned long date;             // 타임 스탬프
} Data;

#endif