#include <Redirect.hpp>

RedirectContent::RedirectContent(const string& path) : Content(path){
	cout << PURPLE << "Constructing a Redirect Content" << RESET << endl;
}

RedirectContent::~RedirectContent(){};

string RedirectContent::toString() const {
	return "";
}

/*

301 Moved Permanently	: The requested resource has been permanently moved to a new URL, and future requests should use the new URL.
302 Found				: The requested resource has been temporarily moved to a new URL, and future requests should continue to use the original URL.
303 See Other			: The requested resource can be found at a different URL, and the client should retrieve the resource using a GET request to the new URL.
307 Temporary Redirect	: The requested resource has been temporarily moved to a new URL, and future requests should continue to use the original URL.
308 Permanent Redirect	: The requested resource has been permanently moved to a new URL, and future requests should use the new URL.

*/