#include <stdio.h>
#include <curl/curl.h>
#include "BTC.h"

extern char URL[100];

int main(void) {

    CURL *curl = curl_easy_init();

    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, URL[100]);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    else {
        printf("[error] curl init failed\n");   // test
        return 1;
    }

    return 0;
}