//
// Created by YoUr_IcOn on 12.10.2020.
//

#ifndef LAB_1_SCLIENT_H
#define LAB_1_SCLIENT_H

#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <winsock.h>

using namespace std;

class SClient {
public:
    SClient(SOCKET s, SOCKADDR_IN sock_in);
    ~SClient();
    void handle();
private:
    SOCKET c_sock;
    SOCKADDR_IN c_addr;
    char buffer[1024];
};


#endif //LAB_1_SCLIENT_H
