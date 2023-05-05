#ifndef TEST_HPP
# define TEST_HPP

/* ************************************************************************** */

typedef struct unitests {
    int			success_expected;
    const char* value;
}	unitests;

#define VERBOSE_TEST            true
#define HIDE_SUCCESFULL_TEST    false
#define SHOW_ERROR_IN_PARSING   false

/* ************************************************************************** */

#endif /* TEST_HPP */