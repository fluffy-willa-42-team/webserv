#include <iostream>
#include <ResponseHeader.hpp>

class Response {
	private:
	protected:

	public:
		Response();
		~Response();
		Response(const Response& other);
		const Response& operator=(const Response& other);
};