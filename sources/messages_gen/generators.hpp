#pragma once


#include "../json_lib/json.hpp"

using namespace std;
using json = nlohmann::json;


json generate_hello(string username, size_t password_hash);

json generate_hello_ans(bool client_status, bool password_status, vector<string> users);

json generate_registration(string username, size_t password_hash);

json generate_registration_ans(bool status);

json generate_message_req(string username, size_t password_hash);

json generate_message_req_ans(bool autorize_flag, int count_new, map<string, string> messages);

json generate_send(string username, size_t password_hash, string destination_username, string type, string message);

json generate_send_ans(bool autorize_flag, bool user_exist, bool message_sent);
