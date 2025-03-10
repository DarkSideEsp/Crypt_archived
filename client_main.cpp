#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>

#include "sources/client/client.hpp"


using namespace std;


bool listen_run;
const int timer = 1;
const char* server_ip = "127.0.0.1";
const int port = 1234;


int main(){
    Client client(server_ip, port, timer);

    client.client_log_in();

    listen_run = true;
    thread listener_th(&Client::listener, &client, ref(listen_run));
    listener_th.detach();


    /*
    Something
    */


    listen_run = false;
    sleep(2 * timer);
}
