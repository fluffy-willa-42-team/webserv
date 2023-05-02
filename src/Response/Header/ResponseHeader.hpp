/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:11:39 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 09:12:09 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

class ResponseHeader {
	private:
	protected:
	public:
		ResponseHeader();
		~ResponseHeader();
		ResponseHeader(const ResponseHeader& other);
		const ResponseHeader& operator=(const ResponseHeader& other);
};

/* ************************************************************************** */

#endif /* RESPONSEHEADER_HPP */