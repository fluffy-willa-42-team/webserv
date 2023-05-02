#include <iostream>

class Header {
	private:
	protected:
	public:
		Header();
		~Header();
		Header(const Header& other);
		const Header& operator=(const Header& other);
};
