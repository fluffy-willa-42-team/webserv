#include "Content.hpp"

Content::~Content(){}

std::ostream& operator<<(std::ostream& out, const Content& content)
{
	out	<< "Content-Length: " << content.length;

	if (content.length > 0)
	out	<< endl << "Content-Type: " << content.type << endl
		<< endl
		<< content.toString();
	return out;
}