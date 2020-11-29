//
// Created by YoUr_IcOn on 06.11.2020.
//

#include "iostream"
#include <cstdio>
#include "winsock2.h"
#include "windows.h"
#include <cmath>

#define PORT 123

int count_clients = 0;

double * gauss(double **a, double *y, int n)
{
    double *x, max;
    int k, index;
    const double eps = 0.00001;  // точность
    x = new double[n];
    k = 0;
    while (k < n)
    {
        // Поиск строки с максимальным a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < eps)
        {
            return 0;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        // Нормализация уравнений
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}

DWORD WINAPI thread_func(LPVOID context){
    SOCKET client_socket = *(SOCKET*) context;
    char *buff = new char[sizeof(int)];
    int bytes = recv(client_socket, buff, sizeof(int), 0);
    int n = *(int*)buff;
    buff = new char [sizeof(double) * n];
    bytes = recv(client_socket, buff, sizeof(double) * n, 0);
    double *y = (double*)buff;
    double **b = new double*[n];
    for (int i = 0; i < n; i++) {
        b[i] = new double[n];
    }
    for (int i = 0; i < n; i++) {
        b[i] = new double[n];
        bytes = recv(client_socket, (char*)b[i], sizeof(double) * n, 0);
    }
    double *x = gauss(b, y, n);
    send(client_socket, (char*) x, sizeof(double) * n, 0);
    closesocket(client_socket);
    return 0;
}

int main(int argc, char* argv[]){
    char buff[1024];

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
    local_addr.sin_port = htons(PORT);
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

    SOCKET client_socket;
    sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);

    while(client_socket = accept(server_socket, (sockaddr *) (&client_addr), &client_addr_size)){
        HOSTENT *hst;
        hst = gethostbyaddr((char *)&client_addr.sin_addr.s_addr, 4, AF_INET);
        printf("\n+%s [%s] new connect\n",
               (hst) ? hst->h_name : "",
               inet_ntoa(client_addr.sin_addr));
        QueueUserWorkItem(thread_func, &client_socket, 0);
    }
    return 0;
}