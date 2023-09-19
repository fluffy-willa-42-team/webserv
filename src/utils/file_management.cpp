#include "utils.hpp"

bool isFileReadable(const string& filepath) {
    ifstream file(filepath.c_str());

    if (file.is_open()) {
        file.close();
        return true;
    }

    return false;
}