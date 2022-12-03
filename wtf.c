#include <curl/curl.h>

int main(void) {

CURL *hnd = curl_easy_init();

curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
curl_easy_setopt(hnd, CURLOPT_URL, "https://api.upbit.com/v1/ticker?markets=KRW-btc");

struct curl_slist *headers = NULL;
headers = curl_slist_append(headers, "accept: application/json");
curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

CURLcode ret = curl_easy_perform(hnd);
}