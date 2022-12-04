/**
 @file      get_info.c
 @brief     url 생성 및 데이터 수신 함수를 정의한 소스 파일
 @author    이승헌
 */
#include "get_info.h"

void make_url(char *url) {
    char ticker[10] = "";

    printf("What's ticker? : ");
    scanf(" %s", ticker);
    strncat(url, ticker, strlen(ticker));

    return;
}

void get_info(const char* url) {
    FILE *fp = fopen("result.json", "w");
    if (fp == NULL) {
        printf("fopen ERR\n");
        return;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("curl ERR\n");
        return;
    }

    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);      // 표준출력으로 나오는 curl의 결과를 파일로 바꾼다
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    fclose(fp);
    json_object *result = json_object_from_file("result.json");
    json_object *data, *price, *fluctuate_rate, *trade_volume;

    data = json_object_array_get_idx(result, 0);
    price = json_object_object_get(data, "trade_price");
    fluctuate_rate = json_object_object_get(data, "signed_change_rate");
    trade_volume = json_object_object_get(data, "acc_trade_price_24h");


    //########################

    coin_data.price = atof(json_object_get_string(price));                  // coin_data 구조체의 멤버를 실시간 값으로 계속 초기화 + 실수형 데이터 타입으로 변환
    coin_data.fluctate_rate = atof(json_object_get_string(fluctuate_rate));
    coin_data.trade_volume = atof(json_object_get_string(trade_volume));
    // printf("가격 : %d원\n변동률 : %.2lf%%\n거래량 : %d원\n\n", coin_data.price, coin_data.fluctate_rate, coin_data.trade_volume);

    if(coin_data.price >= coin_data.ath_1m)     // 고점 갱신할 때 ath_1m 최신화
    {
        coin_data.ath_1m = coin_data.price;
    }
    if(coin_data.price <= coin_data.atl_1m)     // 저점 갱신할 때 atl_1m 최신화
    {
        coin_data.atl_1m = coin_data.price;
    }
    if(coin_data.start_price == 0)              // 프로그램 켰을 때 시작가 저장 
    {
        coin_data.start_price = coin_data.price;
    }
    coef = (SCREEN_HEIGHT/2) / coin_data.start_price;
    
    coin_data.price_coef = coin_data.price*coef;
    coin_data.ath_coef = coin_data.ath_1m*coef;
    // printf("%.1lf\n",(double)SDL_GetTicks()/1000);
    // if(SDL_GetTicks() == 60)
    //     {
            
    //     }

    return;
}
