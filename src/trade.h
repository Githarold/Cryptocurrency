/**
 @file      trade.h
 @brief     주문 처리 및 잔고 관리 함수 선언
 @author    이승헌
 */

#ifndef TRADE_H
#define TRADE_H

#include "defs.h"
#include "init.h"
#include "input.h"
#include "draw_chart.h"

/* trade.c에서 사용할 변수 정의 */
double profits;                    // 수익금 
double buy_price;                  // 체결 가격
double trade_money;                // position에 투입한 금액
double rate_of_return;             // 수익률
double liquidation_price;          // 청산 가격(배율에 따라 일정 수익률 이하로 떨어지면 투자금액 청산)
extern double picture_percent;

/* main.h에 정의된 전역 변수 사용 */
extern short in_position_flag, short_long_flag;           // 0 : Short / 1 : Long
extern double left_money;                                 // 보유중인 잔고
extern Data coin_data;                                    // 실시간 코인 정보
extern Text profits_board;                                // 수익금을 표시하기 위한 구조체
extern Text buy_price_board;                              // 체결 가격을 표시하기 위한 구조체
extern Text rate_of_return_board;                         // 수익률을 표시하기 위한 구조체
extern Text liquidation_money_board;                      // 청산 가격을 표시하기 위한 구조체


/**
 @brief position에 들어갈 때의 정보들을 처리한다.

 투자 비율과 배율을 인자로 받아 체결가, 투입 가격, 청산가, 잔고를 계산

 @return 리턴 값 없음
*/
void open_position(float, int);

/**
 @brief 사용자가 포지션을 청산할 때 잔고 최신화 및 수익금 초기화를 진행한다.

 잔고에 (투입 금액 + 수익금)을 더해주고, 수익금과 수익률을 초기화

 @return 리턴 값 없음
*/
void close_position(void);

/**
 @brief 포지션을 가지고 있을 때, 수익률과 수익금을 계산한다.

 수익률과 수익금 계산, 그리고 청산 유무를 확인하여 청산 시 close_position 함수를 호출

 @return 리턴 값 없음
*/
void calculate_position(int);

#endif