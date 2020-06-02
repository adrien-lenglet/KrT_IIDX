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
# /* BOOST_PP_EXPR_IIF186 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF186(bit, expr) BOOST_PP_EXPR_IIF186_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF186(bit, expr) BOOST_PP_EXPR_IIF186_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF186_OO(par) BOOST_PP_EXPR_IIF186_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF186_I(bit, expr) BOOST_PP_EXPR_IIF186_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF186_0(expr)
# define BOOST_PP_EXPR_IIF186_1(expr) expr
