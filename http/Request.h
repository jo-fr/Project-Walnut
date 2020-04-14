#pragma once
#ifndef WEBSERVER_REQUEST_H
#define WEBSERVER_REQUEST_H

#include <string>
#include <vector>
#include <sstream>
#include "Header.h"

class Request : public Header {

private:
    void parseHeaders(std::vector<std::string> *headerlines);
    void parseStartline(std::string *line);
    bool isValidHTTPVersion();
    bool isValidMethod();
    static void splitRequestIntoParts(std::string *startline, std::vector<std::string> *headerlines, std::string *body, char *req);

public:
    explicit Request(char *req);
    void validateRequest();
};

#endif //WEBSERVER_REQUEST_H
