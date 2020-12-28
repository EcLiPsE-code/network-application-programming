#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <vector>
#include <ctime>
#include <sys/select.h>
#include <iostream>
#include <cmath>
using namespace std;


int nclients = 0;

int CountOfClients;
long start_time, end_time;

int main() {
  double A, B, newA, newB, eps, length, s1 = 0, s = 0;
  // create a socket
  int server_socket = 0;
  int checkSelect, checkBind, checkListen, checkSend, checkSockopt;
  fd_set master; // create a master set
  fd_set clients; // create set for clients
  printf("TCP SERVER \n");
  cout << "Enter the number of clients:\n";
  cin >> CountOfClients;
    cout << "Enter A:\n";
    cin >> A;
    cout << "Enter B:\n";
    cin >> B;
    cout << "Enter eps:\n";
    cin >> eps;
    length = (B - A) / CountOfClients;

  setlocale(0, "");
  newA = A;
    newB = A + length;
    vector<double> newAs(CountOfClients);
    vector<double> newBs(CountOfClients);
    newAs[0] = newA;
    newBs[0] = newB;
    for (int i = 1; i < CountOfClients; i++)
    {
        newA = newB;
        newB = newB + length;
        newAs[i] = newA;
        newBs[i] = newB;


    }


  // define the server address
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  FD_ZERO(&master); // zero the set

  // (Domain, Type of socket, Protocol)
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(server_socket == -1){
    perror("socket");
    exit(1);
  }

  // bind the socket to our specified IP and port
  server_address.sin_family = AF_INET; // // knows what type of server_address
  server_address.sin_port = htons(9002); // htons() converts data format so that our struct can understand the port number
  server_address.sin_addr.s_addr = INADDR_ANY; // bind to any available address
  memset(server_address.sin_zero, '\0', sizeof server_address.sin_zero); // for padding, to make it the same size as struct sockaddr

  int yes = 1;
  checkSockopt = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  if(checkSockopt == -1){
    perror("setsockopt");
    exit(1);
  }

  checkBind = bind(server_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
  if(checkBind == -1){
    perror("unable to bind");
    exit(1);
  }

  // begin listening for clients attempting to connect
  checkListen = listen(server_socket, CountOfClients);
  if(checkListen == -1){
    perror("listen");
    exit(1);
  }

  fflush(stdout);

  //printf("server socket: \t%d\n", server_socket);
  FD_SET(server_socket, &master); // sets the bit for the server_socket in the master socket set
  printf("Ожидание подключений...\n");
  //My
  socklen_t addrlen;
  int client_socket;
  addrlen = sizeof(struct sockaddr_in);
  vector<int> client_sockets(CountOfClients);
  while(client_socket = accept(server_socket, (struct sockaddr *)&client_address, &addrlen)){
	  client_sockets[nclients] = client_socket;
	  nclients++; // увеличиваем счетчик подключившихся клиентов
	  // пытаемся получить имя хоста
	  hostent* hst;
	  hst = gethostbyaddr((char*)&client_address.sin_addr.s_addr, 4, AF_INET);

	  // вывод сведений о клиенте
	  printf("+%s [%s] new connect!\n",
		  (hst) ? hst->h_name : "", inet_ntoa(client_address.sin_addr));
	  if (nclients == CountOfClients) {
		  start_time = clock();
		  for (int i = 0; i < CountOfClients; i++) {
		      	send(client_sockets[i], (char*)&newAs[i], sizeof(double), 0);
                	send(client_sockets[i], (char*)&newBs[i], sizeof(double), 0);
                	send(client_sockets[i], (char*)&eps, sizeof(double), 0);
	                int bytes_recv;
	                bytes_recv = recv(client_sockets[i], (char*)&s1, sizeof(double), 0);
	                //cout << "new S = " << s1 << endl;
	                s = s + s1;
	                nclients--;
	                printf("-disconnect\n");
	                {
	                    close(client_sockets[i]);
	                }
		  }
		              end_time = clock() - start_time;
           		      cout << "Final S = " << s << endl;

	  }
  }
  //EndMy

close(server_socket);
return 0;
}
