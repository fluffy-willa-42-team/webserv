/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 12:28:53 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHEADER_HPP
# define REQUESTHEADER_HPP

/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>

#include "using.hpp"

/* ************************************************************************** */

class RequestHeader {
	private:
		string method;			//	GET
		string path;			//	/test
		string protocol;		//	HTTP/1.1
		string host;			//	Host: www.example.com
		size_t port;			//	Host: www.example.com:8080
		string userAgent;		//	User-Agent: Mozilla/5.0
		string accept;			//	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
		string connection;		//	Connection: keep-alive

	// ParseLine.cpp {
		bool parse_line(const string& line, size_t index);
		bool parseStartLine(const string& line);
		bool parseHostHeader(const string& line);
		bool parseHeader(const string& line);
	// }
		
	protected:
	public:
		RequestHeader(const string& input);
		class InvalidRequest : public std::exception { public: virtual const char* what() const throw() { return ("Invalid Request"); } };
};

/* ************************************************************************** */

#endif /* REQUESTHEADER_HPP */