#include "utils.h"
#include <fstream>
//cleanString removes spaces and line breaks from the start and end of a given string
void utils::cleanString(std::string *string) {
    if ((*string)[0] == ' ') string->erase(string->begin());
    if ((*string)[string->size() - 1] == ' ') string->erase(string->end() - 1);
    if ((*string)[string->size() - 1] == '\n') string->erase(string->end() - 1);
    if ((*string)[string->size() - 1] == '\r') string->erase(string->end() - 1);
}

//tokenize splits a given input string into tokens on every given delimiter
std::vector<std::string> utils::tokenize(const std::string &input, char delimiter, int iterations) {
    std::stringstream line((input));
    std::vector<std::string> tokens;
    std::string intermediate;
    auto splitCounter = 0;

    while ((iterations == -1 || splitCounter < iterations) && getline(line, intermediate, delimiter)) {
        cleanString(&intermediate);
        tokens.push_back(intermediate);
        splitCounter++;
    }

    return tokens;
}

std::string utils::fetchFile(const std::string& directory, const std::string& file) {

    std::ifstream ifs(directory + file);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                    (std::istreambuf_iterator<char>()    ) );

    return content;
}
