#include <CGI.hpp>

CGIContent::CGIContent(const string& path) : Content(path){
	cout << PURPLE << "Constructing a CGI Content" << RESET << endl;
};

CGIContent::~CGIContent(){}

string CGIContent::toString() const {
	return "";
}