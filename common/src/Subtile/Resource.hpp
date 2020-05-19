// Include ResourceEnd.hpp when you're done doing that

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/variadic/to_tuple.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/push_front.hpp>
#include <boost/preprocessor/tuple/pop_front.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#define dir_classname(name) BOOST_PP_CAT(name, _class)

#ifndef DIR_IMPL

#define dir_class(name, ...) class dir_classname(name) { BOOST_PP_SEQ_FOR_EACH(dir_each, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) }

#define dir_each(r, data, x) \
private: using BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(1, x), _type) = BOOST_PP_TUPLE_ELEM(0, x);\
BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(1, x), _type) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(1, x), _storage); \
public: BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(1, x), _type)& BOOST_PP_TUPLE_ELEM(1, x)(void);

#define dir(name, ...) (dir_class(name, __VA_ARGS__), name)
#define dir_export(name, ...) extern dir_class(name, __VA_ARGS__) name;

#else

#include "Macro/boost_pp_for_each.h_dupped.hpp"
#include "Macro/dir_eachimpl.hpp_dupped.hpp"

#define dir_classimpl(ns, ...) BOOST_PP_SEQ_FOR_EACH(dir_eachimpl0, ns, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define dir(name, ...) (dir_classname(name), name, (__VA_ARGS__))
#define dir_export(name, ...) dir_classname(name) name; dir_classimpl(dir_classname(name), __VA_ARGS__)

#endif