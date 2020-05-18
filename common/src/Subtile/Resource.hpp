// Include ResourceEnd.hpp when you're done doing that

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#define REM(...) __VA_ARGS__
#define EAT(...)

#define TYPEOF(x) DETAIL_TYPEOF(DETAIL_TYPEOF_PROBE x,)
#define DETAIL_TYPEOF(...) DETAIL_TYPEOF_HEAD(__VA_ARGS__)
#define DETAIL_TYPEOF_HEAD(x, ...) REM x
#define DETAIL_TYPEOF_PROBE(...) (__VA_ARGS__),
#define STRIP(x) EAT x
#define PAIR(x) REM x

#define declfolder_classname(name) BOOST_PP_CAT(name, _class)
#define declfolder_class(name, ...) class declfolder_classname(name) { BOOST_PP_SEQ_FOR_EACH_I(declfolder_each, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) }

#ifndef DECLFOLDER_IMPL
#define declfolder_each(r, data, i, x) \
private: using BOOST_PP_CAT(STRIP(x), _type) = TYPEOF(x);\
BOOST_PP_CAT(STRIP(x), _type) BOOST_PP_CAT(STRIP(x), _storage); \
public: BOOST_PP_CAT(STRIP(x), _type)& STRIP(x)(void);
#else
#endif

#define declfolder(name, ...) (declfolder_class(name, __VA_ARGS__)) name
#define declfolder_export(name, ...) declfolder_class(name, __VA_ARGS__) name;