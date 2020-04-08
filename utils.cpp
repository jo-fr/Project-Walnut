#include <vector>
#include <sstream>
#include <iostream>

namespace utils {

    std::vector<std::string> tokenize(const std::string& input, char delimiter) {
        std::stringstream line(input);
        std::vector<std::string> tokens;
        std::string intermediate;

        while (getline(line, intermediate, delimiter)) {
            tokens.push_back(intermediate);
        }

        return tokens;
    }
}