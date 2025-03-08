#pragma once


#include <string>

using namespace std;


extern bool listen_run;
extern const int timer;
extern const char* server_ip;
extern const int port;


void listener(int client_socket, sockaddr_in server_addr);

int init_client();

sockaddr_in get_server_addr();
