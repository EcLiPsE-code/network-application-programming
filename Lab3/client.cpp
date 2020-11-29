
#include <iostream>
#include <cstdio>
#include "winsock2.h"
#include "windows.h"
#include <cmath>

#define PORT 123
#define SERVERADDR "127.0.0.1"

int main() {
    char *buff = new char[1024];
    printf("TCP CLIENT\n");

    if (WSAStartup(0x202, (WSADATA *) &buff[0])) {
        printf("WSAStart error %d\n", WSAGetLastError());
        return 1;
    }

    SOCKET client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        printf("Socket() error %d\n", WSAGetLastError());
        return 1;
    }

    sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    HOSTENT *hst;
    if (inet_addr(SERVERADDR) != INADDR_NONE) dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else{
        if (hst == gethostbyname(SERVERADDR)) {}
        else {
            printf("Invalid address %d\n", WSAGetLastError());
            closesocket(client_socket);
            WSACleanup();
            return 1;
        }
    }
    if (connect(client_socket, (sockaddr *) &dest_addr, sizeof(dest_addr))){
        printf("Connect error %d\n", WSAGetLastError());
        return 1;
    }
    printf("Connect with %s\n", SERVERADDR);

    printf("Enter quantity: ");
    int n; //кол-во уравнений
    std::cin >> n;

    double **a = new double*[n]; //матрица А
    double *y = new double[n]; // вектор У

    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            printf("a[%d][%d]= ", i, j);
            scanf("%lf", &a[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("y[%d]= ", i);
        scanf("%lf", &y[i]);
    }

    send(client_socket, (char*) &n, sizeof(int), 0);
    send(client_socket, (char*) y, sizeof(double) * n, 0);
    for ( int i = 0; i < n; i++) {
        send(client_socket, (char *) a[i], sizeof(double) * n, 0);
    }
    buff = new char [sizeof(double) * n];
    int bytes = recv(client_socket, buff, sizeof(double) * n, 0);
    double *x = (double*)buff;
    printf("x = [ ");
    for ( int i = 0; i < n; i++){
        printf(" %lf" , x[i]);
    }
    printf("]");
    closesocket(client_socket);
    WSACleanup();
    system("pause");
    return 0;
}
