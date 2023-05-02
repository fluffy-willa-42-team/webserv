#include <iostream>

class ResponseHeader {
	private:
	protected:
	public:
		ResponseHeader();
		~ResponseHeader();
		ResponseHeader(const ResponseHeader& other);
		const ResponseHeader& operator=(const ResponseHeader& other);
};
