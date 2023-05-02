#include <iostream>
#include <Header.hpp>

class Request {
	private:
		Header		header;
		std::string	data;
	protected:

	public:
		Request();
		~Request();
		Request(const Request& other);
		const Request& operator=(const Request& other);

		virtual std::string toString() = 0;
};