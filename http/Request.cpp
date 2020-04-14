#include "Request.h"

#include <utility>
#include <vector>
#include <sstream>
#include <iostream>
#include "../utils.h"
#include <stdexcept>
using namespace std;


Request::Request(char *req) {

    string startline , body;
    vector<string> headerlines;

    splitRequestIntoParts(&startline,&headerlines, &body, req);

    this->m_body = body;
    cout << "Body: " << this->m_body << endl;
    this->parseStartline(&startline);
    cout << "Startline: " << startline << endl;
    this->parseHeaders(&headerlines);

    this->validateRequest();

}

//splitRequestIntoParts takes the raw request and splits it into the startline, headlines, and m_body
void Request::splitRequestIntoParts(string *startline, vector<string> *headerlines, string *body, char *req) {
    std::stringstream line((req));
    std::string intermediate;
    vector<string> results;

    while(getline(line, intermediate, '\n')) {
        if(intermediate == "\r") {
            std::string b;

            getline(line, b, '\0');
            results.push_back(b);
            break;
        } else {
            utils::cleanString(&intermediate);
            results.push_back(intermediate);
        }
    }

    *startline = results.at(0);
    results.erase(results.begin());

    *body = results.at(results.size() - 1);
    results.erase(results.end() - 1);

    *headerlines = results;
}

//parseStartline takes the tokenized startline and casts it into its request object
void Request::parseStartline(string *line) {
    vector<string> values = utils::tokenize((*line), ' ');
    if (values.size() != 3) throw runtime_error("invalid Startline");

    string method = values.at(0);
    string path = values.at(1);
    string version = values.at(2);

    utils::cleanString(&version);

    this->m_method = getMethod(method);
    this->m_path = path;
    this->m_version = version;

}

//parseHeader takes a 3D vector and casts the headerlines into the Request object
void Request::parseHeaders(vector<string> *headerlines) {
    for (const auto & headerline : *headerlines) {
        auto v = utils::tokenize(headerline, ':', 2);
        cout << "Größe:" << v.size() << endl;
        if (v.size() != 2) throw runtime_error("invalid Headerline");

        auto key = move(v.at(0));
        auto value = move(v.at(1));

        auto tokenizedValues = utils::tokenize(value, ',');

        addHeaderline(key, tokenizedValues);

    }
}

//validateRequest checks if the header data is valid
void Request::validateRequest() {
    if (!this->isValidMethod()) throw runtime_error("HTTP Method is not valid");
    if (!this->isValidHTTPVersion()) throw runtime_error("HTTP Version is not valid");
}

//isValidHTTPVersion checks if the HTTP m_version is valid
bool Request::isValidHTTPVersion() {
    return m_version == "HTTP/1.1";
}

//isValidHTTPVersion checks if the HTTP method is valid
bool Request::isValidMethod() {
    return m_method != -1;
}
