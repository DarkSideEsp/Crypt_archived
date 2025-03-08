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
const int port = 1234;


int main(){
    pair<int, sockaddr_in> temp = init_server();
    cout << "Server Initialized\n";
    int server_socket = temp.first;
    sockaddr_in server_addr = temp.second;

    start_server(server_socket, server_addr);
    cout << "Server started\n";

    
    listener_run = true;
    thread listener_th(listener, server_socket, server_addr);
    listener_th.detach();


    string line = "";
    while(line != "exit"){
        cout << "> ";
        getline(cin, line);

        if(line == "stop server"){
            listener_run = false;
            close(server_socket);
            cout << "Server stopped\n";
        }
    }
}
