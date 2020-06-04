#pragma once

#define SEQ_TUPLE_ENC1(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC0

#define SEQ_FOR_EACH1(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH1_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH1_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH2(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH1_0(...)

#define SEQ_TUPLE_ENC2(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC1

#define SEQ_FOR_EACH2(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH2_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH2_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH3(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH2_0(...)

#define SEQ_TUPLE_ENC3(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC2

#define SEQ_FOR_EACH3(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH3_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH3_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH4(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH3_0(...)

#define SEQ_TUPLE_ENC4(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC3

#define SEQ_FOR_EACH4(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH4_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH4_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH5(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH4_0(...)

#define SEQ_TUPLE_ENC5(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC4

#define SEQ_FOR_EACH5(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH5_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH5_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH6(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH5_0(...)

#define SEQ_TUPLE_ENC6(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC5

#define SEQ_FOR_EACH6(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH6_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH6_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH7(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH6_0(...)

#define SEQ_TUPLE_ENC7(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC6

#define SEQ_FOR_EACH7(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH7_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH7_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH8(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH7_0(...)

#define SEQ_TUPLE_ENC8(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC7

#define SEQ_FOR_EACH8(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH8_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH8_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH9(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH8_0(...)

#define SEQ_TUPLE_ENC9(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC8

#define SEQ_FOR_EACH9(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH9_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH9_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH10(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH9_0(...)

#define SEQ_TUPLE_ENC10(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC9

#define SEQ_FOR_EACH10(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH10_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH10_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH11(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH10_0(...)

#define SEQ_TUPLE_ENC11(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC10

#define SEQ_FOR_EACH11(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH11_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH11_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH12(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH11_0(...)

#define SEQ_TUPLE_ENC12(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC11

#define SEQ_FOR_EACH12(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH12_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH12_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH13(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH12_0(...)

#define SEQ_TUPLE_ENC13(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC12

#define SEQ_FOR_EACH13(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH13_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH13_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH14(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH13_0(...)

#define SEQ_TUPLE_ENC14(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC13

#define SEQ_FOR_EACH14(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH14_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH14_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH15(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH14_0(...)

#define SEQ_TUPLE_ENC15(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC14

#define SEQ_FOR_EACH15(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH15_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH15_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH16(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH15_0(...)

#define SEQ_TUPLE_ENC16(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC15

#define SEQ_FOR_EACH16(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH16_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH16_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH17(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH16_0(...)

#define SEQ_TUPLE_ENC17(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC16

#define SEQ_FOR_EACH17(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH17_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH17_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH18(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH17_0(...)

#define SEQ_TUPLE_ENC18(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC17

#define SEQ_FOR_EACH18(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH18_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH18_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH19(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH18_0(...)

#define SEQ_TUPLE_ENC19(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC18

#define SEQ_FOR_EACH19(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH19_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH19_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH20(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH19_0(...)

#define SEQ_TUPLE_ENC20(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC19

#define SEQ_FOR_EACH20(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH20_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH20_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH21(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH20_0(...)

#define SEQ_TUPLE_ENC21(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC20

#define SEQ_FOR_EACH21(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH21_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH21_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH22(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH21_0(...)

#define SEQ_TUPLE_ENC22(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC21

#define SEQ_FOR_EACH22(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH22_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH22_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH23(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH22_0(...)

#define SEQ_TUPLE_ENC23(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC22

#define SEQ_FOR_EACH23(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH23_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH23_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH24(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH23_0(...)

#define SEQ_TUPLE_ENC24(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC23

#define SEQ_FOR_EACH24(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH24_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH24_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH25(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH24_0(...)

#define SEQ_TUPLE_ENC25(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC24

#define SEQ_FOR_EACH25(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH25_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH25_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH26(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH25_0(...)

#define SEQ_TUPLE_ENC26(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC25

#define SEQ_FOR_EACH26(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH26_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH26_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH27(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH26_0(...)

#define SEQ_TUPLE_ENC27(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC26

#define SEQ_FOR_EACH27(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH27_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH27_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH28(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH27_0(...)

#define SEQ_TUPLE_ENC28(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC27

#define SEQ_FOR_EACH28(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH28_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH28_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH29(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH28_0(...)

#define SEQ_TUPLE_ENC29(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC28

#define SEQ_FOR_EACH29(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH29_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH29_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH30(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH29_0(...)

#define SEQ_TUPLE_ENC30(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC29

#define SEQ_FOR_EACH30(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH30_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH30_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH31(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH30_0(...)

#define SEQ_TUPLE_ENC31(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC30

#define SEQ_FOR_EACH31(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH31_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH31_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH32(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH31_0(...)

#define SEQ_TUPLE_ENC32(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC31

#define SEQ_FOR_EACH32(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH32_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH32_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH33(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH32_0(...)

#define SEQ_TUPLE_ENC33(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC32

#define SEQ_FOR_EACH33(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH33_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH33_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH34(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH33_0(...)

#define SEQ_TUPLE_ENC34(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC33

#define SEQ_FOR_EACH34(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH34_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH34_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH35(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH34_0(...)

#define SEQ_TUPLE_ENC35(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC34

#define SEQ_FOR_EACH35(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH35_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH35_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH36(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH35_0(...)

#define SEQ_TUPLE_ENC36(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC35

#define SEQ_FOR_EACH36(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH36_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH36_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH37(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH36_0(...)

#define SEQ_TUPLE_ENC37(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC36

#define SEQ_FOR_EACH37(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH37_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH37_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH38(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH37_0(...)

#define SEQ_TUPLE_ENC38(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC37

#define SEQ_FOR_EACH38(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH38_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH38_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH39(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH38_0(...)

#define SEQ_TUPLE_ENC39(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC38

#define SEQ_FOR_EACH39(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH39_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH39_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH40(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH39_0(...)

#define SEQ_TUPLE_ENC40(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC39

#define SEQ_FOR_EACH40(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH40_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH40_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH41(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH40_0(...)

#define SEQ_TUPLE_ENC41(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC40

#define SEQ_FOR_EACH41(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH41_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH41_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH42(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH41_0(...)

#define SEQ_TUPLE_ENC42(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC41

#define SEQ_FOR_EACH42(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH42_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH42_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH43(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH42_0(...)

#define SEQ_TUPLE_ENC43(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC42

#define SEQ_FOR_EACH43(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH43_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH43_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH44(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH43_0(...)

#define SEQ_TUPLE_ENC44(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC43

#define SEQ_FOR_EACH44(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH44_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH44_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH45(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH44_0(...)

#define SEQ_TUPLE_ENC45(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC44

#define SEQ_FOR_EACH45(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH45_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH45_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH46(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH45_0(...)

#define SEQ_TUPLE_ENC46(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC45

#define SEQ_FOR_EACH46(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH46_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH46_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH47(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH46_0(...)

#define SEQ_TUPLE_ENC47(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC46

#define SEQ_FOR_EACH47(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH47_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH47_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH48(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH47_0(...)

#define SEQ_TUPLE_ENC48(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC47

#define SEQ_FOR_EACH48(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH48_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH48_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH49(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH48_0(...)

#define SEQ_TUPLE_ENC49(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC48

#define SEQ_FOR_EACH49(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH49_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH49_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH50(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH49_0(...)

#define SEQ_TUPLE_ENC50(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC49

#define SEQ_FOR_EACH50(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH50_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH50_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH51(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH50_0(...)

#define SEQ_TUPLE_ENC51(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC50

#define SEQ_FOR_EACH51(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH51_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH51_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH52(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH51_0(...)

#define SEQ_TUPLE_ENC52(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC51

#define SEQ_FOR_EACH52(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH52_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH52_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH53(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH52_0(...)

#define SEQ_TUPLE_ENC53(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC52

#define SEQ_FOR_EACH53(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH53_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH53_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH54(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH53_0(...)

#define SEQ_TUPLE_ENC54(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC53

#define SEQ_FOR_EACH54(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH54_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH54_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH55(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH54_0(...)

#define SEQ_TUPLE_ENC55(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC54

#define SEQ_FOR_EACH55(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH55_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH55_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH56(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH55_0(...)

#define SEQ_TUPLE_ENC56(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC55

#define SEQ_FOR_EACH56(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH56_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH56_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH57(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH56_0(...)

#define SEQ_TUPLE_ENC57(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC56

#define SEQ_FOR_EACH57(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH57_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH57_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH58(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH57_0(...)

#define SEQ_TUPLE_ENC58(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC57

#define SEQ_FOR_EACH58(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH58_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH58_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH59(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH58_0(...)

#define SEQ_TUPLE_ENC59(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC58

#define SEQ_FOR_EACH59(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH59_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH59_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH60(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH59_0(...)

#define SEQ_TUPLE_ENC60(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC59

#define SEQ_FOR_EACH60(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH60_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH60_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH61(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH60_0(...)

#define SEQ_TUPLE_ENC61(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC60

#define SEQ_FOR_EACH61(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH61_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH61_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH62(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH61_0(...)

#define SEQ_TUPLE_ENC62(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC61

#define SEQ_FOR_EACH62(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH62_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH62_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH63(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH62_0(...)

#define SEQ_TUPLE_ENC63(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC62

#define SEQ_FOR_EACH63(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH63_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH63_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH64(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH63_0(...)

#define SEQ_TUPLE_ENC64(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC63

#define SEQ_FOR_EACH64(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH64_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH64_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH65(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH64_0(...)

#define SEQ_TUPLE_ENC65(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC64

#define SEQ_FOR_EACH65(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH65_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH65_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH66(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH65_0(...)

#define SEQ_TUPLE_ENC66(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC65

#define SEQ_FOR_EACH66(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH66_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH66_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH67(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH66_0(...)

#define SEQ_TUPLE_ENC67(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC66

#define SEQ_FOR_EACH67(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH67_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH67_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH68(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH67_0(...)

#define SEQ_TUPLE_ENC68(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC67

#define SEQ_FOR_EACH68(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH68_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH68_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH69(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH68_0(...)

#define SEQ_TUPLE_ENC69(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC68

#define SEQ_FOR_EACH69(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH69_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH69_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH70(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH69_0(...)

#define SEQ_TUPLE_ENC70(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC69

#define SEQ_FOR_EACH70(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH70_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH70_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH71(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH70_0(...)

#define SEQ_TUPLE_ENC71(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC70

#define SEQ_FOR_EACH71(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH71_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH71_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH72(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH71_0(...)

#define SEQ_TUPLE_ENC72(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC71

#define SEQ_FOR_EACH72(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH72_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH72_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH73(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH72_0(...)

#define SEQ_TUPLE_ENC73(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC72

#define SEQ_FOR_EACH73(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH73_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH73_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH74(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH73_0(...)

#define SEQ_TUPLE_ENC74(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC73

#define SEQ_FOR_EACH74(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH74_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH74_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH75(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH74_0(...)

#define SEQ_TUPLE_ENC75(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC74

#define SEQ_FOR_EACH75(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH75_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH75_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH76(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH75_0(...)

#define SEQ_TUPLE_ENC76(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC75

#define SEQ_FOR_EACH76(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH76_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH76_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH77(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH76_0(...)

#define SEQ_TUPLE_ENC77(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC76

#define SEQ_FOR_EACH77(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH77_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH77_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH78(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH77_0(...)

#define SEQ_TUPLE_ENC78(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC77

#define SEQ_FOR_EACH78(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH78_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH78_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH79(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH78_0(...)

#define SEQ_TUPLE_ENC79(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC78

#define SEQ_FOR_EACH79(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH79_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH79_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH80(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH79_0(...)

#define SEQ_TUPLE_ENC80(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC79

#define SEQ_FOR_EACH80(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH80_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH80_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH81(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH80_0(...)

#define SEQ_TUPLE_ENC81(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC80

#define SEQ_FOR_EACH81(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH81_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH81_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH82(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH81_0(...)

#define SEQ_TUPLE_ENC82(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC81

#define SEQ_FOR_EACH82(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH82_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH82_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH83(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH82_0(...)

#define SEQ_TUPLE_ENC83(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC82

#define SEQ_FOR_EACH83(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH83_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH83_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH84(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH83_0(...)

#define SEQ_TUPLE_ENC84(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC83

#define SEQ_FOR_EACH84(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH84_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH84_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH85(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH84_0(...)

#define SEQ_TUPLE_ENC85(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC84

#define SEQ_FOR_EACH85(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH85_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH85_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH86(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH85_0(...)

#define SEQ_TUPLE_ENC86(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC85

#define SEQ_FOR_EACH86(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH86_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH86_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH87(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH86_0(...)

#define SEQ_TUPLE_ENC87(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC86

#define SEQ_FOR_EACH87(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH87_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH87_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH88(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH87_0(...)

#define SEQ_TUPLE_ENC88(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC87

#define SEQ_FOR_EACH88(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH88_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH88_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH89(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH88_0(...)

#define SEQ_TUPLE_ENC89(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC88

#define SEQ_FOR_EACH89(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH89_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH89_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH90(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH89_0(...)

#define SEQ_TUPLE_ENC90(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC89

#define SEQ_FOR_EACH90(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH90_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH90_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH91(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH90_0(...)

#define SEQ_TUPLE_ENC91(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC90

#define SEQ_FOR_EACH91(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH91_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH91_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH92(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH91_0(...)

#define SEQ_TUPLE_ENC92(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC91

#define SEQ_FOR_EACH92(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH92_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH92_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH93(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH92_0(...)

#define SEQ_TUPLE_ENC93(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC92

#define SEQ_FOR_EACH93(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH93_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH93_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH94(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH93_0(...)

#define SEQ_TUPLE_ENC94(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC93

#define SEQ_FOR_EACH94(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH94_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH94_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH95(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH94_0(...)

#define SEQ_TUPLE_ENC95(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC94

#define SEQ_FOR_EACH95(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH95_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH95_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH96(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH95_0(...)

#define SEQ_TUPLE_ENC96(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC95

#define SEQ_FOR_EACH96(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH96_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH96_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH97(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH96_0(...)

#define SEQ_TUPLE_ENC97(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC96

#define SEQ_FOR_EACH97(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH97_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH97_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH98(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH97_0(...)

#define SEQ_TUPLE_ENC98(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC97

#define SEQ_FOR_EACH98(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH98_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH98_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH99(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH98_0(...)

#define SEQ_TUPLE_ENC99(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC98

#define SEQ_FOR_EACH99(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH99_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH99_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH100(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH99_0(...)

#define SEQ_TUPLE_ENC100(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC99

#define SEQ_FOR_EACH100(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH100_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH100_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH101(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH100_0(...)

#define SEQ_TUPLE_ENC101(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC100

#define SEQ_FOR_EACH101(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH101_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH101_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH102(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH101_0(...)

#define SEQ_TUPLE_ENC102(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC101

#define SEQ_FOR_EACH102(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH102_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH102_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH103(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH102_0(...)

#define SEQ_TUPLE_ENC103(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC102

#define SEQ_FOR_EACH103(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH103_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH103_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH104(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH103_0(...)

#define SEQ_TUPLE_ENC104(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC103

#define SEQ_FOR_EACH104(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH104_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH104_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH105(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH104_0(...)

#define SEQ_TUPLE_ENC105(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC104

#define SEQ_FOR_EACH105(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH105_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH105_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH106(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH105_0(...)

#define SEQ_TUPLE_ENC106(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC105

#define SEQ_FOR_EACH106(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH106_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH106_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH107(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH106_0(...)

#define SEQ_TUPLE_ENC107(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC106

#define SEQ_FOR_EACH107(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH107_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH107_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH108(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH107_0(...)

#define SEQ_TUPLE_ENC108(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC107

#define SEQ_FOR_EACH108(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH108_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH108_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH109(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH108_0(...)

#define SEQ_TUPLE_ENC109(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC108

#define SEQ_FOR_EACH109(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH109_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH109_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH110(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH109_0(...)

#define SEQ_TUPLE_ENC110(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC109

#define SEQ_FOR_EACH110(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH110_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH110_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH111(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH110_0(...)

#define SEQ_TUPLE_ENC111(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC110

#define SEQ_FOR_EACH111(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH111_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH111_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH112(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH111_0(...)

#define SEQ_TUPLE_ENC112(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC111

#define SEQ_FOR_EACH112(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH112_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH112_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH113(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH112_0(...)

#define SEQ_TUPLE_ENC113(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC112

#define SEQ_FOR_EACH113(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH113_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH113_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH114(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH113_0(...)

#define SEQ_TUPLE_ENC114(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC113

#define SEQ_FOR_EACH114(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH114_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH114_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH115(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH114_0(...)

#define SEQ_TUPLE_ENC115(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC114

#define SEQ_FOR_EACH115(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH115_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH115_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH116(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH115_0(...)

#define SEQ_TUPLE_ENC116(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC115

#define SEQ_FOR_EACH116(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH116_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH116_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH117(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH116_0(...)

#define SEQ_TUPLE_ENC117(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC116

#define SEQ_FOR_EACH117(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH117_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH117_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH118(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH117_0(...)

#define SEQ_TUPLE_ENC118(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC117

#define SEQ_FOR_EACH118(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH118_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH118_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH119(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH118_0(...)

#define SEQ_TUPLE_ENC119(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC118

#define SEQ_FOR_EACH119(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH119_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH119_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH120(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH119_0(...)

#define SEQ_TUPLE_ENC120(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC119

#define SEQ_FOR_EACH120(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH120_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH120_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH121(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH120_0(...)

#define SEQ_TUPLE_ENC121(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC120

#define SEQ_FOR_EACH121(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH121_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH121_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH122(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH121_0(...)

#define SEQ_TUPLE_ENC122(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC121

#define SEQ_FOR_EACH122(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH122_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH122_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH123(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH122_0(...)

#define SEQ_TUPLE_ENC123(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC122

#define SEQ_FOR_EACH123(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH123_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH123_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH124(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH123_0(...)

#define SEQ_TUPLE_ENC124(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC123

#define SEQ_FOR_EACH124(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH124_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH124_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH125(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH124_0(...)

#define SEQ_TUPLE_ENC125(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC124

#define SEQ_FOR_EACH125(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH125_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH125_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH126(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH125_0(...)

#define SEQ_TUPLE_ENC126(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC125

#define SEQ_FOR_EACH126(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH126_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH126_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH127(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH126_0(...)

#define SEQ_TUPLE_ENC127(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC126

#define SEQ_FOR_EACH127(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH127_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH127_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH128(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH127_0(...)

#define SEQ_TUPLE_ENC128(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC127

#define SEQ_FOR_EACH128(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH128_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH128_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH129(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH128_0(...)

#define SEQ_TUPLE_ENC129(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC128

#define SEQ_FOR_EACH129(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH129_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH129_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH130(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH129_0(...)

#define SEQ_TUPLE_ENC130(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC129

#define SEQ_FOR_EACH130(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH130_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH130_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH131(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH130_0(...)

#define SEQ_TUPLE_ENC131(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC130

#define SEQ_FOR_EACH131(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH131_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH131_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH132(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH131_0(...)

#define SEQ_TUPLE_ENC132(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC131

#define SEQ_FOR_EACH132(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH132_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH132_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH133(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH132_0(...)

#define SEQ_TUPLE_ENC133(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC132

#define SEQ_FOR_EACH133(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH133_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH133_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH134(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH133_0(...)

#define SEQ_TUPLE_ENC134(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC133

#define SEQ_FOR_EACH134(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH134_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH134_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH135(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH134_0(...)

#define SEQ_TUPLE_ENC135(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC134

#define SEQ_FOR_EACH135(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH135_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH135_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH136(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH135_0(...)

#define SEQ_TUPLE_ENC136(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC135

#define SEQ_FOR_EACH136(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH136_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH136_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH137(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH136_0(...)

#define SEQ_TUPLE_ENC137(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC136

#define SEQ_FOR_EACH137(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH137_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH137_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH138(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH137_0(...)

#define SEQ_TUPLE_ENC138(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC137

#define SEQ_FOR_EACH138(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH138_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH138_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH139(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH138_0(...)

#define SEQ_TUPLE_ENC139(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC138

#define SEQ_FOR_EACH139(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH139_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH139_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH140(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH139_0(...)

#define SEQ_TUPLE_ENC140(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC139

#define SEQ_FOR_EACH140(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH140_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH140_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH141(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH140_0(...)

#define SEQ_TUPLE_ENC141(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC140

#define SEQ_FOR_EACH141(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH141_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH141_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH142(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH141_0(...)

#define SEQ_TUPLE_ENC142(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC141

#define SEQ_FOR_EACH142(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH142_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH142_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH143(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH142_0(...)

#define SEQ_TUPLE_ENC143(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC142

#define SEQ_FOR_EACH143(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH143_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH143_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH144(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH143_0(...)

#define SEQ_TUPLE_ENC144(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC143

#define SEQ_FOR_EACH144(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH144_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH144_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH145(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH144_0(...)

#define SEQ_TUPLE_ENC145(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC144

#define SEQ_FOR_EACH145(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH145_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH145_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH146(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH145_0(...)

#define SEQ_TUPLE_ENC146(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC145

#define SEQ_FOR_EACH146(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH146_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH146_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH147(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH146_0(...)

#define SEQ_TUPLE_ENC147(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC146

#define SEQ_FOR_EACH147(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH147_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH147_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH148(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH147_0(...)

#define SEQ_TUPLE_ENC148(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC147

#define SEQ_FOR_EACH148(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH148_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH148_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH149(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH148_0(...)

#define SEQ_TUPLE_ENC149(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC148

#define SEQ_FOR_EACH149(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH149_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH149_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH150(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH149_0(...)

#define SEQ_TUPLE_ENC150(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC149

#define SEQ_FOR_EACH150(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH150_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH150_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH151(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH150_0(...)

#define SEQ_TUPLE_ENC151(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC150

#define SEQ_FOR_EACH151(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH151_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH151_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH152(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH151_0(...)

#define SEQ_TUPLE_ENC152(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC151

#define SEQ_FOR_EACH152(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH152_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH152_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH153(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH152_0(...)

#define SEQ_TUPLE_ENC153(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC152

#define SEQ_FOR_EACH153(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH153_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH153_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH154(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH153_0(...)

#define SEQ_TUPLE_ENC154(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC153

#define SEQ_FOR_EACH154(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH154_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH154_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH155(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH154_0(...)

#define SEQ_TUPLE_ENC155(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC154

#define SEQ_FOR_EACH155(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH155_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH155_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH156(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH155_0(...)

#define SEQ_TUPLE_ENC156(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC155

#define SEQ_FOR_EACH156(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH156_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH156_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH157(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH156_0(...)

#define SEQ_TUPLE_ENC157(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC156

#define SEQ_FOR_EACH157(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH157_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH157_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH158(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH157_0(...)

#define SEQ_TUPLE_ENC158(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC157

#define SEQ_FOR_EACH158(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH158_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH158_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH159(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH158_0(...)

#define SEQ_TUPLE_ENC159(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC158

#define SEQ_FOR_EACH159(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH159_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH159_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH160(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH159_0(...)

#define SEQ_TUPLE_ENC160(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC159

#define SEQ_FOR_EACH160(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH160_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH160_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH161(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH160_0(...)

#define SEQ_TUPLE_ENC161(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC160

#define SEQ_FOR_EACH161(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH161_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH161_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH162(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH161_0(...)

#define SEQ_TUPLE_ENC162(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC161

#define SEQ_FOR_EACH162(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH162_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH162_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH163(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH162_0(...)

#define SEQ_TUPLE_ENC163(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC162

#define SEQ_FOR_EACH163(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH163_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH163_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH164(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH163_0(...)

#define SEQ_TUPLE_ENC164(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC163

#define SEQ_FOR_EACH164(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH164_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH164_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH165(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH164_0(...)

#define SEQ_TUPLE_ENC165(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC164

#define SEQ_FOR_EACH165(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH165_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH165_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH166(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH165_0(...)

#define SEQ_TUPLE_ENC166(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC165

#define SEQ_FOR_EACH166(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH166_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH166_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH167(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH166_0(...)

#define SEQ_TUPLE_ENC167(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC166

#define SEQ_FOR_EACH167(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH167_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH167_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH168(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH167_0(...)

#define SEQ_TUPLE_ENC168(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC167

#define SEQ_FOR_EACH168(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH168_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH168_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH169(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH168_0(...)

#define SEQ_TUPLE_ENC169(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC168

#define SEQ_FOR_EACH169(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH169_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH169_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH170(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH169_0(...)

#define SEQ_TUPLE_ENC170(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC169

#define SEQ_FOR_EACH170(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH170_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH170_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH171(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH170_0(...)

#define SEQ_TUPLE_ENC171(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC170

#define SEQ_FOR_EACH171(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH171_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH171_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH172(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH171_0(...)

#define SEQ_TUPLE_ENC172(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC171

#define SEQ_FOR_EACH172(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH172_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH172_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH173(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH172_0(...)

#define SEQ_TUPLE_ENC173(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC172

#define SEQ_FOR_EACH173(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH173_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH173_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH174(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH173_0(...)

#define SEQ_TUPLE_ENC174(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC173

#define SEQ_FOR_EACH174(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH174_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH174_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH175(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH174_0(...)

#define SEQ_TUPLE_ENC175(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC174

#define SEQ_FOR_EACH175(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH175_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH175_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH176(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH175_0(...)

#define SEQ_TUPLE_ENC176(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC175

#define SEQ_FOR_EACH176(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH176_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH176_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH177(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH176_0(...)

#define SEQ_TUPLE_ENC177(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC176

#define SEQ_FOR_EACH177(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH177_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH177_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH178(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH177_0(...)

#define SEQ_TUPLE_ENC178(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC177

#define SEQ_FOR_EACH178(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH178_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH178_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH179(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH178_0(...)

#define SEQ_TUPLE_ENC179(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC178

#define SEQ_FOR_EACH179(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH179_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH179_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH180(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH179_0(...)

#define SEQ_TUPLE_ENC180(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC179

#define SEQ_FOR_EACH180(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH180_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH180_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH181(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH180_0(...)

#define SEQ_TUPLE_ENC181(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC180

#define SEQ_FOR_EACH181(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH181_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH181_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH182(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH181_0(...)

#define SEQ_TUPLE_ENC182(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC181

#define SEQ_FOR_EACH182(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH182_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH182_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH183(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH182_0(...)

#define SEQ_TUPLE_ENC183(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC182

#define SEQ_FOR_EACH183(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH183_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH183_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH184(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH183_0(...)

#define SEQ_TUPLE_ENC184(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC183

#define SEQ_FOR_EACH184(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH184_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH184_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH185(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH184_0(...)

#define SEQ_TUPLE_ENC185(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC184

#define SEQ_FOR_EACH185(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH185_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH185_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH186(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH185_0(...)

#define SEQ_TUPLE_ENC186(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC185

#define SEQ_FOR_EACH186(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH186_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH186_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH187(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH186_0(...)

#define SEQ_TUPLE_ENC187(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC186

#define SEQ_FOR_EACH187(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH187_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH187_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH188(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH187_0(...)

#define SEQ_TUPLE_ENC188(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC187

#define SEQ_FOR_EACH188(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH188_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH188_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH189(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH188_0(...)

#define SEQ_TUPLE_ENC189(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC188

#define SEQ_FOR_EACH189(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH189_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH189_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH190(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH189_0(...)

#define SEQ_TUPLE_ENC190(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC189

#define SEQ_FOR_EACH190(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH190_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH190_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH191(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH190_0(...)

#define SEQ_TUPLE_ENC191(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC190

#define SEQ_FOR_EACH191(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH191_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH191_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH192(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH191_0(...)

#define SEQ_TUPLE_ENC192(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC191

#define SEQ_FOR_EACH192(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH192_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH192_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH193(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH192_0(...)

#define SEQ_TUPLE_ENC193(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC192

#define SEQ_FOR_EACH193(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH193_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH193_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH194(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH193_0(...)

#define SEQ_TUPLE_ENC194(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC193

#define SEQ_FOR_EACH194(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH194_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH194_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH195(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH194_0(...)

#define SEQ_TUPLE_ENC195(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC194

#define SEQ_FOR_EACH195(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH195_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH195_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH196(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH195_0(...)

#define SEQ_TUPLE_ENC196(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC195

#define SEQ_FOR_EACH196(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH196_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH196_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH197(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH196_0(...)

#define SEQ_TUPLE_ENC197(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC196

#define SEQ_FOR_EACH197(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH197_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH197_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH198(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH197_0(...)

#define SEQ_TUPLE_ENC198(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC197

#define SEQ_FOR_EACH198(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH198_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH198_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH199(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH198_0(...)

#define SEQ_TUPLE_ENC199(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC198

#define SEQ_FOR_EACH199(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH199_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH199_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH200(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH199_0(...)

#define SEQ_TUPLE_ENC200(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC199

#define SEQ_FOR_EACH200(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH200_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH200_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH201(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH200_0(...)

#define SEQ_TUPLE_ENC201(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC200

#define SEQ_FOR_EACH201(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH201_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH201_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH202(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH201_0(...)

#define SEQ_TUPLE_ENC202(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC201

#define SEQ_FOR_EACH202(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH202_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH202_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH203(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH202_0(...)

#define SEQ_TUPLE_ENC203(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC202

#define SEQ_FOR_EACH203(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH203_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH203_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH204(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH203_0(...)

#define SEQ_TUPLE_ENC204(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC203

#define SEQ_FOR_EACH204(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH204_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH204_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH205(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH204_0(...)

#define SEQ_TUPLE_ENC205(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC204

#define SEQ_FOR_EACH205(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH205_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH205_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH206(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH205_0(...)

#define SEQ_TUPLE_ENC206(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC205

#define SEQ_FOR_EACH206(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH206_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH206_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH207(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH206_0(...)

#define SEQ_TUPLE_ENC207(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC206

#define SEQ_FOR_EACH207(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH207_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH207_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH208(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH207_0(...)

#define SEQ_TUPLE_ENC208(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC207

#define SEQ_FOR_EACH208(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH208_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH208_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH209(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH208_0(...)

#define SEQ_TUPLE_ENC209(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC208

#define SEQ_FOR_EACH209(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH209_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH209_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH210(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH209_0(...)

#define SEQ_TUPLE_ENC210(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC209

#define SEQ_FOR_EACH210(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH210_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH210_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH211(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH210_0(...)

#define SEQ_TUPLE_ENC211(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC210

#define SEQ_FOR_EACH211(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH211_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH211_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH212(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH211_0(...)

#define SEQ_TUPLE_ENC212(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC211

#define SEQ_FOR_EACH212(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH212_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH212_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH213(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH212_0(...)

#define SEQ_TUPLE_ENC213(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC212

#define SEQ_FOR_EACH213(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH213_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH213_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH214(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH213_0(...)

#define SEQ_TUPLE_ENC214(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC213

#define SEQ_FOR_EACH214(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH214_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH214_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH215(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH214_0(...)

#define SEQ_TUPLE_ENC215(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC214

#define SEQ_FOR_EACH215(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH215_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH215_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH216(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH215_0(...)

#define SEQ_TUPLE_ENC216(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC215

#define SEQ_FOR_EACH216(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH216_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH216_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH217(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH216_0(...)

#define SEQ_TUPLE_ENC217(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC216

#define SEQ_FOR_EACH217(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH217_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH217_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH218(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH217_0(...)

#define SEQ_TUPLE_ENC218(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC217

#define SEQ_FOR_EACH218(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH218_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH218_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH219(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH218_0(...)

#define SEQ_TUPLE_ENC219(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC218

#define SEQ_FOR_EACH219(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH219_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH219_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH220(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH219_0(...)

#define SEQ_TUPLE_ENC220(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC219

#define SEQ_FOR_EACH220(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH220_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH220_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH221(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH220_0(...)

#define SEQ_TUPLE_ENC221(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC220

#define SEQ_FOR_EACH221(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH221_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH221_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH222(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH221_0(...)

#define SEQ_TUPLE_ENC222(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC221

#define SEQ_FOR_EACH222(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH222_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH222_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH223(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH222_0(...)

#define SEQ_TUPLE_ENC223(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC222

#define SEQ_FOR_EACH223(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH223_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH223_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH224(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH223_0(...)

#define SEQ_TUPLE_ENC224(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC223

#define SEQ_FOR_EACH224(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH224_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH224_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH225(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH224_0(...)

#define SEQ_TUPLE_ENC225(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC224

#define SEQ_FOR_EACH225(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH225_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH225_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH226(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH225_0(...)

#define SEQ_TUPLE_ENC226(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC225

#define SEQ_FOR_EACH226(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH226_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH226_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH227(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH226_0(...)

#define SEQ_TUPLE_ENC227(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC226

#define SEQ_FOR_EACH227(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH227_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH227_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH228(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH227_0(...)

#define SEQ_TUPLE_ENC228(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC227

#define SEQ_FOR_EACH228(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH228_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH228_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH229(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH228_0(...)

#define SEQ_TUPLE_ENC229(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC228

#define SEQ_FOR_EACH229(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH229_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH229_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH230(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH229_0(...)

#define SEQ_TUPLE_ENC230(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC229

#define SEQ_FOR_EACH230(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH230_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH230_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH231(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH230_0(...)

#define SEQ_TUPLE_ENC231(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC230

#define SEQ_FOR_EACH231(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH231_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH231_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH232(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH231_0(...)

#define SEQ_TUPLE_ENC232(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC231

#define SEQ_FOR_EACH232(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH232_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH232_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH233(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH232_0(...)

#define SEQ_TUPLE_ENC233(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC232

#define SEQ_FOR_EACH233(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH233_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH233_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH234(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH233_0(...)

#define SEQ_TUPLE_ENC234(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC233

#define SEQ_FOR_EACH234(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH234_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH234_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH235(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH234_0(...)

#define SEQ_TUPLE_ENC235(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC234

#define SEQ_FOR_EACH235(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH235_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH235_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH236(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH235_0(...)

#define SEQ_TUPLE_ENC236(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC235

#define SEQ_FOR_EACH236(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH236_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH236_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH237(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH236_0(...)

#define SEQ_TUPLE_ENC237(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC236

#define SEQ_FOR_EACH237(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH237_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH237_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH238(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH237_0(...)

#define SEQ_TUPLE_ENC238(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC237

#define SEQ_FOR_EACH238(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH238_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH238_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH239(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH238_0(...)

#define SEQ_TUPLE_ENC239(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC238

#define SEQ_FOR_EACH239(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH239_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH239_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH240(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH239_0(...)

#define SEQ_TUPLE_ENC240(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC239

#define SEQ_FOR_EACH240(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH240_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH240_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH241(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH240_0(...)

#define SEQ_TUPLE_ENC241(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC240

#define SEQ_FOR_EACH241(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH241_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH241_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH242(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH241_0(...)

#define SEQ_TUPLE_ENC242(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC241

#define SEQ_FOR_EACH242(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH242_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH242_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH243(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH242_0(...)

#define SEQ_TUPLE_ENC243(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC242

#define SEQ_FOR_EACH243(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH243_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH243_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH244(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH243_0(...)

#define SEQ_TUPLE_ENC244(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC243

#define SEQ_FOR_EACH244(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH244_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH244_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH245(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH244_0(...)

#define SEQ_TUPLE_ENC245(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC244

#define SEQ_FOR_EACH245(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH245_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH245_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH246(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH245_0(...)

#define SEQ_TUPLE_ENC246(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC245

#define SEQ_FOR_EACH246(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH246_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH246_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH247(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH246_0(...)

#define SEQ_TUPLE_ENC247(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC246

#define SEQ_FOR_EACH247(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH247_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH247_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH248(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH247_0(...)

#define SEQ_TUPLE_ENC248(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC247

#define SEQ_FOR_EACH248(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH248_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH248_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH249(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH248_0(...)

#define SEQ_TUPLE_ENC249(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC248

#define SEQ_FOR_EACH249(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH249_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH249_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH250(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH249_0(...)

#define SEQ_TUPLE_ENC250(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC249

#define SEQ_FOR_EACH250(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH250_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH250_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH251(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH250_0(...)

#define SEQ_TUPLE_ENC251(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC250

#define SEQ_FOR_EACH251(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH251_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH251_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH252(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH251_0(...)

#define SEQ_TUPLE_ENC252(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC251

#define SEQ_FOR_EACH252(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH252_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH252_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH253(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH252_0(...)

#define SEQ_TUPLE_ENC253(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC252

#define SEQ_FOR_EACH253(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH253_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH253_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH254(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH253_0(...)

#define SEQ_TUPLE_ENC254(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC253

#define SEQ_FOR_EACH254(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH254_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH254_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH255(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH254_0(...)

#define SEQ_TUPLE_ENC255(el) SEQ_MARK_ELEM_CONT(el), SEQ_TUPLE_ENC254

#define SEQ_FOR_EACH255(macro, data, end, el, ...) BOOST_PP_CAT(SEQ_FOR_EACH255_, end) (macro, data, BOOST_PP_REM el, __VA_ARGS__)
#define SEQ_FOR_EACH255_1(macro, data, el, ...) macro(data, el) SEQ_FOR_EACH256(macro, data, __VA_ARGS__)
#define SEQ_FOR_EACH255_0(...)

