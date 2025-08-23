#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <httplib.h>
#include <jsoncpp/json/json.h>

#include <string>
#include <iostream>

using namespace httplib;
using namespace std;

class HTTPClient
{   
    private:
        string generate_endpoint(string end_point,string name_thread, string count);
        Json::Value convert_string_json(string data_form_server);
        unique_ptr<Client> client;
    public:
        HTTPClient(string url,int port):client(make_unique<Client>(url,port)){};
       // ~HTTPClient();
        Json::Value send_get_request(string end_point, string name_thread, string count);
        Json::Value send_post_request(string end_point, string name_thread, string count, Json::Value *send_data);   
};

#endif