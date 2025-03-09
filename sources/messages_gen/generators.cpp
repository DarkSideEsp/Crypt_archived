#include <string>
#include <vector>
#include <map>

#include "generators.hpp"
#include "../json_lib/json.hpp"


using namespace std;
using json = nlohmann::json;


json generate_hello(string username, size_t password_hash){
    json hello;

    hello["type"] = "hello";
    hello["data"]["username"] = username;
    hello["data"]["password"] = password_hash;

    return hello;
}

json generate_hello_ans(bool client_status, bool password_status, vector<string> users){
    json hello_ans;

    hello_ans["type"] = "hello_ans";
    hello_ans["data"]["client_status"] = client_status;
    hello_ans["data"]["password_status"] = password_status;
    hello_ans["data"]["users_list"] = users;

    return hello_ans;
}

json generate_registration(string username, size_t password_hash){
    json registration;

    registration["type"] = "registration";
    registration["data"]["username"] = username;
    registration["data"]["password"] = password_hash;

    return registration;
}

json generate_registration_ans(bool status){
    json registration_ans;

    registration_ans["type"] = "registration_ans";
    registration_ans["data"]["status"] = status;

    return registration_ans;
}

json generate_message_req(string username, size_t password_hash){
    json message_req;

    message_req["type"] = "messages_req";
    message_req["data"]["username"] = username;
    message_req["data"]["password"] = password_hash;

    return message_req;
}

json generate_message_req_ans(bool autorize_flag, int count_new, map<string, string> messages){
    json message_req_ans;

    message_req_ans["type"] = "message_req_ans";
    message_req_ans["data"]["autorize_flag"] = autorize_flag;
    message_req_ans["data"]["count_new"] = count_new;
    message_req_ans["data"]["messages"] = messages;

    return message_req_ans;
}

json generate_send(string username, size_t password_hash, string destination_username, string type, string message){
    json send;

    send["type"] = "send";
    send["data"]["username"] = username;
    send["data"]["password"] = password_hash;
    send["data"]["dest_username"] = destination_username;
    send["data"]["type"] = type;
    send["data"]["message"] = message;

    return send;
}

json generate_send_ans(bool autorize_flag, bool user_exist, bool message_sent){
    json send_ans;

    send_ans["type"] = "send_ans";
    send_ans["data"]["autorize_flag"] = autorize_flag;
    send_ans["data"]["user_exist"] = user_exist;
    send_ans["data"]["message_sent"] = message_sent;

    return send_ans;
}
