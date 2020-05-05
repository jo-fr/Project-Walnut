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
    this->m_version = std::move(version);
}

void Response::makeResponseString() {

    std::string full_response;
    full_response += "HTTP/1.1 " + std::to_string(this->m_statuscode) + " " + Header::statusCodes[this->m_statuscode] + "\r\n";

    for (const auto& line : m_headers) {
        std::string headerline;
        headerline += line.first + ": " + line.second;

        full_response += headerline + "\r\n";
    }
    full_response += "\r\n";

    full_response +=  m_body;
    this->m_response = std::move(full_response);

}

std::string Response::getResponseMsg() {
    return m_response;
}
