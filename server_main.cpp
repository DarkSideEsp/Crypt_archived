#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main(){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
    listen(server_socket, 10);

    while(true){
        unsigned int addr;
        int client_socket = accept(server_socket, nullptr, nullptr);
        cout << "Yep" << "\n";
        close(client_socket);
    }
}