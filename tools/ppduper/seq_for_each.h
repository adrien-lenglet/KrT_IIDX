#define SEQ_TUPLE_ENC|it|(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC|it - 1|

#define SEQ_FOR_EACH|it|(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH|it|_, end) (macro, data, SEQ_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH|it|_1(macro, data, el, ...) macro(data, el) SEQ_EXPAND|it|(SEQ_FOR_EACH|it + 1| SEQ_GEN_ARGS(macro, data, __VA_ARGS__))
#define SEQ_FOR_EACH|it|_0(...)
#define SEQ_EXPAND|it|(x) x