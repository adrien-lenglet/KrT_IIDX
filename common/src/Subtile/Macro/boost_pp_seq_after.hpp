#pragma once

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_PP_SEQ_AFTER(seq) BOOST_PP_CAT(BOOST_PP_SEQ_AFTER_END_, BOOST_PP_SEQ_SIZE_0 seq)

#include "boost_pp_seq_after_end.h_dupped.hpp"