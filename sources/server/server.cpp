#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <thread>

#include "server.hpp"


using namespace std;



pair<int, sockaddr_in> init_server(){
    pair<int, sockaddr_in> arguments;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    arguments.first = server_socket;
    arguments.second = server_addr;

    return arguments;
}


void start_server(int server_socket, sockaddr_in server_addr){
    bind(server_socket, (sockaddr*) &server_addr, sizeof(server_addr));
    listen(server_socket, 10);
}


void catch_client_data(int client_socket, sockaddr_in client_addr){
    cout << inet_ntoa(client_addr.sin_addr) << "\n";

    close(client_socket);
}


void listener(int server_socket, sockaddr_in server_addr){
    while(listener_run){
        sockaddr_in client_addr;

        int client_socket = accept(server_socket, (sockaddr*) &client_addr, nullptr);

        thread(catch_client_data, client_socket, client_addr).detach();
    }
}

// int main(){
//     int server_socket = socket(AF_INET, SOCK_STREAM, 0);
//     sockaddr_in server_addr;
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(1234);

//     server_addr.sin_addr.s_addr = INADDR_ANY;


//     bind(server_socket, (sockaddr*) &server_addr, sizeof(server_addr));
//     listen(server_socket, 10);
//     cout << "Server ready\n";

//     cout << "Yep\n";
//     sockaddr_in addr;
//     int client_socket = accept(server_socket, (sockaddr*) &addr, nullptr);
//     cout << "DoubleYep\t" << inet_ntoa(addr.sin_addr) << "\n";
    
//     char buffer[1024];
//     recv(client_socket, buffer, sizeof(buffer), 0);
//     send(client_socket, buffer, sizeof(buffer), 0);

//     close(client_socket);
// }