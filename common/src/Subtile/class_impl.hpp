#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/push_front.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/expand.hpp>

#include "Macro/boost_pp_for_each.h_dupped.hpp"
#include "Macro/boost_pp_expr_if.h_dupped.hpp"
#include "Macro/boost_pp_expr_iif.h_dupped.hpp"
#include "Macro/boost_pp_bool.h_dupped.hpp"

#define EVAL(...) EVAL1024(__VA_ARGS__)
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

#define PP_ARG_COUNT_I(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
a13, a14, a15, ...) a15
#define PP_ARG_COUNT(...) PP_ARG_COUNT_I(foo, ## __VA_ARGS__, 13, 12, 11, \
10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define rc(...) EVAL(__rc0(__VA_ARGS__))
#define __impl_for_each(r, data, x) data::x

#include "Macro/class_impl_rc.hpp_dupped.hpp"

#define sc(name, ...) (name, __VA_ARGS__)
#define lc(name, ...) (name, (), __VA_ARGS__)
#define lc_single(name, ...) (lc(name, __VA_ARGS__))