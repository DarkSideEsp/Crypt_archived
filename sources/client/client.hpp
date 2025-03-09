#pragma once


#include <string>
#include <vector>

using namespace std;


extern bool listen_run;
extern const int timer;
extern const char* server_ip;
extern const int port;


void listener(int client_socket, sockaddr_in server_addr);

int init_client();

sockaddr_in get_server_addr();

pair<int, string> send_message(string message, int client_socket, sockaddr_in server_addr);

pair<pair<string, size_t>, vector<string>> client_cli_start(int client_socket, sockaddr_in server_addr);

pair<pair<string, size_t>, vector<string>> autorization(int client_socket, sockaddr_in server_addr);

pair<pair<string, size_t>, vector<string>> registration(int client_socket, sockaddr_in server_addr);
