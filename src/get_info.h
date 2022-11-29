#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

#define BUFF_SIZE 1024

void make_url(char *);
void get_info(const char*);