#pragma once

#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H

#include "Socket.h"
#include <string>

class Server {
private:
    Socket m_socket;
    bool m_running;

public:
    Server();
    void Run(int port);


};


#endif //WEBSERVER_SERVER_H
