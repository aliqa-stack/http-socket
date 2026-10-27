#include "http_server.h"
#include <iostream>
#include <sstream>
#include <arpa/inet.h>

namespace{
    void log(const std::string &message){
        std::cout<<message<<"\n";
    }

    void ExitWithError(const std::string &ErrorMessage){
        log("ERROR: " + ErrorMessage);
        exit(1);
    }
}

namespace http{
    TcpServer::TcpServer(std::string ip_adress, int port)
        :m_ipadress(ip_adress),m_port(port),m_socket(),m_new_socket(),m_incomingmessage(),
        socketAddress(),socketAddress_len(sizeof(socketAddress)),m_serverMSG()
    {
        Startserver();

    }
    TcpServer::~TcpServer(){
        CloseServer();
    }

    int TcpServer::Startserver(){
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(m_socket < 0){
            ExitWithError("cannot create socket");
            return 1;
        }
        return 0;
    }

    void TcpServer::ConnectSCT(){
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_port = htons(m_port);
        socketAddress.sin_addr.s_addr = INADDR_ANY;
        if(bind(m_socket, (struct sockaddr*)&socketAddress, sizeof(socketAddress)) < 0){
            ExitWithError("cannot bind the socket");
            CloseServer();

        }
        if(listen(m_socket, 20) < 0){
            ExitWithError("cannot cannot listen the ip");
            CloseServer();
 
        }
        std::ostringstream ss;
        ss<<"\n listening on address: "<<inet_ntoa(socketAddress.sin_addr)<<"PORT : "<<ntohs(socketAddress.sin_port)<<"***\n\n";
        log(ss.str());


    }

    void TcpServer::AcceptMSG(){
        int client = accept(m_socket, nullptr, &socketAddress_len);
        if(client < 0){
            ExitWithError("cannot accept client");
        }
        char buffer[1024] = {0};
        ssize_t received = read(client, buffer, sizeof(buffer) - 1);
        if(received < 0){
            ExitWithError("failed to received from client");
        }
        std::cout<<"message from client: "<<buffer<<"\n";
        close(client);
        CloseServer();

    }

    char TcpServer::SendMSG(){
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_port = htons(m_port);
        socketAddress.sin_addr.s_addr = INADDR_ANY;
        int clientSide = connect(m_socket, (struct sockaddr*)&socketAddress, socketAddress_len);
        if(clientSide < 0){
            ExitWithError("cannot connect to server");
        }
        char message[1024] = "hello from the client side";
        ssize_t packet = send(m_socket, message, strlen(message), MSG_NOSIGNAL);
        if(packet < 0){
            ExitWithError("failed sending a message");
        }
        close(m_socket);

        return *message;
    }

    void TcpServer::CloseServer(){
        close(m_socket);
        close(m_new_socket);
        exit(0);
    }
 
}

int main(){
    using namespace http; 
    TcpServer server = TcpServer("0.0.0.0", 8080);
    server.ConnectSCT();
    server.SendMSG();

    


    return 0;
}