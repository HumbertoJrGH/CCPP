#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define PORT 4999
#define BUFFER_SIZE 1024

int main()
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};
	const char *hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("Setsockopt failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Defining the server address
	address.sin_family = AF_INET;			  // IPv4
	address.sin_addr.s_addr = INADDR_ANY; // Bind to any address
	address.sin_port = htons(PORT);		  // Port

	// Bind the socket to the specified port
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("Bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Listen for incoming connections (backlog size 3)
	if (listen(server_fd, 3) < 0)
	{
		perror("Listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	// Accept an incoming connection
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
	{
		perror("Accept failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Read data from the client
	read(new_socket, buffer, BUFFER_SIZE);
	printf("Received: %s\n", buffer);

	// Send a response to the client
	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	// Close the socket
	close(new_socket);
	close(server_fd);

	return 0;
}