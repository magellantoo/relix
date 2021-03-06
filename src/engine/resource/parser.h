#ifndef __PARSER_H__
#define __PARSER_H__

// Library
#include <stdio.h>

// Engine
#include "constants.h"
#include "list/array.h"
#include "string/string.h"

// Value types
#define JSON_NULL 0
#define JSON_STRING 1
#define JSON_INT 2
#define JSON_OBJ 3
#define JSON_ARRAY 4
#define JSON_TRUE 5
#define JSON_FALSE 6

typedef struct JsonVal {
} JsonVal;

// Resource Node
typedef struct JsonNode {
    int type;
    void *data;
} JsonNode;

typedef struct JsonObjProp {
    String *key;
    JsonNode *value;
} JsonObjProp;

typedef struct JsonObjData {
    Array props;
} JsonObjData;

int closeJsonNode(JsonNode *node);
JsonNode *parseFile(FILE *file);

JsonNode *getObjValue(JsonNode *node, char *key);

#endif

