// Include ResourceEnd.hpp when you're done doing that

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/type_traits/add_const.hpp>
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

#define REM(...) __VA_ARGS__
#define EAT(...)

#define TYPEOF(x) DETAIL_TYPEOF(DETAIL_TYPEOF_PROBE x,)
#define DETAIL_TYPEOF(...) DETAIL_TYPEOF_HEAD(__VA_ARGS__)
#define DETAIL_TYPEOF_HEAD(x, ...) REM x
#define DETAIL_TYPEOF_PROBE(...) (__VA_ARGS__),
#define STRIP(x) EAT x
#define PAIR(x) REM x

#define declfolder_classname(name) BOOST_PP_CAT(name, _class)

#ifndef DECLFOLDER_IMPL

#define declfolder_class(name, ...) class declfolder_classname(name) { BOOST_PP_SEQ_FOR_EACH_I(declfolder_each, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) }

#define declfolder_each(r, data, i, x) \
private: using BOOST_PP_CAT(STRIP(x), _type) = TYPEOF(x);\
BOOST_PP_CAT(STRIP(x), _type) BOOST_PP_CAT(STRIP(x), _storage); \
public: BOOST_PP_CAT(STRIP(x), _type)& STRIP(x)(void);

#define declfolder(name, ...) (declfolder_class(name, __VA_ARGS__)) name
#define declfolder_export(name, ...) extern declfolder_class(name, __VA_ARGS__) name;

#else

#define declfolder_classimpl(ns, ...) BOOST_PP_SEQ_FOR_EACH_I(declfolder_eachimpl, ns, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define NS_MACRO(ns, name, ...) declfolder_classimpl(ns::name, __VA_ARGS__)

#define declfolder_eachimpl(r, ns, i, x) \
ns::BOOST_PP_CAT(STRIP(x), _type)& ns::STRIP(x)(void) \
{ \
	return BOOST_PP_CAT(STRIP(x), _storage); \
} BOOST_PP_IF(BOOST_PP_SUB(BOOST_PP_TUPLE_SIZE(TYPEOF(x)), 2), BOOST_PP_EMPTY(), BOOST_PP_EXPAND(NS_MACRO BOOST_PP_TUPLE_PUSH_FRONT(BOOST_PP_TUPLE_POP_FRONT(TYPEOF(x)), ns)))

#define declfolder(name, ...) (BOOST_PP_TUPLE_PUSH_FRONT(BOOST_PP_TUPLE_PUSH_FRONT(BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__), declfolder_classname(name)), foo)) name
#define declfolder_export(name, ...) declfolder_classname(name) name; declfolder_classimpl(declfolder_classname(name), __VA_ARGS__)

#endif