/**
 @file      get_info.c
 @brief     url 생성 및 데이터 수신 함수를 정의한 소스 파일
 @author    이승헌
 */
#include "get_info.h"

void make_url(char *url) {
    char ticker[10] = "";

    printf("What's ticker? : ");
    fgets(ticker, 10, stdin);
    strcat(url, ticker);

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

    printf("url : %s", url);      // debug

    json_object *result = json_object_from_file("result.json");
    json_object *data, *price, *fluctuate_rate;

    data = json_object_object_get(result, "data");
    price = json_object_object_get(data, "closing_price");
    fluctuate_rate = json_object_object_get(data, "fluctate_rate_24H");

    printf("price : %s원\n", json_object_get_string(price));
    printf("변동률 : %s%%\n", json_object_get_string(fluctuate_rate));

    return;
}
