#ifndef WEBSERVER_REQUEST_H
#define WEBSERVER_REQUEST_H

#include <string>
#include <vector>
#include <sstream>

enum httpMethod {
    GET,
    POST,
    PUT,
    DELETE,
    CONNECT,
    HEAD,
    OPTIONS,
    PATCH,
    TRACE,
    UNKNOWN = -1,
};

enum connection {
    CLOSE,
    KEEPALIVE,
    INVALID = -1,
};

struct headers {
    std::string host;
    std::vector<std::string> acceptTypes;
    std::vector<std::string> language;
    connection connection;

};

class Request {
private:
    httpMethod method;
    std::string path;
    std::string version;
    headers headers{};
    std::string body = "";

    static std::vector<std::vector<std::string>> tokenizeRequest(char* req);
    void parseHeaders( std::vector<std::vector<std::string>>);
    void parseStartline(std::vector<std::string> line);
    static httpMethod getMethod(const std::string& method);
    static connection getConnection(const std::string& connection);
    bool isValidHTTPVersion();
    bool isValidMethod();

public:
    explicit Request(char* req);
    void validateRequest();
    void printRequest();

};


#endif //WEBSERVER_REQUEST_H
