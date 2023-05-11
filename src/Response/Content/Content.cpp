#include "Content.hpp"

Content::~Content(){}

std::ostream& operator<<(std::ostream& out, const Content& content)
{
	out << content.toString();
	return out;
}