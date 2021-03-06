#pragma once
#ifndef WEBSERVER_RESPONSE_H
#define WEBSERVER_RESPONSE_H

#include <string>
#include "Header.h"


class Response : public Header {
private:
    int m_statuscode{};
    std::string m_response;


public:
    Response();
    void setStatusCode(int statuscode);
    void setVersion(std::string version);
    void setResponseBody(std::string body);
    void makeResponseString();
    std::string getResponseMsg();

};


#endif //WEBSERVER_RESPONSE_H
