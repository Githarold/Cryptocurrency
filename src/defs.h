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
#include "assert.h"
#include "curl/curl.h"
#include "json-c/json.h"
#include "math.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_timer.h"

#define BUFF_SIZE 1024          // 문자열 버퍼 크기 800, 600
#define SCREEN_WIDTH 1100       // 화면 너비(픽셀)
#define SCREEN_HEIGHT 768       // 화면 높이(픽셀)
#define TICK_INTERVAL 60000 
#define CHART_WIDTH 800         // 차트 표현할 공간 너비(픽셀)
#define CHART_HEIGHT 600        // 차트 표현할 공간 높이(픽셀)
#define URL "https://api.upbit.com/v1/candles/minutes/1?market=KRW-"        // 파싱할 데이터가 담긴 URL

/* 구조체 정의 */
/**
 @brief  App : 프로그램 전체적으로 관리해야 하는 요소를 모아 놓은 구조체
*/
typedef struct {
    SDL_Renderer *renderer; // 렌더링 관리를 위한 구조체
    SDL_Window *window;     // 창 관리를 위한 구조체
    TTF_Font *font;         // 폰트 관리를 위한 구조체
} App;

/**
 @brief  Text : 프로그램 내에 문자열을 표시할 경우 문자열을 나타내는 구조체
*/
typedef struct {
    SDL_Rect pos;               // 직사각형 객체의 상태를 나타내기 위한 구조체
    SDL_Color color;            // 글씨 색깔을 저장하는 구조체
    SDL_Surface *surface;       // 폰트 렌더링을 위해 필요한 구조체
    SDL_Texture *texture;       // 텍스쳐를 담고 있는 구조체 (문자열을 surface로 만들고 texture에 저장)
    char value_text[BUFF_SIZE]; // 문자열을 텍스쳐로 만들기 위해 필요한 문자열
} Text;

/**
 @brief  Rect : 차트를 만들기 위한 직사각형의 texture 정보를 담고있는 구조체
*/
typedef struct {
    SDL_Texture *texture;   // 텍스쳐를 담고 있는 구조체 (문자열을 surface로 만들고 texture에 저장)
} RECT;

/**
 @brief  Data : 캔들에서의 코인의 가격정보, 시간 정보 등이 담겨있는 구조체
*/
typedef struct {
    char candle_date_time_kst[20];              // 캔들 기준 시각
    char candle_date_time_kst_check[20];        // for count
    double candle_acc_trade_volume;             // 누적 거래량  
    double candle_acc_trade_volume_high;        // 최대 거래량 
    double candle_acc_trade_volume_coef;        // 변환 후 거래량
    double opening_price;                       // 캔들의 시작가
    double high_price;                          // 캔들의 고가
    double low_price;                           // 캔들의 저가
    double trade_price;                         // 코인의 시장가
    double opening_coef;                        // 변환 후 시작가
    double high_coef;                           // 변환 후 고가
    double low_coef;                            // 변환 후 저가
    double trade_coef;                          // 변환 후 시장가
    double pro_opening_price;                   // 프로그램 시작했을 때 가격
} Data;

typedef struct {
    SDL_Rect pos;           // 직사각형 객체의 상태를 나타내기 위한 구조체 여기에 객체의 좌표, 위치 저장
    SDL_Texture *texture;   // 텍스쳐를 담고 있는 구조체 (그림파일을 열어 텍스쳐에 저장)
} Entity;

#endif