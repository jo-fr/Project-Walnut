#include "Socket.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>

Socket::Socket() {
    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw std::runtime_error("unable to create socket");
};

void Socket::Bind(int port) {

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(port);

    m_addrlen = sizeof(m_address);

    memset(m_address.sin_zero, 0, m_addrlen);

    if (bind(m_socket, (struct sockaddr *)&m_address, m_addrlen) < 0)
        throw std::runtime_error("unable to bind socket");
}

void Socket::Listen() {
    if (listen(m_socket, 10) < 0)
        throw std::runtime_error("unable to listen");
}

Socket Socket::Accept() {
    int new_socket;
    if ((new_socket = accept(m_socket, (struct sockaddr *)&m_address, (socklen_t *)&m_addrlen)) < 0)
        throw std::runtime_error("unable to accept requests");

    return Socket(new_socket, m_address);
}

void Socket::Recv(char *req) {
    if (recv(m_socket, req, 30000, 0) < 0)
        throw std::runtime_error("nothing to read");
}

void Socket::Send(char *resp) {
    if (send(m_socket, resp, strlen(resp), 0) < 0)
        throw std::runtime_error("unable to send");
}

void Socket::Close() {
    if(m_socket != 0) close(m_socket);
    m_socket = 0;
}
