#ifndef HTTP_SERVER_LINUX
#define HTTP_SERVER_LINUX
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include <string>

//soon will be added code for windows
#if defined(WIN32)
    #include <winsock.h>
    #include <stdlib.h>
    #include <string.h>
#endif //win32 api

namespace http{
    class TcpServer{
        public:
            TcpServer(std::string ip_adress, int port);
            ~TcpServer();
        private:
            std::string m_ipadress;
            int m_port;
            int m_socket;
            int m_new_socket;
            char client_msg;
            long m_incomingmessage;
            struct sockaddr_in socketAddress;
            unsigned int socketAddress_len;
            std::string m_serverMSG;

            int Startserver();
            void ConnectSCT();
            void SendMSG();
            void AcceptMSG();
            void SendMSG();
            void CloseServer();

    };
}



#endif //http_server