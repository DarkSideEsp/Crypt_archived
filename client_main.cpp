#include <iostream>
#include <unistd.h>
#include <thread>
#include <string>
#include <mutex>

#include "sources/client/client.hpp"


using namespace std;


bool listen_run;
const int timer = 1;
const char* server_ip = "127.0.0.1";
const int port = 1234;


int main(){
    Client client(server_ip, port, timer);

    client.client_log_in();

    listen_run = true;
    thread(&Client::listener, &client, ref(listen_run)).detach();


    mutex mtx;

    mtx.lock();
    cout << "\nClient ready to work. To send message use:\n\tsend text to destination_username\n";
    mtx.unlock();

    string line = "";
    while(line != "exit"){
        getline(cin, line);
        client.command(line);
    }


    listen_run = false;
    sleep(2 * timer);
}
