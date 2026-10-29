#ifndef HTTP_SERVER_LINUX
#define HTTP_SERVER_LINUX

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

#if defined(WIN32)
    #include <winsock.h>
    #include <stdlib.h>
    #include <string.h>
#endif

namespace http{
    class TcpServer {
    public:
        TcpServer(std::string ip_adress, int port);
        ~TcpServer();

        void ConnectSCT();
        void AcceptMSG();
        void SendMSG(const std::string& message);

    private:
        std::string m_ipadress;
        int m_port;
        int m_socket;
        int m_new_socket;
        struct sockaddr_in socketAddress;
        unsigned int socketAddress_len;
        std::string m_serverMSG;

        int Startserver();
        void address_Storage();
        void CloseServer();
    };
}

#endif // HTTP_SERVER_LINUX