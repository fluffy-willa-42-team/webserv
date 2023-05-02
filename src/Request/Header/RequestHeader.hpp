/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:00 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 09:14:16 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHEADER_HPP
# define REQUESTHEADER_HPP

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

class RequestHeader {
	private:
		std::string method;
		std::string test;
	protected:
	public:
		RequestHeader(){}
		~RequestHeader(){}
		RequestHeader(const RequestHeader& other){(void) other;}
		const RequestHeader& operator=(const RequestHeader& other){
			(void) other;
			return (*this);
		}
};

/* ************************************************************************** */

#endif /* REQUESTHEADER_HPP */