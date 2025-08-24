#include "httpclinet.h"

HTTPClient::HTTPClient(string url,int port, int count_con)
{
    for(int i=0;i<count_con;i++)
        pool_clients.push(make_unique<Client>(url,port));
}

shared_ptr<Client> HTTPClient::get_connection(){
    unique_lock<mutex> lock(accsses);
    cond.wait(lock,[this]{return !pool_clients.empty();});
    auto client=pool_clients.front();
    pool_clients.pop();
    return client;
}

void HTTPClient::insert_queue_unused_con(shared_ptr<Client> clinet)
{
    unique_lock<mutex> lock(accsses);
    pool_clients.push(clinet);
    cond.notify_one();
}


string Requests::generate_endpoint(string end_point,string name_thread, string count)
{
    std::string str_con=end_point+"?"+name_thread+"="+count;
    return str_con;
}

Json::Value Requests::convert_string_json(string data_form_server)
{
    Json::Value get_json;
    Json::Reader reder;
    reder.parse(data_form_server,get_json);
    return get_json;
}

Json::Value Requests::send_get_request(string end_point, string name_thread, string count)
{
    string end_point_with_param=generate_endpoint(end_point,name_thread,count);
    shared_ptr<Client> clinet=this->http_clinet->get_connection();
    auto result=clinet.get()->Get(end_point_with_param);
    Json::Value json=convert_string_json(result->body);
    this->http_clinet->insert_queue_unused_con(clinet);
    return json;
}

Json::Value Requests::send_post_request(string end_point, string name_thread, string count, Json::Value *send_data)   
{
    string end_point_with_param=generate_endpoint(end_point,name_thread,count);
    Json::StreamWriterBuilder swb;
    string msg=Json::writeString(swb,send_data);
    shared_ptr<Client> clinet=this->http_clinet->get_connection();
    auto result=clinet.get()->Post(end_point_with_param,msg,"application/json");
    Json::Value json=this->convert_string_json(result->body);
    this->http_clinet->insert_queue_unused_con(clinet);
    return json;
}

// HTTPClient::~HTTPClient()
// {
//     this->client.get()->~Client();
// }