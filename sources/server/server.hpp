#pragma once


#include <string>

using namespace std;


extern bool listener_run;
extern const int port;


pair<int, sockaddr_in> init_server();

void start_server(int server_socket, sockaddr_in server_addr);

void catch_client_data(int client_socket, sockaddr_in client_addr);

void listener(int server_socket, sockaddr_in server_addr);