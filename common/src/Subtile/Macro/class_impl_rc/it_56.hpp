#pragma once

#define __rc86(name, sub, first, ...) BOOST_PP_EXPR_IF86(BOOST_PP_EXPAND(PP_ARG_COUNT sub), BOOST_PP_SEQ_FOR_EACH86(__sub_for_each86, name, BOOST_PP_TUPLE_TO_SEQ(sub))) first BOOST_PP_SEQ_FOR_EACH(__impl_for_each, name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define __sub_for_each86(r, data, x) __rc87 BOOST_PP_TUPLE_PUSH_FRONT(BOOST_PP_TUPLE_POP_FRONT(x), data::BOOST_PP_TUPLE_ELEM(0, x))