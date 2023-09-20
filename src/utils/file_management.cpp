#include "utils.hpp"
#include "unistd.h"
#include <sys/stat.h>

bool isFileReadable(const string& filepath) {
    ifstream file(filepath.c_str());

    if (file.is_open()) {
        file.close();
        return true;
    }

    return false;
}

bool isFileExecutable(const string& filepath) {
    // Check if the file exists
    if (access(filepath.c_str(), F_OK) == -1) {
        return false;
    }

    // Check if the file is executable
    return access(filepath.c_str(), X_OK) == 0;
}

bool doesFolderExists(const string& folderPath) {
    struct stat info;
    if (stat(folderPath.c_str(), &info) != 0) {
        // If stat fails, the folder does not exist or is inaccessible.
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

string mergeFilePaths(const string& base, const string& path) {
    if (path.empty() || path[0] == '/') {
        return path;
    }

    string result;

    // Include the leading "./" if the file path starts with "./"
    if (path.find("./") == 0) {
        result = "./";
    }

    // Remove leading './' from the path
    string cleanedPath = path;
    if (cleanedPath.find("./") == 0) {
        cleanedPath = cleanedPath.substr(2);
    }

    // Ensure that the cleaned path does not start with '/'
    if (cleanedPath[0] == '/') {
        cleanedPath = cleanedPath.substr(1);
    }

    result += base;

    // Ensure that the base path ends with a '/'
    if (!base.empty() && base[base.length() - 1] != '/') {
        result += '/';
    }

    result += cleanedPath;
    return result;
}