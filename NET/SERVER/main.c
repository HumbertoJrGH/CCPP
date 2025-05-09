#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "json/json_builder.h"

#define PORT 4999
#define BUFFER_SIZE 1024

int server_fd;

void handle_sigint(int sig)
{
	(void)sig;
	printf("\nServer interrupted...\n");
	if (server_fd >= 0)
		close(server_fd);
	exit(0);
}

int main()
{
	int new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};

	// INTERRUPTION SIGNAL CAPTURE
	signal(SIGINT, handle_sigint);

	// SOCKET CREATION
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket creation failed...");
		exit(EXIT_FAILURE);
	}

	// SOCKET OPTIONS
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("Socket definition failed...");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// SERVER ADDRESS CONFIGURATION
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// VINCULATION
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("Binding failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Escutando
	if (listen(server_fd, 3) < 0)
	{
		perror("Falha em listen");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port: %d...\n", PORT);

	// MAING LOOP
	while (1)
	{
		printf("\nAwaiting for request...\n");

		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
		{
			perror("Accept error");
			continue;
		}

		memset(buffer, 0, BUFFER_SIZE); // Limpa o buffer
		read(new_socket, buffer, BUFFER_SIZE);
		printf("Received: %s\n", buffer);

		if (strncmp(buffer, "/shutdown", 9) == 0)
		{
			char *shutdown_response = json_create();
			json_add_string(&shutdown_response, "status", "shutting_down");
			json_add_string(&shutdown_response, "message", "Server is stopping");
			json_finalize(&shutdown_response);

			send(new_socket, shutdown_response, strlen(shutdown_response), 0);
			printf("Shutdown command received, sending shutdown response!\n");
			close(new_socket);
			break;
		}

		char *json_response = json_create();
		json_add_string(&json_response, "status", "ok");
		json_add_string(&json_response, "message", "Hello from server!");
		json_add_int(&json_response, "port", PORT);
		json_finalize(&json_response);

		int content_length = strlen(json_response);

		char response[1024];
		snprintf(response, sizeof(response),
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: application/json\r\n"
					"Content-Length: %d\r\n"
					"\r\n"
					"%s",
					content_length, json_response);

		send(new_socket, response, strlen(response), 0);
		free(json_response);
		printf("JSON response sent.\n");

		close(new_socket); // Fecha conexão com o cliente
	}

	close(server_fd);
	printf("Server shutdown completed!\n");

	return 0;
}