#pragma once


#include <string>
#include <vector>

#include "../json_lib/json.hpp"

using namespace std;
using json = nlohmann::json;


extern bool listener_run;
extern const int port;

extern vector<pair<string, size_t>> users;
extern vector<string> username_list;


pair<int, sockaddr_in> init_server();

void start_server(int server_socket, sockaddr_in server_addr);

void catch_client(int client_socket);

void listener(int server_socket, sockaddr_in server_addr);

json hello_processing(json request);

json registration_processing(json request);
