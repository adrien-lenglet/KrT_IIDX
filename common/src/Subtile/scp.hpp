#pragma once

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>

#include "Macro/boost_pp_defer.hpp"
#include "Macro/boost_pp_eval.hpp"

#define SEQ_MARK_ELEM(m, el) (m, (el))
#define SEQ_MARK_ELEM_CONT(el) SEQ_MARK_ELEM(1, el)
#define SEQ_MARK_ELEM_END(el) SEQ_MARK_ELEM(0, el)

#define SEQ_MARK_END(seq) BOOST_PP_CAT(SEQ_MARK_END_II(seq), _END) SEQ_MARK_ELEM_END(end)
#define SEQ_MARK_END_II(seq) BOOST_PP_EVAL2p8(SEQ_MARK_END_I seq)
#define SEQ_MARK_END_I(el) SEQ_MARK_ELEM_CONT(el) BOOST_PP_DEFER(_SEQ_MARK_END_I)()
#define _SEQ_MARK_END_I() SEQ_MARK_END_I
#define SEQ_MARK_END_I_END


#define SEQ_FOR_EACH_DEGEN(...) __VA_ARGS__)

#define SEQ_FOR_EACH(macro, data, seq) BOOST_PP_EVAL2p8(SEQ_FOR_EACH_I(macro, data, SEQ_MARK_END(seq)))
#define SEQ_FOR_EACH_I(macro, data, seq) SEQ_FOR_EACH_GRAB BOOST_PP_LPAREN() macro, data, SEQ_FOR_EACH_DEGEN seq

#define SEQ_FOR_EACH_GRAB(macro, data, end, el) BOOST_PP_CAT(SEQ_FOR_EACH_GRAB_, end)(macro, data, el)
#define SEQ_FOR_EACH_GRAB_1(macro, data, el) macro(data, BOOST_PP_REM el) BOOST_PP_DEFER(_SEQ_FOR_EACH_GRAB)() BOOST_PP_LPAREN() macro, data, SEQ_FOR_EACH_DEGEN
#define SEQ_FOR_EACH_GRAB_0(...)
#define _SEQ_FOR_EACH_GRAB() SEQ_FOR_EACH_GRAB


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