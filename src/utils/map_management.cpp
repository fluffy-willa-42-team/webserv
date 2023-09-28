#include "utils.hpp"

char** createCopy(const vector<string>& vec) {
	char** charArray = new char*[vec.size() + 1];
	memset(charArray, 0, (vec.size() + 1) * sizeof(char*));

	for (size_t i = 0; i < vec.size(); ++i) {
		charArray[i] = new char[vec[i].length() + 1];
		std::strcpy(charArray[i], vec[i].c_str());
	}
	return charArray;
}

void freeCopy(const vector<string>& vec, char *const *copy) {
	for (size_t i = 0; i < vec.size(); ++i) {
		delete[] copy[i];
	}
	delete[] copy;
}
