#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <httplib.h>
#include <jsoncpp/json/json.h>

#include <string>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace httplib;
using namespace std;

class HTTPClient;

class Requests
{
private:
    Json::Value convert_string_json(string data_form_server);
    string generate_endpoint(string end_point, string name_thread, string count);
    HTTPClient *http_clinet;
public:
    Requests(HTTPClient *http_clinet):http_clinet(http_clinet){};
    Json::Value send_get_request(string end_point, string name_thread, string count);
    Json::Value send_post_request(string end_point, string name_thread, string count, Json::Value *send_data);
};

class HTTPClient
{
    friend class Requests;
private:
    queue<shared_ptr<Client>> pool_clients;
    mutex accsses;
    condition_variable cond;
    shared_ptr<Client> get_connection();
    void insert_queue_unused_con(shared_ptr<Client> clinet);
public:
    HTTPClient(string url, int port, int count_con);
    // ~HTTPClient();
};


#endif