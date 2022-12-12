/**
 @file      init.h
 @brief     무한 루프 진입 전 객체 및 SDL 요소 초기화를 위한 함수 선언
 @author    이승헌
*/

#ifndef INIT_H
#define INIT_H

#include "defs.h"

extern App app;
extern Data data;
extern Entity chart[30];
extern Entity chart_kkori[30];
extern Entity chart_volume[30];
extern Entity layout;

extern Text coin_price_board;
extern Text left_money_board;
extern Text buy_price_board;
extern Text liquidation_money_board;
extern Text rate_of_return_board;
extern Text profits_board;

/* main.h에 정의된 전역 변수 사용 */
/**
 @brief 프로그램 수행에 필요한 초기화 과정 수행

 SDL 초기화 과정을 수행한다. 또한 .png와 .jpg 파일을 사용하기 위한 작업도 수행한다.

 @return 리턴 값 없음
*/
void InitSDL(void);

/**
 @brief TTF폰트 사용을 위한 초기화 과정 수행

 TTF폰트 초기화 과정을 수행한다.

 @return 리턴 값 없음
*/
void InitTTF(void);

/**
 @brief 프로그램 종료에 필요한 루틴을 수행하고 프로그램 종료

 프로그램 종료 전 전역변수 \ref app 의 \ref App.renderer 와 \ref App.window 를
 닫고 프로그램을 종료한다.

 @return 리턴 값 없음
*/
void QuitSDL(int flag);

/**
 @brief 연 폰트 파일을 닫고 TTF 엔진 종료

 @return 리턴 값 없음
*/
void QuitTTF(void);

/**
 @brief 전역 변수 메모리 내용 초기화

 모든 전역 변수의 메모리 내용을 0으로 초기화한다.

 @return 리턴 값 없음
*/
void InitMemorySet(void);

/**
 @brief 차트를 화면에 표시하기 전 초기화

 차트를 그리기 위해 초기화한다.

 @return 리턴 값 없음
*/
void InitChart(void);

void InitLayout(void);

void InitScoreBoard(void);

#endif