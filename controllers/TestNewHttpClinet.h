#pragma once

#include <drogon/WebSocketController.h>

#include <httplib.h>

#include <vector>

#include "httpclinet.h"

using namespace drogon;
using namespace httplib;
using namespace std;

class TestNewHttpClinet : public drogon::WebSocketController<TestNewHttpClinet>
{
  private:
    int count=0;
    vector<WebSocketConnectionPtr> connections;
    //Json::Value json;
  public:
    void handleNewMessage(const WebSocketConnectionPtr&,
      string &&,
      const WebSocketMessageType &) override;
    void handleNewConnection(const HttpRequestPtr &,
          const WebSocketConnectionPtr&) override;
    void handleConnectionClosed(const WebSocketConnectionPtr&) override;
    WS_PATH_LIST_BEGIN
    // list path definitions here;
    WS_PATH_ADD("/test_new_api");
    WS_PATH_LIST_END
};
