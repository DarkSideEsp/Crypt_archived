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

    cout << "Server Initialized\n";

    arguments.first = server_socket;
    arguments.second = server_addr;

    return arguments;
}


void start_server(int server_socket, sockaddr_in server_addr){
    bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    listen(server_socket, 10);

    cout << "Server started\n";
}


void catch_client(int client_socket){
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int bytes = recv(client_socket, buffer, sizeof(buffer), 0);
    if(bytes == -1){
        cout << "Some Error in getting data: " << errno << "\n";
    }
    send(client_socket, buffer, bytes, 0);

    cout << buffer << "\n";

    close(client_socket);
}


void listener(int server_socket, sockaddr_in server_addr){
    cout << "Ready to clients\n";
    while(listener_run){
        sockaddr_in client_addr;
        socklen_t len;
        int client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &len);

        cout << "New client: " << inet_ntoa((client_addr.sin_addr)) << "\n";

        thread(catch_client, client_socket).detach();
    }
    cout << "Listener stopped\n";
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