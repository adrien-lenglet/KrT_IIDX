# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_EXPR_IIF112 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF112(bit, expr) BOOST_PP_EXPR_IIF112_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF112(bit, expr) BOOST_PP_EXPR_IIF112_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF112_OO(par) BOOST_PP_EXPR_IIF112_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF112_I(bit, expr) BOOST_PP_EXPR_IIF112_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF112_0(expr)
# define BOOST_PP_EXPR_IIF112_1(expr) expr
