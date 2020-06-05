#pragma once

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>

#ifndef SEQ_TUPLE_ENC1
#include "seq_for_each/it_1024.hduped"
#endif

#define SEQ_SEQ_SIZE(seq) BOOST_PP_CAT(SEQ_SEQ_SIZE_I(seq), _END)
#define SEQ_SEQ_SIZE_I(seq) SEQ_SEQ_SIZE0 seq

#define SEQ_REM(...) __VA_ARGS__
#define SEQ_EXPAND(x) SEQ_EXPAND_I(x)
#define SEQ_EXPAND_I(x) x

#define SEQ_MARK_ELEM(m, el) m, (el)
#define SEQ_MARK_ELEM_CONT(el) SEQ_MARK_ELEM(1, el)
#define SEQ_MARK_ELEM_END(el) SEQ_MARK_ELEM(0, el)

#define SEQ_TUPLE_ENC(seq) BOOST_PP_CAT(SEQ_TUPLE_ENC, SEQ_SEQ_SIZE(seq)) seq SEQ_MARK_ELEM_END(end)
#define SEQ_TUPLE_ENC0

#define SEQ_FOR_EACH(macro, data, seq) SEQ_EXPAND(SEQ_FOR_EACH_I(macro, data, seq))
#define SEQ_FOR_EACH_I(macro, data, seq) SEQ_FOR_EACH1 SEQ_FOR_EACH_II(macro, data, seq)
#define SEQ_FOR_EACH_II(macro, data, seq) (macro, data, SEQ_TUPLE_ENC(seq))
#define SEQ_GEN_ARGS(macro, data, ...) (macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH_EXPAND(x) SEQ_FOR_EACH_EXPAND_I(x)
#define SEQ_FOR_EACH_EXPAND_I(x) x