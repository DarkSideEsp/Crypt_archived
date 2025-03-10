#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>

#include "server.hpp"
#include "../json_lib/json.hpp"
#include "../messages_gen/generators.hpp"


using namespace std;
using json = nlohmann::json;


Server::Server(int port){
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    users.resize(0);
    username_list.resize(0);

    cout << "Server Initialized\n";
}

void Server::start_server(){
    bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    listen(server_socket, 10);

    cout << "Server started\n";
}

void Server::listener(bool& listener_run){
    cout << "Ready to clients\n";
    while(listener_run){
        sockaddr_in client_addr;
        socklen_t len;
        int client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &len);

        cout << "New client: " << inet_ntoa((client_addr.sin_addr)) << "\n";

        thread(&Server::catch_client, this, client_socket).detach();
    }
    cout << "Listener stopped\n";
}

void Server::close_server_socket(){
    close(server_socket);
}


void Server::catch_client(int client_socket){
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int bytes = recv(client_socket, buffer, sizeof(buffer), 0);
    if(bytes == -1){
        cout << "Some Error in getting data: " << errno << "\n";
    }

    
    json request = json::parse(buffer);
    json response;
    if(request["type"] == "hello"){
        response = hello_processing(request);
    }else if(request["type"] == "registration"){
        response = registration_processing(request);
    }

    send(client_socket, to_string(response).c_str(), to_string(response).size(), 0);

    close(client_socket);
}

json Server::hello_processing(json request){
    bool client_status = false;
    bool password_status = false;

    mtx.lock();
    for(auto &user : users){
        if(user.first == request["data"]["username"]){
            client_status = true;
            if(user.second == request["data"]["password"])
                password_status = true;
            break;
        }
    }
    mtx.unlock();

    if(client_status && password_status)
        return generate_hello_ans(client_status, password_status, username_list);
    else
        return generate_hello_ans(client_status, password_status, {});
}

json Server::registration_processing(json request){
    bool status = true;

    mtx.lock();
    for(auto &user : username_list){
        if(user == request["data"]["username"]){
            status = false;
            break;
        }
    }
    mtx.unlock();

    if(!status){
        return generate_registration_ans(status);
    }else{
        mtx.lock();
        users.push_back({request["data"]["username"], request["data"]["password"]});
        username_list.push_back(request["data"]["username"]);
        mtx.unlock();
        return generate_registration_ans(status);
    }
}
