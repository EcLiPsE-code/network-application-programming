#include "src/srvr/SServer.h"

int main(){
    SServer* server;
    server->port = 3487;
    server->startServer();
    return 0;
}