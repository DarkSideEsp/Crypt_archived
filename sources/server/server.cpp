#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <vector>
#include <map>

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

    mtx.lock();
    cout << "\nServer Initialized\n";
    mtx.unlock();
}

void Server::start_server(){
    if(bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) != 0){
        mtx.lock();
        cout << "\nSomething went wrong in server binding\t" << strerror(errno) << "\n";
        mtx.unlock();
        return;
    }
    if(listen(server_socket, 10) != 0){
        mtx.lock();
        cout << "\nSomething went wrong in server listen starting\t" << strerror(errno) << "\n";
        mtx.unlock();
        return;
    }

    mtx.lock();
    cout << "\nServer started\n";
    mtx.unlock();
}

void Server::listener(bool& listener_run){
    mtx.lock();
    cout << "\nReady to clients\n";
    mtx.unlock();

    while(listener_run){
        sockaddr_in client_addr;
        socklen_t len;
        int client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &len);

        // cout << "New client: " << inet_ntoa((client_addr.sin_addr)) << "\n";

        thread(&Server::catch_client, this, client_socket).detach();
    }

    mtx.lock();
    cout << "\nListener stopped\n";
    mtx.unlock();
}

void Server::close_server_socket(){
    close(server_socket);
}

vector<string> Server::get_username_list(){
    return username_list;
}


void Server::catch_client(int client_socket){
    mtx.lock();
    client_count++;
    client_visited_count++;
    mtx.unlock();

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int bytes = recv(client_socket, buffer, sizeof(buffer), 0);
    if(bytes == -1){
        mtx.lock();
        cout << "\nSome Error in getting data: " << errno << "\n";
        mtx.unlock();
    }

    json request = json::parse(buffer);
    
    json response;
    if(request["type"] == "hello"){
        response = hello_processing(request);
    }else if(request["type"] == "registration"){
        response = registration_processing(request);
    }else if(request["type"] == "send"){
        response = send_processing(request);
    }else if(request["type"] == "messages_req"){
        response = message_req_processing(request);
    }

    send(client_socket, to_string(response).c_str(), to_string(response).size(), 0);

    close(client_socket);

    mtx.lock();
    client_count--;
    mtx.unlock();
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
        user_messages[request["data"]["username"]] = {};
        mtx.unlock();
        return generate_registration_ans(status);
    }
}

json Server::send_processing(json request){
    bool autorize_flag = false;
    bool user_exist = false;
    bool message_sent = false;

    mtx.lock();
    for(auto &user : users){
        if(user.first == request["data"]["username"] && user.second == request["data"]["password"]){
            autorize_flag = true;
        }
        if(user.first == request["data"]["dest_username"]){
            user_exist = true;
        }
        if(user_exist && autorize_flag) break;
    }
    mtx.unlock();

    if(autorize_flag && user_exist){
        string dest_name = request["data"]["dest_username"];
        string username = request["data"]["username"];
        string message = request["data"]["message"];

        mtx.lock();
        user_messages[dest_name].insert({username, message});
        mtx.unlock();
        message_sent = true;

        return generate_send_ans(autorize_flag, user_exist, message_sent);
    }else{
        return generate_send_ans(autorize_flag, autorize_flag && user_exist, message_sent);
    }
}

json Server::message_req_processing(json request){
    string username = request["data"]["username"];

    bool autorize_flag = false;
    int count_new = 0;
    map<string, string> messages = {};

    mtx.lock();
    for(auto& user : users){
        if(user.first == request["data"]["username"] && user.second == request["data"]["password"]){
            autorize_flag = true;
            break;
        }
    }
    mtx.unlock();

    if(!autorize_flag) return generate_message_req_ans(autorize_flag, count_new, messages);

    count_new = user_messages[username].size();
    messages = user_messages[username];
    user_messages[username].clear();

    return generate_message_req_ans(autorize_flag, count_new, messages);
}
