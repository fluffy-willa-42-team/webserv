#include <iostream>
#include <Header.hpp>

class Request {
	private:
	protected:

	public:
		Request();
		~Request();
		Request(const Request& other);
		const Request& operator=(const Request& other);
};