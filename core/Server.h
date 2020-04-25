#pragma once

#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H

#include "Socket.h"
#include "../http/Response.h"
#include "../http/Request.h"
#include <string>

class Server {
private:
    Socket m_socket;
    bool m_running;
    static Request* handleRequest(char *req);
    static Response* makeResponse(const std::string& path);
    void printAddress(int port);

public:
    Server();
    void Run(int port);


};


#endif //WEBSERVER_SERVER_H
