#pragma once

#ifndef WEBSERVER_SOCKET_H
#define WEBSERVER_SOCKET_H

#include <netinet/in.h>
#include <string>

class Socket {

private:
    int m_socket, m_addrlen{};
    struct sockaddr_in m_address{};
    explicit Socket(int new_socket, sockaddr_in address): m_socket(new_socket), m_address(address){};

public:
    Socket();
    void Bind(int port);
    void Close();
    void Listen();
    Socket Accept();
    void Recv(char* req);
    void Send(const std::string resp);

};


#endif //WEBSERVER_SOCKET_H
