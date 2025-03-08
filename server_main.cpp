#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>

using namespace std;

int main(){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);

    server_addr.sin_addr.s_addr = INADDR_ANY;


    bind(server_socket, (sockaddr*) &server_addr, sizeof(server_addr));
    listen(server_socket, 10);
    cout << "Server ready\n";

    cout << "Yep\n";
    sockaddr_in addr;
    int client_socket = accept(server_socket, (sockaddr*) &addr, nullptr);
    cout << "DoubleYep\t" << inet_ntoa(addr.sin_addr) << "\n";
    
    char buffer[1024];
    recv(client_socket, buffer, sizeof(buffer), 0);
    send(client_socket, buffer, sizeof(buffer), 0);

    close(client_socket);
}