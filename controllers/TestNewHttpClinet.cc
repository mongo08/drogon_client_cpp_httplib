#include "TestNewHttpClinet.h"

void TestNewHttpClinet::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    if (type!=WebSocketMessageType::Ping){
        HTTPClient http_clinet("127.0.0.1",9021,10);
        Requests req(&http_clinet);
        cout<<"ququ"<<endl;
        Json::Value get_json=req.send_get_request("/ququ_epta","thread1","0");
        int val_count=get_json["count"].asInt();
        cout<<"get request "<<val_count<<endl;
        Json::Value send_data;
        send_data["req"]=10;
        get_json=req.send_post_request("/post_ququ","thread2","1",&send_data);
        val_count=get_json["count"].asInt();
        cout<<"post request "<<val_count<<endl;
    }
}

void TestNewHttpClinet::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    this->connections.push_back(wsConnPtr);
    cout<<"count connected "<<this->connections.size()<<endl;
}


void TestNewHttpClinet::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
}
