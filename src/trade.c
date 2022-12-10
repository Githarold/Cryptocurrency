/**
 @file      trade.c
 @brief     주문 처리 및 잔고 관리 등을 정의한 소스파일
 @author    이승헌
 */

#include "trade.h"

void open_position(float trade_rate, int leverage)
{
    in_position_flag = 1;

    buy_price = coin_data.trade_price;                    // 체결 가격 저장
    trade_price = (1 - 0.02 * leverage) * left_money * trade_rate;              // 투자 금액 계산  수수료 적용
    left_money -= trade_price;                                                  // 잔고 최신화
    if (short_long_flag)    // Long position일 경우의 청산 가격 정의
    {
        liquidation_price = buy_price - buy_price/leverage;
    }
    else                    // Short position일 경우의 청산 가격 정의
    {
        liquidation_price = buy_price + buy_price/leverage;
    }
    
    return;
}

void close_position(void)
{
    left_money += (1 - 0.1 * leverage) * (trade_price + profits);
    profits = 0.0;
    rate_of_return = 0.0;
    trade_price = 0;

    // + 화면에 띄우고있는 가격들 없애기

    in_position_flag = 0;
    printf("Liquidation!!!!\n");

    return;
}

void calculate_position(int leverage)
{
    if (short_long_flag)    // Long position일 경우
    {
        profits = (coin_data.trade_price - buy_price) * leverage * trade_price / buy_price;

        if (coin_data.trade_price < liquidation_price)
        {
            profits = -trade_price;
            close_position();
        }
    }
    else                    // Short position일 경우
    {
        profits = (buy_price - coin_data.trade_price) * leverage * trade_price / buy_price;

        if (coin_data.trade_price > liquidation_price)
        {
            profits = -trade_price;
            close_position();
        }
    }

    rate_of_return = profits * 100 / trade_price;

    return;
}