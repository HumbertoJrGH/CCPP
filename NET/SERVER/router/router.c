#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "router.h"

// ESTRUTURA PARA CADA ROTA
typedef struct
{
	char method[8];
	char path[128];
	route_handler_t handler;
} Route;

#define MAX_ROUTES 32
static Route routes[MAX_ROUTES];
static int route_count = 0;

// REGISTRA UMA NOVA ROTA
void router_add(const char *method, const char *path, route_handler_t handler)
{
	if (route_count >= MAX_ROUTES)
	{
		fprintf(stderr, "Too many routes!\n");
		return;
	}

	strncpy(routes[route_count].method, method, sizeof(routes[route_count].method));
	strncpy(routes[route_count].path, path, sizeof(routes[route_count].path));
	routes[route_count].handler = handler;
	route_count++;
}

// SIMPLES PARSER DE MÉTODO E CAMINHO (linha 1 da requisição)
void parse_http_request_line(const char *request, char *method, char *path)
{
	sscanf(request, "%7s %127s", method, path);
}

// PROCURA A ROTA CORRESPONDENTE E EXECUTA
void route_dispatch(int client_socket, const char *request)
{
	char method[8];
	char path[128];

	parse_http_request_line(request, method, path);

	for (int i = 0; i < route_count; ++i)
	{
		if (strcmp(routes[i].method, method) == 0 && strcmp(routes[i].path, path) == 0)
		{
			routes[i].handler(client_socket, request);
			return;
		}
	}

	// ROTA NÃO ENCONTRADA
	const char *response =
		 "HTTP/1.1 404 Not Found\r\n"
		 "Content-Type: text/plain\r\n"
		 "Content-Length: 13\r\n"
		 "\r\n"
		 "404 Not Found";
	send(client_socket, response, strlen(response), 0);
}
