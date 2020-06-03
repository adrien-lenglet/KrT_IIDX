#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/push_front.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/pop_front.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#include "Macro/boost_pp_eval.hpp"
#include "Macro/boost_pp_defer.hpp"

#define class_impl(...) BOOST_PP_EVAL2p8(__rc_base(__VA_ARGS__))
#define sci(name, ...) BOOST_PP_EVAL2p8(__rc(name,, ((__VA_ARGS__))))
#define scp ))((
#define __impl_for_each(r, data, x) data REM x

#define REM(...) __VA_ARGS__

#define _BOOST_PP_SEQ_FOR_EACH() BOOST_PP_SEQ_FOR_EACH

#define __rc(name, sub, seq) REM BOOST_PP_SEQ_ELEM(0, seq) BOOST_PP_SEQ_FOR_EACH(__impl_for_each, name, BOOST_PP_SEQ_POP_FRONT(seq))

#define sub_class(...) ((__VA_ARGS__))