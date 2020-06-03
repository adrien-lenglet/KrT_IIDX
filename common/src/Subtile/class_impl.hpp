#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/pop_front.hpp>

#include "Macro/boost_pp_eval.hpp"
#include "Macro/boost_pp_defer.hpp"

#define scc(name, ...) __rc(name,, ((__VA_ARGS__)))
#define scp ))((
#define __impl_for_each(r, data, x) data BOOST_PP_REM x

#define __rc(name, sub, seq) BOOST_PP_REM BOOST_PP_SEQ_ELEM(0, seq) BOOST_PP_SEQ_FOR_EACH(__impl_for_each, name, BOOST_PP_SEQ_POP_FRONT(seq))