#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>




int main(){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0 );
    if (clientSocket < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("connect");
        close(clientSocket);
        return 1;
    }

     char message[1024];
    std::cin>>message;
    if (send(clientSocket, &message, strlen(message), MSG_NOSIGNAL) < 0) {
        perror("send");
        close(clientSocket);
        return 1;
    }
    close(clientSocket);
    

    return 0;
}