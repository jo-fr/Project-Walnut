#pragma once

#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H

#include "Socket.h"
class Server {
private:
    Socket m_socket;
    bool m_running;
    char *m_msg;
    void parser(char buffer[]);

public:
    Server();
    void Run(int port);
};


#endif //WEBSERVER_SERVER_H
