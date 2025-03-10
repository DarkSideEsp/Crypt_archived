#include <iostream>
#include <unistd.h>
#include <thread>
#include <string>
#include <vector>
#include <mutex>

#include "sources/server/server.hpp"


using namespace std;


bool listener_run;
const int port = 1234;


int main(){
    mutex mtx;

    Server* server = nullptr;

    string line = "";
    while(line != "exit"){
        getline(cin, line);

        if(line == "commands"){
            mtx.lock();
            cout << " init server \n start server \n stop server \n get used usernames \n commands \n exit \n delete server \n";
            mtx.unlock();
            
        }else if(line == "stop server"){
            if(server == nullptr){
                mtx.lock();
                cout << "You havent initialized server yet. Try: init server\n";
                mtx.unlock();
                continue;
            }
            listener_run = false;
            server->close_server_socket();
            mtx.lock();
            cout << "Server stopped\n";
            mtx.unlock();

        }else if(line == "init server"){
            server = new Server(port);

        }else if(line == "start server"){
            if(server == nullptr){
                mtx.lock();
                cout << "You havent initialize server yet. Try: init server\n";
                mtx.unlock();
                continue;
            }
            server->start_server();
            
            listener_run = true;
            thread(&Server::listener, server, ref(listener_run)).detach();

        }else if(line == "get used usernames"){
            if(server == nullptr){
                mtx.lock();
                cout << "You havent initialize server yet. Try: init server\n";
                mtx.unlock();
                continue;
            }
            vector<string> username_list = server->get_username_list();

            mtx.lock();
            cout << " ";
            for(auto &username : username_list) cout << username << " ";
            cout << "\n";
            mtx.unlock();

        }else if(line == "delete server"){
            if(server == nullptr){
                mtx.lock();
                cout << "You havent initialize server yet. Try: init server\n";
                mtx.unlock();
                continue;
            }
            mtx.lock();
            cout << "It will delete all users and all waiting messages\nYou really wanna delete server?(Yes/n)";
            string user_ans = "";
            cin >> user_ans;
            if(user_ans == "Yes"){
                cout << "Double check. You really wanna do this?(Yes/n)";
                cin >> user_ans;
                if(user_ans == "Yes"){
                    delete server;
                    server = nullptr;
                    cout << "Server has been deleted\n";
                }
            }
            mtx.unlock();
        }
    }
    sleep(1);
}
