#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <map>

#include "client.hpp"
#include "../messages_gen/generators.hpp"
#include "../json_lib/json.hpp"


using namespace std;
using json = nlohmann::json;


Client::Client(const char* server_ip, int port, int timer): server_ip(server_ip), port(port), timer(timer){
    init_server_addr();
}

void Client::listener(bool& listen_run){
    mtx.lock();
    cout << "\nListener started\n";
    mtx.unlock();
    while(listen_run){
        get_messages();
        sleep(timer);
    }
    mtx.lock();
    cout << "\nListener stopped\n";
    mtx.unlock();
}

void Client::client_log_in(){
    pair<pair<string, size_t>, vector<string>> username_password_users;
    string line;

    mtx.lock();
    cout << "\nAre you registered(Y/n)? ";
    mtx.unlock();
    
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
            mtx.lock();
            cout << "\nPlease write Y or n: ";
            cin >> line;
            mtx.unlock();
        }
    }

    username = username_password_users.first.first;
    password = username_password_users.first.second;

    username_list = username_password_users.second;
}

void Client::command(string line){
    if(line.size() == 0) return;

    vector<string> splitted_line;
    stringstream stream(line);

    string i = "";
    while(getline(stream, i, ' ')) splitted_line.push_back(i);

    if(splitted_line[0] == "send"){
        if(splitted_line[1] == "text"){
            send_text_message(splitted_line[3]);
        }
    }
}



int Client::init_client(){
    return socket(AF_INET, SOCK_STREAM, 0);
}

void Client::init_server_addr(){
    server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0){
        mtx.lock();
        cout << "Что-то пошло не так на этапе инициализации IP-адреса сервера. \n";
        mtx.unlock();
        exit;
    }
}

pair<int, string> Client::send_message(string message){
    int client_socket = init_client();

    if(connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) != 0){
        mtx.lock();
        cout << "Something went in connection :( \t" << strerror(errno) << "\n";
        mtx.unlock();
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
        mtx.lock();
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;
        mtx.unlock();

        autorization_req = generate_hello(username, h(password));

        pair<int, string> ans = send_message(to_string(autorization_req));

        if(ans.first == -400){
            mtx.lock();
            cout << "Something went wrong on connection so try again\n";
            mtx.unlock();
            continue;
        }else if(ans.first == 200){
            autorization_req_ans = json::parse(ans.second);
        }

        if(autorization_req_ans["type"] != "hello_ans"){
            mtx.lock();
            cout << "Caught unexpected response\nTry again\n";
            mtx.unlock();
            continue;
        }else if(autorization_req_ans["data"]["client_status"] == false){
            mtx.lock();
            cout << "You havent registered yet. Instead of autorization try registration\n";
            mtx.unlock();
            returnable_val = registration();
        }else if(autorization_req_ans["data"]["password_status"] == false){
            mtx.lock();
            cout << "Password you wrote is incorrect. Try again.\n";
            mtx.unlock();
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

    mtx.lock();
    cout << "Welcome to registration. It is a simple messages transfer. Any user is identified using unique username and password. Now lets make you username\n";
    mtx.unlock();
    while(true){
        mtx.lock();
        cout << "Enter prefered username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        mtx.unlock();

        registration_req = generate_registration(username, h(password));

        pair<int, string> ans = send_message(to_string(registration_req));

        if(ans.first == -400){
            mtx.lock();
            cout << "Something went wrong on connection\nTry again\n";
            mtx.unlock();
            continue;
        }else if(ans.first == 200){
            registration_req_ans = json::parse(ans.second);
        }

        if(registration_req_ans["type"] != "registration_ans"){
            mtx.lock();
            cout << "Caught unexpected response\nTry again\n";
            mtx.unlock();
            continue;
        }else if(registration_req["data"]["status"] == false){
            mtx.lock();
            cout << "This username already used, try other.\n";
            mtx.unlock();
            continue;
        }else{
            mtx.lock();
            cout << "Successful registration\nNow lets make autorization\n";
            mtx.unlock();
            returnable_val = autorization();
            return returnable_val;
        }
    }
}

void Client::send_text_message(string destination){
    string message = "";
    json send_req, send_ans;
    pair<int, string> send_response;

    if(username == destination){
        mtx.lock();
        cout << "Sorry you cant send message for yourself ;)\n";
        mtx.unlock();
        return;
    }

    while(true){
        mtx.lock();
        cout << "Enter your message: ";
        cin >> message;
        mtx.unlock();

        send_req = generate_send(username, password, destination, "text", message);

        send_response = send_message(to_string(send_req));

        if(send_response.first == -400){
            mtx.lock();
            cout << "Something went wrong on connection\nTry again\n";
            mtx.unlock();
            continue;
        }else if(send_response.first == 200){
            send_ans = json::parse(send_response.second);
        }

        if(send_ans["type"] != "send_ans"){
            mtx.lock();
            cout << "Caught unexpected response\nTry again\n";
            mtx.unlock();
            continue;
        }else if(!send_ans["data"]["autorize_flag"]){
            mtx.lock();
            cout << "Wrong password or username. Log in again.\n";
            mtx.unlock();

            client_log_in();
            continue;
        }else if(!send_ans["data"]["user_exist"]){
            mtx.lock();
            cout << "Wrong destination username\nTry send command again\n";
            mtx.unlock();
            return;
        }else if(!send_ans["data"]["message_sent"]){
            mtx.lock();
            cout << "Mistake in sending message\nTry send command again\n";
            mtx.unlock();
            return;
        }else{
            mtx.lock();
            cout << "Shipped :)\n";
            break;
        }
    }
}

void Client::get_messages(){
    json response, request;

    request = generate_message_req(username, password);

    pair<int, string> ans = send_message(to_string(request));

    if(ans.first == 200) response = json::parse(ans.second);
    else return;

    if(response["type"] != "message_req_ans") return;

    if(!response["data"]["autorize_flag"]) return;

    if(response["data"]["count_new"] == 0) return;

    map<string, string> messages;
    response["data"]["messages"].get_to(messages);

    mtx.lock();
    for(auto& [from_username, input_message] : messages){
        cout << "New message from: " << from_username << ". With text:\n" << input_message << "\n";
    }
    mtx.unlock();
}
