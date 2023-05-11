#include <Redirect.hpp>

RedirectContent::RedirectContent(const string& path) : Content(path){
	cout << PURPLE << "Constructing a Redirect Content" << RESET << endl;
}

RedirectContent::~RedirectContent(){};

string RedirectContent::toString() const {
	return "";
}