#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>

#include "sources/server/server.hpp"


using namespace std;


bool listener_run;
const int port = 1515;


int main(){
    pair<int, sockaddr_in> temp = init_server();
    int server_socket = temp.first;
    sockaddr_in server_addr = temp.second;

    start_server(server_socket, server_addr);
    
    listener_run = true;
    thread listener_th(listener, server_socket, server_addr);
    listener_th.detach();


    sleep(1);
    string line = "";
    while(line != "exit"){
        getline(cin, line);

        if(line == "stop server"){
            listener_run = false;
            close(server_socket);
            cout << "Server stopped\n";
        }
    }
}
