//
// Created by YoUr_IcOn on 30.10.2020.
//
#include "iostream"
#include <cstdio>
#include <cstring>
#include "winsock2.h"
#include "windows.h"
#include <cmath>
#include <string>

#define PORT 123
#define SERVERADDR "127.0.0.1"

float func(float x){
    return pow(x, 3) * cos(x);
}

int main(){
    char buff[1024];
    printf("TCP Client started\n");

    if (WSAStartup(0x0202, (WSADATA *)&buff[0])){
        printf("Error WSAStartup %d\n", WSAGetLastError());
        return 1;
    }

    SOCKET client_socket;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0){
        printf("Socket() error %d\n", WSAGetLastError());
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    HOSTENT *hst;

    if (inet_addr(SERVERADDR) != INADDR_NONE){
        server_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
    }
    else{
        hst = gethostbyname(SERVERADDR);
        if (hst){
            ((unsigned long *)&server_addr.sin_addr)[0] = ((unsigned long **)hst->h_addr_list)[0][0];
        }
        else{
            printf("Invalid address %d\n", WSAGetLastError());
            closesocket(client_socket);
            WSACleanup();
            return 1;
        }
    }
    int result = connect(client_socket, (sockaddr *) &server_addr, sizeof(server_addr));
    if (result == SOCKET_ERROR){
        printf("Connect error %d\n", WSAGetLastError());
        return 1;
    }

    char buffer[1024];
    // Чтение и передача сообщений
    int nsize = recv(client_socket, &buffer[0], sizeof(buffer), 0);
    printf("Server=>Client: %s\n", buffer);
    while (nsize != SOCKET_ERROR) {
        float x;
        float y;
        recv(client_socket, reinterpret_cast<char *>(&x), sizeof(x), 0);
        y = func(x);
        std::cout << "calc form server y = func(" + std::to_string(x) + ") = " + std::to_string(y) << std::endl;
        send(client_socket, reinterpret_cast<char *>(&y), sizeof(y), 0);
    }
    return 0;
}

