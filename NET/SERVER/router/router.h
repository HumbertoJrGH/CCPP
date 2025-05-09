#ifndef ROUTER_H
#define ROUTER_H

typedef void (*route_handler_t)(int client_socket, const char *request);

void router_add(const char *method, const char *path, route_handler_t handler);

void route_dispatch(int client_socket, const char *request);

#endif