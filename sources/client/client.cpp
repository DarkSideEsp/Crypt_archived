#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

#include "client.hpp"
#include "../messages_gen/generators.hpp"
#include "../json_lib/json.hpp"


using namespace std;
using json = nlohmann::json;


Client::Client(const char* server_ip, int port, int timer): server_ip(server_ip), port(port), timer(timer){
    init_server_addr();
}

void Client::listener(bool& listen_run){
    cout << "Listener started\n";
    while(listen_run){
        /*
        Gen Listen message
        Send it
        Get the ans
        Write if it exist
        */

        sleep(timer);
    }
    cout << "Listener stopped\n";
}

void Client::client_log_in(){
    pair<pair<string, size_t>, vector<string>> username_password_users;
    string line;

    cout << "Are you registered(Y/n)? ";
    
    bool wrote_status = false;
    cin >> line;
    while(!wrote_status){
        if(line == "Y"){
            wrote_status = true;
            username_password_users = autorization();
        }else if(line == "n"){
            wrote_status = true;
            username_password_users = registration();
        }else{
            cout << "Please write Y or n\n";
        }
    }

    username = username_password_users.first.first;
    password = username_password_users.first.second;

    username_list = username_password_users.second;
}


int Client::init_client(){
    return socket(AF_INET, SOCK_STREAM, 0);
}

void Client::init_server_addr(){
    server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0){
        cout << "Что-то пошло не так на этапе инициализации IP-адреса сервера. \n";
        exit;
    }
}

pair<int, string> Client::send_message(string message){
    int client_socket = init_client();

    if(connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) != 0){
        cout << "Something went in connection :( \t" << strerror(errno) << "\n";
        return {-400, strerror(errno)};
    }

    send(client_socket, message.c_str(), message.size(), 0);

    string buffer_str = "";
    char buffer[1024];
    int got_bytes = 2;
    while(got_bytes > 0){
        memset(buffer, 0, sizeof(buffer));
        got_bytes = recv(client_socket, buffer, sizeof(buffer), 0);

        buffer_str += buffer;
    }

    close(client_socket);

    return {200, buffer_str};
}

pair<pair<string, size_t>, vector<string>> Client::autorization(){
    string username, password;
    hash<string> h;
    json autorization_req_ans, autorization_req;
    pair<pair<string, size_t>, vector<string>> returnable_val;

    while(true){
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        autorization_req = generate_hello(username, h(password));

        pair<int, string> ans = send_message(to_string(autorization_req));

        if(ans.first == -400){
            cout << "Something went wrong on connection so try again\n";
            continue;
        }else if(ans.first == 200){
            autorization_req_ans = json::parse(ans.second);
        }

        if(autorization_req_ans["type"] != "hello_ans"){
            cout << "Caught unexpected response\nTry again\n";
            continue;
        }else if(autorization_req_ans["data"]["client_status"] == false){
            cout << "You havent registered yet. Instead of autorization try registration\n";
            returnable_val = registration();
        }else if(autorization_req_ans["data"]["password_status"] == false){
            cout << "Password you wrote is incorrect. Try again.\n";
            continue;
        }else{
            returnable_val.first.first = username;
            returnable_val.first.second = h(password);
            autorization_req_ans["data"]["users_list"].get_to(returnable_val.second);
        }

        return returnable_val;
    }
}

pair<pair<string, size_t>, vector<string>> Client::registration(){
    string username, password;
    json registration_req, registration_req_ans;
    hash<string> h;
    pair<pair<string, size_t>, vector<string>> returnable_val;

    cout << "Welcome to registration. It is a simple messages transfer. Any user is identified using unique username and password. Now lets make you username\n";
    while(true){
        cout << "Enter prefered username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        registration_req = generate_registration(username, h(password));

        pair<int, string> ans = send_message(to_string(registration_req));

        if(ans.first == -400){
            cout << "Something went wrong on connection\nTry again\n";
            continue;
        }else if(ans.first == 200){
            registration_req_ans = json::parse(ans.second);
        }

        if(registration_req_ans["type"] != "registration_ans"){
            cout << "Caught unexpected response\nTry again\n";
            continue;
        }else if(registration_req["data"]["status"] == false){
            cout << "This username already used? try other.\n";
            continue;
        }else{
            cout << "Successful registration\nNow lets make autorization\n";
            returnable_val = autorization();
            return returnable_val;
        }
    }
}
