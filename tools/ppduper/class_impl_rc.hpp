#pragma once

#define __rc|it|(name, sub, first, ...) BOOST_PP_SEQ_FOR_EACH|it|(__sub_for_each|it|, name, sub) first BOOST_PP_SEQ_FOR_EACH(__impl_for_each, name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define __sub_for_each|it|(r, data, x) __rc|it + 1| BOOST_PP_TUPLE_PUSH_FRONT(BOOST_PP_TUPLE_POP_FRONT(x), data::BOOST_PP_TUPLE_ELEM(0, x))