#define SEQ_MARK_END_I|it|(el) SEQ_MARK_ELEM_CONT(el) SEQ_MARK_END_I|it + 1|
#define SEQ_MARK_END_I|it|_END

#define SEQ_FOR_EACH_GRAB|it|(macro, data, end, el) BOOST_PP_CAT(SEQ_FOR_EACH_GRAB|it|_, end)(macro, data, el)
#define SEQ_FOR_EACH_GRAB|it|_1(macro, data, el) macro(data, BOOST_PP_REM el) SEQ_FOR_EACH_GRAB|it + 1| BOOST_PP_LPAREN() macro, data, SEQ_FOR_EACH_DEGEN
#define SEQ_FOR_EACH_GRAB|it|_0(...)