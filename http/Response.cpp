#include "Response.h"

#include <utility>
#include <vector>
#include <map>
#include <string>
#include <iostream>

void Response::setStatusCode(int statuscode) {
    this->m_statuscode = statuscode;
}

Response::Response() {
}

void Response::setResponseBody(std::string body) {
    this->m_body = std::move(body);
}

void Response::setVersion(std::string version) {
    this->m_version = version;
}

void Response::makeResponseMsg() {


    //stringifyHeader
    //setStartline

    auto startline = "HTTP/1.1 "  + std::to_string(this->m_statuscode) + " " + Header::statusCodes[this->m_statuscode] + "\n";
    //setHeaders
    std::string header;

    for (const auto& line : m_headers) {
        std::string headerline;
        headerline += line.first + ": ";

        for (const auto& entry : line.second) {
            headerline += entry;

            //TODO: add comma seperation
            //headerline +=",";
        }

        header += headerline + "\n";
    }

    std::string body = "\n" + this->m_body;
   auto full_response = startline + header + body;
   m_response = const_cast<char *>(full_response.c_str());


}

char *Response::getResponseMsg() {
    return this->m_response;
}


