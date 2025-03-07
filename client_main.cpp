#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main(){
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    if(inet_pton(AF_INET, "192.168.194.113", &server_addr.sin_addr) <= 0) cout << "Somethink fucked\n";

    if(connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) cout << "Another fuck\n";

    
    close(client_socket);
}