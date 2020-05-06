#include "Server.h"
#include "../http/Request.h"
#include "../http/Response.h"
#include "../utils.h"
#include <iostream>
#include <mime/mime.h>

#define WWW_DIRECTORY "./www"

Server::Server() {
    m_running = false;
    m_socket = Socket();
}

void Server::Run(int port) {
    m_socket.Bind(port);
    m_socket.Listen();
    m_running = true;

    printAddress(port);

    while (m_running) {
        Socket socket_accept = m_socket.Accept();

        char req[30000] = {0};
        socket_accept.Recv(req);

        std::cout << "######## Incoming Request ########" << std::endl;
        std::cout << req << std::endl;

        auto request = handleRequest(req);

        std::string path;
        if ((path = request->getPath()) == "/") path = "/index.html";

        auto response = makeResponse(path);

        std::cout << "######## Response Sent ########" << std::endl;
        std::string responseMessage = response->getResponseMsg();
        std::cout << responseMessage << std::endl;

        socket_accept.Send(responseMessage);

        socket_accept.Close();
    }

    m_socket.Close();
}

Response *Server::makeResponse(const std::string& path) {

    std::string content = utils::fetchFile(WWW_DIRECTORY, path);

    auto *res = new Response();
    if (!content.empty()) {
        res->setStatusCode(200);
        res->addHeaderline("Content-Type",mime::lookup(path));
        
    } else {
        res->setStatusCode(404);
        content = "<center>404: File not Found</center>";
        res->addHeaderline("Content-Type","text/html");
    }

    res->addHeaderline("Content-Length", std::to_string(content.size()));
    res->setResponseBody(content);
    res->makeResponseString();

    return res;
}

Request *Server::handleRequest(char *req) {
    auto *request = new Request(req);
    request->validateRequest();
    return request;
}

void Server::printAddress(int port) {
    std::cout << "##########################################################" << std::endl;
    std::cout << "######## Server running on http://localhost:" << port << "/ ########" << std::endl;
    std::cout << "##########################################################" << std::endl << std::endl;
}
