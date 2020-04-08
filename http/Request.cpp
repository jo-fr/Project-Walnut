//
// Created by Ford Prefect on 07.04.20.
//

#include "Request.h"

#include <vector>
#include <sstream>
#include <iostream>
#include "../utils.cpp"


Request::Request(char *req) {

    std::vector<std::vector<std::string>> results = tokenizeRequest(req);

    this->parseStartline(results.at(0));
    this->parseHeaders(results);

    this->validateRequest();

};

//tokenizeRequest takes the raw request and splits it up on every '\n' and ' ' into a 3D vector
std::vector<std::vector<std::string>> Request::tokenizeRequest(char *req) {
    std::vector<std::string> lines = utils::tokenize(req, '\n');
    std::vector<std::vector<std::string>> results;

    results.reserve(lines.size());
for (const auto & line : lines) {
        results.push_back(utils::tokenize(line, ' '));
    }

    return results;
}

//parseStartline takes the tokenized startline and casts it into its request object
void Request::parseStartline(std::vector<std::string> line) {
    this->method = getMethod(line.at(0));
    this->path = line.at(1);
    this->version = line.at(2);

}

//parseHeader takes a 3D vector and casts the header lines into the Request object
void Request::parseHeaders(std::vector<std::vector<std::string>> headerlines) {
    for (auto &line : headerlines) {
        if (line[0] == "Host:") this->headers.host = line[1];
        if (line[0] == "Accept-Language:") this->headers.language = utils::tokenize(line[1], ',');
        if (line[0] == "Accept:") this->headers.acceptTypes = utils::tokenize(line[1], ',');
        if (line[0] == "Connection:") this->headers.connection = getConnection(line[1]);
    }
}

//validateRequest checks if the header data is valid
void Request::validateRequest() {
    if (!this->isValidMethod())
        throw std::runtime_error("HTTP Method is not valid");

    if (!this->isValidHTTPVersion())
        throw std::runtime_error("HTTP Version is not valid");
}
//isValidHTTPVersion checks if the HTTP version is valid
bool Request::isValidHTTPVersion() {
    return version == "HTTP/1.1\r";
}

//isValidHTTPVersion checks if the HTTP method is valid
bool Request::isValidMethod() {
    return method != -1;
}

//getMethod takes the HTTP method as a string and returns it as an enumerator
httpMethod Request::getMethod(const std::string &method) {
    if (method == "GET") return GET;
    if (method == "POST") return POST;
    if (method == "PUT") return PUT;
    if (method == "DELETE") return DELETE;
    if (method == "CONNECT") return CONNECT;
    if (method == "HEAD") return HEAD;
    if (method == "OPTIONS") return OPTIONS;
    if (method == "PATCH") return PATCH;
    if (method == "TRACE") return TRACE;

    return UNKNOWN;

}

///getConnection takes the connection type and returns it as an enumerator
connection Request::getConnection(const std::string &connection) {
    if (connection == "keep-alive") return KEEPALIVE;
    if (connection == "close") return CLOSE;

    return INVALID;

}

void Request::printRequest() {
    std::cout << "Host: " << this->headers.host << std::endl;
    std::cout << "Path: " << this->path << std::endl;
    std::cout << "Method: " << this->method << std::endl;

    for (auto &i : this->headers.acceptTypes) {
        std::cout << i << std::endl;
    }
}
