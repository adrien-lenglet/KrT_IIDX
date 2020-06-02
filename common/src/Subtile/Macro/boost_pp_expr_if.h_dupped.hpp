#pragma once

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF0 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF0(cond, expr) BOOST_PP_EXPR_IIF0(BOOST_PP_BOOL0(cond), expr)
# else
#    define BOOST_PP_EXPR_IF0(cond, expr) BOOST_PP_EXPR_IF0_I(cond, expr)
#    define BOOST_PP_EXPR_IF0_I(cond, expr) BOOST_PP_EXPR_IIF0(BOOST_PP_BOOL0(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF1 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF1(cond, expr) BOOST_PP_EXPR_IIF1(BOOST_PP_BOOL1(cond), expr)
# else
#    define BOOST_PP_EXPR_IF1(cond, expr) BOOST_PP_EXPR_IF1_I(cond, expr)
#    define BOOST_PP_EXPR_IF1_I(cond, expr) BOOST_PP_EXPR_IIF1(BOOST_PP_BOOL1(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF2 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF2(cond, expr) BOOST_PP_EXPR_IIF2(BOOST_PP_BOOL2(cond), expr)
# else
#    define BOOST_PP_EXPR_IF2(cond, expr) BOOST_PP_EXPR_IF2_I(cond, expr)
#    define BOOST_PP_EXPR_IF2_I(cond, expr) BOOST_PP_EXPR_IIF2(BOOST_PP_BOOL2(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF3 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF3(cond, expr) BOOST_PP_EXPR_IIF3(BOOST_PP_BOOL3(cond), expr)
# else
#    define BOOST_PP_EXPR_IF3(cond, expr) BOOST_PP_EXPR_IF3_I(cond, expr)
#    define BOOST_PP_EXPR_IF3_I(cond, expr) BOOST_PP_EXPR_IIF3(BOOST_PP_BOOL3(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF4 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF4(cond, expr) BOOST_PP_EXPR_IIF4(BOOST_PP_BOOL4(cond), expr)
# else
#    define BOOST_PP_EXPR_IF4(cond, expr) BOOST_PP_EXPR_IF4_I(cond, expr)
#    define BOOST_PP_EXPR_IF4_I(cond, expr) BOOST_PP_EXPR_IIF4(BOOST_PP_BOOL4(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF5 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF5(cond, expr) BOOST_PP_EXPR_IIF5(BOOST_PP_BOOL5(cond), expr)
# else
#    define BOOST_PP_EXPR_IF5(cond, expr) BOOST_PP_EXPR_IF5_I(cond, expr)
#    define BOOST_PP_EXPR_IF5_I(cond, expr) BOOST_PP_EXPR_IIF5(BOOST_PP_BOOL5(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF6 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF6(cond, expr) BOOST_PP_EXPR_IIF6(BOOST_PP_BOOL6(cond), expr)
# else
#    define BOOST_PP_EXPR_IF6(cond, expr) BOOST_PP_EXPR_IF6_I(cond, expr)
#    define BOOST_PP_EXPR_IF6_I(cond, expr) BOOST_PP_EXPR_IIF6(BOOST_PP_BOOL6(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF7 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF7(cond, expr) BOOST_PP_EXPR_IIF7(BOOST_PP_BOOL7(cond), expr)
# else
#    define BOOST_PP_EXPR_IF7(cond, expr) BOOST_PP_EXPR_IF7_I(cond, expr)
#    define BOOST_PP_EXPR_IF7_I(cond, expr) BOOST_PP_EXPR_IIF7(BOOST_PP_BOOL7(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF8 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF8(cond, expr) BOOST_PP_EXPR_IIF8(BOOST_PP_BOOL8(cond), expr)
# else
#    define BOOST_PP_EXPR_IF8(cond, expr) BOOST_PP_EXPR_IF8_I(cond, expr)
#    define BOOST_PP_EXPR_IF8_I(cond, expr) BOOST_PP_EXPR_IIF8(BOOST_PP_BOOL8(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF9 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF9(cond, expr) BOOST_PP_EXPR_IIF9(BOOST_PP_BOOL9(cond), expr)
# else
#    define BOOST_PP_EXPR_IF9(cond, expr) BOOST_PP_EXPR_IF9_I(cond, expr)
#    define BOOST_PP_EXPR_IF9_I(cond, expr) BOOST_PP_EXPR_IIF9(BOOST_PP_BOOL9(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF10 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF10(cond, expr) BOOST_PP_EXPR_IIF10(BOOST_PP_BOOL10(cond), expr)
# else
#    define BOOST_PP_EXPR_IF10(cond, expr) BOOST_PP_EXPR_IF10_I(cond, expr)
#    define BOOST_PP_EXPR_IF10_I(cond, expr) BOOST_PP_EXPR_IIF10(BOOST_PP_BOOL10(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF11 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF11(cond, expr) BOOST_PP_EXPR_IIF11(BOOST_PP_BOOL11(cond), expr)
# else
#    define BOOST_PP_EXPR_IF11(cond, expr) BOOST_PP_EXPR_IF11_I(cond, expr)
#    define BOOST_PP_EXPR_IF11_I(cond, expr) BOOST_PP_EXPR_IIF11(BOOST_PP_BOOL11(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF12 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF12(cond, expr) BOOST_PP_EXPR_IIF12(BOOST_PP_BOOL12(cond), expr)
# else
#    define BOOST_PP_EXPR_IF12(cond, expr) BOOST_PP_EXPR_IF12_I(cond, expr)
#    define BOOST_PP_EXPR_IF12_I(cond, expr) BOOST_PP_EXPR_IIF12(BOOST_PP_BOOL12(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF13 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF13(cond, expr) BOOST_PP_EXPR_IIF13(BOOST_PP_BOOL13(cond), expr)
# else
#    define BOOST_PP_EXPR_IF13(cond, expr) BOOST_PP_EXPR_IF13_I(cond, expr)
#    define BOOST_PP_EXPR_IF13_I(cond, expr) BOOST_PP_EXPR_IIF13(BOOST_PP_BOOL13(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF14 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF14(cond, expr) BOOST_PP_EXPR_IIF14(BOOST_PP_BOOL14(cond), expr)
# else
#    define BOOST_PP_EXPR_IF14(cond, expr) BOOST_PP_EXPR_IF14_I(cond, expr)
#    define BOOST_PP_EXPR_IF14_I(cond, expr) BOOST_PP_EXPR_IIF14(BOOST_PP_BOOL14(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF15 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF15(cond, expr) BOOST_PP_EXPR_IIF15(BOOST_PP_BOOL15(cond), expr)
# else
#    define BOOST_PP_EXPR_IF15(cond, expr) BOOST_PP_EXPR_IF15_I(cond, expr)
#    define BOOST_PP_EXPR_IF15_I(cond, expr) BOOST_PP_EXPR_IIF15(BOOST_PP_BOOL15(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF16 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF16(cond, expr) BOOST_PP_EXPR_IIF16(BOOST_PP_BOOL16(cond), expr)
# else
#    define BOOST_PP_EXPR_IF16(cond, expr) BOOST_PP_EXPR_IF16_I(cond, expr)
#    define BOOST_PP_EXPR_IF16_I(cond, expr) BOOST_PP_EXPR_IIF16(BOOST_PP_BOOL16(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF17 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF17(cond, expr) BOOST_PP_EXPR_IIF17(BOOST_PP_BOOL17(cond), expr)
# else
#    define BOOST_PP_EXPR_IF17(cond, expr) BOOST_PP_EXPR_IF17_I(cond, expr)
#    define BOOST_PP_EXPR_IF17_I(cond, expr) BOOST_PP_EXPR_IIF17(BOOST_PP_BOOL17(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF18 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF18(cond, expr) BOOST_PP_EXPR_IIF18(BOOST_PP_BOOL18(cond), expr)
# else
#    define BOOST_PP_EXPR_IF18(cond, expr) BOOST_PP_EXPR_IF18_I(cond, expr)
#    define BOOST_PP_EXPR_IF18_I(cond, expr) BOOST_PP_EXPR_IIF18(BOOST_PP_BOOL18(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF19 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF19(cond, expr) BOOST_PP_EXPR_IIF19(BOOST_PP_BOOL19(cond), expr)
# else
#    define BOOST_PP_EXPR_IF19(cond, expr) BOOST_PP_EXPR_IF19_I(cond, expr)
#    define BOOST_PP_EXPR_IF19_I(cond, expr) BOOST_PP_EXPR_IIF19(BOOST_PP_BOOL19(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF20 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF20(cond, expr) BOOST_PP_EXPR_IIF20(BOOST_PP_BOOL20(cond), expr)
# else
#    define BOOST_PP_EXPR_IF20(cond, expr) BOOST_PP_EXPR_IF20_I(cond, expr)
#    define BOOST_PP_EXPR_IF20_I(cond, expr) BOOST_PP_EXPR_IIF20(BOOST_PP_BOOL20(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF21 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF21(cond, expr) BOOST_PP_EXPR_IIF21(BOOST_PP_BOOL21(cond), expr)
# else
#    define BOOST_PP_EXPR_IF21(cond, expr) BOOST_PP_EXPR_IF21_I(cond, expr)
#    define BOOST_PP_EXPR_IF21_I(cond, expr) BOOST_PP_EXPR_IIF21(BOOST_PP_BOOL21(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF22 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF22(cond, expr) BOOST_PP_EXPR_IIF22(BOOST_PP_BOOL22(cond), expr)
# else
#    define BOOST_PP_EXPR_IF22(cond, expr) BOOST_PP_EXPR_IF22_I(cond, expr)
#    define BOOST_PP_EXPR_IF22_I(cond, expr) BOOST_PP_EXPR_IIF22(BOOST_PP_BOOL22(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF23 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF23(cond, expr) BOOST_PP_EXPR_IIF23(BOOST_PP_BOOL23(cond), expr)
# else
#    define BOOST_PP_EXPR_IF23(cond, expr) BOOST_PP_EXPR_IF23_I(cond, expr)
#    define BOOST_PP_EXPR_IF23_I(cond, expr) BOOST_PP_EXPR_IIF23(BOOST_PP_BOOL23(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF24 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF24(cond, expr) BOOST_PP_EXPR_IIF24(BOOST_PP_BOOL24(cond), expr)
# else
#    define BOOST_PP_EXPR_IF24(cond, expr) BOOST_PP_EXPR_IF24_I(cond, expr)
#    define BOOST_PP_EXPR_IF24_I(cond, expr) BOOST_PP_EXPR_IIF24(BOOST_PP_BOOL24(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF25 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF25(cond, expr) BOOST_PP_EXPR_IIF25(BOOST_PP_BOOL25(cond), expr)
# else
#    define BOOST_PP_EXPR_IF25(cond, expr) BOOST_PP_EXPR_IF25_I(cond, expr)
#    define BOOST_PP_EXPR_IF25_I(cond, expr) BOOST_PP_EXPR_IIF25(BOOST_PP_BOOL25(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF26 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF26(cond, expr) BOOST_PP_EXPR_IIF26(BOOST_PP_BOOL26(cond), expr)
# else
#    define BOOST_PP_EXPR_IF26(cond, expr) BOOST_PP_EXPR_IF26_I(cond, expr)
#    define BOOST_PP_EXPR_IF26_I(cond, expr) BOOST_PP_EXPR_IIF26(BOOST_PP_BOOL26(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF27 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF27(cond, expr) BOOST_PP_EXPR_IIF27(BOOST_PP_BOOL27(cond), expr)
# else
#    define BOOST_PP_EXPR_IF27(cond, expr) BOOST_PP_EXPR_IF27_I(cond, expr)
#    define BOOST_PP_EXPR_IF27_I(cond, expr) BOOST_PP_EXPR_IIF27(BOOST_PP_BOOL27(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF28 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF28(cond, expr) BOOST_PP_EXPR_IIF28(BOOST_PP_BOOL28(cond), expr)
# else
#    define BOOST_PP_EXPR_IF28(cond, expr) BOOST_PP_EXPR_IF28_I(cond, expr)
#    define BOOST_PP_EXPR_IF28_I(cond, expr) BOOST_PP_EXPR_IIF28(BOOST_PP_BOOL28(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF29 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF29(cond, expr) BOOST_PP_EXPR_IIF29(BOOST_PP_BOOL29(cond), expr)
# else
#    define BOOST_PP_EXPR_IF29(cond, expr) BOOST_PP_EXPR_IF29_I(cond, expr)
#    define BOOST_PP_EXPR_IF29_I(cond, expr) BOOST_PP_EXPR_IIF29(BOOST_PP_BOOL29(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF30 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF30(cond, expr) BOOST_PP_EXPR_IIF30(BOOST_PP_BOOL30(cond), expr)
# else
#    define BOOST_PP_EXPR_IF30(cond, expr) BOOST_PP_EXPR_IF30_I(cond, expr)
#    define BOOST_PP_EXPR_IF30_I(cond, expr) BOOST_PP_EXPR_IIF30(BOOST_PP_BOOL30(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF31 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF31(cond, expr) BOOST_PP_EXPR_IIF31(BOOST_PP_BOOL31(cond), expr)
# else
#    define BOOST_PP_EXPR_IF31(cond, expr) BOOST_PP_EXPR_IF31_I(cond, expr)
#    define BOOST_PP_EXPR_IF31_I(cond, expr) BOOST_PP_EXPR_IIF31(BOOST_PP_BOOL31(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF32 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF32(cond, expr) BOOST_PP_EXPR_IIF32(BOOST_PP_BOOL32(cond), expr)
# else
#    define BOOST_PP_EXPR_IF32(cond, expr) BOOST_PP_EXPR_IF32_I(cond, expr)
#    define BOOST_PP_EXPR_IF32_I(cond, expr) BOOST_PP_EXPR_IIF32(BOOST_PP_BOOL32(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF33 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF33(cond, expr) BOOST_PP_EXPR_IIF33(BOOST_PP_BOOL33(cond), expr)
# else
#    define BOOST_PP_EXPR_IF33(cond, expr) BOOST_PP_EXPR_IF33_I(cond, expr)
#    define BOOST_PP_EXPR_IF33_I(cond, expr) BOOST_PP_EXPR_IIF33(BOOST_PP_BOOL33(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF34 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF34(cond, expr) BOOST_PP_EXPR_IIF34(BOOST_PP_BOOL34(cond), expr)
# else
#    define BOOST_PP_EXPR_IF34(cond, expr) BOOST_PP_EXPR_IF34_I(cond, expr)
#    define BOOST_PP_EXPR_IF34_I(cond, expr) BOOST_PP_EXPR_IIF34(BOOST_PP_BOOL34(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF35 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF35(cond, expr) BOOST_PP_EXPR_IIF35(BOOST_PP_BOOL35(cond), expr)
# else
#    define BOOST_PP_EXPR_IF35(cond, expr) BOOST_PP_EXPR_IF35_I(cond, expr)
#    define BOOST_PP_EXPR_IF35_I(cond, expr) BOOST_PP_EXPR_IIF35(BOOST_PP_BOOL35(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF36 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF36(cond, expr) BOOST_PP_EXPR_IIF36(BOOST_PP_BOOL36(cond), expr)
# else
#    define BOOST_PP_EXPR_IF36(cond, expr) BOOST_PP_EXPR_IF36_I(cond, expr)
#    define BOOST_PP_EXPR_IF36_I(cond, expr) BOOST_PP_EXPR_IIF36(BOOST_PP_BOOL36(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF37 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF37(cond, expr) BOOST_PP_EXPR_IIF37(BOOST_PP_BOOL37(cond), expr)
# else
#    define BOOST_PP_EXPR_IF37(cond, expr) BOOST_PP_EXPR_IF37_I(cond, expr)
#    define BOOST_PP_EXPR_IF37_I(cond, expr) BOOST_PP_EXPR_IIF37(BOOST_PP_BOOL37(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF38 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF38(cond, expr) BOOST_PP_EXPR_IIF38(BOOST_PP_BOOL38(cond), expr)
# else
#    define BOOST_PP_EXPR_IF38(cond, expr) BOOST_PP_EXPR_IF38_I(cond, expr)
#    define BOOST_PP_EXPR_IF38_I(cond, expr) BOOST_PP_EXPR_IIF38(BOOST_PP_BOOL38(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF39 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF39(cond, expr) BOOST_PP_EXPR_IIF39(BOOST_PP_BOOL39(cond), expr)
# else
#    define BOOST_PP_EXPR_IF39(cond, expr) BOOST_PP_EXPR_IF39_I(cond, expr)
#    define BOOST_PP_EXPR_IF39_I(cond, expr) BOOST_PP_EXPR_IIF39(BOOST_PP_BOOL39(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF40 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF40(cond, expr) BOOST_PP_EXPR_IIF40(BOOST_PP_BOOL40(cond), expr)
# else
#    define BOOST_PP_EXPR_IF40(cond, expr) BOOST_PP_EXPR_IF40_I(cond, expr)
#    define BOOST_PP_EXPR_IF40_I(cond, expr) BOOST_PP_EXPR_IIF40(BOOST_PP_BOOL40(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF41 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF41(cond, expr) BOOST_PP_EXPR_IIF41(BOOST_PP_BOOL41(cond), expr)
# else
#    define BOOST_PP_EXPR_IF41(cond, expr) BOOST_PP_EXPR_IF41_I(cond, expr)
#    define BOOST_PP_EXPR_IF41_I(cond, expr) BOOST_PP_EXPR_IIF41(BOOST_PP_BOOL41(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF42 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF42(cond, expr) BOOST_PP_EXPR_IIF42(BOOST_PP_BOOL42(cond), expr)
# else
#    define BOOST_PP_EXPR_IF42(cond, expr) BOOST_PP_EXPR_IF42_I(cond, expr)
#    define BOOST_PP_EXPR_IF42_I(cond, expr) BOOST_PP_EXPR_IIF42(BOOST_PP_BOOL42(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF43 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF43(cond, expr) BOOST_PP_EXPR_IIF43(BOOST_PP_BOOL43(cond), expr)
# else
#    define BOOST_PP_EXPR_IF43(cond, expr) BOOST_PP_EXPR_IF43_I(cond, expr)
#    define BOOST_PP_EXPR_IF43_I(cond, expr) BOOST_PP_EXPR_IIF43(BOOST_PP_BOOL43(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF44 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF44(cond, expr) BOOST_PP_EXPR_IIF44(BOOST_PP_BOOL44(cond), expr)
# else
#    define BOOST_PP_EXPR_IF44(cond, expr) BOOST_PP_EXPR_IF44_I(cond, expr)
#    define BOOST_PP_EXPR_IF44_I(cond, expr) BOOST_PP_EXPR_IIF44(BOOST_PP_BOOL44(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF45 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF45(cond, expr) BOOST_PP_EXPR_IIF45(BOOST_PP_BOOL45(cond), expr)
# else
#    define BOOST_PP_EXPR_IF45(cond, expr) BOOST_PP_EXPR_IF45_I(cond, expr)
#    define BOOST_PP_EXPR_IF45_I(cond, expr) BOOST_PP_EXPR_IIF45(BOOST_PP_BOOL45(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF46 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF46(cond, expr) BOOST_PP_EXPR_IIF46(BOOST_PP_BOOL46(cond), expr)
# else
#    define BOOST_PP_EXPR_IF46(cond, expr) BOOST_PP_EXPR_IF46_I(cond, expr)
#    define BOOST_PP_EXPR_IF46_I(cond, expr) BOOST_PP_EXPR_IIF46(BOOST_PP_BOOL46(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF47 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF47(cond, expr) BOOST_PP_EXPR_IIF47(BOOST_PP_BOOL47(cond), expr)
# else
#    define BOOST_PP_EXPR_IF47(cond, expr) BOOST_PP_EXPR_IF47_I(cond, expr)
#    define BOOST_PP_EXPR_IF47_I(cond, expr) BOOST_PP_EXPR_IIF47(BOOST_PP_BOOL47(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF48 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF48(cond, expr) BOOST_PP_EXPR_IIF48(BOOST_PP_BOOL48(cond), expr)
# else
#    define BOOST_PP_EXPR_IF48(cond, expr) BOOST_PP_EXPR_IF48_I(cond, expr)
#    define BOOST_PP_EXPR_IF48_I(cond, expr) BOOST_PP_EXPR_IIF48(BOOST_PP_BOOL48(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF49 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF49(cond, expr) BOOST_PP_EXPR_IIF49(BOOST_PP_BOOL49(cond), expr)
# else
#    define BOOST_PP_EXPR_IF49(cond, expr) BOOST_PP_EXPR_IF49_I(cond, expr)
#    define BOOST_PP_EXPR_IF49_I(cond, expr) BOOST_PP_EXPR_IIF49(BOOST_PP_BOOL49(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF50 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF50(cond, expr) BOOST_PP_EXPR_IIF50(BOOST_PP_BOOL50(cond), expr)
# else
#    define BOOST_PP_EXPR_IF50(cond, expr) BOOST_PP_EXPR_IF50_I(cond, expr)
#    define BOOST_PP_EXPR_IF50_I(cond, expr) BOOST_PP_EXPR_IIF50(BOOST_PP_BOOL50(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF51 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF51(cond, expr) BOOST_PP_EXPR_IIF51(BOOST_PP_BOOL51(cond), expr)
# else
#    define BOOST_PP_EXPR_IF51(cond, expr) BOOST_PP_EXPR_IF51_I(cond, expr)
#    define BOOST_PP_EXPR_IF51_I(cond, expr) BOOST_PP_EXPR_IIF51(BOOST_PP_BOOL51(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF52 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF52(cond, expr) BOOST_PP_EXPR_IIF52(BOOST_PP_BOOL52(cond), expr)
# else
#    define BOOST_PP_EXPR_IF52(cond, expr) BOOST_PP_EXPR_IF52_I(cond, expr)
#    define BOOST_PP_EXPR_IF52_I(cond, expr) BOOST_PP_EXPR_IIF52(BOOST_PP_BOOL52(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF53 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF53(cond, expr) BOOST_PP_EXPR_IIF53(BOOST_PP_BOOL53(cond), expr)
# else
#    define BOOST_PP_EXPR_IF53(cond, expr) BOOST_PP_EXPR_IF53_I(cond, expr)
#    define BOOST_PP_EXPR_IF53_I(cond, expr) BOOST_PP_EXPR_IIF53(BOOST_PP_BOOL53(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF54 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF54(cond, expr) BOOST_PP_EXPR_IIF54(BOOST_PP_BOOL54(cond), expr)
# else
#    define BOOST_PP_EXPR_IF54(cond, expr) BOOST_PP_EXPR_IF54_I(cond, expr)
#    define BOOST_PP_EXPR_IF54_I(cond, expr) BOOST_PP_EXPR_IIF54(BOOST_PP_BOOL54(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF55 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF55(cond, expr) BOOST_PP_EXPR_IIF55(BOOST_PP_BOOL55(cond), expr)
# else
#    define BOOST_PP_EXPR_IF55(cond, expr) BOOST_PP_EXPR_IF55_I(cond, expr)
#    define BOOST_PP_EXPR_IF55_I(cond, expr) BOOST_PP_EXPR_IIF55(BOOST_PP_BOOL55(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF56 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF56(cond, expr) BOOST_PP_EXPR_IIF56(BOOST_PP_BOOL56(cond), expr)
# else
#    define BOOST_PP_EXPR_IF56(cond, expr) BOOST_PP_EXPR_IF56_I(cond, expr)
#    define BOOST_PP_EXPR_IF56_I(cond, expr) BOOST_PP_EXPR_IIF56(BOOST_PP_BOOL56(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF57 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF57(cond, expr) BOOST_PP_EXPR_IIF57(BOOST_PP_BOOL57(cond), expr)
# else
#    define BOOST_PP_EXPR_IF57(cond, expr) BOOST_PP_EXPR_IF57_I(cond, expr)
#    define BOOST_PP_EXPR_IF57_I(cond, expr) BOOST_PP_EXPR_IIF57(BOOST_PP_BOOL57(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF58 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF58(cond, expr) BOOST_PP_EXPR_IIF58(BOOST_PP_BOOL58(cond), expr)
# else
#    define BOOST_PP_EXPR_IF58(cond, expr) BOOST_PP_EXPR_IF58_I(cond, expr)
#    define BOOST_PP_EXPR_IF58_I(cond, expr) BOOST_PP_EXPR_IIF58(BOOST_PP_BOOL58(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF59 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF59(cond, expr) BOOST_PP_EXPR_IIF59(BOOST_PP_BOOL59(cond), expr)
# else
#    define BOOST_PP_EXPR_IF59(cond, expr) BOOST_PP_EXPR_IF59_I(cond, expr)
#    define BOOST_PP_EXPR_IF59_I(cond, expr) BOOST_PP_EXPR_IIF59(BOOST_PP_BOOL59(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF60 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF60(cond, expr) BOOST_PP_EXPR_IIF60(BOOST_PP_BOOL60(cond), expr)
# else
#    define BOOST_PP_EXPR_IF60(cond, expr) BOOST_PP_EXPR_IF60_I(cond, expr)
#    define BOOST_PP_EXPR_IF60_I(cond, expr) BOOST_PP_EXPR_IIF60(BOOST_PP_BOOL60(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF61 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF61(cond, expr) BOOST_PP_EXPR_IIF61(BOOST_PP_BOOL61(cond), expr)
# else
#    define BOOST_PP_EXPR_IF61(cond, expr) BOOST_PP_EXPR_IF61_I(cond, expr)
#    define BOOST_PP_EXPR_IF61_I(cond, expr) BOOST_PP_EXPR_IIF61(BOOST_PP_BOOL61(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF62 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF62(cond, expr) BOOST_PP_EXPR_IIF62(BOOST_PP_BOOL62(cond), expr)
# else
#    define BOOST_PP_EXPR_IF62(cond, expr) BOOST_PP_EXPR_IF62_I(cond, expr)
#    define BOOST_PP_EXPR_IF62_I(cond, expr) BOOST_PP_EXPR_IIF62(BOOST_PP_BOOL62(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF63 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF63(cond, expr) BOOST_PP_EXPR_IIF63(BOOST_PP_BOOL63(cond), expr)
# else
#    define BOOST_PP_EXPR_IF63(cond, expr) BOOST_PP_EXPR_IF63_I(cond, expr)
#    define BOOST_PP_EXPR_IF63_I(cond, expr) BOOST_PP_EXPR_IIF63(BOOST_PP_BOOL63(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF64 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF64(cond, expr) BOOST_PP_EXPR_IIF64(BOOST_PP_BOOL64(cond), expr)
# else
#    define BOOST_PP_EXPR_IF64(cond, expr) BOOST_PP_EXPR_IF64_I(cond, expr)
#    define BOOST_PP_EXPR_IF64_I(cond, expr) BOOST_PP_EXPR_IIF64(BOOST_PP_BOOL64(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF65 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF65(cond, expr) BOOST_PP_EXPR_IIF65(BOOST_PP_BOOL65(cond), expr)
# else
#    define BOOST_PP_EXPR_IF65(cond, expr) BOOST_PP_EXPR_IF65_I(cond, expr)
#    define BOOST_PP_EXPR_IF65_I(cond, expr) BOOST_PP_EXPR_IIF65(BOOST_PP_BOOL65(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF66 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF66(cond, expr) BOOST_PP_EXPR_IIF66(BOOST_PP_BOOL66(cond), expr)
# else
#    define BOOST_PP_EXPR_IF66(cond, expr) BOOST_PP_EXPR_IF66_I(cond, expr)
#    define BOOST_PP_EXPR_IF66_I(cond, expr) BOOST_PP_EXPR_IIF66(BOOST_PP_BOOL66(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF67 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF67(cond, expr) BOOST_PP_EXPR_IIF67(BOOST_PP_BOOL67(cond), expr)
# else
#    define BOOST_PP_EXPR_IF67(cond, expr) BOOST_PP_EXPR_IF67_I(cond, expr)
#    define BOOST_PP_EXPR_IF67_I(cond, expr) BOOST_PP_EXPR_IIF67(BOOST_PP_BOOL67(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF68 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF68(cond, expr) BOOST_PP_EXPR_IIF68(BOOST_PP_BOOL68(cond), expr)
# else
#    define BOOST_PP_EXPR_IF68(cond, expr) BOOST_PP_EXPR_IF68_I(cond, expr)
#    define BOOST_PP_EXPR_IF68_I(cond, expr) BOOST_PP_EXPR_IIF68(BOOST_PP_BOOL68(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF69 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF69(cond, expr) BOOST_PP_EXPR_IIF69(BOOST_PP_BOOL69(cond), expr)
# else
#    define BOOST_PP_EXPR_IF69(cond, expr) BOOST_PP_EXPR_IF69_I(cond, expr)
#    define BOOST_PP_EXPR_IF69_I(cond, expr) BOOST_PP_EXPR_IIF69(BOOST_PP_BOOL69(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF70 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF70(cond, expr) BOOST_PP_EXPR_IIF70(BOOST_PP_BOOL70(cond), expr)
# else
#    define BOOST_PP_EXPR_IF70(cond, expr) BOOST_PP_EXPR_IF70_I(cond, expr)
#    define BOOST_PP_EXPR_IF70_I(cond, expr) BOOST_PP_EXPR_IIF70(BOOST_PP_BOOL70(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF71 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF71(cond, expr) BOOST_PP_EXPR_IIF71(BOOST_PP_BOOL71(cond), expr)
# else
#    define BOOST_PP_EXPR_IF71(cond, expr) BOOST_PP_EXPR_IF71_I(cond, expr)
#    define BOOST_PP_EXPR_IF71_I(cond, expr) BOOST_PP_EXPR_IIF71(BOOST_PP_BOOL71(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF72 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF72(cond, expr) BOOST_PP_EXPR_IIF72(BOOST_PP_BOOL72(cond), expr)
# else
#    define BOOST_PP_EXPR_IF72(cond, expr) BOOST_PP_EXPR_IF72_I(cond, expr)
#    define BOOST_PP_EXPR_IF72_I(cond, expr) BOOST_PP_EXPR_IIF72(BOOST_PP_BOOL72(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF73 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF73(cond, expr) BOOST_PP_EXPR_IIF73(BOOST_PP_BOOL73(cond), expr)
# else
#    define BOOST_PP_EXPR_IF73(cond, expr) BOOST_PP_EXPR_IF73_I(cond, expr)
#    define BOOST_PP_EXPR_IF73_I(cond, expr) BOOST_PP_EXPR_IIF73(BOOST_PP_BOOL73(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF74 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF74(cond, expr) BOOST_PP_EXPR_IIF74(BOOST_PP_BOOL74(cond), expr)
# else
#    define BOOST_PP_EXPR_IF74(cond, expr) BOOST_PP_EXPR_IF74_I(cond, expr)
#    define BOOST_PP_EXPR_IF74_I(cond, expr) BOOST_PP_EXPR_IIF74(BOOST_PP_BOOL74(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF75 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF75(cond, expr) BOOST_PP_EXPR_IIF75(BOOST_PP_BOOL75(cond), expr)
# else
#    define BOOST_PP_EXPR_IF75(cond, expr) BOOST_PP_EXPR_IF75_I(cond, expr)
#    define BOOST_PP_EXPR_IF75_I(cond, expr) BOOST_PP_EXPR_IIF75(BOOST_PP_BOOL75(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF76 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF76(cond, expr) BOOST_PP_EXPR_IIF76(BOOST_PP_BOOL76(cond), expr)
# else
#    define BOOST_PP_EXPR_IF76(cond, expr) BOOST_PP_EXPR_IF76_I(cond, expr)
#    define BOOST_PP_EXPR_IF76_I(cond, expr) BOOST_PP_EXPR_IIF76(BOOST_PP_BOOL76(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF77 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF77(cond, expr) BOOST_PP_EXPR_IIF77(BOOST_PP_BOOL77(cond), expr)
# else
#    define BOOST_PP_EXPR_IF77(cond, expr) BOOST_PP_EXPR_IF77_I(cond, expr)
#    define BOOST_PP_EXPR_IF77_I(cond, expr) BOOST_PP_EXPR_IIF77(BOOST_PP_BOOL77(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF78 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF78(cond, expr) BOOST_PP_EXPR_IIF78(BOOST_PP_BOOL78(cond), expr)
# else
#    define BOOST_PP_EXPR_IF78(cond, expr) BOOST_PP_EXPR_IF78_I(cond, expr)
#    define BOOST_PP_EXPR_IF78_I(cond, expr) BOOST_PP_EXPR_IIF78(BOOST_PP_BOOL78(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF79 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF79(cond, expr) BOOST_PP_EXPR_IIF79(BOOST_PP_BOOL79(cond), expr)
# else
#    define BOOST_PP_EXPR_IF79(cond, expr) BOOST_PP_EXPR_IF79_I(cond, expr)
#    define BOOST_PP_EXPR_IF79_I(cond, expr) BOOST_PP_EXPR_IIF79(BOOST_PP_BOOL79(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF80 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF80(cond, expr) BOOST_PP_EXPR_IIF80(BOOST_PP_BOOL80(cond), expr)
# else
#    define BOOST_PP_EXPR_IF80(cond, expr) BOOST_PP_EXPR_IF80_I(cond, expr)
#    define BOOST_PP_EXPR_IF80_I(cond, expr) BOOST_PP_EXPR_IIF80(BOOST_PP_BOOL80(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF81 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF81(cond, expr) BOOST_PP_EXPR_IIF81(BOOST_PP_BOOL81(cond), expr)
# else
#    define BOOST_PP_EXPR_IF81(cond, expr) BOOST_PP_EXPR_IF81_I(cond, expr)
#    define BOOST_PP_EXPR_IF81_I(cond, expr) BOOST_PP_EXPR_IIF81(BOOST_PP_BOOL81(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF82 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF82(cond, expr) BOOST_PP_EXPR_IIF82(BOOST_PP_BOOL82(cond), expr)
# else
#    define BOOST_PP_EXPR_IF82(cond, expr) BOOST_PP_EXPR_IF82_I(cond, expr)
#    define BOOST_PP_EXPR_IF82_I(cond, expr) BOOST_PP_EXPR_IIF82(BOOST_PP_BOOL82(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF83 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF83(cond, expr) BOOST_PP_EXPR_IIF83(BOOST_PP_BOOL83(cond), expr)
# else
#    define BOOST_PP_EXPR_IF83(cond, expr) BOOST_PP_EXPR_IF83_I(cond, expr)
#    define BOOST_PP_EXPR_IF83_I(cond, expr) BOOST_PP_EXPR_IIF83(BOOST_PP_BOOL83(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF84 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF84(cond, expr) BOOST_PP_EXPR_IIF84(BOOST_PP_BOOL84(cond), expr)
# else
#    define BOOST_PP_EXPR_IF84(cond, expr) BOOST_PP_EXPR_IF84_I(cond, expr)
#    define BOOST_PP_EXPR_IF84_I(cond, expr) BOOST_PP_EXPR_IIF84(BOOST_PP_BOOL84(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF85 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF85(cond, expr) BOOST_PP_EXPR_IIF85(BOOST_PP_BOOL85(cond), expr)
# else
#    define BOOST_PP_EXPR_IF85(cond, expr) BOOST_PP_EXPR_IF85_I(cond, expr)
#    define BOOST_PP_EXPR_IF85_I(cond, expr) BOOST_PP_EXPR_IIF85(BOOST_PP_BOOL85(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF86 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF86(cond, expr) BOOST_PP_EXPR_IIF86(BOOST_PP_BOOL86(cond), expr)
# else
#    define BOOST_PP_EXPR_IF86(cond, expr) BOOST_PP_EXPR_IF86_I(cond, expr)
#    define BOOST_PP_EXPR_IF86_I(cond, expr) BOOST_PP_EXPR_IIF86(BOOST_PP_BOOL86(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF87 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF87(cond, expr) BOOST_PP_EXPR_IIF87(BOOST_PP_BOOL87(cond), expr)
# else
#    define BOOST_PP_EXPR_IF87(cond, expr) BOOST_PP_EXPR_IF87_I(cond, expr)
#    define BOOST_PP_EXPR_IF87_I(cond, expr) BOOST_PP_EXPR_IIF87(BOOST_PP_BOOL87(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF88 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF88(cond, expr) BOOST_PP_EXPR_IIF88(BOOST_PP_BOOL88(cond), expr)
# else
#    define BOOST_PP_EXPR_IF88(cond, expr) BOOST_PP_EXPR_IF88_I(cond, expr)
#    define BOOST_PP_EXPR_IF88_I(cond, expr) BOOST_PP_EXPR_IIF88(BOOST_PP_BOOL88(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF89 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF89(cond, expr) BOOST_PP_EXPR_IIF89(BOOST_PP_BOOL89(cond), expr)
# else
#    define BOOST_PP_EXPR_IF89(cond, expr) BOOST_PP_EXPR_IF89_I(cond, expr)
#    define BOOST_PP_EXPR_IF89_I(cond, expr) BOOST_PP_EXPR_IIF89(BOOST_PP_BOOL89(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF90 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF90(cond, expr) BOOST_PP_EXPR_IIF90(BOOST_PP_BOOL90(cond), expr)
# else
#    define BOOST_PP_EXPR_IF90(cond, expr) BOOST_PP_EXPR_IF90_I(cond, expr)
#    define BOOST_PP_EXPR_IF90_I(cond, expr) BOOST_PP_EXPR_IIF90(BOOST_PP_BOOL90(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF91 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF91(cond, expr) BOOST_PP_EXPR_IIF91(BOOST_PP_BOOL91(cond), expr)
# else
#    define BOOST_PP_EXPR_IF91(cond, expr) BOOST_PP_EXPR_IF91_I(cond, expr)
#    define BOOST_PP_EXPR_IF91_I(cond, expr) BOOST_PP_EXPR_IIF91(BOOST_PP_BOOL91(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF92 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF92(cond, expr) BOOST_PP_EXPR_IIF92(BOOST_PP_BOOL92(cond), expr)
# else
#    define BOOST_PP_EXPR_IF92(cond, expr) BOOST_PP_EXPR_IF92_I(cond, expr)
#    define BOOST_PP_EXPR_IF92_I(cond, expr) BOOST_PP_EXPR_IIF92(BOOST_PP_BOOL92(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF93 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF93(cond, expr) BOOST_PP_EXPR_IIF93(BOOST_PP_BOOL93(cond), expr)
# else
#    define BOOST_PP_EXPR_IF93(cond, expr) BOOST_PP_EXPR_IF93_I(cond, expr)
#    define BOOST_PP_EXPR_IF93_I(cond, expr) BOOST_PP_EXPR_IIF93(BOOST_PP_BOOL93(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF94 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF94(cond, expr) BOOST_PP_EXPR_IIF94(BOOST_PP_BOOL94(cond), expr)
# else
#    define BOOST_PP_EXPR_IF94(cond, expr) BOOST_PP_EXPR_IF94_I(cond, expr)
#    define BOOST_PP_EXPR_IF94_I(cond, expr) BOOST_PP_EXPR_IIF94(BOOST_PP_BOOL94(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF95 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF95(cond, expr) BOOST_PP_EXPR_IIF95(BOOST_PP_BOOL95(cond), expr)
# else
#    define BOOST_PP_EXPR_IF95(cond, expr) BOOST_PP_EXPR_IF95_I(cond, expr)
#    define BOOST_PP_EXPR_IF95_I(cond, expr) BOOST_PP_EXPR_IIF95(BOOST_PP_BOOL95(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF96 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF96(cond, expr) BOOST_PP_EXPR_IIF96(BOOST_PP_BOOL96(cond), expr)
# else
#    define BOOST_PP_EXPR_IF96(cond, expr) BOOST_PP_EXPR_IF96_I(cond, expr)
#    define BOOST_PP_EXPR_IF96_I(cond, expr) BOOST_PP_EXPR_IIF96(BOOST_PP_BOOL96(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF97 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF97(cond, expr) BOOST_PP_EXPR_IIF97(BOOST_PP_BOOL97(cond), expr)
# else
#    define BOOST_PP_EXPR_IF97(cond, expr) BOOST_PP_EXPR_IF97_I(cond, expr)
#    define BOOST_PP_EXPR_IF97_I(cond, expr) BOOST_PP_EXPR_IIF97(BOOST_PP_BOOL97(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF98 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF98(cond, expr) BOOST_PP_EXPR_IIF98(BOOST_PP_BOOL98(cond), expr)
# else
#    define BOOST_PP_EXPR_IF98(cond, expr) BOOST_PP_EXPR_IF98_I(cond, expr)
#    define BOOST_PP_EXPR_IF98_I(cond, expr) BOOST_PP_EXPR_IIF98(BOOST_PP_BOOL98(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF99 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF99(cond, expr) BOOST_PP_EXPR_IIF99(BOOST_PP_BOOL99(cond), expr)
# else
#    define BOOST_PP_EXPR_IF99(cond, expr) BOOST_PP_EXPR_IF99_I(cond, expr)
#    define BOOST_PP_EXPR_IF99_I(cond, expr) BOOST_PP_EXPR_IIF99(BOOST_PP_BOOL99(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF100 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF100(cond, expr) BOOST_PP_EXPR_IIF100(BOOST_PP_BOOL100(cond), expr)
# else
#    define BOOST_PP_EXPR_IF100(cond, expr) BOOST_PP_EXPR_IF100_I(cond, expr)
#    define BOOST_PP_EXPR_IF100_I(cond, expr) BOOST_PP_EXPR_IIF100(BOOST_PP_BOOL100(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF101 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF101(cond, expr) BOOST_PP_EXPR_IIF101(BOOST_PP_BOOL101(cond), expr)
# else
#    define BOOST_PP_EXPR_IF101(cond, expr) BOOST_PP_EXPR_IF101_I(cond, expr)
#    define BOOST_PP_EXPR_IF101_I(cond, expr) BOOST_PP_EXPR_IIF101(BOOST_PP_BOOL101(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF102 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF102(cond, expr) BOOST_PP_EXPR_IIF102(BOOST_PP_BOOL102(cond), expr)
# else
#    define BOOST_PP_EXPR_IF102(cond, expr) BOOST_PP_EXPR_IF102_I(cond, expr)
#    define BOOST_PP_EXPR_IF102_I(cond, expr) BOOST_PP_EXPR_IIF102(BOOST_PP_BOOL102(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF103 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF103(cond, expr) BOOST_PP_EXPR_IIF103(BOOST_PP_BOOL103(cond), expr)
# else
#    define BOOST_PP_EXPR_IF103(cond, expr) BOOST_PP_EXPR_IF103_I(cond, expr)
#    define BOOST_PP_EXPR_IF103_I(cond, expr) BOOST_PP_EXPR_IIF103(BOOST_PP_BOOL103(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF104 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF104(cond, expr) BOOST_PP_EXPR_IIF104(BOOST_PP_BOOL104(cond), expr)
# else
#    define BOOST_PP_EXPR_IF104(cond, expr) BOOST_PP_EXPR_IF104_I(cond, expr)
#    define BOOST_PP_EXPR_IF104_I(cond, expr) BOOST_PP_EXPR_IIF104(BOOST_PP_BOOL104(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF105 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF105(cond, expr) BOOST_PP_EXPR_IIF105(BOOST_PP_BOOL105(cond), expr)
# else
#    define BOOST_PP_EXPR_IF105(cond, expr) BOOST_PP_EXPR_IF105_I(cond, expr)
#    define BOOST_PP_EXPR_IF105_I(cond, expr) BOOST_PP_EXPR_IIF105(BOOST_PP_BOOL105(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF106 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF106(cond, expr) BOOST_PP_EXPR_IIF106(BOOST_PP_BOOL106(cond), expr)
# else
#    define BOOST_PP_EXPR_IF106(cond, expr) BOOST_PP_EXPR_IF106_I(cond, expr)
#    define BOOST_PP_EXPR_IF106_I(cond, expr) BOOST_PP_EXPR_IIF106(BOOST_PP_BOOL106(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF107 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF107(cond, expr) BOOST_PP_EXPR_IIF107(BOOST_PP_BOOL107(cond), expr)
# else
#    define BOOST_PP_EXPR_IF107(cond, expr) BOOST_PP_EXPR_IF107_I(cond, expr)
#    define BOOST_PP_EXPR_IF107_I(cond, expr) BOOST_PP_EXPR_IIF107(BOOST_PP_BOOL107(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF108 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF108(cond, expr) BOOST_PP_EXPR_IIF108(BOOST_PP_BOOL108(cond), expr)
# else
#    define BOOST_PP_EXPR_IF108(cond, expr) BOOST_PP_EXPR_IF108_I(cond, expr)
#    define BOOST_PP_EXPR_IF108_I(cond, expr) BOOST_PP_EXPR_IIF108(BOOST_PP_BOOL108(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF109 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF109(cond, expr) BOOST_PP_EXPR_IIF109(BOOST_PP_BOOL109(cond), expr)
# else
#    define BOOST_PP_EXPR_IF109(cond, expr) BOOST_PP_EXPR_IF109_I(cond, expr)
#    define BOOST_PP_EXPR_IF109_I(cond, expr) BOOST_PP_EXPR_IIF109(BOOST_PP_BOOL109(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF110 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF110(cond, expr) BOOST_PP_EXPR_IIF110(BOOST_PP_BOOL110(cond), expr)
# else
#    define BOOST_PP_EXPR_IF110(cond, expr) BOOST_PP_EXPR_IF110_I(cond, expr)
#    define BOOST_PP_EXPR_IF110_I(cond, expr) BOOST_PP_EXPR_IIF110(BOOST_PP_BOOL110(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF111 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF111(cond, expr) BOOST_PP_EXPR_IIF111(BOOST_PP_BOOL111(cond), expr)
# else
#    define BOOST_PP_EXPR_IF111(cond, expr) BOOST_PP_EXPR_IF111_I(cond, expr)
#    define BOOST_PP_EXPR_IF111_I(cond, expr) BOOST_PP_EXPR_IIF111(BOOST_PP_BOOL111(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF112 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF112(cond, expr) BOOST_PP_EXPR_IIF112(BOOST_PP_BOOL112(cond), expr)
# else
#    define BOOST_PP_EXPR_IF112(cond, expr) BOOST_PP_EXPR_IF112_I(cond, expr)
#    define BOOST_PP_EXPR_IF112_I(cond, expr) BOOST_PP_EXPR_IIF112(BOOST_PP_BOOL112(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF113 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF113(cond, expr) BOOST_PP_EXPR_IIF113(BOOST_PP_BOOL113(cond), expr)
# else
#    define BOOST_PP_EXPR_IF113(cond, expr) BOOST_PP_EXPR_IF113_I(cond, expr)
#    define BOOST_PP_EXPR_IF113_I(cond, expr) BOOST_PP_EXPR_IIF113(BOOST_PP_BOOL113(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF114 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF114(cond, expr) BOOST_PP_EXPR_IIF114(BOOST_PP_BOOL114(cond), expr)
# else
#    define BOOST_PP_EXPR_IF114(cond, expr) BOOST_PP_EXPR_IF114_I(cond, expr)
#    define BOOST_PP_EXPR_IF114_I(cond, expr) BOOST_PP_EXPR_IIF114(BOOST_PP_BOOL114(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF115 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF115(cond, expr) BOOST_PP_EXPR_IIF115(BOOST_PP_BOOL115(cond), expr)
# else
#    define BOOST_PP_EXPR_IF115(cond, expr) BOOST_PP_EXPR_IF115_I(cond, expr)
#    define BOOST_PP_EXPR_IF115_I(cond, expr) BOOST_PP_EXPR_IIF115(BOOST_PP_BOOL115(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF116 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF116(cond, expr) BOOST_PP_EXPR_IIF116(BOOST_PP_BOOL116(cond), expr)
# else
#    define BOOST_PP_EXPR_IF116(cond, expr) BOOST_PP_EXPR_IF116_I(cond, expr)
#    define BOOST_PP_EXPR_IF116_I(cond, expr) BOOST_PP_EXPR_IIF116(BOOST_PP_BOOL116(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF117 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF117(cond, expr) BOOST_PP_EXPR_IIF117(BOOST_PP_BOOL117(cond), expr)
# else
#    define BOOST_PP_EXPR_IF117(cond, expr) BOOST_PP_EXPR_IF117_I(cond, expr)
#    define BOOST_PP_EXPR_IF117_I(cond, expr) BOOST_PP_EXPR_IIF117(BOOST_PP_BOOL117(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF118 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF118(cond, expr) BOOST_PP_EXPR_IIF118(BOOST_PP_BOOL118(cond), expr)
# else
#    define BOOST_PP_EXPR_IF118(cond, expr) BOOST_PP_EXPR_IF118_I(cond, expr)
#    define BOOST_PP_EXPR_IF118_I(cond, expr) BOOST_PP_EXPR_IIF118(BOOST_PP_BOOL118(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF119 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF119(cond, expr) BOOST_PP_EXPR_IIF119(BOOST_PP_BOOL119(cond), expr)
# else
#    define BOOST_PP_EXPR_IF119(cond, expr) BOOST_PP_EXPR_IF119_I(cond, expr)
#    define BOOST_PP_EXPR_IF119_I(cond, expr) BOOST_PP_EXPR_IIF119(BOOST_PP_BOOL119(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF120 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF120(cond, expr) BOOST_PP_EXPR_IIF120(BOOST_PP_BOOL120(cond), expr)
# else
#    define BOOST_PP_EXPR_IF120(cond, expr) BOOST_PP_EXPR_IF120_I(cond, expr)
#    define BOOST_PP_EXPR_IF120_I(cond, expr) BOOST_PP_EXPR_IIF120(BOOST_PP_BOOL120(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF121 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF121(cond, expr) BOOST_PP_EXPR_IIF121(BOOST_PP_BOOL121(cond), expr)
# else
#    define BOOST_PP_EXPR_IF121(cond, expr) BOOST_PP_EXPR_IF121_I(cond, expr)
#    define BOOST_PP_EXPR_IF121_I(cond, expr) BOOST_PP_EXPR_IIF121(BOOST_PP_BOOL121(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF122 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF122(cond, expr) BOOST_PP_EXPR_IIF122(BOOST_PP_BOOL122(cond), expr)
# else
#    define BOOST_PP_EXPR_IF122(cond, expr) BOOST_PP_EXPR_IF122_I(cond, expr)
#    define BOOST_PP_EXPR_IF122_I(cond, expr) BOOST_PP_EXPR_IIF122(BOOST_PP_BOOL122(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF123 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF123(cond, expr) BOOST_PP_EXPR_IIF123(BOOST_PP_BOOL123(cond), expr)
# else
#    define BOOST_PP_EXPR_IF123(cond, expr) BOOST_PP_EXPR_IF123_I(cond, expr)
#    define BOOST_PP_EXPR_IF123_I(cond, expr) BOOST_PP_EXPR_IIF123(BOOST_PP_BOOL123(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF124 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF124(cond, expr) BOOST_PP_EXPR_IIF124(BOOST_PP_BOOL124(cond), expr)
# else
#    define BOOST_PP_EXPR_IF124(cond, expr) BOOST_PP_EXPR_IF124_I(cond, expr)
#    define BOOST_PP_EXPR_IF124_I(cond, expr) BOOST_PP_EXPR_IIF124(BOOST_PP_BOOL124(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF125 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF125(cond, expr) BOOST_PP_EXPR_IIF125(BOOST_PP_BOOL125(cond), expr)
# else
#    define BOOST_PP_EXPR_IF125(cond, expr) BOOST_PP_EXPR_IF125_I(cond, expr)
#    define BOOST_PP_EXPR_IF125_I(cond, expr) BOOST_PP_EXPR_IIF125(BOOST_PP_BOOL125(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF126 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF126(cond, expr) BOOST_PP_EXPR_IIF126(BOOST_PP_BOOL126(cond), expr)
# else
#    define BOOST_PP_EXPR_IF126(cond, expr) BOOST_PP_EXPR_IF126_I(cond, expr)
#    define BOOST_PP_EXPR_IF126_I(cond, expr) BOOST_PP_EXPR_IIF126(BOOST_PP_BOOL126(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF127 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF127(cond, expr) BOOST_PP_EXPR_IIF127(BOOST_PP_BOOL127(cond), expr)
# else
#    define BOOST_PP_EXPR_IF127(cond, expr) BOOST_PP_EXPR_IF127_I(cond, expr)
#    define BOOST_PP_EXPR_IF127_I(cond, expr) BOOST_PP_EXPR_IIF127(BOOST_PP_BOOL127(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF128 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF128(cond, expr) BOOST_PP_EXPR_IIF128(BOOST_PP_BOOL128(cond), expr)
# else
#    define BOOST_PP_EXPR_IF128(cond, expr) BOOST_PP_EXPR_IF128_I(cond, expr)
#    define BOOST_PP_EXPR_IF128_I(cond, expr) BOOST_PP_EXPR_IIF128(BOOST_PP_BOOL128(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF129 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF129(cond, expr) BOOST_PP_EXPR_IIF129(BOOST_PP_BOOL129(cond), expr)
# else
#    define BOOST_PP_EXPR_IF129(cond, expr) BOOST_PP_EXPR_IF129_I(cond, expr)
#    define BOOST_PP_EXPR_IF129_I(cond, expr) BOOST_PP_EXPR_IIF129(BOOST_PP_BOOL129(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF130 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF130(cond, expr) BOOST_PP_EXPR_IIF130(BOOST_PP_BOOL130(cond), expr)
# else
#    define BOOST_PP_EXPR_IF130(cond, expr) BOOST_PP_EXPR_IF130_I(cond, expr)
#    define BOOST_PP_EXPR_IF130_I(cond, expr) BOOST_PP_EXPR_IIF130(BOOST_PP_BOOL130(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF131 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF131(cond, expr) BOOST_PP_EXPR_IIF131(BOOST_PP_BOOL131(cond), expr)
# else
#    define BOOST_PP_EXPR_IF131(cond, expr) BOOST_PP_EXPR_IF131_I(cond, expr)
#    define BOOST_PP_EXPR_IF131_I(cond, expr) BOOST_PP_EXPR_IIF131(BOOST_PP_BOOL131(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF132 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF132(cond, expr) BOOST_PP_EXPR_IIF132(BOOST_PP_BOOL132(cond), expr)
# else
#    define BOOST_PP_EXPR_IF132(cond, expr) BOOST_PP_EXPR_IF132_I(cond, expr)
#    define BOOST_PP_EXPR_IF132_I(cond, expr) BOOST_PP_EXPR_IIF132(BOOST_PP_BOOL132(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF133 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF133(cond, expr) BOOST_PP_EXPR_IIF133(BOOST_PP_BOOL133(cond), expr)
# else
#    define BOOST_PP_EXPR_IF133(cond, expr) BOOST_PP_EXPR_IF133_I(cond, expr)
#    define BOOST_PP_EXPR_IF133_I(cond, expr) BOOST_PP_EXPR_IIF133(BOOST_PP_BOOL133(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF134 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF134(cond, expr) BOOST_PP_EXPR_IIF134(BOOST_PP_BOOL134(cond), expr)
# else
#    define BOOST_PP_EXPR_IF134(cond, expr) BOOST_PP_EXPR_IF134_I(cond, expr)
#    define BOOST_PP_EXPR_IF134_I(cond, expr) BOOST_PP_EXPR_IIF134(BOOST_PP_BOOL134(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF135 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF135(cond, expr) BOOST_PP_EXPR_IIF135(BOOST_PP_BOOL135(cond), expr)
# else
#    define BOOST_PP_EXPR_IF135(cond, expr) BOOST_PP_EXPR_IF135_I(cond, expr)
#    define BOOST_PP_EXPR_IF135_I(cond, expr) BOOST_PP_EXPR_IIF135(BOOST_PP_BOOL135(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF136 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF136(cond, expr) BOOST_PP_EXPR_IIF136(BOOST_PP_BOOL136(cond), expr)
# else
#    define BOOST_PP_EXPR_IF136(cond, expr) BOOST_PP_EXPR_IF136_I(cond, expr)
#    define BOOST_PP_EXPR_IF136_I(cond, expr) BOOST_PP_EXPR_IIF136(BOOST_PP_BOOL136(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF137 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF137(cond, expr) BOOST_PP_EXPR_IIF137(BOOST_PP_BOOL137(cond), expr)
# else
#    define BOOST_PP_EXPR_IF137(cond, expr) BOOST_PP_EXPR_IF137_I(cond, expr)
#    define BOOST_PP_EXPR_IF137_I(cond, expr) BOOST_PP_EXPR_IIF137(BOOST_PP_BOOL137(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF138 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF138(cond, expr) BOOST_PP_EXPR_IIF138(BOOST_PP_BOOL138(cond), expr)
# else
#    define BOOST_PP_EXPR_IF138(cond, expr) BOOST_PP_EXPR_IF138_I(cond, expr)
#    define BOOST_PP_EXPR_IF138_I(cond, expr) BOOST_PP_EXPR_IIF138(BOOST_PP_BOOL138(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF139 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF139(cond, expr) BOOST_PP_EXPR_IIF139(BOOST_PP_BOOL139(cond), expr)
# else
#    define BOOST_PP_EXPR_IF139(cond, expr) BOOST_PP_EXPR_IF139_I(cond, expr)
#    define BOOST_PP_EXPR_IF139_I(cond, expr) BOOST_PP_EXPR_IIF139(BOOST_PP_BOOL139(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF140 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF140(cond, expr) BOOST_PP_EXPR_IIF140(BOOST_PP_BOOL140(cond), expr)
# else
#    define BOOST_PP_EXPR_IF140(cond, expr) BOOST_PP_EXPR_IF140_I(cond, expr)
#    define BOOST_PP_EXPR_IF140_I(cond, expr) BOOST_PP_EXPR_IIF140(BOOST_PP_BOOL140(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF141 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF141(cond, expr) BOOST_PP_EXPR_IIF141(BOOST_PP_BOOL141(cond), expr)
# else
#    define BOOST_PP_EXPR_IF141(cond, expr) BOOST_PP_EXPR_IF141_I(cond, expr)
#    define BOOST_PP_EXPR_IF141_I(cond, expr) BOOST_PP_EXPR_IIF141(BOOST_PP_BOOL141(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF142 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF142(cond, expr) BOOST_PP_EXPR_IIF142(BOOST_PP_BOOL142(cond), expr)
# else
#    define BOOST_PP_EXPR_IF142(cond, expr) BOOST_PP_EXPR_IF142_I(cond, expr)
#    define BOOST_PP_EXPR_IF142_I(cond, expr) BOOST_PP_EXPR_IIF142(BOOST_PP_BOOL142(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF143 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF143(cond, expr) BOOST_PP_EXPR_IIF143(BOOST_PP_BOOL143(cond), expr)
# else
#    define BOOST_PP_EXPR_IF143(cond, expr) BOOST_PP_EXPR_IF143_I(cond, expr)
#    define BOOST_PP_EXPR_IF143_I(cond, expr) BOOST_PP_EXPR_IIF143(BOOST_PP_BOOL143(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF144 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF144(cond, expr) BOOST_PP_EXPR_IIF144(BOOST_PP_BOOL144(cond), expr)
# else
#    define BOOST_PP_EXPR_IF144(cond, expr) BOOST_PP_EXPR_IF144_I(cond, expr)
#    define BOOST_PP_EXPR_IF144_I(cond, expr) BOOST_PP_EXPR_IIF144(BOOST_PP_BOOL144(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF145 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF145(cond, expr) BOOST_PP_EXPR_IIF145(BOOST_PP_BOOL145(cond), expr)
# else
#    define BOOST_PP_EXPR_IF145(cond, expr) BOOST_PP_EXPR_IF145_I(cond, expr)
#    define BOOST_PP_EXPR_IF145_I(cond, expr) BOOST_PP_EXPR_IIF145(BOOST_PP_BOOL145(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF146 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF146(cond, expr) BOOST_PP_EXPR_IIF146(BOOST_PP_BOOL146(cond), expr)
# else
#    define BOOST_PP_EXPR_IF146(cond, expr) BOOST_PP_EXPR_IF146_I(cond, expr)
#    define BOOST_PP_EXPR_IF146_I(cond, expr) BOOST_PP_EXPR_IIF146(BOOST_PP_BOOL146(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF147 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF147(cond, expr) BOOST_PP_EXPR_IIF147(BOOST_PP_BOOL147(cond), expr)
# else
#    define BOOST_PP_EXPR_IF147(cond, expr) BOOST_PP_EXPR_IF147_I(cond, expr)
#    define BOOST_PP_EXPR_IF147_I(cond, expr) BOOST_PP_EXPR_IIF147(BOOST_PP_BOOL147(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF148 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF148(cond, expr) BOOST_PP_EXPR_IIF148(BOOST_PP_BOOL148(cond), expr)
# else
#    define BOOST_PP_EXPR_IF148(cond, expr) BOOST_PP_EXPR_IF148_I(cond, expr)
#    define BOOST_PP_EXPR_IF148_I(cond, expr) BOOST_PP_EXPR_IIF148(BOOST_PP_BOOL148(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF149 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF149(cond, expr) BOOST_PP_EXPR_IIF149(BOOST_PP_BOOL149(cond), expr)
# else
#    define BOOST_PP_EXPR_IF149(cond, expr) BOOST_PP_EXPR_IF149_I(cond, expr)
#    define BOOST_PP_EXPR_IF149_I(cond, expr) BOOST_PP_EXPR_IIF149(BOOST_PP_BOOL149(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF150 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF150(cond, expr) BOOST_PP_EXPR_IIF150(BOOST_PP_BOOL150(cond), expr)
# else
#    define BOOST_PP_EXPR_IF150(cond, expr) BOOST_PP_EXPR_IF150_I(cond, expr)
#    define BOOST_PP_EXPR_IF150_I(cond, expr) BOOST_PP_EXPR_IIF150(BOOST_PP_BOOL150(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF151 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF151(cond, expr) BOOST_PP_EXPR_IIF151(BOOST_PP_BOOL151(cond), expr)
# else
#    define BOOST_PP_EXPR_IF151(cond, expr) BOOST_PP_EXPR_IF151_I(cond, expr)
#    define BOOST_PP_EXPR_IF151_I(cond, expr) BOOST_PP_EXPR_IIF151(BOOST_PP_BOOL151(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF152 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF152(cond, expr) BOOST_PP_EXPR_IIF152(BOOST_PP_BOOL152(cond), expr)
# else
#    define BOOST_PP_EXPR_IF152(cond, expr) BOOST_PP_EXPR_IF152_I(cond, expr)
#    define BOOST_PP_EXPR_IF152_I(cond, expr) BOOST_PP_EXPR_IIF152(BOOST_PP_BOOL152(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF153 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF153(cond, expr) BOOST_PP_EXPR_IIF153(BOOST_PP_BOOL153(cond), expr)
# else
#    define BOOST_PP_EXPR_IF153(cond, expr) BOOST_PP_EXPR_IF153_I(cond, expr)
#    define BOOST_PP_EXPR_IF153_I(cond, expr) BOOST_PP_EXPR_IIF153(BOOST_PP_BOOL153(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF154 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF154(cond, expr) BOOST_PP_EXPR_IIF154(BOOST_PP_BOOL154(cond), expr)
# else
#    define BOOST_PP_EXPR_IF154(cond, expr) BOOST_PP_EXPR_IF154_I(cond, expr)
#    define BOOST_PP_EXPR_IF154_I(cond, expr) BOOST_PP_EXPR_IIF154(BOOST_PP_BOOL154(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF155 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF155(cond, expr) BOOST_PP_EXPR_IIF155(BOOST_PP_BOOL155(cond), expr)
# else
#    define BOOST_PP_EXPR_IF155(cond, expr) BOOST_PP_EXPR_IF155_I(cond, expr)
#    define BOOST_PP_EXPR_IF155_I(cond, expr) BOOST_PP_EXPR_IIF155(BOOST_PP_BOOL155(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF156 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF156(cond, expr) BOOST_PP_EXPR_IIF156(BOOST_PP_BOOL156(cond), expr)
# else
#    define BOOST_PP_EXPR_IF156(cond, expr) BOOST_PP_EXPR_IF156_I(cond, expr)
#    define BOOST_PP_EXPR_IF156_I(cond, expr) BOOST_PP_EXPR_IIF156(BOOST_PP_BOOL156(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF157 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF157(cond, expr) BOOST_PP_EXPR_IIF157(BOOST_PP_BOOL157(cond), expr)
# else
#    define BOOST_PP_EXPR_IF157(cond, expr) BOOST_PP_EXPR_IF157_I(cond, expr)
#    define BOOST_PP_EXPR_IF157_I(cond, expr) BOOST_PP_EXPR_IIF157(BOOST_PP_BOOL157(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF158 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF158(cond, expr) BOOST_PP_EXPR_IIF158(BOOST_PP_BOOL158(cond), expr)
# else
#    define BOOST_PP_EXPR_IF158(cond, expr) BOOST_PP_EXPR_IF158_I(cond, expr)
#    define BOOST_PP_EXPR_IF158_I(cond, expr) BOOST_PP_EXPR_IIF158(BOOST_PP_BOOL158(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF159 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF159(cond, expr) BOOST_PP_EXPR_IIF159(BOOST_PP_BOOL159(cond), expr)
# else
#    define BOOST_PP_EXPR_IF159(cond, expr) BOOST_PP_EXPR_IF159_I(cond, expr)
#    define BOOST_PP_EXPR_IF159_I(cond, expr) BOOST_PP_EXPR_IIF159(BOOST_PP_BOOL159(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF160 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF160(cond, expr) BOOST_PP_EXPR_IIF160(BOOST_PP_BOOL160(cond), expr)
# else
#    define BOOST_PP_EXPR_IF160(cond, expr) BOOST_PP_EXPR_IF160_I(cond, expr)
#    define BOOST_PP_EXPR_IF160_I(cond, expr) BOOST_PP_EXPR_IIF160(BOOST_PP_BOOL160(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF161 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF161(cond, expr) BOOST_PP_EXPR_IIF161(BOOST_PP_BOOL161(cond), expr)
# else
#    define BOOST_PP_EXPR_IF161(cond, expr) BOOST_PP_EXPR_IF161_I(cond, expr)
#    define BOOST_PP_EXPR_IF161_I(cond, expr) BOOST_PP_EXPR_IIF161(BOOST_PP_BOOL161(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF162 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF162(cond, expr) BOOST_PP_EXPR_IIF162(BOOST_PP_BOOL162(cond), expr)
# else
#    define BOOST_PP_EXPR_IF162(cond, expr) BOOST_PP_EXPR_IF162_I(cond, expr)
#    define BOOST_PP_EXPR_IF162_I(cond, expr) BOOST_PP_EXPR_IIF162(BOOST_PP_BOOL162(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF163 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF163(cond, expr) BOOST_PP_EXPR_IIF163(BOOST_PP_BOOL163(cond), expr)
# else
#    define BOOST_PP_EXPR_IF163(cond, expr) BOOST_PP_EXPR_IF163_I(cond, expr)
#    define BOOST_PP_EXPR_IF163_I(cond, expr) BOOST_PP_EXPR_IIF163(BOOST_PP_BOOL163(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF164 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF164(cond, expr) BOOST_PP_EXPR_IIF164(BOOST_PP_BOOL164(cond), expr)
# else
#    define BOOST_PP_EXPR_IF164(cond, expr) BOOST_PP_EXPR_IF164_I(cond, expr)
#    define BOOST_PP_EXPR_IF164_I(cond, expr) BOOST_PP_EXPR_IIF164(BOOST_PP_BOOL164(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF165 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF165(cond, expr) BOOST_PP_EXPR_IIF165(BOOST_PP_BOOL165(cond), expr)
# else
#    define BOOST_PP_EXPR_IF165(cond, expr) BOOST_PP_EXPR_IF165_I(cond, expr)
#    define BOOST_PP_EXPR_IF165_I(cond, expr) BOOST_PP_EXPR_IIF165(BOOST_PP_BOOL165(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF166 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF166(cond, expr) BOOST_PP_EXPR_IIF166(BOOST_PP_BOOL166(cond), expr)
# else
#    define BOOST_PP_EXPR_IF166(cond, expr) BOOST_PP_EXPR_IF166_I(cond, expr)
#    define BOOST_PP_EXPR_IF166_I(cond, expr) BOOST_PP_EXPR_IIF166(BOOST_PP_BOOL166(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF167 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF167(cond, expr) BOOST_PP_EXPR_IIF167(BOOST_PP_BOOL167(cond), expr)
# else
#    define BOOST_PP_EXPR_IF167(cond, expr) BOOST_PP_EXPR_IF167_I(cond, expr)
#    define BOOST_PP_EXPR_IF167_I(cond, expr) BOOST_PP_EXPR_IIF167(BOOST_PP_BOOL167(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF168 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF168(cond, expr) BOOST_PP_EXPR_IIF168(BOOST_PP_BOOL168(cond), expr)
# else
#    define BOOST_PP_EXPR_IF168(cond, expr) BOOST_PP_EXPR_IF168_I(cond, expr)
#    define BOOST_PP_EXPR_IF168_I(cond, expr) BOOST_PP_EXPR_IIF168(BOOST_PP_BOOL168(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF169 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF169(cond, expr) BOOST_PP_EXPR_IIF169(BOOST_PP_BOOL169(cond), expr)
# else
#    define BOOST_PP_EXPR_IF169(cond, expr) BOOST_PP_EXPR_IF169_I(cond, expr)
#    define BOOST_PP_EXPR_IF169_I(cond, expr) BOOST_PP_EXPR_IIF169(BOOST_PP_BOOL169(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF170 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF170(cond, expr) BOOST_PP_EXPR_IIF170(BOOST_PP_BOOL170(cond), expr)
# else
#    define BOOST_PP_EXPR_IF170(cond, expr) BOOST_PP_EXPR_IF170_I(cond, expr)
#    define BOOST_PP_EXPR_IF170_I(cond, expr) BOOST_PP_EXPR_IIF170(BOOST_PP_BOOL170(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF171 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF171(cond, expr) BOOST_PP_EXPR_IIF171(BOOST_PP_BOOL171(cond), expr)
# else
#    define BOOST_PP_EXPR_IF171(cond, expr) BOOST_PP_EXPR_IF171_I(cond, expr)
#    define BOOST_PP_EXPR_IF171_I(cond, expr) BOOST_PP_EXPR_IIF171(BOOST_PP_BOOL171(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF172 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF172(cond, expr) BOOST_PP_EXPR_IIF172(BOOST_PP_BOOL172(cond), expr)
# else
#    define BOOST_PP_EXPR_IF172(cond, expr) BOOST_PP_EXPR_IF172_I(cond, expr)
#    define BOOST_PP_EXPR_IF172_I(cond, expr) BOOST_PP_EXPR_IIF172(BOOST_PP_BOOL172(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF173 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF173(cond, expr) BOOST_PP_EXPR_IIF173(BOOST_PP_BOOL173(cond), expr)
# else
#    define BOOST_PP_EXPR_IF173(cond, expr) BOOST_PP_EXPR_IF173_I(cond, expr)
#    define BOOST_PP_EXPR_IF173_I(cond, expr) BOOST_PP_EXPR_IIF173(BOOST_PP_BOOL173(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF174 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF174(cond, expr) BOOST_PP_EXPR_IIF174(BOOST_PP_BOOL174(cond), expr)
# else
#    define BOOST_PP_EXPR_IF174(cond, expr) BOOST_PP_EXPR_IF174_I(cond, expr)
#    define BOOST_PP_EXPR_IF174_I(cond, expr) BOOST_PP_EXPR_IIF174(BOOST_PP_BOOL174(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF175 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF175(cond, expr) BOOST_PP_EXPR_IIF175(BOOST_PP_BOOL175(cond), expr)
# else
#    define BOOST_PP_EXPR_IF175(cond, expr) BOOST_PP_EXPR_IF175_I(cond, expr)
#    define BOOST_PP_EXPR_IF175_I(cond, expr) BOOST_PP_EXPR_IIF175(BOOST_PP_BOOL175(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF176 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF176(cond, expr) BOOST_PP_EXPR_IIF176(BOOST_PP_BOOL176(cond), expr)
# else
#    define BOOST_PP_EXPR_IF176(cond, expr) BOOST_PP_EXPR_IF176_I(cond, expr)
#    define BOOST_PP_EXPR_IF176_I(cond, expr) BOOST_PP_EXPR_IIF176(BOOST_PP_BOOL176(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF177 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF177(cond, expr) BOOST_PP_EXPR_IIF177(BOOST_PP_BOOL177(cond), expr)
# else
#    define BOOST_PP_EXPR_IF177(cond, expr) BOOST_PP_EXPR_IF177_I(cond, expr)
#    define BOOST_PP_EXPR_IF177_I(cond, expr) BOOST_PP_EXPR_IIF177(BOOST_PP_BOOL177(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF178 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF178(cond, expr) BOOST_PP_EXPR_IIF178(BOOST_PP_BOOL178(cond), expr)
# else
#    define BOOST_PP_EXPR_IF178(cond, expr) BOOST_PP_EXPR_IF178_I(cond, expr)
#    define BOOST_PP_EXPR_IF178_I(cond, expr) BOOST_PP_EXPR_IIF178(BOOST_PP_BOOL178(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF179 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF179(cond, expr) BOOST_PP_EXPR_IIF179(BOOST_PP_BOOL179(cond), expr)
# else
#    define BOOST_PP_EXPR_IF179(cond, expr) BOOST_PP_EXPR_IF179_I(cond, expr)
#    define BOOST_PP_EXPR_IF179_I(cond, expr) BOOST_PP_EXPR_IIF179(BOOST_PP_BOOL179(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF180 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF180(cond, expr) BOOST_PP_EXPR_IIF180(BOOST_PP_BOOL180(cond), expr)
# else
#    define BOOST_PP_EXPR_IF180(cond, expr) BOOST_PP_EXPR_IF180_I(cond, expr)
#    define BOOST_PP_EXPR_IF180_I(cond, expr) BOOST_PP_EXPR_IIF180(BOOST_PP_BOOL180(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF181 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF181(cond, expr) BOOST_PP_EXPR_IIF181(BOOST_PP_BOOL181(cond), expr)
# else
#    define BOOST_PP_EXPR_IF181(cond, expr) BOOST_PP_EXPR_IF181_I(cond, expr)
#    define BOOST_PP_EXPR_IF181_I(cond, expr) BOOST_PP_EXPR_IIF181(BOOST_PP_BOOL181(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF182 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF182(cond, expr) BOOST_PP_EXPR_IIF182(BOOST_PP_BOOL182(cond), expr)
# else
#    define BOOST_PP_EXPR_IF182(cond, expr) BOOST_PP_EXPR_IF182_I(cond, expr)
#    define BOOST_PP_EXPR_IF182_I(cond, expr) BOOST_PP_EXPR_IIF182(BOOST_PP_BOOL182(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF183 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF183(cond, expr) BOOST_PP_EXPR_IIF183(BOOST_PP_BOOL183(cond), expr)
# else
#    define BOOST_PP_EXPR_IF183(cond, expr) BOOST_PP_EXPR_IF183_I(cond, expr)
#    define BOOST_PP_EXPR_IF183_I(cond, expr) BOOST_PP_EXPR_IIF183(BOOST_PP_BOOL183(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF184 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF184(cond, expr) BOOST_PP_EXPR_IIF184(BOOST_PP_BOOL184(cond), expr)
# else
#    define BOOST_PP_EXPR_IF184(cond, expr) BOOST_PP_EXPR_IF184_I(cond, expr)
#    define BOOST_PP_EXPR_IF184_I(cond, expr) BOOST_PP_EXPR_IIF184(BOOST_PP_BOOL184(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF185 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF185(cond, expr) BOOST_PP_EXPR_IIF185(BOOST_PP_BOOL185(cond), expr)
# else
#    define BOOST_PP_EXPR_IF185(cond, expr) BOOST_PP_EXPR_IF185_I(cond, expr)
#    define BOOST_PP_EXPR_IF185_I(cond, expr) BOOST_PP_EXPR_IIF185(BOOST_PP_BOOL185(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF186 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF186(cond, expr) BOOST_PP_EXPR_IIF186(BOOST_PP_BOOL186(cond), expr)
# else
#    define BOOST_PP_EXPR_IF186(cond, expr) BOOST_PP_EXPR_IF186_I(cond, expr)
#    define BOOST_PP_EXPR_IF186_I(cond, expr) BOOST_PP_EXPR_IIF186(BOOST_PP_BOOL186(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF187 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF187(cond, expr) BOOST_PP_EXPR_IIF187(BOOST_PP_BOOL187(cond), expr)
# else
#    define BOOST_PP_EXPR_IF187(cond, expr) BOOST_PP_EXPR_IF187_I(cond, expr)
#    define BOOST_PP_EXPR_IF187_I(cond, expr) BOOST_PP_EXPR_IIF187(BOOST_PP_BOOL187(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF188 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF188(cond, expr) BOOST_PP_EXPR_IIF188(BOOST_PP_BOOL188(cond), expr)
# else
#    define BOOST_PP_EXPR_IF188(cond, expr) BOOST_PP_EXPR_IF188_I(cond, expr)
#    define BOOST_PP_EXPR_IF188_I(cond, expr) BOOST_PP_EXPR_IIF188(BOOST_PP_BOOL188(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF189 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF189(cond, expr) BOOST_PP_EXPR_IIF189(BOOST_PP_BOOL189(cond), expr)
# else
#    define BOOST_PP_EXPR_IF189(cond, expr) BOOST_PP_EXPR_IF189_I(cond, expr)
#    define BOOST_PP_EXPR_IF189_I(cond, expr) BOOST_PP_EXPR_IIF189(BOOST_PP_BOOL189(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF190 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF190(cond, expr) BOOST_PP_EXPR_IIF190(BOOST_PP_BOOL190(cond), expr)
# else
#    define BOOST_PP_EXPR_IF190(cond, expr) BOOST_PP_EXPR_IF190_I(cond, expr)
#    define BOOST_PP_EXPR_IF190_I(cond, expr) BOOST_PP_EXPR_IIF190(BOOST_PP_BOOL190(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF191 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF191(cond, expr) BOOST_PP_EXPR_IIF191(BOOST_PP_BOOL191(cond), expr)
# else
#    define BOOST_PP_EXPR_IF191(cond, expr) BOOST_PP_EXPR_IF191_I(cond, expr)
#    define BOOST_PP_EXPR_IF191_I(cond, expr) BOOST_PP_EXPR_IIF191(BOOST_PP_BOOL191(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF192 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF192(cond, expr) BOOST_PP_EXPR_IIF192(BOOST_PP_BOOL192(cond), expr)
# else
#    define BOOST_PP_EXPR_IF192(cond, expr) BOOST_PP_EXPR_IF192_I(cond, expr)
#    define BOOST_PP_EXPR_IF192_I(cond, expr) BOOST_PP_EXPR_IIF192(BOOST_PP_BOOL192(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF193 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF193(cond, expr) BOOST_PP_EXPR_IIF193(BOOST_PP_BOOL193(cond), expr)
# else
#    define BOOST_PP_EXPR_IF193(cond, expr) BOOST_PP_EXPR_IF193_I(cond, expr)
#    define BOOST_PP_EXPR_IF193_I(cond, expr) BOOST_PP_EXPR_IIF193(BOOST_PP_BOOL193(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF194 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF194(cond, expr) BOOST_PP_EXPR_IIF194(BOOST_PP_BOOL194(cond), expr)
# else
#    define BOOST_PP_EXPR_IF194(cond, expr) BOOST_PP_EXPR_IF194_I(cond, expr)
#    define BOOST_PP_EXPR_IF194_I(cond, expr) BOOST_PP_EXPR_IIF194(BOOST_PP_BOOL194(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF195 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF195(cond, expr) BOOST_PP_EXPR_IIF195(BOOST_PP_BOOL195(cond), expr)
# else
#    define BOOST_PP_EXPR_IF195(cond, expr) BOOST_PP_EXPR_IF195_I(cond, expr)
#    define BOOST_PP_EXPR_IF195_I(cond, expr) BOOST_PP_EXPR_IIF195(BOOST_PP_BOOL195(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF196 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF196(cond, expr) BOOST_PP_EXPR_IIF196(BOOST_PP_BOOL196(cond), expr)
# else
#    define BOOST_PP_EXPR_IF196(cond, expr) BOOST_PP_EXPR_IF196_I(cond, expr)
#    define BOOST_PP_EXPR_IF196_I(cond, expr) BOOST_PP_EXPR_IIF196(BOOST_PP_BOOL196(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF197 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF197(cond, expr) BOOST_PP_EXPR_IIF197(BOOST_PP_BOOL197(cond), expr)
# else
#    define BOOST_PP_EXPR_IF197(cond, expr) BOOST_PP_EXPR_IF197_I(cond, expr)
#    define BOOST_PP_EXPR_IF197_I(cond, expr) BOOST_PP_EXPR_IIF197(BOOST_PP_BOOL197(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF198 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF198(cond, expr) BOOST_PP_EXPR_IIF198(BOOST_PP_BOOL198(cond), expr)
# else
#    define BOOST_PP_EXPR_IF198(cond, expr) BOOST_PP_EXPR_IF198_I(cond, expr)
#    define BOOST_PP_EXPR_IF198_I(cond, expr) BOOST_PP_EXPR_IIF198(BOOST_PP_BOOL198(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF199 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF199(cond, expr) BOOST_PP_EXPR_IIF199(BOOST_PP_BOOL199(cond), expr)
# else
#    define BOOST_PP_EXPR_IF199(cond, expr) BOOST_PP_EXPR_IF199_I(cond, expr)
#    define BOOST_PP_EXPR_IF199_I(cond, expr) BOOST_PP_EXPR_IIF199(BOOST_PP_BOOL199(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF200 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF200(cond, expr) BOOST_PP_EXPR_IIF200(BOOST_PP_BOOL200(cond), expr)
# else
#    define BOOST_PP_EXPR_IF200(cond, expr) BOOST_PP_EXPR_IF200_I(cond, expr)
#    define BOOST_PP_EXPR_IF200_I(cond, expr) BOOST_PP_EXPR_IIF200(BOOST_PP_BOOL200(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF201 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF201(cond, expr) BOOST_PP_EXPR_IIF201(BOOST_PP_BOOL201(cond), expr)
# else
#    define BOOST_PP_EXPR_IF201(cond, expr) BOOST_PP_EXPR_IF201_I(cond, expr)
#    define BOOST_PP_EXPR_IF201_I(cond, expr) BOOST_PP_EXPR_IIF201(BOOST_PP_BOOL201(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF202 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF202(cond, expr) BOOST_PP_EXPR_IIF202(BOOST_PP_BOOL202(cond), expr)
# else
#    define BOOST_PP_EXPR_IF202(cond, expr) BOOST_PP_EXPR_IF202_I(cond, expr)
#    define BOOST_PP_EXPR_IF202_I(cond, expr) BOOST_PP_EXPR_IIF202(BOOST_PP_BOOL202(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF203 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF203(cond, expr) BOOST_PP_EXPR_IIF203(BOOST_PP_BOOL203(cond), expr)
# else
#    define BOOST_PP_EXPR_IF203(cond, expr) BOOST_PP_EXPR_IF203_I(cond, expr)
#    define BOOST_PP_EXPR_IF203_I(cond, expr) BOOST_PP_EXPR_IIF203(BOOST_PP_BOOL203(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF204 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF204(cond, expr) BOOST_PP_EXPR_IIF204(BOOST_PP_BOOL204(cond), expr)
# else
#    define BOOST_PP_EXPR_IF204(cond, expr) BOOST_PP_EXPR_IF204_I(cond, expr)
#    define BOOST_PP_EXPR_IF204_I(cond, expr) BOOST_PP_EXPR_IIF204(BOOST_PP_BOOL204(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF205 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF205(cond, expr) BOOST_PP_EXPR_IIF205(BOOST_PP_BOOL205(cond), expr)
# else
#    define BOOST_PP_EXPR_IF205(cond, expr) BOOST_PP_EXPR_IF205_I(cond, expr)
#    define BOOST_PP_EXPR_IF205_I(cond, expr) BOOST_PP_EXPR_IIF205(BOOST_PP_BOOL205(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF206 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF206(cond, expr) BOOST_PP_EXPR_IIF206(BOOST_PP_BOOL206(cond), expr)
# else
#    define BOOST_PP_EXPR_IF206(cond, expr) BOOST_PP_EXPR_IF206_I(cond, expr)
#    define BOOST_PP_EXPR_IF206_I(cond, expr) BOOST_PP_EXPR_IIF206(BOOST_PP_BOOL206(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF207 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF207(cond, expr) BOOST_PP_EXPR_IIF207(BOOST_PP_BOOL207(cond), expr)
# else
#    define BOOST_PP_EXPR_IF207(cond, expr) BOOST_PP_EXPR_IF207_I(cond, expr)
#    define BOOST_PP_EXPR_IF207_I(cond, expr) BOOST_PP_EXPR_IIF207(BOOST_PP_BOOL207(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF208 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF208(cond, expr) BOOST_PP_EXPR_IIF208(BOOST_PP_BOOL208(cond), expr)
# else
#    define BOOST_PP_EXPR_IF208(cond, expr) BOOST_PP_EXPR_IF208_I(cond, expr)
#    define BOOST_PP_EXPR_IF208_I(cond, expr) BOOST_PP_EXPR_IIF208(BOOST_PP_BOOL208(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF209 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF209(cond, expr) BOOST_PP_EXPR_IIF209(BOOST_PP_BOOL209(cond), expr)
# else
#    define BOOST_PP_EXPR_IF209(cond, expr) BOOST_PP_EXPR_IF209_I(cond, expr)
#    define BOOST_PP_EXPR_IF209_I(cond, expr) BOOST_PP_EXPR_IIF209(BOOST_PP_BOOL209(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF210 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF210(cond, expr) BOOST_PP_EXPR_IIF210(BOOST_PP_BOOL210(cond), expr)
# else
#    define BOOST_PP_EXPR_IF210(cond, expr) BOOST_PP_EXPR_IF210_I(cond, expr)
#    define BOOST_PP_EXPR_IF210_I(cond, expr) BOOST_PP_EXPR_IIF210(BOOST_PP_BOOL210(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF211 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF211(cond, expr) BOOST_PP_EXPR_IIF211(BOOST_PP_BOOL211(cond), expr)
# else
#    define BOOST_PP_EXPR_IF211(cond, expr) BOOST_PP_EXPR_IF211_I(cond, expr)
#    define BOOST_PP_EXPR_IF211_I(cond, expr) BOOST_PP_EXPR_IIF211(BOOST_PP_BOOL211(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF212 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF212(cond, expr) BOOST_PP_EXPR_IIF212(BOOST_PP_BOOL212(cond), expr)
# else
#    define BOOST_PP_EXPR_IF212(cond, expr) BOOST_PP_EXPR_IF212_I(cond, expr)
#    define BOOST_PP_EXPR_IF212_I(cond, expr) BOOST_PP_EXPR_IIF212(BOOST_PP_BOOL212(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF213 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF213(cond, expr) BOOST_PP_EXPR_IIF213(BOOST_PP_BOOL213(cond), expr)
# else
#    define BOOST_PP_EXPR_IF213(cond, expr) BOOST_PP_EXPR_IF213_I(cond, expr)
#    define BOOST_PP_EXPR_IF213_I(cond, expr) BOOST_PP_EXPR_IIF213(BOOST_PP_BOOL213(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF214 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF214(cond, expr) BOOST_PP_EXPR_IIF214(BOOST_PP_BOOL214(cond), expr)
# else
#    define BOOST_PP_EXPR_IF214(cond, expr) BOOST_PP_EXPR_IF214_I(cond, expr)
#    define BOOST_PP_EXPR_IF214_I(cond, expr) BOOST_PP_EXPR_IIF214(BOOST_PP_BOOL214(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF215 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF215(cond, expr) BOOST_PP_EXPR_IIF215(BOOST_PP_BOOL215(cond), expr)
# else
#    define BOOST_PP_EXPR_IF215(cond, expr) BOOST_PP_EXPR_IF215_I(cond, expr)
#    define BOOST_PP_EXPR_IF215_I(cond, expr) BOOST_PP_EXPR_IIF215(BOOST_PP_BOOL215(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF216 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF216(cond, expr) BOOST_PP_EXPR_IIF216(BOOST_PP_BOOL216(cond), expr)
# else
#    define BOOST_PP_EXPR_IF216(cond, expr) BOOST_PP_EXPR_IF216_I(cond, expr)
#    define BOOST_PP_EXPR_IF216_I(cond, expr) BOOST_PP_EXPR_IIF216(BOOST_PP_BOOL216(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF217 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF217(cond, expr) BOOST_PP_EXPR_IIF217(BOOST_PP_BOOL217(cond), expr)
# else
#    define BOOST_PP_EXPR_IF217(cond, expr) BOOST_PP_EXPR_IF217_I(cond, expr)
#    define BOOST_PP_EXPR_IF217_I(cond, expr) BOOST_PP_EXPR_IIF217(BOOST_PP_BOOL217(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF218 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF218(cond, expr) BOOST_PP_EXPR_IIF218(BOOST_PP_BOOL218(cond), expr)
# else
#    define BOOST_PP_EXPR_IF218(cond, expr) BOOST_PP_EXPR_IF218_I(cond, expr)
#    define BOOST_PP_EXPR_IF218_I(cond, expr) BOOST_PP_EXPR_IIF218(BOOST_PP_BOOL218(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF219 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF219(cond, expr) BOOST_PP_EXPR_IIF219(BOOST_PP_BOOL219(cond), expr)
# else
#    define BOOST_PP_EXPR_IF219(cond, expr) BOOST_PP_EXPR_IF219_I(cond, expr)
#    define BOOST_PP_EXPR_IF219_I(cond, expr) BOOST_PP_EXPR_IIF219(BOOST_PP_BOOL219(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF220 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF220(cond, expr) BOOST_PP_EXPR_IIF220(BOOST_PP_BOOL220(cond), expr)
# else
#    define BOOST_PP_EXPR_IF220(cond, expr) BOOST_PP_EXPR_IF220_I(cond, expr)
#    define BOOST_PP_EXPR_IF220_I(cond, expr) BOOST_PP_EXPR_IIF220(BOOST_PP_BOOL220(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF221 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF221(cond, expr) BOOST_PP_EXPR_IIF221(BOOST_PP_BOOL221(cond), expr)
# else
#    define BOOST_PP_EXPR_IF221(cond, expr) BOOST_PP_EXPR_IF221_I(cond, expr)
#    define BOOST_PP_EXPR_IF221_I(cond, expr) BOOST_PP_EXPR_IIF221(BOOST_PP_BOOL221(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF222 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF222(cond, expr) BOOST_PP_EXPR_IIF222(BOOST_PP_BOOL222(cond), expr)
# else
#    define BOOST_PP_EXPR_IF222(cond, expr) BOOST_PP_EXPR_IF222_I(cond, expr)
#    define BOOST_PP_EXPR_IF222_I(cond, expr) BOOST_PP_EXPR_IIF222(BOOST_PP_BOOL222(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF223 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF223(cond, expr) BOOST_PP_EXPR_IIF223(BOOST_PP_BOOL223(cond), expr)
# else
#    define BOOST_PP_EXPR_IF223(cond, expr) BOOST_PP_EXPR_IF223_I(cond, expr)
#    define BOOST_PP_EXPR_IF223_I(cond, expr) BOOST_PP_EXPR_IIF223(BOOST_PP_BOOL223(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF224 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF224(cond, expr) BOOST_PP_EXPR_IIF224(BOOST_PP_BOOL224(cond), expr)
# else
#    define BOOST_PP_EXPR_IF224(cond, expr) BOOST_PP_EXPR_IF224_I(cond, expr)
#    define BOOST_PP_EXPR_IF224_I(cond, expr) BOOST_PP_EXPR_IIF224(BOOST_PP_BOOL224(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF225 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF225(cond, expr) BOOST_PP_EXPR_IIF225(BOOST_PP_BOOL225(cond), expr)
# else
#    define BOOST_PP_EXPR_IF225(cond, expr) BOOST_PP_EXPR_IF225_I(cond, expr)
#    define BOOST_PP_EXPR_IF225_I(cond, expr) BOOST_PP_EXPR_IIF225(BOOST_PP_BOOL225(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF226 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF226(cond, expr) BOOST_PP_EXPR_IIF226(BOOST_PP_BOOL226(cond), expr)
# else
#    define BOOST_PP_EXPR_IF226(cond, expr) BOOST_PP_EXPR_IF226_I(cond, expr)
#    define BOOST_PP_EXPR_IF226_I(cond, expr) BOOST_PP_EXPR_IIF226(BOOST_PP_BOOL226(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF227 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF227(cond, expr) BOOST_PP_EXPR_IIF227(BOOST_PP_BOOL227(cond), expr)
# else
#    define BOOST_PP_EXPR_IF227(cond, expr) BOOST_PP_EXPR_IF227_I(cond, expr)
#    define BOOST_PP_EXPR_IF227_I(cond, expr) BOOST_PP_EXPR_IIF227(BOOST_PP_BOOL227(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF228 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF228(cond, expr) BOOST_PP_EXPR_IIF228(BOOST_PP_BOOL228(cond), expr)
# else
#    define BOOST_PP_EXPR_IF228(cond, expr) BOOST_PP_EXPR_IF228_I(cond, expr)
#    define BOOST_PP_EXPR_IF228_I(cond, expr) BOOST_PP_EXPR_IIF228(BOOST_PP_BOOL228(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF229 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF229(cond, expr) BOOST_PP_EXPR_IIF229(BOOST_PP_BOOL229(cond), expr)
# else
#    define BOOST_PP_EXPR_IF229(cond, expr) BOOST_PP_EXPR_IF229_I(cond, expr)
#    define BOOST_PP_EXPR_IF229_I(cond, expr) BOOST_PP_EXPR_IIF229(BOOST_PP_BOOL229(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF230 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF230(cond, expr) BOOST_PP_EXPR_IIF230(BOOST_PP_BOOL230(cond), expr)
# else
#    define BOOST_PP_EXPR_IF230(cond, expr) BOOST_PP_EXPR_IF230_I(cond, expr)
#    define BOOST_PP_EXPR_IF230_I(cond, expr) BOOST_PP_EXPR_IIF230(BOOST_PP_BOOL230(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF231 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF231(cond, expr) BOOST_PP_EXPR_IIF231(BOOST_PP_BOOL231(cond), expr)
# else
#    define BOOST_PP_EXPR_IF231(cond, expr) BOOST_PP_EXPR_IF231_I(cond, expr)
#    define BOOST_PP_EXPR_IF231_I(cond, expr) BOOST_PP_EXPR_IIF231(BOOST_PP_BOOL231(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF232 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF232(cond, expr) BOOST_PP_EXPR_IIF232(BOOST_PP_BOOL232(cond), expr)
# else
#    define BOOST_PP_EXPR_IF232(cond, expr) BOOST_PP_EXPR_IF232_I(cond, expr)
#    define BOOST_PP_EXPR_IF232_I(cond, expr) BOOST_PP_EXPR_IIF232(BOOST_PP_BOOL232(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF233 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF233(cond, expr) BOOST_PP_EXPR_IIF233(BOOST_PP_BOOL233(cond), expr)
# else
#    define BOOST_PP_EXPR_IF233(cond, expr) BOOST_PP_EXPR_IF233_I(cond, expr)
#    define BOOST_PP_EXPR_IF233_I(cond, expr) BOOST_PP_EXPR_IIF233(BOOST_PP_BOOL233(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF234 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF234(cond, expr) BOOST_PP_EXPR_IIF234(BOOST_PP_BOOL234(cond), expr)
# else
#    define BOOST_PP_EXPR_IF234(cond, expr) BOOST_PP_EXPR_IF234_I(cond, expr)
#    define BOOST_PP_EXPR_IF234_I(cond, expr) BOOST_PP_EXPR_IIF234(BOOST_PP_BOOL234(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF235 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF235(cond, expr) BOOST_PP_EXPR_IIF235(BOOST_PP_BOOL235(cond), expr)
# else
#    define BOOST_PP_EXPR_IF235(cond, expr) BOOST_PP_EXPR_IF235_I(cond, expr)
#    define BOOST_PP_EXPR_IF235_I(cond, expr) BOOST_PP_EXPR_IIF235(BOOST_PP_BOOL235(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF236 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF236(cond, expr) BOOST_PP_EXPR_IIF236(BOOST_PP_BOOL236(cond), expr)
# else
#    define BOOST_PP_EXPR_IF236(cond, expr) BOOST_PP_EXPR_IF236_I(cond, expr)
#    define BOOST_PP_EXPR_IF236_I(cond, expr) BOOST_PP_EXPR_IIF236(BOOST_PP_BOOL236(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF237 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF237(cond, expr) BOOST_PP_EXPR_IIF237(BOOST_PP_BOOL237(cond), expr)
# else
#    define BOOST_PP_EXPR_IF237(cond, expr) BOOST_PP_EXPR_IF237_I(cond, expr)
#    define BOOST_PP_EXPR_IF237_I(cond, expr) BOOST_PP_EXPR_IIF237(BOOST_PP_BOOL237(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF238 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF238(cond, expr) BOOST_PP_EXPR_IIF238(BOOST_PP_BOOL238(cond), expr)
# else
#    define BOOST_PP_EXPR_IF238(cond, expr) BOOST_PP_EXPR_IF238_I(cond, expr)
#    define BOOST_PP_EXPR_IF238_I(cond, expr) BOOST_PP_EXPR_IIF238(BOOST_PP_BOOL238(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF239 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF239(cond, expr) BOOST_PP_EXPR_IIF239(BOOST_PP_BOOL239(cond), expr)
# else
#    define BOOST_PP_EXPR_IF239(cond, expr) BOOST_PP_EXPR_IF239_I(cond, expr)
#    define BOOST_PP_EXPR_IF239_I(cond, expr) BOOST_PP_EXPR_IIF239(BOOST_PP_BOOL239(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF240 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF240(cond, expr) BOOST_PP_EXPR_IIF240(BOOST_PP_BOOL240(cond), expr)
# else
#    define BOOST_PP_EXPR_IF240(cond, expr) BOOST_PP_EXPR_IF240_I(cond, expr)
#    define BOOST_PP_EXPR_IF240_I(cond, expr) BOOST_PP_EXPR_IIF240(BOOST_PP_BOOL240(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF241 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF241(cond, expr) BOOST_PP_EXPR_IIF241(BOOST_PP_BOOL241(cond), expr)
# else
#    define BOOST_PP_EXPR_IF241(cond, expr) BOOST_PP_EXPR_IF241_I(cond, expr)
#    define BOOST_PP_EXPR_IF241_I(cond, expr) BOOST_PP_EXPR_IIF241(BOOST_PP_BOOL241(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF242 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF242(cond, expr) BOOST_PP_EXPR_IIF242(BOOST_PP_BOOL242(cond), expr)
# else
#    define BOOST_PP_EXPR_IF242(cond, expr) BOOST_PP_EXPR_IF242_I(cond, expr)
#    define BOOST_PP_EXPR_IF242_I(cond, expr) BOOST_PP_EXPR_IIF242(BOOST_PP_BOOL242(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF243 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF243(cond, expr) BOOST_PP_EXPR_IIF243(BOOST_PP_BOOL243(cond), expr)
# else
#    define BOOST_PP_EXPR_IF243(cond, expr) BOOST_PP_EXPR_IF243_I(cond, expr)
#    define BOOST_PP_EXPR_IF243_I(cond, expr) BOOST_PP_EXPR_IIF243(BOOST_PP_BOOL243(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF244 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF244(cond, expr) BOOST_PP_EXPR_IIF244(BOOST_PP_BOOL244(cond), expr)
# else
#    define BOOST_PP_EXPR_IF244(cond, expr) BOOST_PP_EXPR_IF244_I(cond, expr)
#    define BOOST_PP_EXPR_IF244_I(cond, expr) BOOST_PP_EXPR_IIF244(BOOST_PP_BOOL244(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF245 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF245(cond, expr) BOOST_PP_EXPR_IIF245(BOOST_PP_BOOL245(cond), expr)
# else
#    define BOOST_PP_EXPR_IF245(cond, expr) BOOST_PP_EXPR_IF245_I(cond, expr)
#    define BOOST_PP_EXPR_IF245_I(cond, expr) BOOST_PP_EXPR_IIF245(BOOST_PP_BOOL245(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF246 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF246(cond, expr) BOOST_PP_EXPR_IIF246(BOOST_PP_BOOL246(cond), expr)
# else
#    define BOOST_PP_EXPR_IF246(cond, expr) BOOST_PP_EXPR_IF246_I(cond, expr)
#    define BOOST_PP_EXPR_IF246_I(cond, expr) BOOST_PP_EXPR_IIF246(BOOST_PP_BOOL246(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF247 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF247(cond, expr) BOOST_PP_EXPR_IIF247(BOOST_PP_BOOL247(cond), expr)
# else
#    define BOOST_PP_EXPR_IF247(cond, expr) BOOST_PP_EXPR_IF247_I(cond, expr)
#    define BOOST_PP_EXPR_IF247_I(cond, expr) BOOST_PP_EXPR_IIF247(BOOST_PP_BOOL247(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF248 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF248(cond, expr) BOOST_PP_EXPR_IIF248(BOOST_PP_BOOL248(cond), expr)
# else
#    define BOOST_PP_EXPR_IF248(cond, expr) BOOST_PP_EXPR_IF248_I(cond, expr)
#    define BOOST_PP_EXPR_IF248_I(cond, expr) BOOST_PP_EXPR_IIF248(BOOST_PP_BOOL248(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF249 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF249(cond, expr) BOOST_PP_EXPR_IIF249(BOOST_PP_BOOL249(cond), expr)
# else
#    define BOOST_PP_EXPR_IF249(cond, expr) BOOST_PP_EXPR_IF249_I(cond, expr)
#    define BOOST_PP_EXPR_IF249_I(cond, expr) BOOST_PP_EXPR_IIF249(BOOST_PP_BOOL249(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF250 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF250(cond, expr) BOOST_PP_EXPR_IIF250(BOOST_PP_BOOL250(cond), expr)
# else
#    define BOOST_PP_EXPR_IF250(cond, expr) BOOST_PP_EXPR_IF250_I(cond, expr)
#    define BOOST_PP_EXPR_IF250_I(cond, expr) BOOST_PP_EXPR_IIF250(BOOST_PP_BOOL250(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF251 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF251(cond, expr) BOOST_PP_EXPR_IIF251(BOOST_PP_BOOL251(cond), expr)
# else
#    define BOOST_PP_EXPR_IF251(cond, expr) BOOST_PP_EXPR_IF251_I(cond, expr)
#    define BOOST_PP_EXPR_IF251_I(cond, expr) BOOST_PP_EXPR_IIF251(BOOST_PP_BOOL251(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF252 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF252(cond, expr) BOOST_PP_EXPR_IIF252(BOOST_PP_BOOL252(cond), expr)
# else
#    define BOOST_PP_EXPR_IF252(cond, expr) BOOST_PP_EXPR_IF252_I(cond, expr)
#    define BOOST_PP_EXPR_IF252_I(cond, expr) BOOST_PP_EXPR_IIF252(BOOST_PP_BOOL252(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF253 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF253(cond, expr) BOOST_PP_EXPR_IIF253(BOOST_PP_BOOL253(cond), expr)
# else
#    define BOOST_PP_EXPR_IF253(cond, expr) BOOST_PP_EXPR_IF253_I(cond, expr)
#    define BOOST_PP_EXPR_IF253_I(cond, expr) BOOST_PP_EXPR_IIF253(BOOST_PP_BOOL253(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF254 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF254(cond, expr) BOOST_PP_EXPR_IIF254(BOOST_PP_BOOL254(cond), expr)
# else
#    define BOOST_PP_EXPR_IF254(cond, expr) BOOST_PP_EXPR_IF254_I(cond, expr)
#    define BOOST_PP_EXPR_IF254_I(cond, expr) BOOST_PP_EXPR_IIF254(BOOST_PP_BOOL254(cond), expr)
# endif

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF255 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF255(cond, expr) BOOST_PP_EXPR_IIF255(BOOST_PP_BOOL255(cond), expr)
# else
#    define BOOST_PP_EXPR_IF255(cond, expr) BOOST_PP_EXPR_IF255_I(cond, expr)
#    define BOOST_PP_EXPR_IF255_I(cond, expr) BOOST_PP_EXPR_IIF255(BOOST_PP_BOOL255(cond), expr)
# endif

