/**
 @file      draw_chart.h
 @brief     차트 구현을 위한 함수 선언
 @author    이태겸
*/
#ifndef DRAW_CHART_H
#define DRAW_CHART_H

#include "defs.h"

/* main.h에 정의된 전역 변수 사용 */
extern int check;
extern Data coin_data;
extern App app;
extern int i;
extern short short_long_flag;
extern double buy_price;
extern double coef_chart, coef_chart_before;
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

/**
 @brief 배경을 흰색으로 지정하고 화면에 렌더링된 모든 요소 제거

 배경 내용을 모두 지우고 흰색으로 칠한다. main() 내 무한 루프에서 가장 먼저
 호출한다.

 @return 리턴 값 없음
*/
void ClearWindow(void);

/**
 @brief 화면에 렌더링 결과 표시(보여주기)

 \ref Draw 모듈에서 수행한 렌더링 결과를 화면에 표시한다.

 @return 리턴 값 없음
*/
void ShowWindow(void);

/**
 @brief 업비트에서의 시간 측정(업비트 시간으로 1분이 지났는지 확인)

 받아오는 데이터 중 시간데이터(candle_date_time_kst, 문자열)를 이전값과 비교
 1분이 지났음을 확인하면 움직이게 될 chart를 바꿔준다.

 @return 리턴 값 없음
*/
void checktime(void);

/**
 @brief 봉의 높이 결정 (가격차트의 막대와 꼬리, 거래량 그래프의 막대)

 lsd2 window는 좌측 상단을 기준으로 -y로 갈수록 y값이 증가하고 +x로 갈수록 x값이 증가한다. 차트는 가격의 높낮이를 
 바탕으로 하므로 좌표의 변환 또한 필요하다. 
 
 이미지는 x,y좌표 기준으로 우측 하단에 출력되므로 실시간 데이터를 기반으로 차트를 매끄럽게 움직이기 위해서는 
 가격이 상승할 때는 현재가를 기준으로, 가격이 하락할 때는 시작가를 기준으로 abs(현재가 - 시작가)만큼을 
 막대의 높이로 가져야 한다. 가격 변동이 생길 시 움직인다.(가격차트에서 막대)

 꼬리 막대는 고가의 좌표를 기준으로 (고가 - 저가)를 높이로 가지며 고가, 저가가 새로 갱신되었을 때 움직인다. 

 거래량의 경우 최고 거래량이 거래량 차트의 높이를 꽉 채우게 된다. 이전의 최고 거래량을 기준으로 나머지 거래량 차트가 그려지게 되며
 최고 거래량이 갱신되었을 경우 그 거래량이 차트의 높이를 채우게 되고 나머지 거래량은 갱신된 최고 거래량에 대한 비율로 줄어들게 된다.

 가격 차트에서 막대, 꼬리 그리고 거래량 차트에서 막대는 가격이 상승하거나 변하지 않을 때 붉은색(양봉), 
 가격이 하락할 때 푸른색(음봉)을 띄게 된다. 
 @return 리턴 값 없음
*/
void DefineChartHeight(void);

/**
 @brief Entity 구조체 렌더링

 Entity를 렌더링한다. 대상 Entity 는 적절하게 초기화되어 \ref Entity.texture 와
 \ref Entity.pos 의 위치 (x, y)가 설정되어 있어야 한다.
 SDL_RenderCopy를 사용하여 이전에 설정한 이미지를 dst만큼의 사각형에 출력하게 된다. 
 하나의 이미지로 다양한 사각형을 표현하기 위해 SDL_RenderCopy함수만 사용하였다.
 실시간 가격에 의해 기준점과 높이가 결정되고 이를 바탕으로 동적인 차트를 구현하였다.

 @return 리턴 값 없음
*/
void RenderChart(Entity *object);

/**
 @brief 폰트 크기에 맞는 Text 구조체 렌더링

 Text를 렌더링한다. 대상 Text 는 적절하게 초기화되어 \ref Text.texture 와 \ref
 Text.pos 의 위치 (x, y)가 설정되어 있어야 한다. 기본 폰트의 크기가 22로 지정되어 있고
 이 크기에 적합한 Text만을 렌더링한다. (실시간 가격 Text, 남은 돈 Text)
 
 @return 리턴 값 없음
*/
void RenderBoard(Text *object);

/**
 @brief 프로그램이 켜진 상태에서 차트의 구성요소 렌더링
 RenderChart와 RenderBoard를 호출하여 차트의 구성요소인 막대(거래량), 막대(가격), 꼬리(가격), 
 코인의 실시간 가격 Text, 남은 돈 Text를 렌더링한다.

 @return 리턴 값 없음
*/
void DrawChart(void);

/**
 @brief 설정한 폰트 크기에 맞지 않은 Text 구조체 렌더링
 하나의 App 구조체를 사용하다보니 폰트의 크기를 하나로밖에 설정할 수 없었고 이를 보완하기 위해
 차트 막대를 표현한 방법을(이미지를 설정한 크기 dest 에 끼워넣기) 사용하여 폰트의 크기를 강제로 줄였다. 
 이는 프로그램 실행 시 나오는 화면의 우측 하단에 있는 position 부분에 보여진다.

 @return 리턴 값 없음
*/
void RenderPositionBoard(Text *object);

/**
 @brief position을 들어간 상태에서 position의 구성요소 렌더링
 position을 잡았는지 flag를 통해 확인하여 RenderPositionBoard를 호출 후, position의 구성요소 렌더링

 @return 리턴 값 없음
*/
void DrawPositionInfo(void);

#endif