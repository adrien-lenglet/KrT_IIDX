#pragma once

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>

#include "Macro/seq_for_each.h_dupped.hpp"

#define SEQ_MARK_ELEM(m, el) m, (el)
#define SEQ_MARK_ELEM_CONT(el) SEQ_MARK_ELEM(1, el)
#define SEQ_MARK_ELEM_END(el) SEQ_MARK_ELEM(0, el)

#define SEQ_TUPLE_ENC(seq) BOOST_PP_CAT(SEQ_TUPLE_ENC, BOOST_PP_SEQ_SIZE(seq)) seq SEQ_MARK_ELEM_END(end)
#define SEQ_TUPLE_ENC0

#define SEQ_EXPAND(x) SEQ_EXPAND_I(x)
#define SEQ_EXPAND_I(x) x

#define SEQ_FOR_EACH(macro, data, seq) SEQ_EXPAND(SEQ_FOR_EACH_I(macro, data, seq))
#define SEQ_FOR_EACH_I(macro, data, seq) SEQ_FOR_EACH1 BOOST_PP_LPAREN() macro, data, SEQ_TUPLE_ENC(seq) BOOST_PP_RPAREN()

#define rt_scc(name, ...) __scc_unwrap(__scc_impl(name, ((1)((__VA_ARGS__)))))

#define scc(name, ...) ))) __scc_impl(name, ((1)((__VA_ARGS__)))) ((1)((
#define scp )))((3)((

#define __scc_impl(name, seq) SEQ_FOR_EACH(__scc_for_each, name, seq)
#define __scc_seq_payload(seq) BOOST_PP_EXPAND(BOOST_PP_REM BOOST_PP_SEQ_ELEM(1, seq))

#define __scc_for_each_1(_, payload) (1)((payload))
#define __scc_for_each_2(name, payload) (2)((name::payload))
#define __scc_for_each_3(name, payload) (2)((name payload))
#define __scc_for_each(name, seq) (BOOST_PP_CAT(__scc_for_each_, BOOST_PP_SEQ_ELEM(0, seq)) (name, __scc_seq_payload(seq)))

#define __scc_unwrap(seq) SEQ_FOR_EACH(__scc_unwrap_for_each,, seq)
#define __scc_unwrap_for_each(_, seq) __scc_seq_payload(seq)