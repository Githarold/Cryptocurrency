/**
 @file      trade.c
 @brief     주문 처리 및 잔고 관리 등을 정의한 소스파일
 @author    이승헌
 */

#include "trade.h"

void open_position(float trade_rate, int leverage)
{
    in_position_flag = 1;   // in_position_flag를 1로 변경하여 포지션을 가지고 있음을 표시

    buy_price = coin_data.trade_price;                                  // 포지션 진입 시 체결 가격 저장
    trade_money = (1 - 0.0002 * leverage) * left_money * trade_rate;    // 투자금액 계산 시 (0.02% * 배율)의 수수료 적용(Binance 선물거래 기준)
    left_money *= (1 - trade_rate);                                     // 잔고를 투자금액만큼 빼주어 최신화

    if (short_long_flag)    // Long position일 경우의 청산 가격 설정
    {
        liquidation_price = buy_price - buy_price/leverage;
    }
    else                    // Short position일 경우의 청산 가격 설정
    {
        liquidation_price = buy_price + buy_price/leverage;
    }
    
    return;
}

void close_position(void)
{
    // 포지션 청산 시 잔고에 (투자금 + 수익금)을 더해줌. (0.1 * 배율)의 수수료 적용(Binance 선물거래 기준)
    left_money += ((1 - 0.001 * leverage) * (trade_money + profits));
    
    profits = 0.0;          //
    rate_of_return = 0.0;   // 수익금, 수익률 및 투자금액 초기화
    trade_money = 0;        //

    in_position_flag = 0;   // 포지션을 가지고 있지 않음을 표시

    return;
}

void calculate_position(int leverage)
{
    if (short_long_flag)    // Long position일 경우
    {
        // 수익금 계산 부분. (현재가 - 체결가)에 배율을 곱하고 투자금액 대비 체결가(= 수량)을 곱해줌
        profits = (coin_data.trade_price - buy_price) * leverage * trade_money / buy_price;

        if (coin_data.trade_price < liquidation_price)  // 청산 가격보다 떨어져 청산될 경우
        {
            profits = -trade_money;                     // 투자금액 + 수익금이 0이 되도록 수익금 조정
            close_position();                           // 포지션 청산
        }
    }
    else                    // Short position일 경우
    {
        // 수익금 계산 부분. Long 포지션 수익금 계산에 부호만 바꾸어줌
        profits = (buy_price - coin_data.trade_price) * leverage * trade_money / buy_price;

        if (coin_data.trade_price > liquidation_price)  // 청산 가격보다 가격이 올라 청산될 경우
        {
            profits = -trade_money;                     // 투자금액 + 수익금이 0이 되도록 수익금 조정
            close_position();                           // 포지션 청산
        }
    }

    rate_of_return = profits * 100 / trade_money;       // 수익률 = (수익금 / 투자금액) * 100

    return;
}