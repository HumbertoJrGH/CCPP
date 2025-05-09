#include "json_builder.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define JSON_INIT_SIZE 256

char *json_create()
{
	char *json = (char *)malloc(JSON_INIT_SIZE);
	if (!json)
		return NULL;
	strcpy(json, "{");
	return json;
}

void json_add_string(char **json, const char *key, const char *value)
{
	if (!json || !*json)
		return;

	if ((*json)[strlen(*json) - 1] != '{')
		strcat(*json, ", ");

	char entry[256];

	snprintf(entry, sizeof(entry), "\"%s\": \"%s\"", key, value);
	strcat(*json, entry);
}

void json_add_int(char **json, const char *key, int value)
{
	if (!json || !*json)
		return;

	if ((*json)[strlen(*json) - 1] != '{')
		strcat(*json, ", ");

	char entry[128];
	snprintf(entry, sizeof(entry), "\"%s\": %d", key, value);
	strcat(*json, entry);
}

void json_finalize(char **json)
{
	if (!json || !*json)
		return;
	strcat(*json, " }");
}
