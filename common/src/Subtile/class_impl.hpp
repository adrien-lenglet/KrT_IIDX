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
#include "Macro/boost_pp_defer.hpp"

#define class_impl(...) BOOST_PP_EVAL2p8(__rc(__VA_ARGS__))
#define __impl_for_each(r, data, x) data::x

#define _BOOST_PP_SEQ_FOR_EACH() BOOST_PP_SEQ_FOR_EACH

#define __rc(name, sub, first, ...) BOOST_PP_DEFER(_BOOST_PP_SEQ_FOR_EACH)()(__sub_for_each, name, sub) first BOOST_PP_SEQ_FOR_EACH(__impl_for_each, name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define __sub_for_each(r, data, x) __rc BOOST_PP_TUPLE_PUSH_FRONT(BOOST_PP_TUPLE_POP_FRONT(x), data::BOOST_PP_TUPLE_ELEM(0, x))

#define sub_class(...) ((__VA_ARGS__))