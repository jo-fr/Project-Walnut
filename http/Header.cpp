#include "Header.h"

#include <string>
#include <vector>

void Header::addHeaderline(const std::string& key,const std::string& value) {
    this->m_headers.insert(std::pair<std::string, std::string>(key, value));
}

///getMethod takes the HTTP method as a string and returns it as an enumerator
Header::httpMethod Header::getMethod(const std::string &method) {
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
Header::connection Header::getConnection(const std::string &connection) {
    if (connection == "keep-alive") return KEEPALIVE;
    if (connection == "close") return CLOSE;

    return INVALID;

}
