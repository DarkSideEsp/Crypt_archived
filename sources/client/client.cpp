#include <thread>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>


#include "client.hpp"

using namespace std;


void listener(int client_socket, sockaddr_in server_addr){
    return;
}


int init_client(){
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    return client_socket;
}


sockaddr_in get_server_addr(){
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, (const char*) &server_ip, &server_addr.sin_addr) <= 0){
        cout << "Что-то пошло не так на этапе инициализации IP-адреса сервера. \n";
        exit;
    }

    return server_addr;
}


pair<int, string> send_message(string message, int client_socket, sockaddr_in server_addr){
    if(connect(client_socket, (sockaddr*) &server_addr, sizeof(server_addr)) == 1){
        return {-400, ""};
    }

    send(client_socket, message.c_str(), message.size(), 0);
    
    char buffer[2048];
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);

    close(client_socket);

    return {200, (string) buffer};
}

/*
int main(){
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    if(inet_pton(AF_INET, "192.168.194.113", &server_addr.sin_addr) <= 0) cout << "Somethink fucked\n";

    if(connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) cout << "Another fuck\n";

    string message = "hi";
    send(client_socket, message.c_str(), message.size(), 0);

    close(client_socket);
}
*/