#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>

#include "sources/client/client.hpp"

using namespace std;


bool listen_run = true;
const int timer = 1;
const string server_ip = "192.168.194.113";
const int port = 1234;


int main(){
    int client_socket = init_client();


    sockaddr_in server_addr = get_server_addr();
}
