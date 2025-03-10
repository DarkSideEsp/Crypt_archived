#pragma once


#include <string>
#include <arpa/inet.h>
#include <vector>

using namespace std;


class Client{
public:
    Client(const char* server_ip, int port, int timer);
    void listener(bool& listen_run);
    void client_log_in();

protected:
    int init_client();
    void init_server_addr();
    pair<int, string> send_message(string message);
    pair<pair<string, size_t>, vector<string>> autorization();
    pair<pair<string, size_t>, vector<string>> registration();

private:
    int client_socket;
    const int timer;
    sockaddr_in server_addr;
    string username;
    size_t password;
    vector<string> username_list;
    const char* server_ip;
    const size_t port;
};
