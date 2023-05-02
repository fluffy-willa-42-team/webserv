#include <iostream>

class RequestHeader {
	private:
	protected:
	public:
		RequestHeader();
		~RequestHeader();
		RequestHeader(const RequestHeader& other);
		const RequestHeader& operator=(const RequestHeader& other);
};
