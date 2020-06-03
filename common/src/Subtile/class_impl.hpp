#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/push_front.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#include "Macro/boost_pp_eval.hpp"

#define BOOST_PP_DEFER(m) m BOOST_PP_EMPTY()

#define PP_ARG_COUNT_I(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, \
a13, a14, a15, ...) a15
#define PP_ARG_COUNT(...) PP_ARG_COUNT_I(foo, ## __VA_ARGS__, 13, 12, 11, \
10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define class_impl(...) BOOST_PP_EVAL2p8(__rc(__VA_ARGS__))
#define __impl_for_each(r, data, x) data::x

#define _BOOST_PP_SEQ_FOR_EACH() BOOST_PP_SEQ_FOR_EACH

#define __rc(name, sub, first, ...) BOOST_PP_DEFER(_BOOST_PP_SEQ_FOR_EACH)()(__sub_for_each, name, sub) first BOOST_PP_SEQ_FOR_EACH(__impl_for_each, name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define __sub_for_each(r, data, x) __rc BOOST_PP_TUPLE_PUSH_FRONT(BOOST_PP_TUPLE_POP_FRONT(x), data::BOOST_PP_TUPLE_ELEM(0, x))

#define cl(...) ((__VA_ARGS__))

#define sc(name, ...) (name, __VA_ARGS__)
#define lc(name, ...) (name, (), __VA_ARGS__)
#define lc_single(name, ...) (lc(name, __VA_ARGS__))