#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include "../json/json_builder.h"

#define COMPLEXITY 1000000000

void handle_status(int client_socket, const char *request)
{
	(void)request;
	char *json = json_create();
	json_add_string(&json, "status", "online");
	json_add_string(&json, "message", "Server is running");
	json_finalize(&json);

	char response[1024];
	snprintf(response, sizeof(response),
				"HTTP/1.1 200 OK\r\n"
				"Content-Type: application/json\r\n"
				"Content-Length: %ld\r\n"
				"\r\n"
				"%s",
				strlen(json), json);

	send(client_socket, response, strlen(response), 0);
	free(json);
}

int heavy_computation()
{
	int count = 0;
	for (int i = 2; i < COMPLEXITY; ++i)
	{
		int prime = 1;
		for (int j = 2; j * j <= i; ++j)
			if (i % j == 0)
			{
				prime = 0;
				break;
			}
		if (prime)
			count++;
	}
	return count;
}

void handle_test(int client_socket, const char *request)
{
	(void)request;
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	int result = heavy_computation();

	clock_gettime(CLOCK_MONOTONIC, &end);

	double elapsed_ms = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

	char *json = json_create();
	json_add_string(&json, "status", "ok");

	char info[64];
	snprintf(info, sizeof(info), "Found %d primes", result);
	json_add_string(&json, "task", info);

	char time_str[64];
	snprintf(time_str, sizeof(time_str), "%.3f", elapsed_ms);
	json_add_string(&json, "elapsed_ms", time_str);

	json_finalize(&json);

	char response[2048];
	snprintf(response, sizeof(response),
				"HTTP/1.1 200 OK\r\n"
				"Content-Type: application/json\r\n"
				"Content-Length: %ld\r\n"
				"\r\n"
				"%s",
				strlen(json), json);

	send(client_socket, response, strlen(response), 0);
	free(json);
}