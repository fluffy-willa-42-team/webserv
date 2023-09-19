#include "utils.hpp"
#include "unistd.h"

bool isFileReadable(const string& filepath) {
    ifstream file(filepath.c_str());

    if (file.is_open()) {
        file.close();
        return true;
    }

    return false;
}

bool isFileExecutable(const std::string& filepath) {
    // Check if the file exists
    if (access(filepath.c_str(), F_OK) == -1) {
        return false;
    }

    // Check if the file is executable
    return access(filepath.c_str(), X_OK) == 0;
}