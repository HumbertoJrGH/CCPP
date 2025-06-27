#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"
#include "../router/router.h"
#include "../controllers/status_controller.h"
#include "../controllers/shutdown_controller.h"

#define BUFFER_SIZE 1024

#define AUTH_TOKEN "token-secreto"
#define AUTH_HEADER "X-TOKEN-UV"

int server_fd;

// HANDLER PARA CTRL+C
void handle_sigint(int sig)
{
	(void)sig;
	printf("\nServer interrupted. Closing socket...\n");
	if (server_fd >= 0)
		close(server_fd);
	exit(0);
}

void send_invalid_token_response(int socket)
{
	const char *response =
		 "HTTP/1.1 401 Unauthorized\r\n"
		 "Content-Type: application/json\r\n"
		 "Connection: close\r\n"
		 "\r\n"
		 "{\"error\": \"Token inválido\"}\n";
	write(socket, response, strlen(response));
}

char *get_header_value(const char *request, const char *header_name)
{
	const char *header_start = strstr(request, header_name);
	if (!header_start)
		return NULL;

	header_start += strlen(header_name);
	if (*header_start == ':')
		header_start++;
	while (*header_start == ' ')
		header_start++;

	const char *header_end = strchr(header_start, '\r');
	if (!header_end)
		return NULL;

	size_t length = header_end - header_start;
	char *value = malloc(length + 1);
	if (!value)
		return NULL;

	strncpy(value, header_start, length);
	value[length] = '\0';
	return value;
}

void server_start(int port)
{
	int new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};

	// CAPTURA CTRL+C
	signal(SIGINT, handle_sigint);

	// CRIA SOCKET
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("Socket options failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("Binding failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("Listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d...\n", port);

	// REGISTRA ROTAS
	router_add("GET", "/status", handle_status);
	router_add("GET", "/test", handle_test);
	router_add("POST", "/shutdown", handle_shutdown);

	// LOOP PRINCIPAL
	while (1)
	{
		printf("\nWaiting for connection...\n");

		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
		{
			perror("Accept failed");
			continue;
		}

		memset(buffer, 0, BUFFER_SIZE);
		read(new_socket, buffer, BUFFER_SIZE);
		printf("Received:\n%s\n", buffer);

		// DESPACHA A ROTA
		char *token = get_header_value(buffer, AUTH_HEADER);
		if (!token || strcmp(token, AUTH_TOKEN) != 0)
			send_invalid_token_response(new_socket);
		else
			route_dispatch(new_socket, buffer);

		if (token)
			free(token);

		close(new_socket);
	}

	close(server_fd);
	printf("Server shutdown.\n");
}