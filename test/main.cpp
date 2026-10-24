#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>




int main(){
    int server = socket(AF_INET, SOCK_STREAM, 0 );
    if (server < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    if (bind(server, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind");
        close(server);
        return 1;
    }
    if (listen(server, 5) < 0) {
        perror("listen");
        close(server);
        return 1;
    }

    int client = accept(server, nullptr, nullptr);
    if (client < 0) {
        perror("accept");
        close(server);
        return 1;
    }

    char buffer[1024] = {0};
    ssize_t received = recv(client, buffer, sizeof(buffer) - 1, 0);
    if (received < 0) {
        perror("recv");
        close(client);
        close(server);
        return 1;
    }
    std::cout<<"message from client : "<<buffer<<"\n";
    close(client);
    close(server);

    return 0;
}
