#include <stdio.h>
#include <json-c/json.h>
 
int main(int argc, char **argv)
{
/*
{ "header": { "dataSize": 1000, "dataType": "text", "macAddress": "00:00:00:00:00" }, 
   "data": { "data1": 1, "data2": "TEST2", "comment": "This is a test!!", 
        "nameInfo": { "name": "홍길동", "regiid": "1406163000001" }, 
        "phoneNumber": [ "010-0000-0000", "010-1111-1111", "010-2222-2222" ] } }
*/
    char *buff = "{ \"header\": { \"dataSize\": 1000, \"dataType\": \"text\", \"macAddress\": \"00:00:00:00:00\" }, \"data\": { \"data1\": 1, \"data2\": \"TEST2\", \"comment\": \"This is a test!!\", \"nameInfo\": { \"name\": \"홍길동\", \"regiid\": \"1406163000001\" }, \"phoneNumber\": [ \"010-0000-0000\", \"010-1111-1111\", \"010-2222-2222\" ] } }";
    json_object *myobj, *headerobj, *dataobj;
    json_object *dobj, *dval;
    int i;
 
    /* JSON type의 데이터를 읽는다. */
    myobj = json_tokener_parse(buff);
 
    headerobj = json_object_object_get(myobj, "header");
    dataobj   = json_object_object_get(myobj, "data");
 
    /* header 영역 파싱 */
    dval = json_object_object_get(headerobj, "dataType");
    printf("dataType : %s\n", json_object_get_string(dval));
    dval = json_object_object_get(headerobj, "macAddress");
    printf("macAddress : %s\n", json_object_get_string(dval));
 
    /* data 영역 파싱 */
    dval = json_object_object_get(dataobj, "data1");
    printf("data1 : %d\n", json_object_get_int(dval));
    
    /* data.nameInfo 영역 파싱( object안에 object ) */
    dobj = json_object_object_get(dataobj, "nameInfo");
    dval = json_object_object_get(dobj, "name");
    printf("nameInfo.name : %s\n", json_object_get_string(dval));
    dval = json_object_object_get(dobj, "regiid");
    printf("nameInfo.regiid : %s\n", json_object_get_string(dval));
    
    /* data.phoneNumber 파싱 ( array type ) */
    dobj = json_object_object_get(dataobj, "phoneNumber");
    printf("nameInfo.phoneNumber is\n");
    for (i = 0; i < json_object_array_length(dobj); i++)
    {
        dval = json_object_array_get_idx(dobj, i);
        printf("   %s\n", json_object_get_string(dval));
    }
    return(0);
}