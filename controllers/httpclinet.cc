#include "httpclinet.h"

string HTTPClient::generate_endpoint(string end_point,string name_thread, string count)
{
    std::string str_con=end_point+"?"+name_thread+"="+count;
    return str_con;
}

Json::Value HTTPClient::convert_string_json(string data_form_server)
{
    Json::Value get_json;
    Json::Reader reder;
    reder.parse(data_form_server,get_json);
    return get_json;
}

Json::Value HTTPClient::send_get_request(string end_point, string name_thread, string count)
{
    string end_point_with_param=generate_endpoint(end_point,name_thread,count);
    auto result=this->client.get()->Get(end_point_with_param);
    Json::Value json=this->convert_string_json(result->body);
    return json;
}

Json::Value HTTPClient::send_post_request(string end_point, string name_thread, string count, Json::Value *send_data)   
{
    string end_point_with_param=generate_endpoint(end_point,name_thread,count);
    Json::StreamWriterBuilder swb;
    string msg=Json::writeString(swb,send_data);
    auto result=this->client.get()->Post(end_point_with_param,msg,"application/json");
    Json::Value json=this->convert_string_json(result->body);
    return json;
}

// HTTPClient::~HTTPClient()
// {
//     this->client.get()->~Client();
// }