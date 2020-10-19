//
// Created by YoUr_IcOn on 12.10.2020.
//

#ifndef LAB_1_SSERVER_H
#define LAB_1_SSERVER_H

#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <winsock.h>

using namespace std;
class SServer {
public:
    SServer();
    ~SServer();
    void startServer();
    void closeServer();
    void handle();
    unsigned short port;
private:
    SOCKET this_s;
    WSAData wsaData;
};


#endif //LAB_1_SSERVER_H
