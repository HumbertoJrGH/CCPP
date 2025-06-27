#ifndef SERVER_H
#define SERVER_H

char *get_header_value(const char *request, const char *header_name);

void server_start(int port);

#endif