#include "Server.h"
#include "../http/Request.h"
#include "../http/Response.h"
#include "../utils.h"
#include <iostream>

Server::Server() {
    m_running = false;
    m_socket = Socket();
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
        auto *r = new Request(req);
        std::cout << "######## Incoming Request ########" << std::endl;
        std::cout << req << std::endl;
        r->validateRequest();

        std::string path = r->getPath();
        std::string msg = utils::fetchFile("../www", path);
        auto *res = new Response();
        res->setStatusCode(200);
        std::cout << "######## Response Sent ########" << std::endl;
        res->setResponseBody(msg);
        res->addHeaderline("Content-Length", std::vector<std::string>{std::to_string(msg.size())});
        res->addHeaderline("Content-Type", std::vector<std::string>{"text/html"});
        res->makeResponseMsg();


        std::cout << res->getResponseMsg() << std::endl;
        socket_accept.Send(res->getResponseMsg());

        socket_accept.Close();
    }

    m_socket.Close();
}
