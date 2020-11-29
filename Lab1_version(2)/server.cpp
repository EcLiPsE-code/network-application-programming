//
// Created by YoUr_IcOn on 30.10.2020.
//
#include "iostream"
#include <cstdio>
#include "winsock2.h"
#include "windows.h"
#include <cmath>

#define MY_PORT 123  //порт, который слушает сервер

float square_figure = 0;

int max_clients = 50; //максимальное количество подключений
int client_count = 0; //текущее количество клиентов

DWORD WINAPI send_task_client(LPVOID arg);
DWORD WINAPI client_handler(LPVOID arg);

float func(float x){
    return pow(x, 3) * cos(x);
}

struct ServerInfo{
    SOCKET *clients; //клиенты
    SOCKET server_socket; //серверный сокет
    int max_clients; // max кол-во клиентво
    int &client_count; //онлайн клиенты
};

struct Arguments{
    SOCKET client_socket;
    float x;
};

int main(int argc, char* argv[]){
    char buff[1024];

    SOCKET clients[50]; //массив подключений

    if (WSAStartup(0x0202, (WSADATA *)&buff[0])){
        printf("Error WSAStartup %d\n", WSAGetLastError());
        return 1;
    }
    //создание сокета сервера
    SOCKET server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Error socket %d\n", WSAGetLastError());
        return 1;
    }

    sockaddr_in local_addr{};
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(MY_PORT);
    local_addr.sin_addr.s_addr = 0;

    //связывание сокета с localhost
    if(bind(server_socket, (sockaddr *)&local_addr, sizeof(local_addr))){
        printf("Error bind $d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    //Ожидание подключений
    //размер очереди 0x100
    if (listen(server_socket, 0x100)){
        printf("Error listen %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    printf("wait connections...\n");

    auto *serverInfo = new ServerInfo{clients, server_socket, max_clients, client_count};
    HANDLE handle_thread = CreateThread(nullptr, 0, client_handler, (LPVOID) serverInfo, 0, 0);
    char buffer[1024];
    while(true){
        std::cout << "Input command: ";
        fgets(buffer, sizeof(buffer), stdin);
        if (!strcmp(&buffer[0], "calc\n")){
            float a;
            float b;
            float n;
            std::cout << "Input a: ";
            std::cin >> a;
            std::cout << "Input b: ";
            std::cin >> b;
            std::cout << "Input n: ";
            std::cin >> n;

            float h = (b - a) * 1.0f / n;
            float x = h;
            int current_client = 0;
            HANDLE runner_thread[client_count];
            do{
                auto *arguments = new Arguments{clients[current_client], x};
                runner_thread[current_client++] = CreateThread(nullptr, 0, send_task_client,
                                                               reinterpret_cast<LPVOID>(arguments), 0, 0);
                if (current_client == client_count){
                    WaitForMultipleObjects(current_client, runner_thread, true, INFINITE);
                    for (int i = 0; i < current_client; i++){
                        CloseHandle(runner_thread[i]);
                    }
                    current_client = 0;
                }
                x += h;
            }while(x < b);
            WaitForMultipleObjects(client_count, runner_thread, true, INFINITE);
            for (int i = 0; i < client_count; i++){
                CloseHandle(runner_thread[i]);
            }
            //square_figure *= h;
            std::cout << "Result: " << square_figure << std::endl;
        }
    }
    closesocket(server_socket);
    WSACleanup();
    return 0;
}

DWORD WINAPI send_task_client(LPVOID arg){
    auto *arguments = reinterpret_cast<Arguments *>(arg);
    SOCKET client_socket = arguments->client_socket;
    float x = arguments->x;
    float y;

    int bytes_send = send(client_socket, reinterpret_cast<char *>(&x), sizeof(x), 0);
    if (bytes_send < 0){
        y = func(x);
        square_figure += y;

        return 1;
    }

    int bytes_recv = recv(client_socket, reinterpret_cast<char *>(&y), sizeof(y), 0);
    if (bytes_recv < 0){
        y = func(x);
        square_figure += y;

        return 1;
    }

    square_figure += y;
    return 1;
}

DWORD WINAPI client_handler(LPVOID arg){
    auto *serverInfo = reinterpret_cast<ServerInfo *>(arg);
    SOCKET server_socket = serverInfo->server_socket;
    SOCKET *clients = serverInfo->clients;
    int max_clients = serverInfo->max_clients;
    int &client_count = serverInfo->client_count;

    delete serverInfo;

    SOCKET client_socket;
    sockaddr_in client_addr{};
    int client_addr_size = sizeof(client_addr);

#define  MSG "Successfully connection to server"
    while((client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_addr), &client_addr_size))){
        clients[client_count++] = client_socket;
        send(client_socket, MSG, sizeof(MSG), 0);
        // Пытаемся получить имя хоста
        HOSTENT *hst;
        hst = gethostbyaddr((char *)&client_addr.sin_addr.s_addr, 4, AF_INET);
        // Вывод сведений о клиенте
        printf("\n+%s [%s] new connect\n",
               (hst) ? hst->h_name : "",
               inet_ntoa(client_addr.sin_addr));
        if (client_count) {
            printf("%d user online\n", client_count);
        } else {
            printf("No user online\n ");
        }
    }
    return 1;
}

