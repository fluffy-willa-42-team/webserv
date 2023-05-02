/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:05 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 09:13:43 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

/* ************************************************************************** */

#include <iostream>
#include <RequestHeader.hpp>

/* ************************************************************************** */

class Request {
	private:
		RequestHeader header;
	protected:
	public:
		Request(){}
		~Request(){}
		Request(const Request& other) : header(other.header){}

		const Request& operator=(const Request& other){
			this->header = other.header;
			return (*this);
		}

		Request(const std::string& input){
			std::cout << input << std::endl;
		}
};

/* ************************************************************************** */

#endif /* REQUEST_HPP */