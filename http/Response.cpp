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

    auto statuscode = std::to_string(this->m_statuscode);
    auto statusMessage = Header::statusCodes[this->m_statuscode];

    auto startline = "HTTP/1.1 " + statuscode + " " + statusMessage + "\n";

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
    header += "\n";

    auto body = this->m_body;
    auto full_response = startline + header + body;
    this->m_response = const_cast<char *>(full_response.c_str());

}

char* Response::getResponseMsg() {
    return this->m_response;
}
