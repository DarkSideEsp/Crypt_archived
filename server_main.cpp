#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <vector>
#include <map>

#include "sources/server/server.hpp"


using namespace std;


bool listener_run;
const int port = 1234;


int main(){
    Server server(port);

    server.start_server();
    
    listener_run = true;
    thread listener_th(&Server::listener, &server, ref(listener_run));
    listener_th.detach();


    sleep(1);
    string line = "";
    while(line != "exit"){
        getline(cin, line);

        if(line == "stop server"){
            listener_run = false;
            server.close_server_socket();
            cout << "Server stopped\n";
        }
    }
}
