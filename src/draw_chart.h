/**
 @file      draw_chart.h
 @brief     차트 구현을 위한 함수 선언
 @author    이태겸
 */

#ifndef DRAW_CHART_H
#define DRAW_CHART_H

#include "defs.h"

/* main.h에 정의된 전역 변수 사용 */
extern short short_long_flag;
extern int check;
extern int i;
extern double buy_price;
extern double coef_chart, coef_chart_before;
extern double rate_of_return;
extern int draw_count;
extern int draw_flag;
extern double picture_percent;
extern App app;
extern Data coin_data;
extern Entity layout;
extern Entity chart[40];
extern Entity chart_kkori[40];
extern Entity chart_volume[40];
extern Entity position_picture;
extern Entity profit_picture;
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
 1분이 지났음을 확인하면 i값을 증가시켜 움직이게 될 chart를 바꿔준다. 
 FixChart를 호출하여 시간이 어느정도 흐른 후 부터는 시간이 지날 때마다 차트를 좌측으로 한 칸씩 밀어 위치를 고정시킨다. 

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

/**
 @brief 일정 시간 후에 차트 위치 고정
 시간이 지남에 따라 차트는 오른쪽으로 움직이지만 차트를 표현할 공간(가로 800, 세로 600)은 제한적이다. 따라서 차트가 x = 600를 넘어가지 못하게 고정한다.
 하나의 봉은 20의 가로 길이를 갖는다. 따라서 x = 600 까지는 봉이 40개 존재할 수 있고 총 40분간의 가격 data밖에 담지 못한다는 단점이 있다. 
 이를 보완하기 위해 40개의 봉이 모두 움직이게 되면(40분이 지나게 되면) 1분이 지날 때마다 차트가 좌측으로 한 칸씩 밀리게 하였다.

 @return 리턴 값 없음
*/
void FixChart(void);

/**
 @brief 선택하는 포지션에 따른 이미지 렌더링
 사용자가 롱 포지션을 선택하면 우측 중단에 "가즈아" 라는 이미지가, 숏 포지션을 선택하면 "누가 가즈아를 외쳤는가" 라는 문구가 담긴 이미지가 렌더링된다.
 @return 리턴 값 없음
*/
void DrawPositionPicture(void);

/**
 @brief 포지션 종료 후 수익률에 따른 이미지 선정 및 렌더링
 flag가 on(1)일 때만 작동한다.
 포지션 종료 시 수익률에 따라 다른 이미지를 렌더링한다. 수익률이 -100%~-20%, -20% ~ -10%, -10% ~ 10%,  10% ~ 20%, 20% ~ 에 따라 출력하는 이미지가 달라진다. 
 렌더링의 경우 RenderPosPic(Entity *object) 를 호출한다. 시간이 지날수록 이미지를 투명도를 점점 높여서 화면에서 사라지게 하였다. 이는 draw_flag 변수를 사용하여 구현하였다. 
 @return 리턴 값 없음
*/
void DrawProfitPicture(void);

/**
 @brief 이미지 렌더링
 @return 리턴 값 없음
*/
void RenderPosPic(Entity *object);
#endif