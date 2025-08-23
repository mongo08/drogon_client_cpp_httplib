import websocket
import time

def start_req():
    ws=websocket.WebSocket()
    ws.connect("ws://127.0.0.1:5555/test_new_api")
    while True:
        ws.send("start")
        time.sleep(0.1)


if __name__=="__main__":
    start_req()
    
