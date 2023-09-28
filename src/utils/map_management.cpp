#include "utils.hpp"

char** createCopy(const map<string, string>& myMap) {
    char** charArray = new char*[myMap.size()];

    size_t i = 0;
    for (map<string, string>::const_iterator it = myMap.begin(); it != myMap.end(); ++it) {
        string keyValue = it->first + "=" + it->second;
        charArray[i] = new char[keyValue.length() + 1];
        std::strcpy(charArray[i], keyValue.c_str());
        ++i;
    }

    return charArray;
}

void freeCopy(const map<string, string>& myMap, char** copy) {
    for (size_t i = 0; i < myMap.size(); ++i) {
        delete[] copy[i];
    }
    delete[] copy;
}