/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:12:53 by awillems          #+#    #+#             */
/*   Updated: 2023/05/02 09:13:14 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_HPP
# define POST_HPP

/* ************************************************************************** */

#include <iostream>
#include <Response.hpp>

/* ************************************************************************** */

class Post : private Response {
	private:
	protected:

	public:
		Post();
		~Post();
		Post(const Post& other);
		const Post& operator=(const Post& other);

		std::string toString(){}
};

/* ************************************************************************** */

#endif /* POST_HPP */