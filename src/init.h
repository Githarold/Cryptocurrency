/**
 @file      init.h
 @brief     무한 루프 진입 전 객체 및 SDL 요소 초기화를 위한 함수 선언
 @author    이승헌, 이태겸
 */

#ifndef INIT_H
#define INIT_H

#include "defs.h"

/* main.h에 정의된 전역 변수 사용 */
extern App app;
extern Data data;
extern Entity layout;
extern Entity search;
extern Entity chart[40];
extern Entity chart_kkori[40];
extern Entity chart_volume[40];
extern Text coin_price_board;
extern Text left_money_board;
extern Text buy_price_board;
extern Text liquidation_money_board;
extern Text rate_of_return_board;
extern Text profits_board;

/**
 @brief 프로그램 수행에 필요한 초기화 과정 수행

 SDL 초기화 과정을 수행한다. 또한 .png와 .jpg 파일을 사용하기 위한 작업도 수행한다.

 @return 리턴 값 없음
*/
void InitSDL(void);

/**
 @brief TTF폰트 사용을 위한 초기화 과정 수행

 TTF폰트 초기화 과정을 수행한다. 폰트는 KoPubWorld Dotum Bold를 사용하며 크기는 22로 설장한다.

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
 @brief 가격, 거래량 차트 초기화

 텍스쳐를 불러오고 위치를 초기화하며 높이를 0으로 초기화한다. chart의 텍스쳐는 가격 정보에 따라 
 달라져야 하지만 가격변동이 없을 때도 양봉으로 취급하여 양봉일때의 이미지로 설정한다. 
 텍스쳐 크기를 객체의 크기(너비와 높이)로 받아오는 것이 아니므로 너비와 높이를 따로 설정해준다.

 꼬리 차트의 경우 막대 차트의 가운데에 위치해야 하므로 막대 차트 x좌표에 width/2 를 더하여 초기화했다.
 또한 가격 차트의 y좌표는 차트를 표현할 공간의 가장 좌측 중간에서 시작해야 하므로 y좌표를 CHART_HEIGHT/2로 초기화했다. 

 하나의 객체가 차트를 표현하는 것이 아닌 배열로 이루어진 객체들이 차트를 표현하므로 모든 객체에 대해 초기화해준다.

 @return 리턴 값 없음
*/
void InitChart(void);

/**
 @brief 레이아웃 초기화

 레이아웃의 텍스쳐를 불러오고 위치를 초기화하며 폭과 높이는 CHART_WIDTH, CHART_HEIGHT으로 초기화 해준다.(차트표현할 공간의 크기)
 텍스쳐는 gfx/layout.png를 사용하고 위치는 원점(화면 좌측 상단)으로 한다.

 @return 리턴 값 없음
*/
void InitLayout(void);

/**
 @brief 스코어보드 초기화

 화면에 표시될 6개의 TEXT의 글씨 색상과 위치를 초기화한다. 
 글씨 색상은 기본적으로 검정색(이후 가격변동에 따라 색 변함), 위치는 레이아웃에 맞게 설정한다. 
 coin_price_board와 left_money_board.color에는 InitTTF에서 설정한 폰트와 그 크기로 텍스트를 보여준다.
 이외의 borad에 대해서는 폰트 크기인 22가 너무 크므로 board의 크기를 조정하여 폰트 크기를 조정한다. (폭과 높이 추가적으로 설정)

 @return 리턴 값 없음
*/
void InitBoard(void);

/**
 @brief 프로그램 조작 안내 이미지 초기화 

 사용자에게 코인의 티커를 입력받기 위해 입력방법을 설명하는 이미지를 초기화한다.

 @return 리턴 값 없음
*/
void InitSearchCoin(void);

#endif