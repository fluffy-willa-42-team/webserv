/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:54:46 by awillems          #+#    #+#             */
/*   Updated: 2023/05/03 09:03:45 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USING_HPP
# define USING_HPP

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

typedef struct unitests {
    int			success_expected;
    const char* value;
}	unitests;

#define VERBOSE_TEST true
#define HIDE_SUCCESFULL_TEST true

/* ************************************************************************** */

using std::pair;
using std::string;
using std::endl;
using std::cout;

/* ************************************************************************** */

#endif /* USING_HPP */