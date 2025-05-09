#ifndef JSON_BUILDER_H
#define JSON_BUILDER_H

char* json_create();
void json_add_string(char** json, const char* key, const char* value);
void json_add_int(char** json, const char* key, int value);
void json_finalize(char** json);

#endif