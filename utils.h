#pragma once

#include <vector>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace utils {

    void cleanString(std::string *string);
    std::vector<std::string> tokenize(const std::string &input, char delimiter, int iterations = -1);
    std::string fetchFile(const std::string& file);

};
