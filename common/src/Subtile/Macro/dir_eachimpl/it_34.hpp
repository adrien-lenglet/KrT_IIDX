#pragma once

#define dir_eachimpl52(r, ns, x) \
ns::BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(1, x), _type)& ns::BOOST_PP_TUPLE_ELEM(1, x)(void) \
{ \
	return BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(1, x), _storage); \
} BOOST_PP_EXPR_IF(BOOST_PP_SUB(BOOST_PP_TUPLE_SIZE(x), 2), BOOST_PP_SEQ_FOR_EACH53(dir_eachimpl53, ns::BOOST_PP_TUPLE_ELEM(0, x), BOOST_PP_TUPLE_TO_SEQ(BOOST_PP_TUPLE_ELEM(2, x))))