#pragma once


#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <arpa/inet.h>
#include <map>

#include "../json_lib/json.hpp"


using namespace std;
using json = nlohmann::json;


class Server{
public:
    Server(int port);
    void start_server();
    void listener(bool& listener_run);
    void close_server_socket();
    vector<string> get_username_list();

protected:
    void catch_client(int client_socket);
    json hello_processing(json request);
    json registration_processing(json request);
    json send_processing(json request);

private:
    vector<pair<string, size_t>> users;
    vector<string> username_list;

    mutex mtx;

    int server_socket;
    sockaddr_in server_addr;

    unsigned int client_visited_count = 0;
    unsigned int client_count = 0;

    map<string, map<string, string>> user_messages;
};
