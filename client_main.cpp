#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>

#include "sources/client/client.hpp"


using namespace std;


bool listen_run = true;
const int timer = 1;
const char* server_ip = "127.0.0.1";
const int port = 1515;


int main(){
    int client_socket = init_client();
    sockaddr_in server_addr = get_server_addr();


    /*
    Hello message
    */

    string message = "Hello";
    pair<int, string> ans = send_message(message, client_socket, server_addr);
    if(ans.first == -400){
        cout << "Что-произошло при подключении к серверу\n";
    }else if(ans.first == 200){
        cout << "Ok\t" << ans.second.size() << "\n";
    }

    thread listener_th(listener, client_socket, server_addr);
    listener_th.detach();


    /*
    Something
    */


    listen_run = false;
    sleep(2 * timer);
}
