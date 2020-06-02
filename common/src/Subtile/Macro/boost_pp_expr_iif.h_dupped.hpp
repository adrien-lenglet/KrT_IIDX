#pragma once

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
# /* BOOST_PP_EXPR_IIF0 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF0(bit, expr) BOOST_PP_EXPR_IIF0_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF0(bit, expr) BOOST_PP_EXPR_IIF0_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF0_OO(par) BOOST_PP_EXPR_IIF0_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF0_I(bit, expr) BOOST_PP_EXPR_IIF0_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF0_0(expr)
# define BOOST_PP_EXPR_IIF0_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF1 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF1(bit, expr) BOOST_PP_EXPR_IIF1_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF1(bit, expr) BOOST_PP_EXPR_IIF1_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF1_OO(par) BOOST_PP_EXPR_IIF1_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF1_I(bit, expr) BOOST_PP_EXPR_IIF1_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF1_0(expr)
# define BOOST_PP_EXPR_IIF1_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF2 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF2(bit, expr) BOOST_PP_EXPR_IIF2_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF2(bit, expr) BOOST_PP_EXPR_IIF2_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF2_OO(par) BOOST_PP_EXPR_IIF2_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF2_I(bit, expr) BOOST_PP_EXPR_IIF2_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF2_0(expr)
# define BOOST_PP_EXPR_IIF2_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF3 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF3(bit, expr) BOOST_PP_EXPR_IIF3_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF3(bit, expr) BOOST_PP_EXPR_IIF3_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF3_OO(par) BOOST_PP_EXPR_IIF3_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF3_I(bit, expr) BOOST_PP_EXPR_IIF3_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF3_0(expr)
# define BOOST_PP_EXPR_IIF3_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF4 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF4(bit, expr) BOOST_PP_EXPR_IIF4_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF4(bit, expr) BOOST_PP_EXPR_IIF4_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF4_OO(par) BOOST_PP_EXPR_IIF4_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF4_I(bit, expr) BOOST_PP_EXPR_IIF4_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF4_0(expr)
# define BOOST_PP_EXPR_IIF4_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF5 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF5(bit, expr) BOOST_PP_EXPR_IIF5_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF5(bit, expr) BOOST_PP_EXPR_IIF5_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF5_OO(par) BOOST_PP_EXPR_IIF5_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF5_I(bit, expr) BOOST_PP_EXPR_IIF5_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF5_0(expr)
# define BOOST_PP_EXPR_IIF5_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF6 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF6(bit, expr) BOOST_PP_EXPR_IIF6_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF6(bit, expr) BOOST_PP_EXPR_IIF6_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF6_OO(par) BOOST_PP_EXPR_IIF6_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF6_I(bit, expr) BOOST_PP_EXPR_IIF6_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF6_0(expr)
# define BOOST_PP_EXPR_IIF6_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF7 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF7(bit, expr) BOOST_PP_EXPR_IIF7_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF7(bit, expr) BOOST_PP_EXPR_IIF7_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF7_OO(par) BOOST_PP_EXPR_IIF7_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF7_I(bit, expr) BOOST_PP_EXPR_IIF7_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF7_0(expr)
# define BOOST_PP_EXPR_IIF7_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF8 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF8(bit, expr) BOOST_PP_EXPR_IIF8_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF8(bit, expr) BOOST_PP_EXPR_IIF8_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF8_OO(par) BOOST_PP_EXPR_IIF8_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF8_I(bit, expr) BOOST_PP_EXPR_IIF8_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF8_0(expr)
# define BOOST_PP_EXPR_IIF8_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF9 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF9(bit, expr) BOOST_PP_EXPR_IIF9_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF9(bit, expr) BOOST_PP_EXPR_IIF9_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF9_OO(par) BOOST_PP_EXPR_IIF9_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF9_I(bit, expr) BOOST_PP_EXPR_IIF9_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF9_0(expr)
# define BOOST_PP_EXPR_IIF9_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF10 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF10(bit, expr) BOOST_PP_EXPR_IIF10_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF10(bit, expr) BOOST_PP_EXPR_IIF10_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF10_OO(par) BOOST_PP_EXPR_IIF10_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF10_I(bit, expr) BOOST_PP_EXPR_IIF10_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF10_0(expr)
# define BOOST_PP_EXPR_IIF10_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF11 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF11(bit, expr) BOOST_PP_EXPR_IIF11_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF11(bit, expr) BOOST_PP_EXPR_IIF11_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF11_OO(par) BOOST_PP_EXPR_IIF11_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF11_I(bit, expr) BOOST_PP_EXPR_IIF11_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF11_0(expr)
# define BOOST_PP_EXPR_IIF11_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF12 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF12(bit, expr) BOOST_PP_EXPR_IIF12_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF12(bit, expr) BOOST_PP_EXPR_IIF12_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF12_OO(par) BOOST_PP_EXPR_IIF12_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF12_I(bit, expr) BOOST_PP_EXPR_IIF12_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF12_0(expr)
# define BOOST_PP_EXPR_IIF12_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF13 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF13(bit, expr) BOOST_PP_EXPR_IIF13_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF13(bit, expr) BOOST_PP_EXPR_IIF13_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF13_OO(par) BOOST_PP_EXPR_IIF13_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF13_I(bit, expr) BOOST_PP_EXPR_IIF13_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF13_0(expr)
# define BOOST_PP_EXPR_IIF13_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF14 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF14(bit, expr) BOOST_PP_EXPR_IIF14_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF14(bit, expr) BOOST_PP_EXPR_IIF14_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF14_OO(par) BOOST_PP_EXPR_IIF14_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF14_I(bit, expr) BOOST_PP_EXPR_IIF14_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF14_0(expr)
# define BOOST_PP_EXPR_IIF14_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF15 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF15(bit, expr) BOOST_PP_EXPR_IIF15_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF15(bit, expr) BOOST_PP_EXPR_IIF15_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF15_OO(par) BOOST_PP_EXPR_IIF15_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF15_I(bit, expr) BOOST_PP_EXPR_IIF15_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF15_0(expr)
# define BOOST_PP_EXPR_IIF15_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF16 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF16(bit, expr) BOOST_PP_EXPR_IIF16_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF16(bit, expr) BOOST_PP_EXPR_IIF16_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF16_OO(par) BOOST_PP_EXPR_IIF16_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF16_I(bit, expr) BOOST_PP_EXPR_IIF16_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF16_0(expr)
# define BOOST_PP_EXPR_IIF16_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF17 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF17(bit, expr) BOOST_PP_EXPR_IIF17_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF17(bit, expr) BOOST_PP_EXPR_IIF17_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF17_OO(par) BOOST_PP_EXPR_IIF17_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF17_I(bit, expr) BOOST_PP_EXPR_IIF17_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF17_0(expr)
# define BOOST_PP_EXPR_IIF17_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF18 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF18(bit, expr) BOOST_PP_EXPR_IIF18_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF18(bit, expr) BOOST_PP_EXPR_IIF18_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF18_OO(par) BOOST_PP_EXPR_IIF18_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF18_I(bit, expr) BOOST_PP_EXPR_IIF18_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF18_0(expr)
# define BOOST_PP_EXPR_IIF18_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF19 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF19(bit, expr) BOOST_PP_EXPR_IIF19_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF19(bit, expr) BOOST_PP_EXPR_IIF19_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF19_OO(par) BOOST_PP_EXPR_IIF19_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF19_I(bit, expr) BOOST_PP_EXPR_IIF19_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF19_0(expr)
# define BOOST_PP_EXPR_IIF19_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF20 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF20(bit, expr) BOOST_PP_EXPR_IIF20_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF20(bit, expr) BOOST_PP_EXPR_IIF20_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF20_OO(par) BOOST_PP_EXPR_IIF20_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF20_I(bit, expr) BOOST_PP_EXPR_IIF20_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF20_0(expr)
# define BOOST_PP_EXPR_IIF20_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF21 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF21(bit, expr) BOOST_PP_EXPR_IIF21_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF21(bit, expr) BOOST_PP_EXPR_IIF21_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF21_OO(par) BOOST_PP_EXPR_IIF21_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF21_I(bit, expr) BOOST_PP_EXPR_IIF21_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF21_0(expr)
# define BOOST_PP_EXPR_IIF21_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF22 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF22(bit, expr) BOOST_PP_EXPR_IIF22_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF22(bit, expr) BOOST_PP_EXPR_IIF22_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF22_OO(par) BOOST_PP_EXPR_IIF22_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF22_I(bit, expr) BOOST_PP_EXPR_IIF22_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF22_0(expr)
# define BOOST_PP_EXPR_IIF22_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF23 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF23(bit, expr) BOOST_PP_EXPR_IIF23_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF23(bit, expr) BOOST_PP_EXPR_IIF23_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF23_OO(par) BOOST_PP_EXPR_IIF23_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF23_I(bit, expr) BOOST_PP_EXPR_IIF23_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF23_0(expr)
# define BOOST_PP_EXPR_IIF23_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF24 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF24(bit, expr) BOOST_PP_EXPR_IIF24_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF24(bit, expr) BOOST_PP_EXPR_IIF24_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF24_OO(par) BOOST_PP_EXPR_IIF24_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF24_I(bit, expr) BOOST_PP_EXPR_IIF24_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF24_0(expr)
# define BOOST_PP_EXPR_IIF24_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF25 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF25(bit, expr) BOOST_PP_EXPR_IIF25_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF25(bit, expr) BOOST_PP_EXPR_IIF25_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF25_OO(par) BOOST_PP_EXPR_IIF25_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF25_I(bit, expr) BOOST_PP_EXPR_IIF25_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF25_0(expr)
# define BOOST_PP_EXPR_IIF25_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF26 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF26(bit, expr) BOOST_PP_EXPR_IIF26_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF26(bit, expr) BOOST_PP_EXPR_IIF26_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF26_OO(par) BOOST_PP_EXPR_IIF26_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF26_I(bit, expr) BOOST_PP_EXPR_IIF26_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF26_0(expr)
# define BOOST_PP_EXPR_IIF26_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF27 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF27(bit, expr) BOOST_PP_EXPR_IIF27_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF27(bit, expr) BOOST_PP_EXPR_IIF27_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF27_OO(par) BOOST_PP_EXPR_IIF27_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF27_I(bit, expr) BOOST_PP_EXPR_IIF27_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF27_0(expr)
# define BOOST_PP_EXPR_IIF27_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF28 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF28(bit, expr) BOOST_PP_EXPR_IIF28_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF28(bit, expr) BOOST_PP_EXPR_IIF28_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF28_OO(par) BOOST_PP_EXPR_IIF28_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF28_I(bit, expr) BOOST_PP_EXPR_IIF28_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF28_0(expr)
# define BOOST_PP_EXPR_IIF28_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF29 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF29(bit, expr) BOOST_PP_EXPR_IIF29_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF29(bit, expr) BOOST_PP_EXPR_IIF29_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF29_OO(par) BOOST_PP_EXPR_IIF29_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF29_I(bit, expr) BOOST_PP_EXPR_IIF29_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF29_0(expr)
# define BOOST_PP_EXPR_IIF29_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF30 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF30(bit, expr) BOOST_PP_EXPR_IIF30_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF30(bit, expr) BOOST_PP_EXPR_IIF30_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF30_OO(par) BOOST_PP_EXPR_IIF30_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF30_I(bit, expr) BOOST_PP_EXPR_IIF30_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF30_0(expr)
# define BOOST_PP_EXPR_IIF30_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF31 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF31(bit, expr) BOOST_PP_EXPR_IIF31_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF31(bit, expr) BOOST_PP_EXPR_IIF31_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF31_OO(par) BOOST_PP_EXPR_IIF31_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF31_I(bit, expr) BOOST_PP_EXPR_IIF31_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF31_0(expr)
# define BOOST_PP_EXPR_IIF31_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF32 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF32(bit, expr) BOOST_PP_EXPR_IIF32_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF32(bit, expr) BOOST_PP_EXPR_IIF32_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF32_OO(par) BOOST_PP_EXPR_IIF32_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF32_I(bit, expr) BOOST_PP_EXPR_IIF32_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF32_0(expr)
# define BOOST_PP_EXPR_IIF32_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF33 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF33(bit, expr) BOOST_PP_EXPR_IIF33_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF33(bit, expr) BOOST_PP_EXPR_IIF33_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF33_OO(par) BOOST_PP_EXPR_IIF33_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF33_I(bit, expr) BOOST_PP_EXPR_IIF33_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF33_0(expr)
# define BOOST_PP_EXPR_IIF33_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF34 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF34(bit, expr) BOOST_PP_EXPR_IIF34_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF34(bit, expr) BOOST_PP_EXPR_IIF34_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF34_OO(par) BOOST_PP_EXPR_IIF34_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF34_I(bit, expr) BOOST_PP_EXPR_IIF34_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF34_0(expr)
# define BOOST_PP_EXPR_IIF34_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF35 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF35(bit, expr) BOOST_PP_EXPR_IIF35_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF35(bit, expr) BOOST_PP_EXPR_IIF35_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF35_OO(par) BOOST_PP_EXPR_IIF35_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF35_I(bit, expr) BOOST_PP_EXPR_IIF35_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF35_0(expr)
# define BOOST_PP_EXPR_IIF35_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF36 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF36(bit, expr) BOOST_PP_EXPR_IIF36_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF36(bit, expr) BOOST_PP_EXPR_IIF36_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF36_OO(par) BOOST_PP_EXPR_IIF36_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF36_I(bit, expr) BOOST_PP_EXPR_IIF36_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF36_0(expr)
# define BOOST_PP_EXPR_IIF36_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF37 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF37(bit, expr) BOOST_PP_EXPR_IIF37_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF37(bit, expr) BOOST_PP_EXPR_IIF37_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF37_OO(par) BOOST_PP_EXPR_IIF37_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF37_I(bit, expr) BOOST_PP_EXPR_IIF37_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF37_0(expr)
# define BOOST_PP_EXPR_IIF37_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF38 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF38(bit, expr) BOOST_PP_EXPR_IIF38_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF38(bit, expr) BOOST_PP_EXPR_IIF38_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF38_OO(par) BOOST_PP_EXPR_IIF38_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF38_I(bit, expr) BOOST_PP_EXPR_IIF38_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF38_0(expr)
# define BOOST_PP_EXPR_IIF38_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF39 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF39(bit, expr) BOOST_PP_EXPR_IIF39_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF39(bit, expr) BOOST_PP_EXPR_IIF39_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF39_OO(par) BOOST_PP_EXPR_IIF39_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF39_I(bit, expr) BOOST_PP_EXPR_IIF39_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF39_0(expr)
# define BOOST_PP_EXPR_IIF39_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF40 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF40(bit, expr) BOOST_PP_EXPR_IIF40_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF40(bit, expr) BOOST_PP_EXPR_IIF40_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF40_OO(par) BOOST_PP_EXPR_IIF40_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF40_I(bit, expr) BOOST_PP_EXPR_IIF40_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF40_0(expr)
# define BOOST_PP_EXPR_IIF40_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF41 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF41(bit, expr) BOOST_PP_EXPR_IIF41_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF41(bit, expr) BOOST_PP_EXPR_IIF41_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF41_OO(par) BOOST_PP_EXPR_IIF41_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF41_I(bit, expr) BOOST_PP_EXPR_IIF41_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF41_0(expr)
# define BOOST_PP_EXPR_IIF41_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF42 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF42(bit, expr) BOOST_PP_EXPR_IIF42_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF42(bit, expr) BOOST_PP_EXPR_IIF42_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF42_OO(par) BOOST_PP_EXPR_IIF42_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF42_I(bit, expr) BOOST_PP_EXPR_IIF42_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF42_0(expr)
# define BOOST_PP_EXPR_IIF42_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF43 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF43(bit, expr) BOOST_PP_EXPR_IIF43_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF43(bit, expr) BOOST_PP_EXPR_IIF43_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF43_OO(par) BOOST_PP_EXPR_IIF43_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF43_I(bit, expr) BOOST_PP_EXPR_IIF43_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF43_0(expr)
# define BOOST_PP_EXPR_IIF43_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF44 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF44(bit, expr) BOOST_PP_EXPR_IIF44_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF44(bit, expr) BOOST_PP_EXPR_IIF44_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF44_OO(par) BOOST_PP_EXPR_IIF44_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF44_I(bit, expr) BOOST_PP_EXPR_IIF44_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF44_0(expr)
# define BOOST_PP_EXPR_IIF44_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF45 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF45(bit, expr) BOOST_PP_EXPR_IIF45_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF45(bit, expr) BOOST_PP_EXPR_IIF45_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF45_OO(par) BOOST_PP_EXPR_IIF45_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF45_I(bit, expr) BOOST_PP_EXPR_IIF45_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF45_0(expr)
# define BOOST_PP_EXPR_IIF45_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF46 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF46(bit, expr) BOOST_PP_EXPR_IIF46_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF46(bit, expr) BOOST_PP_EXPR_IIF46_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF46_OO(par) BOOST_PP_EXPR_IIF46_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF46_I(bit, expr) BOOST_PP_EXPR_IIF46_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF46_0(expr)
# define BOOST_PP_EXPR_IIF46_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF47 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF47(bit, expr) BOOST_PP_EXPR_IIF47_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF47(bit, expr) BOOST_PP_EXPR_IIF47_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF47_OO(par) BOOST_PP_EXPR_IIF47_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF47_I(bit, expr) BOOST_PP_EXPR_IIF47_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF47_0(expr)
# define BOOST_PP_EXPR_IIF47_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF48 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF48(bit, expr) BOOST_PP_EXPR_IIF48_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF48(bit, expr) BOOST_PP_EXPR_IIF48_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF48_OO(par) BOOST_PP_EXPR_IIF48_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF48_I(bit, expr) BOOST_PP_EXPR_IIF48_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF48_0(expr)
# define BOOST_PP_EXPR_IIF48_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF49 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF49(bit, expr) BOOST_PP_EXPR_IIF49_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF49(bit, expr) BOOST_PP_EXPR_IIF49_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF49_OO(par) BOOST_PP_EXPR_IIF49_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF49_I(bit, expr) BOOST_PP_EXPR_IIF49_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF49_0(expr)
# define BOOST_PP_EXPR_IIF49_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF50 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF50(bit, expr) BOOST_PP_EXPR_IIF50_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF50(bit, expr) BOOST_PP_EXPR_IIF50_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF50_OO(par) BOOST_PP_EXPR_IIF50_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF50_I(bit, expr) BOOST_PP_EXPR_IIF50_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF50_0(expr)
# define BOOST_PP_EXPR_IIF50_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF51 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF51(bit, expr) BOOST_PP_EXPR_IIF51_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF51(bit, expr) BOOST_PP_EXPR_IIF51_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF51_OO(par) BOOST_PP_EXPR_IIF51_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF51_I(bit, expr) BOOST_PP_EXPR_IIF51_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF51_0(expr)
# define BOOST_PP_EXPR_IIF51_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF52 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF52(bit, expr) BOOST_PP_EXPR_IIF52_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF52(bit, expr) BOOST_PP_EXPR_IIF52_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF52_OO(par) BOOST_PP_EXPR_IIF52_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF52_I(bit, expr) BOOST_PP_EXPR_IIF52_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF52_0(expr)
# define BOOST_PP_EXPR_IIF52_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF53 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF53(bit, expr) BOOST_PP_EXPR_IIF53_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF53(bit, expr) BOOST_PP_EXPR_IIF53_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF53_OO(par) BOOST_PP_EXPR_IIF53_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF53_I(bit, expr) BOOST_PP_EXPR_IIF53_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF53_0(expr)
# define BOOST_PP_EXPR_IIF53_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF54 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF54(bit, expr) BOOST_PP_EXPR_IIF54_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF54(bit, expr) BOOST_PP_EXPR_IIF54_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF54_OO(par) BOOST_PP_EXPR_IIF54_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF54_I(bit, expr) BOOST_PP_EXPR_IIF54_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF54_0(expr)
# define BOOST_PP_EXPR_IIF54_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF55 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF55(bit, expr) BOOST_PP_EXPR_IIF55_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF55(bit, expr) BOOST_PP_EXPR_IIF55_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF55_OO(par) BOOST_PP_EXPR_IIF55_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF55_I(bit, expr) BOOST_PP_EXPR_IIF55_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF55_0(expr)
# define BOOST_PP_EXPR_IIF55_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF56 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF56(bit, expr) BOOST_PP_EXPR_IIF56_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF56(bit, expr) BOOST_PP_EXPR_IIF56_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF56_OO(par) BOOST_PP_EXPR_IIF56_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF56_I(bit, expr) BOOST_PP_EXPR_IIF56_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF56_0(expr)
# define BOOST_PP_EXPR_IIF56_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF57 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF57(bit, expr) BOOST_PP_EXPR_IIF57_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF57(bit, expr) BOOST_PP_EXPR_IIF57_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF57_OO(par) BOOST_PP_EXPR_IIF57_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF57_I(bit, expr) BOOST_PP_EXPR_IIF57_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF57_0(expr)
# define BOOST_PP_EXPR_IIF57_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF58 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF58(bit, expr) BOOST_PP_EXPR_IIF58_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF58(bit, expr) BOOST_PP_EXPR_IIF58_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF58_OO(par) BOOST_PP_EXPR_IIF58_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF58_I(bit, expr) BOOST_PP_EXPR_IIF58_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF58_0(expr)
# define BOOST_PP_EXPR_IIF58_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF59 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF59(bit, expr) BOOST_PP_EXPR_IIF59_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF59(bit, expr) BOOST_PP_EXPR_IIF59_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF59_OO(par) BOOST_PP_EXPR_IIF59_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF59_I(bit, expr) BOOST_PP_EXPR_IIF59_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF59_0(expr)
# define BOOST_PP_EXPR_IIF59_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF60 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF60(bit, expr) BOOST_PP_EXPR_IIF60_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF60(bit, expr) BOOST_PP_EXPR_IIF60_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF60_OO(par) BOOST_PP_EXPR_IIF60_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF60_I(bit, expr) BOOST_PP_EXPR_IIF60_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF60_0(expr)
# define BOOST_PP_EXPR_IIF60_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF61 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF61(bit, expr) BOOST_PP_EXPR_IIF61_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF61(bit, expr) BOOST_PP_EXPR_IIF61_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF61_OO(par) BOOST_PP_EXPR_IIF61_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF61_I(bit, expr) BOOST_PP_EXPR_IIF61_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF61_0(expr)
# define BOOST_PP_EXPR_IIF61_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF62 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF62(bit, expr) BOOST_PP_EXPR_IIF62_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF62(bit, expr) BOOST_PP_EXPR_IIF62_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF62_OO(par) BOOST_PP_EXPR_IIF62_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF62_I(bit, expr) BOOST_PP_EXPR_IIF62_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF62_0(expr)
# define BOOST_PP_EXPR_IIF62_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF63 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF63(bit, expr) BOOST_PP_EXPR_IIF63_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF63(bit, expr) BOOST_PP_EXPR_IIF63_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF63_OO(par) BOOST_PP_EXPR_IIF63_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF63_I(bit, expr) BOOST_PP_EXPR_IIF63_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF63_0(expr)
# define BOOST_PP_EXPR_IIF63_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF64 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF64(bit, expr) BOOST_PP_EXPR_IIF64_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF64(bit, expr) BOOST_PP_EXPR_IIF64_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF64_OO(par) BOOST_PP_EXPR_IIF64_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF64_I(bit, expr) BOOST_PP_EXPR_IIF64_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF64_0(expr)
# define BOOST_PP_EXPR_IIF64_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF65 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF65(bit, expr) BOOST_PP_EXPR_IIF65_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF65(bit, expr) BOOST_PP_EXPR_IIF65_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF65_OO(par) BOOST_PP_EXPR_IIF65_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF65_I(bit, expr) BOOST_PP_EXPR_IIF65_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF65_0(expr)
# define BOOST_PP_EXPR_IIF65_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF66 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF66(bit, expr) BOOST_PP_EXPR_IIF66_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF66(bit, expr) BOOST_PP_EXPR_IIF66_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF66_OO(par) BOOST_PP_EXPR_IIF66_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF66_I(bit, expr) BOOST_PP_EXPR_IIF66_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF66_0(expr)
# define BOOST_PP_EXPR_IIF66_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF67 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF67(bit, expr) BOOST_PP_EXPR_IIF67_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF67(bit, expr) BOOST_PP_EXPR_IIF67_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF67_OO(par) BOOST_PP_EXPR_IIF67_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF67_I(bit, expr) BOOST_PP_EXPR_IIF67_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF67_0(expr)
# define BOOST_PP_EXPR_IIF67_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF68 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF68(bit, expr) BOOST_PP_EXPR_IIF68_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF68(bit, expr) BOOST_PP_EXPR_IIF68_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF68_OO(par) BOOST_PP_EXPR_IIF68_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF68_I(bit, expr) BOOST_PP_EXPR_IIF68_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF68_0(expr)
# define BOOST_PP_EXPR_IIF68_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF69 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF69(bit, expr) BOOST_PP_EXPR_IIF69_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF69(bit, expr) BOOST_PP_EXPR_IIF69_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF69_OO(par) BOOST_PP_EXPR_IIF69_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF69_I(bit, expr) BOOST_PP_EXPR_IIF69_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF69_0(expr)
# define BOOST_PP_EXPR_IIF69_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF70 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF70(bit, expr) BOOST_PP_EXPR_IIF70_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF70(bit, expr) BOOST_PP_EXPR_IIF70_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF70_OO(par) BOOST_PP_EXPR_IIF70_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF70_I(bit, expr) BOOST_PP_EXPR_IIF70_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF70_0(expr)
# define BOOST_PP_EXPR_IIF70_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF71 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF71(bit, expr) BOOST_PP_EXPR_IIF71_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF71(bit, expr) BOOST_PP_EXPR_IIF71_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF71_OO(par) BOOST_PP_EXPR_IIF71_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF71_I(bit, expr) BOOST_PP_EXPR_IIF71_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF71_0(expr)
# define BOOST_PP_EXPR_IIF71_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF72 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF72(bit, expr) BOOST_PP_EXPR_IIF72_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF72(bit, expr) BOOST_PP_EXPR_IIF72_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF72_OO(par) BOOST_PP_EXPR_IIF72_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF72_I(bit, expr) BOOST_PP_EXPR_IIF72_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF72_0(expr)
# define BOOST_PP_EXPR_IIF72_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF73 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF73(bit, expr) BOOST_PP_EXPR_IIF73_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF73(bit, expr) BOOST_PP_EXPR_IIF73_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF73_OO(par) BOOST_PP_EXPR_IIF73_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF73_I(bit, expr) BOOST_PP_EXPR_IIF73_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF73_0(expr)
# define BOOST_PP_EXPR_IIF73_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF74 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF74(bit, expr) BOOST_PP_EXPR_IIF74_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF74(bit, expr) BOOST_PP_EXPR_IIF74_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF74_OO(par) BOOST_PP_EXPR_IIF74_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF74_I(bit, expr) BOOST_PP_EXPR_IIF74_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF74_0(expr)
# define BOOST_PP_EXPR_IIF74_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF75 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF75(bit, expr) BOOST_PP_EXPR_IIF75_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF75(bit, expr) BOOST_PP_EXPR_IIF75_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF75_OO(par) BOOST_PP_EXPR_IIF75_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF75_I(bit, expr) BOOST_PP_EXPR_IIF75_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF75_0(expr)
# define BOOST_PP_EXPR_IIF75_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF76 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF76(bit, expr) BOOST_PP_EXPR_IIF76_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF76(bit, expr) BOOST_PP_EXPR_IIF76_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF76_OO(par) BOOST_PP_EXPR_IIF76_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF76_I(bit, expr) BOOST_PP_EXPR_IIF76_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF76_0(expr)
# define BOOST_PP_EXPR_IIF76_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF77 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF77(bit, expr) BOOST_PP_EXPR_IIF77_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF77(bit, expr) BOOST_PP_EXPR_IIF77_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF77_OO(par) BOOST_PP_EXPR_IIF77_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF77_I(bit, expr) BOOST_PP_EXPR_IIF77_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF77_0(expr)
# define BOOST_PP_EXPR_IIF77_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF78 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF78(bit, expr) BOOST_PP_EXPR_IIF78_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF78(bit, expr) BOOST_PP_EXPR_IIF78_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF78_OO(par) BOOST_PP_EXPR_IIF78_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF78_I(bit, expr) BOOST_PP_EXPR_IIF78_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF78_0(expr)
# define BOOST_PP_EXPR_IIF78_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF79 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF79(bit, expr) BOOST_PP_EXPR_IIF79_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF79(bit, expr) BOOST_PP_EXPR_IIF79_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF79_OO(par) BOOST_PP_EXPR_IIF79_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF79_I(bit, expr) BOOST_PP_EXPR_IIF79_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF79_0(expr)
# define BOOST_PP_EXPR_IIF79_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF80 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF80(bit, expr) BOOST_PP_EXPR_IIF80_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF80(bit, expr) BOOST_PP_EXPR_IIF80_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF80_OO(par) BOOST_PP_EXPR_IIF80_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF80_I(bit, expr) BOOST_PP_EXPR_IIF80_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF80_0(expr)
# define BOOST_PP_EXPR_IIF80_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF81 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF81(bit, expr) BOOST_PP_EXPR_IIF81_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF81(bit, expr) BOOST_PP_EXPR_IIF81_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF81_OO(par) BOOST_PP_EXPR_IIF81_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF81_I(bit, expr) BOOST_PP_EXPR_IIF81_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF81_0(expr)
# define BOOST_PP_EXPR_IIF81_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF82 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF82(bit, expr) BOOST_PP_EXPR_IIF82_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF82(bit, expr) BOOST_PP_EXPR_IIF82_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF82_OO(par) BOOST_PP_EXPR_IIF82_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF82_I(bit, expr) BOOST_PP_EXPR_IIF82_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF82_0(expr)
# define BOOST_PP_EXPR_IIF82_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF83 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF83(bit, expr) BOOST_PP_EXPR_IIF83_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF83(bit, expr) BOOST_PP_EXPR_IIF83_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF83_OO(par) BOOST_PP_EXPR_IIF83_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF83_I(bit, expr) BOOST_PP_EXPR_IIF83_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF83_0(expr)
# define BOOST_PP_EXPR_IIF83_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF84 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF84(bit, expr) BOOST_PP_EXPR_IIF84_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF84(bit, expr) BOOST_PP_EXPR_IIF84_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF84_OO(par) BOOST_PP_EXPR_IIF84_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF84_I(bit, expr) BOOST_PP_EXPR_IIF84_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF84_0(expr)
# define BOOST_PP_EXPR_IIF84_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF85 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF85(bit, expr) BOOST_PP_EXPR_IIF85_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF85(bit, expr) BOOST_PP_EXPR_IIF85_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF85_OO(par) BOOST_PP_EXPR_IIF85_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF85_I(bit, expr) BOOST_PP_EXPR_IIF85_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF85_0(expr)
# define BOOST_PP_EXPR_IIF85_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF86 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF86(bit, expr) BOOST_PP_EXPR_IIF86_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF86(bit, expr) BOOST_PP_EXPR_IIF86_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF86_OO(par) BOOST_PP_EXPR_IIF86_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF86_I(bit, expr) BOOST_PP_EXPR_IIF86_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF86_0(expr)
# define BOOST_PP_EXPR_IIF86_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF87 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF87(bit, expr) BOOST_PP_EXPR_IIF87_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF87(bit, expr) BOOST_PP_EXPR_IIF87_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF87_OO(par) BOOST_PP_EXPR_IIF87_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF87_I(bit, expr) BOOST_PP_EXPR_IIF87_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF87_0(expr)
# define BOOST_PP_EXPR_IIF87_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF88 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF88(bit, expr) BOOST_PP_EXPR_IIF88_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF88(bit, expr) BOOST_PP_EXPR_IIF88_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF88_OO(par) BOOST_PP_EXPR_IIF88_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF88_I(bit, expr) BOOST_PP_EXPR_IIF88_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF88_0(expr)
# define BOOST_PP_EXPR_IIF88_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF89 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF89(bit, expr) BOOST_PP_EXPR_IIF89_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF89(bit, expr) BOOST_PP_EXPR_IIF89_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF89_OO(par) BOOST_PP_EXPR_IIF89_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF89_I(bit, expr) BOOST_PP_EXPR_IIF89_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF89_0(expr)
# define BOOST_PP_EXPR_IIF89_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF90 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF90(bit, expr) BOOST_PP_EXPR_IIF90_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF90(bit, expr) BOOST_PP_EXPR_IIF90_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF90_OO(par) BOOST_PP_EXPR_IIF90_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF90_I(bit, expr) BOOST_PP_EXPR_IIF90_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF90_0(expr)
# define BOOST_PP_EXPR_IIF90_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF91 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF91(bit, expr) BOOST_PP_EXPR_IIF91_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF91(bit, expr) BOOST_PP_EXPR_IIF91_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF91_OO(par) BOOST_PP_EXPR_IIF91_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF91_I(bit, expr) BOOST_PP_EXPR_IIF91_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF91_0(expr)
# define BOOST_PP_EXPR_IIF91_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF92 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF92(bit, expr) BOOST_PP_EXPR_IIF92_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF92(bit, expr) BOOST_PP_EXPR_IIF92_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF92_OO(par) BOOST_PP_EXPR_IIF92_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF92_I(bit, expr) BOOST_PP_EXPR_IIF92_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF92_0(expr)
# define BOOST_PP_EXPR_IIF92_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF93 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF93(bit, expr) BOOST_PP_EXPR_IIF93_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF93(bit, expr) BOOST_PP_EXPR_IIF93_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF93_OO(par) BOOST_PP_EXPR_IIF93_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF93_I(bit, expr) BOOST_PP_EXPR_IIF93_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF93_0(expr)
# define BOOST_PP_EXPR_IIF93_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF94 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF94(bit, expr) BOOST_PP_EXPR_IIF94_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF94(bit, expr) BOOST_PP_EXPR_IIF94_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF94_OO(par) BOOST_PP_EXPR_IIF94_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF94_I(bit, expr) BOOST_PP_EXPR_IIF94_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF94_0(expr)
# define BOOST_PP_EXPR_IIF94_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF95 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF95(bit, expr) BOOST_PP_EXPR_IIF95_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF95(bit, expr) BOOST_PP_EXPR_IIF95_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF95_OO(par) BOOST_PP_EXPR_IIF95_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF95_I(bit, expr) BOOST_PP_EXPR_IIF95_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF95_0(expr)
# define BOOST_PP_EXPR_IIF95_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF96 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF96(bit, expr) BOOST_PP_EXPR_IIF96_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF96(bit, expr) BOOST_PP_EXPR_IIF96_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF96_OO(par) BOOST_PP_EXPR_IIF96_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF96_I(bit, expr) BOOST_PP_EXPR_IIF96_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF96_0(expr)
# define BOOST_PP_EXPR_IIF96_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF97 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF97(bit, expr) BOOST_PP_EXPR_IIF97_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF97(bit, expr) BOOST_PP_EXPR_IIF97_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF97_OO(par) BOOST_PP_EXPR_IIF97_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF97_I(bit, expr) BOOST_PP_EXPR_IIF97_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF97_0(expr)
# define BOOST_PP_EXPR_IIF97_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF98 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF98(bit, expr) BOOST_PP_EXPR_IIF98_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF98(bit, expr) BOOST_PP_EXPR_IIF98_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF98_OO(par) BOOST_PP_EXPR_IIF98_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF98_I(bit, expr) BOOST_PP_EXPR_IIF98_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF98_0(expr)
# define BOOST_PP_EXPR_IIF98_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF99 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF99(bit, expr) BOOST_PP_EXPR_IIF99_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF99(bit, expr) BOOST_PP_EXPR_IIF99_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF99_OO(par) BOOST_PP_EXPR_IIF99_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF99_I(bit, expr) BOOST_PP_EXPR_IIF99_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF99_0(expr)
# define BOOST_PP_EXPR_IIF99_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF100 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF100(bit, expr) BOOST_PP_EXPR_IIF100_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF100(bit, expr) BOOST_PP_EXPR_IIF100_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF100_OO(par) BOOST_PP_EXPR_IIF100_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF100_I(bit, expr) BOOST_PP_EXPR_IIF100_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF100_0(expr)
# define BOOST_PP_EXPR_IIF100_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF101 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF101(bit, expr) BOOST_PP_EXPR_IIF101_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF101(bit, expr) BOOST_PP_EXPR_IIF101_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF101_OO(par) BOOST_PP_EXPR_IIF101_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF101_I(bit, expr) BOOST_PP_EXPR_IIF101_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF101_0(expr)
# define BOOST_PP_EXPR_IIF101_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF102 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF102(bit, expr) BOOST_PP_EXPR_IIF102_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF102(bit, expr) BOOST_PP_EXPR_IIF102_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF102_OO(par) BOOST_PP_EXPR_IIF102_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF102_I(bit, expr) BOOST_PP_EXPR_IIF102_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF102_0(expr)
# define BOOST_PP_EXPR_IIF102_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF103 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF103(bit, expr) BOOST_PP_EXPR_IIF103_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF103(bit, expr) BOOST_PP_EXPR_IIF103_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF103_OO(par) BOOST_PP_EXPR_IIF103_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF103_I(bit, expr) BOOST_PP_EXPR_IIF103_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF103_0(expr)
# define BOOST_PP_EXPR_IIF103_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF104 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF104(bit, expr) BOOST_PP_EXPR_IIF104_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF104(bit, expr) BOOST_PP_EXPR_IIF104_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF104_OO(par) BOOST_PP_EXPR_IIF104_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF104_I(bit, expr) BOOST_PP_EXPR_IIF104_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF104_0(expr)
# define BOOST_PP_EXPR_IIF104_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF105 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF105(bit, expr) BOOST_PP_EXPR_IIF105_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF105(bit, expr) BOOST_PP_EXPR_IIF105_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF105_OO(par) BOOST_PP_EXPR_IIF105_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF105_I(bit, expr) BOOST_PP_EXPR_IIF105_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF105_0(expr)
# define BOOST_PP_EXPR_IIF105_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF106 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF106(bit, expr) BOOST_PP_EXPR_IIF106_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF106(bit, expr) BOOST_PP_EXPR_IIF106_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF106_OO(par) BOOST_PP_EXPR_IIF106_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF106_I(bit, expr) BOOST_PP_EXPR_IIF106_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF106_0(expr)
# define BOOST_PP_EXPR_IIF106_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF107 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF107(bit, expr) BOOST_PP_EXPR_IIF107_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF107(bit, expr) BOOST_PP_EXPR_IIF107_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF107_OO(par) BOOST_PP_EXPR_IIF107_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF107_I(bit, expr) BOOST_PP_EXPR_IIF107_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF107_0(expr)
# define BOOST_PP_EXPR_IIF107_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF108 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF108(bit, expr) BOOST_PP_EXPR_IIF108_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF108(bit, expr) BOOST_PP_EXPR_IIF108_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF108_OO(par) BOOST_PP_EXPR_IIF108_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF108_I(bit, expr) BOOST_PP_EXPR_IIF108_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF108_0(expr)
# define BOOST_PP_EXPR_IIF108_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF109 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF109(bit, expr) BOOST_PP_EXPR_IIF109_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF109(bit, expr) BOOST_PP_EXPR_IIF109_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF109_OO(par) BOOST_PP_EXPR_IIF109_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF109_I(bit, expr) BOOST_PP_EXPR_IIF109_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF109_0(expr)
# define BOOST_PP_EXPR_IIF109_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF110 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF110(bit, expr) BOOST_PP_EXPR_IIF110_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF110(bit, expr) BOOST_PP_EXPR_IIF110_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF110_OO(par) BOOST_PP_EXPR_IIF110_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF110_I(bit, expr) BOOST_PP_EXPR_IIF110_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF110_0(expr)
# define BOOST_PP_EXPR_IIF110_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF111 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF111(bit, expr) BOOST_PP_EXPR_IIF111_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF111(bit, expr) BOOST_PP_EXPR_IIF111_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF111_OO(par) BOOST_PP_EXPR_IIF111_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF111_I(bit, expr) BOOST_PP_EXPR_IIF111_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF111_0(expr)
# define BOOST_PP_EXPR_IIF111_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF113 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF113(bit, expr) BOOST_PP_EXPR_IIF113_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF113(bit, expr) BOOST_PP_EXPR_IIF113_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF113_OO(par) BOOST_PP_EXPR_IIF113_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF113_I(bit, expr) BOOST_PP_EXPR_IIF113_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF113_0(expr)
# define BOOST_PP_EXPR_IIF113_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF114 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF114(bit, expr) BOOST_PP_EXPR_IIF114_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF114(bit, expr) BOOST_PP_EXPR_IIF114_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF114_OO(par) BOOST_PP_EXPR_IIF114_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF114_I(bit, expr) BOOST_PP_EXPR_IIF114_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF114_0(expr)
# define BOOST_PP_EXPR_IIF114_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF115 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF115(bit, expr) BOOST_PP_EXPR_IIF115_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF115(bit, expr) BOOST_PP_EXPR_IIF115_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF115_OO(par) BOOST_PP_EXPR_IIF115_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF115_I(bit, expr) BOOST_PP_EXPR_IIF115_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF115_0(expr)
# define BOOST_PP_EXPR_IIF115_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF116 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF116(bit, expr) BOOST_PP_EXPR_IIF116_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF116(bit, expr) BOOST_PP_EXPR_IIF116_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF116_OO(par) BOOST_PP_EXPR_IIF116_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF116_I(bit, expr) BOOST_PP_EXPR_IIF116_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF116_0(expr)
# define BOOST_PP_EXPR_IIF116_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF117 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF117(bit, expr) BOOST_PP_EXPR_IIF117_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF117(bit, expr) BOOST_PP_EXPR_IIF117_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF117_OO(par) BOOST_PP_EXPR_IIF117_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF117_I(bit, expr) BOOST_PP_EXPR_IIF117_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF117_0(expr)
# define BOOST_PP_EXPR_IIF117_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF118 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF118(bit, expr) BOOST_PP_EXPR_IIF118_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF118(bit, expr) BOOST_PP_EXPR_IIF118_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF118_OO(par) BOOST_PP_EXPR_IIF118_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF118_I(bit, expr) BOOST_PP_EXPR_IIF118_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF118_0(expr)
# define BOOST_PP_EXPR_IIF118_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF119 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF119(bit, expr) BOOST_PP_EXPR_IIF119_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF119(bit, expr) BOOST_PP_EXPR_IIF119_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF119_OO(par) BOOST_PP_EXPR_IIF119_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF119_I(bit, expr) BOOST_PP_EXPR_IIF119_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF119_0(expr)
# define BOOST_PP_EXPR_IIF119_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF120 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF120(bit, expr) BOOST_PP_EXPR_IIF120_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF120(bit, expr) BOOST_PP_EXPR_IIF120_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF120_OO(par) BOOST_PP_EXPR_IIF120_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF120_I(bit, expr) BOOST_PP_EXPR_IIF120_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF120_0(expr)
# define BOOST_PP_EXPR_IIF120_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF121 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF121(bit, expr) BOOST_PP_EXPR_IIF121_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF121(bit, expr) BOOST_PP_EXPR_IIF121_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF121_OO(par) BOOST_PP_EXPR_IIF121_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF121_I(bit, expr) BOOST_PP_EXPR_IIF121_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF121_0(expr)
# define BOOST_PP_EXPR_IIF121_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF122 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF122(bit, expr) BOOST_PP_EXPR_IIF122_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF122(bit, expr) BOOST_PP_EXPR_IIF122_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF122_OO(par) BOOST_PP_EXPR_IIF122_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF122_I(bit, expr) BOOST_PP_EXPR_IIF122_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF122_0(expr)
# define BOOST_PP_EXPR_IIF122_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF123 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF123(bit, expr) BOOST_PP_EXPR_IIF123_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF123(bit, expr) BOOST_PP_EXPR_IIF123_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF123_OO(par) BOOST_PP_EXPR_IIF123_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF123_I(bit, expr) BOOST_PP_EXPR_IIF123_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF123_0(expr)
# define BOOST_PP_EXPR_IIF123_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF124 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF124(bit, expr) BOOST_PP_EXPR_IIF124_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF124(bit, expr) BOOST_PP_EXPR_IIF124_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF124_OO(par) BOOST_PP_EXPR_IIF124_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF124_I(bit, expr) BOOST_PP_EXPR_IIF124_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF124_0(expr)
# define BOOST_PP_EXPR_IIF124_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF125 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF125(bit, expr) BOOST_PP_EXPR_IIF125_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF125(bit, expr) BOOST_PP_EXPR_IIF125_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF125_OO(par) BOOST_PP_EXPR_IIF125_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF125_I(bit, expr) BOOST_PP_EXPR_IIF125_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF125_0(expr)
# define BOOST_PP_EXPR_IIF125_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF126 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF126(bit, expr) BOOST_PP_EXPR_IIF126_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF126(bit, expr) BOOST_PP_EXPR_IIF126_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF126_OO(par) BOOST_PP_EXPR_IIF126_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF126_I(bit, expr) BOOST_PP_EXPR_IIF126_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF126_0(expr)
# define BOOST_PP_EXPR_IIF126_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF127 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF127(bit, expr) BOOST_PP_EXPR_IIF127_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF127(bit, expr) BOOST_PP_EXPR_IIF127_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF127_OO(par) BOOST_PP_EXPR_IIF127_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF127_I(bit, expr) BOOST_PP_EXPR_IIF127_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF127_0(expr)
# define BOOST_PP_EXPR_IIF127_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF128 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF128(bit, expr) BOOST_PP_EXPR_IIF128_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF128(bit, expr) BOOST_PP_EXPR_IIF128_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF128_OO(par) BOOST_PP_EXPR_IIF128_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF128_I(bit, expr) BOOST_PP_EXPR_IIF128_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF128_0(expr)
# define BOOST_PP_EXPR_IIF128_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF129 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF129(bit, expr) BOOST_PP_EXPR_IIF129_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF129(bit, expr) BOOST_PP_EXPR_IIF129_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF129_OO(par) BOOST_PP_EXPR_IIF129_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF129_I(bit, expr) BOOST_PP_EXPR_IIF129_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF129_0(expr)
# define BOOST_PP_EXPR_IIF129_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF130 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF130(bit, expr) BOOST_PP_EXPR_IIF130_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF130(bit, expr) BOOST_PP_EXPR_IIF130_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF130_OO(par) BOOST_PP_EXPR_IIF130_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF130_I(bit, expr) BOOST_PP_EXPR_IIF130_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF130_0(expr)
# define BOOST_PP_EXPR_IIF130_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF131 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF131(bit, expr) BOOST_PP_EXPR_IIF131_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF131(bit, expr) BOOST_PP_EXPR_IIF131_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF131_OO(par) BOOST_PP_EXPR_IIF131_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF131_I(bit, expr) BOOST_PP_EXPR_IIF131_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF131_0(expr)
# define BOOST_PP_EXPR_IIF131_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF132 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF132(bit, expr) BOOST_PP_EXPR_IIF132_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF132(bit, expr) BOOST_PP_EXPR_IIF132_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF132_OO(par) BOOST_PP_EXPR_IIF132_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF132_I(bit, expr) BOOST_PP_EXPR_IIF132_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF132_0(expr)
# define BOOST_PP_EXPR_IIF132_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF133 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF133(bit, expr) BOOST_PP_EXPR_IIF133_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF133(bit, expr) BOOST_PP_EXPR_IIF133_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF133_OO(par) BOOST_PP_EXPR_IIF133_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF133_I(bit, expr) BOOST_PP_EXPR_IIF133_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF133_0(expr)
# define BOOST_PP_EXPR_IIF133_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF134 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF134(bit, expr) BOOST_PP_EXPR_IIF134_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF134(bit, expr) BOOST_PP_EXPR_IIF134_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF134_OO(par) BOOST_PP_EXPR_IIF134_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF134_I(bit, expr) BOOST_PP_EXPR_IIF134_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF134_0(expr)
# define BOOST_PP_EXPR_IIF134_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF135 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF135(bit, expr) BOOST_PP_EXPR_IIF135_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF135(bit, expr) BOOST_PP_EXPR_IIF135_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF135_OO(par) BOOST_PP_EXPR_IIF135_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF135_I(bit, expr) BOOST_PP_EXPR_IIF135_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF135_0(expr)
# define BOOST_PP_EXPR_IIF135_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF136 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF136(bit, expr) BOOST_PP_EXPR_IIF136_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF136(bit, expr) BOOST_PP_EXPR_IIF136_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF136_OO(par) BOOST_PP_EXPR_IIF136_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF136_I(bit, expr) BOOST_PP_EXPR_IIF136_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF136_0(expr)
# define BOOST_PP_EXPR_IIF136_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF137 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF137(bit, expr) BOOST_PP_EXPR_IIF137_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF137(bit, expr) BOOST_PP_EXPR_IIF137_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF137_OO(par) BOOST_PP_EXPR_IIF137_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF137_I(bit, expr) BOOST_PP_EXPR_IIF137_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF137_0(expr)
# define BOOST_PP_EXPR_IIF137_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF138 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF138(bit, expr) BOOST_PP_EXPR_IIF138_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF138(bit, expr) BOOST_PP_EXPR_IIF138_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF138_OO(par) BOOST_PP_EXPR_IIF138_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF138_I(bit, expr) BOOST_PP_EXPR_IIF138_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF138_0(expr)
# define BOOST_PP_EXPR_IIF138_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF139 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF139(bit, expr) BOOST_PP_EXPR_IIF139_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF139(bit, expr) BOOST_PP_EXPR_IIF139_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF139_OO(par) BOOST_PP_EXPR_IIF139_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF139_I(bit, expr) BOOST_PP_EXPR_IIF139_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF139_0(expr)
# define BOOST_PP_EXPR_IIF139_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF140 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF140(bit, expr) BOOST_PP_EXPR_IIF140_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF140(bit, expr) BOOST_PP_EXPR_IIF140_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF140_OO(par) BOOST_PP_EXPR_IIF140_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF140_I(bit, expr) BOOST_PP_EXPR_IIF140_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF140_0(expr)
# define BOOST_PP_EXPR_IIF140_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF141 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF141(bit, expr) BOOST_PP_EXPR_IIF141_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF141(bit, expr) BOOST_PP_EXPR_IIF141_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF141_OO(par) BOOST_PP_EXPR_IIF141_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF141_I(bit, expr) BOOST_PP_EXPR_IIF141_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF141_0(expr)
# define BOOST_PP_EXPR_IIF141_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF142 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF142(bit, expr) BOOST_PP_EXPR_IIF142_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF142(bit, expr) BOOST_PP_EXPR_IIF142_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF142_OO(par) BOOST_PP_EXPR_IIF142_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF142_I(bit, expr) BOOST_PP_EXPR_IIF142_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF142_0(expr)
# define BOOST_PP_EXPR_IIF142_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF143 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF143(bit, expr) BOOST_PP_EXPR_IIF143_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF143(bit, expr) BOOST_PP_EXPR_IIF143_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF143_OO(par) BOOST_PP_EXPR_IIF143_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF143_I(bit, expr) BOOST_PP_EXPR_IIF143_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF143_0(expr)
# define BOOST_PP_EXPR_IIF143_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF144 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF144(bit, expr) BOOST_PP_EXPR_IIF144_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF144(bit, expr) BOOST_PP_EXPR_IIF144_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF144_OO(par) BOOST_PP_EXPR_IIF144_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF144_I(bit, expr) BOOST_PP_EXPR_IIF144_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF144_0(expr)
# define BOOST_PP_EXPR_IIF144_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF145 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF145(bit, expr) BOOST_PP_EXPR_IIF145_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF145(bit, expr) BOOST_PP_EXPR_IIF145_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF145_OO(par) BOOST_PP_EXPR_IIF145_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF145_I(bit, expr) BOOST_PP_EXPR_IIF145_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF145_0(expr)
# define BOOST_PP_EXPR_IIF145_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF146 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF146(bit, expr) BOOST_PP_EXPR_IIF146_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF146(bit, expr) BOOST_PP_EXPR_IIF146_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF146_OO(par) BOOST_PP_EXPR_IIF146_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF146_I(bit, expr) BOOST_PP_EXPR_IIF146_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF146_0(expr)
# define BOOST_PP_EXPR_IIF146_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF147 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF147(bit, expr) BOOST_PP_EXPR_IIF147_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF147(bit, expr) BOOST_PP_EXPR_IIF147_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF147_OO(par) BOOST_PP_EXPR_IIF147_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF147_I(bit, expr) BOOST_PP_EXPR_IIF147_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF147_0(expr)
# define BOOST_PP_EXPR_IIF147_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF148 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF148(bit, expr) BOOST_PP_EXPR_IIF148_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF148(bit, expr) BOOST_PP_EXPR_IIF148_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF148_OO(par) BOOST_PP_EXPR_IIF148_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF148_I(bit, expr) BOOST_PP_EXPR_IIF148_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF148_0(expr)
# define BOOST_PP_EXPR_IIF148_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF149 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF149(bit, expr) BOOST_PP_EXPR_IIF149_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF149(bit, expr) BOOST_PP_EXPR_IIF149_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF149_OO(par) BOOST_PP_EXPR_IIF149_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF149_I(bit, expr) BOOST_PP_EXPR_IIF149_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF149_0(expr)
# define BOOST_PP_EXPR_IIF149_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF150 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF150(bit, expr) BOOST_PP_EXPR_IIF150_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF150(bit, expr) BOOST_PP_EXPR_IIF150_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF150_OO(par) BOOST_PP_EXPR_IIF150_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF150_I(bit, expr) BOOST_PP_EXPR_IIF150_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF150_0(expr)
# define BOOST_PP_EXPR_IIF150_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF151 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF151(bit, expr) BOOST_PP_EXPR_IIF151_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF151(bit, expr) BOOST_PP_EXPR_IIF151_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF151_OO(par) BOOST_PP_EXPR_IIF151_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF151_I(bit, expr) BOOST_PP_EXPR_IIF151_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF151_0(expr)
# define BOOST_PP_EXPR_IIF151_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF152 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF152(bit, expr) BOOST_PP_EXPR_IIF152_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF152(bit, expr) BOOST_PP_EXPR_IIF152_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF152_OO(par) BOOST_PP_EXPR_IIF152_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF152_I(bit, expr) BOOST_PP_EXPR_IIF152_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF152_0(expr)
# define BOOST_PP_EXPR_IIF152_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF153 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF153(bit, expr) BOOST_PP_EXPR_IIF153_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF153(bit, expr) BOOST_PP_EXPR_IIF153_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF153_OO(par) BOOST_PP_EXPR_IIF153_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF153_I(bit, expr) BOOST_PP_EXPR_IIF153_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF153_0(expr)
# define BOOST_PP_EXPR_IIF153_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF154 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF154(bit, expr) BOOST_PP_EXPR_IIF154_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF154(bit, expr) BOOST_PP_EXPR_IIF154_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF154_OO(par) BOOST_PP_EXPR_IIF154_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF154_I(bit, expr) BOOST_PP_EXPR_IIF154_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF154_0(expr)
# define BOOST_PP_EXPR_IIF154_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF155 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF155(bit, expr) BOOST_PP_EXPR_IIF155_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF155(bit, expr) BOOST_PP_EXPR_IIF155_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF155_OO(par) BOOST_PP_EXPR_IIF155_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF155_I(bit, expr) BOOST_PP_EXPR_IIF155_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF155_0(expr)
# define BOOST_PP_EXPR_IIF155_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF156 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF156(bit, expr) BOOST_PP_EXPR_IIF156_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF156(bit, expr) BOOST_PP_EXPR_IIF156_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF156_OO(par) BOOST_PP_EXPR_IIF156_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF156_I(bit, expr) BOOST_PP_EXPR_IIF156_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF156_0(expr)
# define BOOST_PP_EXPR_IIF156_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF157 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF157(bit, expr) BOOST_PP_EXPR_IIF157_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF157(bit, expr) BOOST_PP_EXPR_IIF157_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF157_OO(par) BOOST_PP_EXPR_IIF157_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF157_I(bit, expr) BOOST_PP_EXPR_IIF157_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF157_0(expr)
# define BOOST_PP_EXPR_IIF157_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF158 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF158(bit, expr) BOOST_PP_EXPR_IIF158_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF158(bit, expr) BOOST_PP_EXPR_IIF158_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF158_OO(par) BOOST_PP_EXPR_IIF158_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF158_I(bit, expr) BOOST_PP_EXPR_IIF158_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF158_0(expr)
# define BOOST_PP_EXPR_IIF158_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF159 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF159(bit, expr) BOOST_PP_EXPR_IIF159_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF159(bit, expr) BOOST_PP_EXPR_IIF159_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF159_OO(par) BOOST_PP_EXPR_IIF159_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF159_I(bit, expr) BOOST_PP_EXPR_IIF159_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF159_0(expr)
# define BOOST_PP_EXPR_IIF159_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF160 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF160(bit, expr) BOOST_PP_EXPR_IIF160_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF160(bit, expr) BOOST_PP_EXPR_IIF160_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF160_OO(par) BOOST_PP_EXPR_IIF160_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF160_I(bit, expr) BOOST_PP_EXPR_IIF160_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF160_0(expr)
# define BOOST_PP_EXPR_IIF160_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF161 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF161(bit, expr) BOOST_PP_EXPR_IIF161_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF161(bit, expr) BOOST_PP_EXPR_IIF161_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF161_OO(par) BOOST_PP_EXPR_IIF161_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF161_I(bit, expr) BOOST_PP_EXPR_IIF161_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF161_0(expr)
# define BOOST_PP_EXPR_IIF161_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF162 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF162(bit, expr) BOOST_PP_EXPR_IIF162_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF162(bit, expr) BOOST_PP_EXPR_IIF162_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF162_OO(par) BOOST_PP_EXPR_IIF162_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF162_I(bit, expr) BOOST_PP_EXPR_IIF162_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF162_0(expr)
# define BOOST_PP_EXPR_IIF162_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF163 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF163(bit, expr) BOOST_PP_EXPR_IIF163_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF163(bit, expr) BOOST_PP_EXPR_IIF163_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF163_OO(par) BOOST_PP_EXPR_IIF163_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF163_I(bit, expr) BOOST_PP_EXPR_IIF163_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF163_0(expr)
# define BOOST_PP_EXPR_IIF163_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF164 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF164(bit, expr) BOOST_PP_EXPR_IIF164_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF164(bit, expr) BOOST_PP_EXPR_IIF164_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF164_OO(par) BOOST_PP_EXPR_IIF164_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF164_I(bit, expr) BOOST_PP_EXPR_IIF164_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF164_0(expr)
# define BOOST_PP_EXPR_IIF164_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF165 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF165(bit, expr) BOOST_PP_EXPR_IIF165_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF165(bit, expr) BOOST_PP_EXPR_IIF165_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF165_OO(par) BOOST_PP_EXPR_IIF165_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF165_I(bit, expr) BOOST_PP_EXPR_IIF165_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF165_0(expr)
# define BOOST_PP_EXPR_IIF165_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF166 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF166(bit, expr) BOOST_PP_EXPR_IIF166_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF166(bit, expr) BOOST_PP_EXPR_IIF166_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF166_OO(par) BOOST_PP_EXPR_IIF166_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF166_I(bit, expr) BOOST_PP_EXPR_IIF166_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF166_0(expr)
# define BOOST_PP_EXPR_IIF166_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF167 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF167(bit, expr) BOOST_PP_EXPR_IIF167_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF167(bit, expr) BOOST_PP_EXPR_IIF167_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF167_OO(par) BOOST_PP_EXPR_IIF167_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF167_I(bit, expr) BOOST_PP_EXPR_IIF167_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF167_0(expr)
# define BOOST_PP_EXPR_IIF167_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF168 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF168(bit, expr) BOOST_PP_EXPR_IIF168_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF168(bit, expr) BOOST_PP_EXPR_IIF168_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF168_OO(par) BOOST_PP_EXPR_IIF168_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF168_I(bit, expr) BOOST_PP_EXPR_IIF168_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF168_0(expr)
# define BOOST_PP_EXPR_IIF168_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF169 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF169(bit, expr) BOOST_PP_EXPR_IIF169_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF169(bit, expr) BOOST_PP_EXPR_IIF169_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF169_OO(par) BOOST_PP_EXPR_IIF169_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF169_I(bit, expr) BOOST_PP_EXPR_IIF169_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF169_0(expr)
# define BOOST_PP_EXPR_IIF169_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF170 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF170(bit, expr) BOOST_PP_EXPR_IIF170_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF170(bit, expr) BOOST_PP_EXPR_IIF170_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF170_OO(par) BOOST_PP_EXPR_IIF170_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF170_I(bit, expr) BOOST_PP_EXPR_IIF170_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF170_0(expr)
# define BOOST_PP_EXPR_IIF170_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF171 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF171(bit, expr) BOOST_PP_EXPR_IIF171_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF171(bit, expr) BOOST_PP_EXPR_IIF171_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF171_OO(par) BOOST_PP_EXPR_IIF171_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF171_I(bit, expr) BOOST_PP_EXPR_IIF171_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF171_0(expr)
# define BOOST_PP_EXPR_IIF171_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF172 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF172(bit, expr) BOOST_PP_EXPR_IIF172_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF172(bit, expr) BOOST_PP_EXPR_IIF172_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF172_OO(par) BOOST_PP_EXPR_IIF172_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF172_I(bit, expr) BOOST_PP_EXPR_IIF172_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF172_0(expr)
# define BOOST_PP_EXPR_IIF172_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF173 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF173(bit, expr) BOOST_PP_EXPR_IIF173_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF173(bit, expr) BOOST_PP_EXPR_IIF173_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF173_OO(par) BOOST_PP_EXPR_IIF173_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF173_I(bit, expr) BOOST_PP_EXPR_IIF173_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF173_0(expr)
# define BOOST_PP_EXPR_IIF173_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF174 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF174(bit, expr) BOOST_PP_EXPR_IIF174_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF174(bit, expr) BOOST_PP_EXPR_IIF174_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF174_OO(par) BOOST_PP_EXPR_IIF174_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF174_I(bit, expr) BOOST_PP_EXPR_IIF174_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF174_0(expr)
# define BOOST_PP_EXPR_IIF174_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF175 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF175(bit, expr) BOOST_PP_EXPR_IIF175_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF175(bit, expr) BOOST_PP_EXPR_IIF175_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF175_OO(par) BOOST_PP_EXPR_IIF175_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF175_I(bit, expr) BOOST_PP_EXPR_IIF175_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF175_0(expr)
# define BOOST_PP_EXPR_IIF175_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF176 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF176(bit, expr) BOOST_PP_EXPR_IIF176_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF176(bit, expr) BOOST_PP_EXPR_IIF176_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF176_OO(par) BOOST_PP_EXPR_IIF176_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF176_I(bit, expr) BOOST_PP_EXPR_IIF176_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF176_0(expr)
# define BOOST_PP_EXPR_IIF176_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF177 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF177(bit, expr) BOOST_PP_EXPR_IIF177_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF177(bit, expr) BOOST_PP_EXPR_IIF177_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF177_OO(par) BOOST_PP_EXPR_IIF177_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF177_I(bit, expr) BOOST_PP_EXPR_IIF177_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF177_0(expr)
# define BOOST_PP_EXPR_IIF177_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF178 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF178(bit, expr) BOOST_PP_EXPR_IIF178_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF178(bit, expr) BOOST_PP_EXPR_IIF178_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF178_OO(par) BOOST_PP_EXPR_IIF178_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF178_I(bit, expr) BOOST_PP_EXPR_IIF178_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF178_0(expr)
# define BOOST_PP_EXPR_IIF178_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF179 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF179(bit, expr) BOOST_PP_EXPR_IIF179_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF179(bit, expr) BOOST_PP_EXPR_IIF179_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF179_OO(par) BOOST_PP_EXPR_IIF179_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF179_I(bit, expr) BOOST_PP_EXPR_IIF179_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF179_0(expr)
# define BOOST_PP_EXPR_IIF179_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF180 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF180(bit, expr) BOOST_PP_EXPR_IIF180_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF180(bit, expr) BOOST_PP_EXPR_IIF180_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF180_OO(par) BOOST_PP_EXPR_IIF180_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF180_I(bit, expr) BOOST_PP_EXPR_IIF180_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF180_0(expr)
# define BOOST_PP_EXPR_IIF180_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF181 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF181(bit, expr) BOOST_PP_EXPR_IIF181_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF181(bit, expr) BOOST_PP_EXPR_IIF181_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF181_OO(par) BOOST_PP_EXPR_IIF181_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF181_I(bit, expr) BOOST_PP_EXPR_IIF181_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF181_0(expr)
# define BOOST_PP_EXPR_IIF181_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF182 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF182(bit, expr) BOOST_PP_EXPR_IIF182_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF182(bit, expr) BOOST_PP_EXPR_IIF182_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF182_OO(par) BOOST_PP_EXPR_IIF182_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF182_I(bit, expr) BOOST_PP_EXPR_IIF182_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF182_0(expr)
# define BOOST_PP_EXPR_IIF182_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF183 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF183(bit, expr) BOOST_PP_EXPR_IIF183_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF183(bit, expr) BOOST_PP_EXPR_IIF183_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF183_OO(par) BOOST_PP_EXPR_IIF183_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF183_I(bit, expr) BOOST_PP_EXPR_IIF183_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF183_0(expr)
# define BOOST_PP_EXPR_IIF183_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF184 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF184(bit, expr) BOOST_PP_EXPR_IIF184_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF184(bit, expr) BOOST_PP_EXPR_IIF184_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF184_OO(par) BOOST_PP_EXPR_IIF184_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF184_I(bit, expr) BOOST_PP_EXPR_IIF184_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF184_0(expr)
# define BOOST_PP_EXPR_IIF184_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF185 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF185(bit, expr) BOOST_PP_EXPR_IIF185_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF185(bit, expr) BOOST_PP_EXPR_IIF185_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF185_OO(par) BOOST_PP_EXPR_IIF185_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF185_I(bit, expr) BOOST_PP_EXPR_IIF185_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF185_0(expr)
# define BOOST_PP_EXPR_IIF185_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF187 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF187(bit, expr) BOOST_PP_EXPR_IIF187_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF187(bit, expr) BOOST_PP_EXPR_IIF187_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF187_OO(par) BOOST_PP_EXPR_IIF187_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF187_I(bit, expr) BOOST_PP_EXPR_IIF187_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF187_0(expr)
# define BOOST_PP_EXPR_IIF187_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF188 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF188(bit, expr) BOOST_PP_EXPR_IIF188_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF188(bit, expr) BOOST_PP_EXPR_IIF188_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF188_OO(par) BOOST_PP_EXPR_IIF188_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF188_I(bit, expr) BOOST_PP_EXPR_IIF188_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF188_0(expr)
# define BOOST_PP_EXPR_IIF188_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF189 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF189(bit, expr) BOOST_PP_EXPR_IIF189_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF189(bit, expr) BOOST_PP_EXPR_IIF189_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF189_OO(par) BOOST_PP_EXPR_IIF189_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF189_I(bit, expr) BOOST_PP_EXPR_IIF189_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF189_0(expr)
# define BOOST_PP_EXPR_IIF189_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF190 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF190(bit, expr) BOOST_PP_EXPR_IIF190_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF190(bit, expr) BOOST_PP_EXPR_IIF190_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF190_OO(par) BOOST_PP_EXPR_IIF190_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF190_I(bit, expr) BOOST_PP_EXPR_IIF190_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF190_0(expr)
# define BOOST_PP_EXPR_IIF190_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF191 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF191(bit, expr) BOOST_PP_EXPR_IIF191_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF191(bit, expr) BOOST_PP_EXPR_IIF191_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF191_OO(par) BOOST_PP_EXPR_IIF191_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF191_I(bit, expr) BOOST_PP_EXPR_IIF191_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF191_0(expr)
# define BOOST_PP_EXPR_IIF191_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF192 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF192(bit, expr) BOOST_PP_EXPR_IIF192_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF192(bit, expr) BOOST_PP_EXPR_IIF192_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF192_OO(par) BOOST_PP_EXPR_IIF192_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF192_I(bit, expr) BOOST_PP_EXPR_IIF192_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF192_0(expr)
# define BOOST_PP_EXPR_IIF192_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF193 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF193(bit, expr) BOOST_PP_EXPR_IIF193_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF193(bit, expr) BOOST_PP_EXPR_IIF193_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF193_OO(par) BOOST_PP_EXPR_IIF193_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF193_I(bit, expr) BOOST_PP_EXPR_IIF193_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF193_0(expr)
# define BOOST_PP_EXPR_IIF193_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF194 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF194(bit, expr) BOOST_PP_EXPR_IIF194_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF194(bit, expr) BOOST_PP_EXPR_IIF194_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF194_OO(par) BOOST_PP_EXPR_IIF194_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF194_I(bit, expr) BOOST_PP_EXPR_IIF194_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF194_0(expr)
# define BOOST_PP_EXPR_IIF194_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF195 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF195(bit, expr) BOOST_PP_EXPR_IIF195_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF195(bit, expr) BOOST_PP_EXPR_IIF195_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF195_OO(par) BOOST_PP_EXPR_IIF195_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF195_I(bit, expr) BOOST_PP_EXPR_IIF195_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF195_0(expr)
# define BOOST_PP_EXPR_IIF195_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF196 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF196(bit, expr) BOOST_PP_EXPR_IIF196_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF196(bit, expr) BOOST_PP_EXPR_IIF196_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF196_OO(par) BOOST_PP_EXPR_IIF196_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF196_I(bit, expr) BOOST_PP_EXPR_IIF196_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF196_0(expr)
# define BOOST_PP_EXPR_IIF196_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF197 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF197(bit, expr) BOOST_PP_EXPR_IIF197_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF197(bit, expr) BOOST_PP_EXPR_IIF197_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF197_OO(par) BOOST_PP_EXPR_IIF197_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF197_I(bit, expr) BOOST_PP_EXPR_IIF197_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF197_0(expr)
# define BOOST_PP_EXPR_IIF197_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF198 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF198(bit, expr) BOOST_PP_EXPR_IIF198_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF198(bit, expr) BOOST_PP_EXPR_IIF198_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF198_OO(par) BOOST_PP_EXPR_IIF198_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF198_I(bit, expr) BOOST_PP_EXPR_IIF198_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF198_0(expr)
# define BOOST_PP_EXPR_IIF198_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF199 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF199(bit, expr) BOOST_PP_EXPR_IIF199_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF199(bit, expr) BOOST_PP_EXPR_IIF199_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF199_OO(par) BOOST_PP_EXPR_IIF199_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF199_I(bit, expr) BOOST_PP_EXPR_IIF199_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF199_0(expr)
# define BOOST_PP_EXPR_IIF199_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF200 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF200(bit, expr) BOOST_PP_EXPR_IIF200_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF200(bit, expr) BOOST_PP_EXPR_IIF200_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF200_OO(par) BOOST_PP_EXPR_IIF200_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF200_I(bit, expr) BOOST_PP_EXPR_IIF200_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF200_0(expr)
# define BOOST_PP_EXPR_IIF200_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF201 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF201(bit, expr) BOOST_PP_EXPR_IIF201_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF201(bit, expr) BOOST_PP_EXPR_IIF201_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF201_OO(par) BOOST_PP_EXPR_IIF201_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF201_I(bit, expr) BOOST_PP_EXPR_IIF201_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF201_0(expr)
# define BOOST_PP_EXPR_IIF201_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF202 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF202(bit, expr) BOOST_PP_EXPR_IIF202_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF202(bit, expr) BOOST_PP_EXPR_IIF202_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF202_OO(par) BOOST_PP_EXPR_IIF202_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF202_I(bit, expr) BOOST_PP_EXPR_IIF202_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF202_0(expr)
# define BOOST_PP_EXPR_IIF202_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF203 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF203(bit, expr) BOOST_PP_EXPR_IIF203_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF203(bit, expr) BOOST_PP_EXPR_IIF203_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF203_OO(par) BOOST_PP_EXPR_IIF203_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF203_I(bit, expr) BOOST_PP_EXPR_IIF203_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF203_0(expr)
# define BOOST_PP_EXPR_IIF203_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF204 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF204(bit, expr) BOOST_PP_EXPR_IIF204_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF204(bit, expr) BOOST_PP_EXPR_IIF204_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF204_OO(par) BOOST_PP_EXPR_IIF204_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF204_I(bit, expr) BOOST_PP_EXPR_IIF204_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF204_0(expr)
# define BOOST_PP_EXPR_IIF204_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF205 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF205(bit, expr) BOOST_PP_EXPR_IIF205_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF205(bit, expr) BOOST_PP_EXPR_IIF205_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF205_OO(par) BOOST_PP_EXPR_IIF205_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF205_I(bit, expr) BOOST_PP_EXPR_IIF205_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF205_0(expr)
# define BOOST_PP_EXPR_IIF205_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF206 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF206(bit, expr) BOOST_PP_EXPR_IIF206_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF206(bit, expr) BOOST_PP_EXPR_IIF206_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF206_OO(par) BOOST_PP_EXPR_IIF206_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF206_I(bit, expr) BOOST_PP_EXPR_IIF206_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF206_0(expr)
# define BOOST_PP_EXPR_IIF206_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF207 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF207(bit, expr) BOOST_PP_EXPR_IIF207_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF207(bit, expr) BOOST_PP_EXPR_IIF207_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF207_OO(par) BOOST_PP_EXPR_IIF207_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF207_I(bit, expr) BOOST_PP_EXPR_IIF207_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF207_0(expr)
# define BOOST_PP_EXPR_IIF207_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF208 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF208(bit, expr) BOOST_PP_EXPR_IIF208_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF208(bit, expr) BOOST_PP_EXPR_IIF208_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF208_OO(par) BOOST_PP_EXPR_IIF208_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF208_I(bit, expr) BOOST_PP_EXPR_IIF208_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF208_0(expr)
# define BOOST_PP_EXPR_IIF208_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF209 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF209(bit, expr) BOOST_PP_EXPR_IIF209_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF209(bit, expr) BOOST_PP_EXPR_IIF209_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF209_OO(par) BOOST_PP_EXPR_IIF209_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF209_I(bit, expr) BOOST_PP_EXPR_IIF209_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF209_0(expr)
# define BOOST_PP_EXPR_IIF209_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF210 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF210(bit, expr) BOOST_PP_EXPR_IIF210_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF210(bit, expr) BOOST_PP_EXPR_IIF210_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF210_OO(par) BOOST_PP_EXPR_IIF210_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF210_I(bit, expr) BOOST_PP_EXPR_IIF210_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF210_0(expr)
# define BOOST_PP_EXPR_IIF210_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF211 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF211(bit, expr) BOOST_PP_EXPR_IIF211_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF211(bit, expr) BOOST_PP_EXPR_IIF211_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF211_OO(par) BOOST_PP_EXPR_IIF211_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF211_I(bit, expr) BOOST_PP_EXPR_IIF211_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF211_0(expr)
# define BOOST_PP_EXPR_IIF211_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF212 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF212(bit, expr) BOOST_PP_EXPR_IIF212_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF212(bit, expr) BOOST_PP_EXPR_IIF212_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF212_OO(par) BOOST_PP_EXPR_IIF212_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF212_I(bit, expr) BOOST_PP_EXPR_IIF212_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF212_0(expr)
# define BOOST_PP_EXPR_IIF212_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF213 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF213(bit, expr) BOOST_PP_EXPR_IIF213_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF213(bit, expr) BOOST_PP_EXPR_IIF213_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF213_OO(par) BOOST_PP_EXPR_IIF213_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF213_I(bit, expr) BOOST_PP_EXPR_IIF213_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF213_0(expr)
# define BOOST_PP_EXPR_IIF213_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF214 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF214(bit, expr) BOOST_PP_EXPR_IIF214_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF214(bit, expr) BOOST_PP_EXPR_IIF214_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF214_OO(par) BOOST_PP_EXPR_IIF214_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF214_I(bit, expr) BOOST_PP_EXPR_IIF214_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF214_0(expr)
# define BOOST_PP_EXPR_IIF214_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF215 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF215(bit, expr) BOOST_PP_EXPR_IIF215_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF215(bit, expr) BOOST_PP_EXPR_IIF215_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF215_OO(par) BOOST_PP_EXPR_IIF215_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF215_I(bit, expr) BOOST_PP_EXPR_IIF215_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF215_0(expr)
# define BOOST_PP_EXPR_IIF215_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF216 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF216(bit, expr) BOOST_PP_EXPR_IIF216_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF216(bit, expr) BOOST_PP_EXPR_IIF216_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF216_OO(par) BOOST_PP_EXPR_IIF216_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF216_I(bit, expr) BOOST_PP_EXPR_IIF216_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF216_0(expr)
# define BOOST_PP_EXPR_IIF216_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF217 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF217(bit, expr) BOOST_PP_EXPR_IIF217_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF217(bit, expr) BOOST_PP_EXPR_IIF217_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF217_OO(par) BOOST_PP_EXPR_IIF217_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF217_I(bit, expr) BOOST_PP_EXPR_IIF217_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF217_0(expr)
# define BOOST_PP_EXPR_IIF217_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF218 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF218(bit, expr) BOOST_PP_EXPR_IIF218_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF218(bit, expr) BOOST_PP_EXPR_IIF218_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF218_OO(par) BOOST_PP_EXPR_IIF218_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF218_I(bit, expr) BOOST_PP_EXPR_IIF218_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF218_0(expr)
# define BOOST_PP_EXPR_IIF218_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF219 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF219(bit, expr) BOOST_PP_EXPR_IIF219_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF219(bit, expr) BOOST_PP_EXPR_IIF219_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF219_OO(par) BOOST_PP_EXPR_IIF219_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF219_I(bit, expr) BOOST_PP_EXPR_IIF219_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF219_0(expr)
# define BOOST_PP_EXPR_IIF219_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF220 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF220(bit, expr) BOOST_PP_EXPR_IIF220_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF220(bit, expr) BOOST_PP_EXPR_IIF220_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF220_OO(par) BOOST_PP_EXPR_IIF220_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF220_I(bit, expr) BOOST_PP_EXPR_IIF220_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF220_0(expr)
# define BOOST_PP_EXPR_IIF220_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF221 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF221(bit, expr) BOOST_PP_EXPR_IIF221_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF221(bit, expr) BOOST_PP_EXPR_IIF221_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF221_OO(par) BOOST_PP_EXPR_IIF221_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF221_I(bit, expr) BOOST_PP_EXPR_IIF221_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF221_0(expr)
# define BOOST_PP_EXPR_IIF221_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF222 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF222(bit, expr) BOOST_PP_EXPR_IIF222_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF222(bit, expr) BOOST_PP_EXPR_IIF222_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF222_OO(par) BOOST_PP_EXPR_IIF222_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF222_I(bit, expr) BOOST_PP_EXPR_IIF222_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF222_0(expr)
# define BOOST_PP_EXPR_IIF222_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF223 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF223(bit, expr) BOOST_PP_EXPR_IIF223_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF223(bit, expr) BOOST_PP_EXPR_IIF223_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF223_OO(par) BOOST_PP_EXPR_IIF223_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF223_I(bit, expr) BOOST_PP_EXPR_IIF223_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF223_0(expr)
# define BOOST_PP_EXPR_IIF223_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF224 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF224(bit, expr) BOOST_PP_EXPR_IIF224_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF224(bit, expr) BOOST_PP_EXPR_IIF224_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF224_OO(par) BOOST_PP_EXPR_IIF224_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF224_I(bit, expr) BOOST_PP_EXPR_IIF224_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF224_0(expr)
# define BOOST_PP_EXPR_IIF224_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF225 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF225(bit, expr) BOOST_PP_EXPR_IIF225_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF225(bit, expr) BOOST_PP_EXPR_IIF225_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF225_OO(par) BOOST_PP_EXPR_IIF225_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF225_I(bit, expr) BOOST_PP_EXPR_IIF225_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF225_0(expr)
# define BOOST_PP_EXPR_IIF225_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF226 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF226(bit, expr) BOOST_PP_EXPR_IIF226_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF226(bit, expr) BOOST_PP_EXPR_IIF226_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF226_OO(par) BOOST_PP_EXPR_IIF226_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF226_I(bit, expr) BOOST_PP_EXPR_IIF226_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF226_0(expr)
# define BOOST_PP_EXPR_IIF226_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF227 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF227(bit, expr) BOOST_PP_EXPR_IIF227_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF227(bit, expr) BOOST_PP_EXPR_IIF227_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF227_OO(par) BOOST_PP_EXPR_IIF227_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF227_I(bit, expr) BOOST_PP_EXPR_IIF227_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF227_0(expr)
# define BOOST_PP_EXPR_IIF227_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF228 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF228(bit, expr) BOOST_PP_EXPR_IIF228_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF228(bit, expr) BOOST_PP_EXPR_IIF228_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF228_OO(par) BOOST_PP_EXPR_IIF228_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF228_I(bit, expr) BOOST_PP_EXPR_IIF228_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF228_0(expr)
# define BOOST_PP_EXPR_IIF228_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF229 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF229(bit, expr) BOOST_PP_EXPR_IIF229_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF229(bit, expr) BOOST_PP_EXPR_IIF229_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF229_OO(par) BOOST_PP_EXPR_IIF229_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF229_I(bit, expr) BOOST_PP_EXPR_IIF229_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF229_0(expr)
# define BOOST_PP_EXPR_IIF229_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF230 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF230(bit, expr) BOOST_PP_EXPR_IIF230_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF230(bit, expr) BOOST_PP_EXPR_IIF230_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF230_OO(par) BOOST_PP_EXPR_IIF230_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF230_I(bit, expr) BOOST_PP_EXPR_IIF230_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF230_0(expr)
# define BOOST_PP_EXPR_IIF230_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF231 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF231(bit, expr) BOOST_PP_EXPR_IIF231_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF231(bit, expr) BOOST_PP_EXPR_IIF231_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF231_OO(par) BOOST_PP_EXPR_IIF231_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF231_I(bit, expr) BOOST_PP_EXPR_IIF231_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF231_0(expr)
# define BOOST_PP_EXPR_IIF231_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF232 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF232(bit, expr) BOOST_PP_EXPR_IIF232_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF232(bit, expr) BOOST_PP_EXPR_IIF232_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF232_OO(par) BOOST_PP_EXPR_IIF232_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF232_I(bit, expr) BOOST_PP_EXPR_IIF232_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF232_0(expr)
# define BOOST_PP_EXPR_IIF232_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF233 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF233(bit, expr) BOOST_PP_EXPR_IIF233_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF233(bit, expr) BOOST_PP_EXPR_IIF233_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF233_OO(par) BOOST_PP_EXPR_IIF233_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF233_I(bit, expr) BOOST_PP_EXPR_IIF233_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF233_0(expr)
# define BOOST_PP_EXPR_IIF233_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF234 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF234(bit, expr) BOOST_PP_EXPR_IIF234_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF234(bit, expr) BOOST_PP_EXPR_IIF234_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF234_OO(par) BOOST_PP_EXPR_IIF234_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF234_I(bit, expr) BOOST_PP_EXPR_IIF234_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF234_0(expr)
# define BOOST_PP_EXPR_IIF234_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF235 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF235(bit, expr) BOOST_PP_EXPR_IIF235_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF235(bit, expr) BOOST_PP_EXPR_IIF235_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF235_OO(par) BOOST_PP_EXPR_IIF235_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF235_I(bit, expr) BOOST_PP_EXPR_IIF235_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF235_0(expr)
# define BOOST_PP_EXPR_IIF235_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF236 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF236(bit, expr) BOOST_PP_EXPR_IIF236_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF236(bit, expr) BOOST_PP_EXPR_IIF236_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF236_OO(par) BOOST_PP_EXPR_IIF236_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF236_I(bit, expr) BOOST_PP_EXPR_IIF236_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF236_0(expr)
# define BOOST_PP_EXPR_IIF236_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF237 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF237(bit, expr) BOOST_PP_EXPR_IIF237_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF237(bit, expr) BOOST_PP_EXPR_IIF237_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF237_OO(par) BOOST_PP_EXPR_IIF237_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF237_I(bit, expr) BOOST_PP_EXPR_IIF237_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF237_0(expr)
# define BOOST_PP_EXPR_IIF237_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF238 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF238(bit, expr) BOOST_PP_EXPR_IIF238_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF238(bit, expr) BOOST_PP_EXPR_IIF238_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF238_OO(par) BOOST_PP_EXPR_IIF238_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF238_I(bit, expr) BOOST_PP_EXPR_IIF238_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF238_0(expr)
# define BOOST_PP_EXPR_IIF238_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF239 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF239(bit, expr) BOOST_PP_EXPR_IIF239_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF239(bit, expr) BOOST_PP_EXPR_IIF239_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF239_OO(par) BOOST_PP_EXPR_IIF239_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF239_I(bit, expr) BOOST_PP_EXPR_IIF239_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF239_0(expr)
# define BOOST_PP_EXPR_IIF239_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF240 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF240(bit, expr) BOOST_PP_EXPR_IIF240_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF240(bit, expr) BOOST_PP_EXPR_IIF240_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF240_OO(par) BOOST_PP_EXPR_IIF240_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF240_I(bit, expr) BOOST_PP_EXPR_IIF240_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF240_0(expr)
# define BOOST_PP_EXPR_IIF240_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF241 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF241(bit, expr) BOOST_PP_EXPR_IIF241_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF241(bit, expr) BOOST_PP_EXPR_IIF241_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF241_OO(par) BOOST_PP_EXPR_IIF241_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF241_I(bit, expr) BOOST_PP_EXPR_IIF241_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF241_0(expr)
# define BOOST_PP_EXPR_IIF241_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF242 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF242(bit, expr) BOOST_PP_EXPR_IIF242_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF242(bit, expr) BOOST_PP_EXPR_IIF242_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF242_OO(par) BOOST_PP_EXPR_IIF242_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF242_I(bit, expr) BOOST_PP_EXPR_IIF242_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF242_0(expr)
# define BOOST_PP_EXPR_IIF242_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF243 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF243(bit, expr) BOOST_PP_EXPR_IIF243_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF243(bit, expr) BOOST_PP_EXPR_IIF243_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF243_OO(par) BOOST_PP_EXPR_IIF243_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF243_I(bit, expr) BOOST_PP_EXPR_IIF243_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF243_0(expr)
# define BOOST_PP_EXPR_IIF243_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF244 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF244(bit, expr) BOOST_PP_EXPR_IIF244_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF244(bit, expr) BOOST_PP_EXPR_IIF244_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF244_OO(par) BOOST_PP_EXPR_IIF244_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF244_I(bit, expr) BOOST_PP_EXPR_IIF244_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF244_0(expr)
# define BOOST_PP_EXPR_IIF244_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF245 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF245(bit, expr) BOOST_PP_EXPR_IIF245_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF245(bit, expr) BOOST_PP_EXPR_IIF245_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF245_OO(par) BOOST_PP_EXPR_IIF245_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF245_I(bit, expr) BOOST_PP_EXPR_IIF245_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF245_0(expr)
# define BOOST_PP_EXPR_IIF245_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF246 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF246(bit, expr) BOOST_PP_EXPR_IIF246_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF246(bit, expr) BOOST_PP_EXPR_IIF246_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF246_OO(par) BOOST_PP_EXPR_IIF246_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF246_I(bit, expr) BOOST_PP_EXPR_IIF246_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF246_0(expr)
# define BOOST_PP_EXPR_IIF246_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF247 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF247(bit, expr) BOOST_PP_EXPR_IIF247_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF247(bit, expr) BOOST_PP_EXPR_IIF247_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF247_OO(par) BOOST_PP_EXPR_IIF247_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF247_I(bit, expr) BOOST_PP_EXPR_IIF247_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF247_0(expr)
# define BOOST_PP_EXPR_IIF247_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF248 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF248(bit, expr) BOOST_PP_EXPR_IIF248_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF248(bit, expr) BOOST_PP_EXPR_IIF248_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF248_OO(par) BOOST_PP_EXPR_IIF248_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF248_I(bit, expr) BOOST_PP_EXPR_IIF248_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF248_0(expr)
# define BOOST_PP_EXPR_IIF248_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF249 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF249(bit, expr) BOOST_PP_EXPR_IIF249_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF249(bit, expr) BOOST_PP_EXPR_IIF249_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF249_OO(par) BOOST_PP_EXPR_IIF249_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF249_I(bit, expr) BOOST_PP_EXPR_IIF249_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF249_0(expr)
# define BOOST_PP_EXPR_IIF249_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF250 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF250(bit, expr) BOOST_PP_EXPR_IIF250_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF250(bit, expr) BOOST_PP_EXPR_IIF250_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF250_OO(par) BOOST_PP_EXPR_IIF250_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF250_I(bit, expr) BOOST_PP_EXPR_IIF250_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF250_0(expr)
# define BOOST_PP_EXPR_IIF250_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF251 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF251(bit, expr) BOOST_PP_EXPR_IIF251_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF251(bit, expr) BOOST_PP_EXPR_IIF251_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF251_OO(par) BOOST_PP_EXPR_IIF251_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF251_I(bit, expr) BOOST_PP_EXPR_IIF251_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF251_0(expr)
# define BOOST_PP_EXPR_IIF251_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF252 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF252(bit, expr) BOOST_PP_EXPR_IIF252_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF252(bit, expr) BOOST_PP_EXPR_IIF252_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF252_OO(par) BOOST_PP_EXPR_IIF252_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF252_I(bit, expr) BOOST_PP_EXPR_IIF252_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF252_0(expr)
# define BOOST_PP_EXPR_IIF252_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF253 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF253(bit, expr) BOOST_PP_EXPR_IIF253_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF253(bit, expr) BOOST_PP_EXPR_IIF253_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF253_OO(par) BOOST_PP_EXPR_IIF253_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF253_I(bit, expr) BOOST_PP_EXPR_IIF253_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF253_0(expr)
# define BOOST_PP_EXPR_IIF253_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF254 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF254(bit, expr) BOOST_PP_EXPR_IIF254_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF254(bit, expr) BOOST_PP_EXPR_IIF254_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF254_OO(par) BOOST_PP_EXPR_IIF254_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF254_I(bit, expr) BOOST_PP_EXPR_IIF254_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF254_0(expr)
# define BOOST_PP_EXPR_IIF254_1(expr) expr

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
# /* BOOST_PP_EXPR_IIF255 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF255(bit, expr) BOOST_PP_EXPR_IIF255_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF255(bit, expr) BOOST_PP_EXPR_IIF255_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF255_OO(par) BOOST_PP_EXPR_IIF255_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF255_I(bit, expr) BOOST_PP_EXPR_IIF255_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF255_0(expr)
# define BOOST_PP_EXPR_IIF255_1(expr) expr

