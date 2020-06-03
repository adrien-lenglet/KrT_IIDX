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

#define rt_scc(name, ...) __scc_unwrap(__scc_impl(name, (((__VA_ARGS__)))))

#define scc(name, ...) ))) __scc_impl(name, (((__VA_ARGS__)))) (((
#define scp )))(()()((

#define __scc_impl(name, seq) BOOST_PP_SEQ_FOR_EACH(__scc_for_each, name, seq)
#define __scc_seq_payload(seq) BOOST_PP_EXPAND(BOOST_PP_REM BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq))

#define __scc_for_each_0(_, payload) ((payload))
#define __scc_for_each_1(name, payload) ()((name::payload))
#define __scc_for_each_2(name, payload) ()((name payload))
#define __scc_for_each(r, name, seq) (BOOST_PP_CAT(__scc_for_each_, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq))) (name, __scc_seq_payload(seq)))

#define __scc_unwrap(seq) BOOST_PP_SEQ_FOR_EACH(__scc_unwrap_for_each,, seq)
#define __scc_unwrap_for_each(r, _, seq) __scc_seq_payload(seq)