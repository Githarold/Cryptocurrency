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
    strncat(url, URL_OPTION, strlen(URL_OPTION));

    return;
}

void get_info(const char* url) {

    // curl_perform의 결과로 나오는 표준 출력을 result.json 파일에 저장하기 위해 fopen() 함수를 사용한다.
    FILE *fp = fopen("result.json", "w");
    if (fp == NULL) {
        printf("fopen ERR\n");
        return;
    }

    // CURL 구조체 타입의 curl 객체 생성. 생성 실패 시 에러코드 출력 후 종료한다.
    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("curl ERR\n");
        return;
    }

    // 표준출력으로 나오는 curl_perform의 결과를 WRITEDATA 옵션의 easy_setopt 함수를 통해 버퍼 fp에 저장한다.
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // 열었던 파일을 fclose() 함수를 통해 닫아준다.
    fclose(fp);

    // 결과로 저장된 json파일을 파싱할 수 있도록 json_object 구조체의 객체들을 만든다.
    json_object *result = json_object_from_file("result.json");
    json_object *data, *trade_price, *opening_price, *high_price, *low_price, *candle_acc_trade_volume, *candle_date_time_kst;

    // 각 key값에 맞는 값들을 받아오는 데이터 파싱을 진행한다.
    data = json_object_array_get_idx(result, 0);
    trade_price = json_object_object_get(data, "trade_price");
    opening_price = json_object_object_get(data, "opening_price");
    high_price = json_object_object_get(data, "high_price");
    low_price = json_object_object_get(data, "low_price");
    candle_acc_trade_volume = json_object_object_get(data, "candle_acc_trade_volume");
    candle_date_time_kst = json_object_object_get(data, "candle_date_time_kst");
    // coin_data.candle_date_time_kst = candle_date_time_kst;
    

    // coin_data 구조체의 멤버들을 실시간 값으로 초기화 + 실수형 데이터 타입으로 변환해준다.
    coin_data.trade_price = atof(json_object_get_string(trade_price));
    coin_data.opening_price = atof(json_object_get_string(opening_price));
    coin_data.high_price = atof(json_object_get_string(high_price));
    coin_data.low_price = atof(json_object_get_string(low_price));
    coin_data.candle_acc_trade_volume = atof(json_object_get_string(candle_acc_trade_volume));
    // coin_data.candle_date_time_kst[19] = *json_object_get_string(candle_date_time_kst); 
    strcpy(coin_data.candle_date_time_kst, json_object_get_string(candle_date_time_kst));

    // if(coin_data.candle_date_time_kst_check == NULL)
    if(check == 0)
    {
        strcpy(coin_data.candle_date_time_kst_check, coin_data.candle_date_time_kst);
        printf("Let's");
        check++;
        
    }
    if(check == 1)
    {
        coin_data.pro_opening_price = coin_data.trade_price;
        printf(" go!\n");
        check++;
    }

    // 차트의 변동을 명확하게 보여주기 위해 변환을 실행한다.
    coin_data.low_coef = (coin_data.low_price-0.97*coin_data.pro_opening_price)*CHART_HEIGHT*((double)100/6)/coin_data.pro_opening_price;
    coin_data.high_coef = (coin_data.high_price-0.97*coin_data.pro_opening_price)*CHART_HEIGHT*((double)100/6)/coin_data.pro_opening_price;
    coin_data.trade_coef = (coin_data.trade_price-0.97*coin_data.pro_opening_price)*CHART_HEIGHT*((double)100/6)/coin_data.pro_opening_price;
    coin_data.opening_coef = (coin_data.opening_price-0.97*coin_data.pro_opening_price)*CHART_HEIGHT*((double)100/6)/coin_data.pro_opening_price;
    
    return;
}
