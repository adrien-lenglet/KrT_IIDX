#pragma once

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/expand.hpp>

#include "Macro/seq_for_each.hpp"

#define rt_scc(name, ...) __scc_unwrap(__scc_impl(name, ((1, (__VA_ARGS__)))))

#define scc(name, ...) ))) __scc_impl(name, ((1, (__VA_ARGS__)))) ((1, (
#define scp )))((3, (

#define scc_tup_num_impl(num, payload) num
#define scc_tup_payload_impl(num, payload) payload
#define scc_tup_num(tup) scc_tup_num_impl tup
#define scc_tup_payload(tup) scc_tup_payload_impl tup

#define __scc_impl(name, seq) SEQ_FOR_EACH(__scc_for_each, name, seq)
#define __scc_seq_payload(seq) BOOST_PP_EXPAND(SEQ_REM scc_tup_payload(seq))

#define __scc_for_each_1(_, payload) ((1, (payload)))
#define __scc_for_each_2(name, payload) ((2, (name::payload)))
#define __scc_for_each_3(name, payload) ((2, (name payload)))
#define __scc_for_each(name, seq) BOOST_PP_CAT(__scc_for_each_, scc_tup_num(seq)) (name, __scc_seq_payload(seq))

#define __scc_unwrap(seq) SEQ_FOR_EACH(__scc_unwrap_for_each,, seq)
#define __scc_unwrap_for_each(_, seq) __scc_seq_payload(seq)