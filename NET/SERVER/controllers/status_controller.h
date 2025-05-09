#ifndef STATUS_CONTROLLER_H
#define STATUS_CONTROLLER_H

void handle_status(int client_socket, const char *request);

void handle_test(int client_socket, const char *request);

#endif
