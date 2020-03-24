#include "Server.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>


Server::Server() {
    m_running = false;
    m_socket = Socket();
    m_msg = (char *)"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 20\n\n <h1>Hello World</h1>";
}

void Server::Run(int port) {
    m_socket.Bind(port);
    m_socket.Listen();
    m_running = true;
    std::cout << "##########################################################" << std::endl;
    std::cout << "######## Server running on http://localhost:" << port << "/ ########" << std::endl;
    std::cout << "##########################################################" << std::endl << std::endl;

    while (m_running) {
        Socket socket_accept = m_socket.Accept();

        char req[30000] = {0};
        socket_accept.Recv(req);
        std::cout << "######## Incoming Request ########" << std::endl;
        parser(req);

       socket_accept.Send(m_msg);
        std::cout << "######## Response Sent ########" << std::endl;
        std::cout << m_msg << std::endl;

        socket_accept.Close();
    }

    m_socket.Close();
}

void Server::parser(char buffer[]) {
    std::cout << buffer << std::endl;
}
