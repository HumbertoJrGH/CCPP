#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../json/json_builder.h"

void handle_shutdown(int client_socket, const char *request)
{
	(void)request;
	char *json = json_create();
	json_add_string(&json, "status", "shutting_down");
	json_add_string(&json, "message", "Server will shut down");
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

	// Encerra o processo
	exit(0);
}
