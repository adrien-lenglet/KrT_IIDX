# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
#pragma once
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BOOL26 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL26(x) BOOST_PP_BOOL26_I(x)
# else
#    define BOOST_PP_BOOL26(x) BOOST_PP_BOOL26_OO((x))
#    define BOOST_PP_BOOL26_OO(par) BOOST_PP_BOOL26_I ## par
# endif
#
# define BOOST_PP_BOOL26_I(x) BOOST_PP_BOOL26_ ## x
#
# define BOOST_PP_BOOL26_0 0
# define BOOST_PP_BOOL26_1 1
# define BOOST_PP_BOOL26_2 1
# define BOOST_PP_BOOL26_3 1
# define BOOST_PP_BOOL26_4 1
# define BOOST_PP_BOOL26_5 1
# define BOOST_PP_BOOL26_6 1
# define BOOST_PP_BOOL26_7 1
# define BOOST_PP_BOOL26_8 1
# define BOOST_PP_BOOL26_9 1
# define BOOST_PP_BOOL26_10 1
# define BOOST_PP_BOOL26_11 1
# define BOOST_PP_BOOL26_12 1
# define BOOST_PP_BOOL26_13 1
# define BOOST_PP_BOOL26_14 1
# define BOOST_PP_BOOL26_15 1
# define BOOST_PP_BOOL26_16 1
# define BOOST_PP_BOOL26_17 1
# define BOOST_PP_BOOL26_18 1
# define BOOST_PP_BOOL26_19 1
# define BOOST_PP_BOOL26_20 1
# define BOOST_PP_BOOL26_21 1
# define BOOST_PP_BOOL26_22 1
# define BOOST_PP_BOOL26_23 1
# define BOOST_PP_BOOL26_24 1
# define BOOST_PP_BOOL26_25 1
# define BOOST_PP_BOOL26_26 1
# define BOOST_PP_BOOL26_27 1
# define BOOST_PP_BOOL26_28 1
# define BOOST_PP_BOOL26_29 1
# define BOOST_PP_BOOL26_30 1
# define BOOST_PP_BOOL26_31 1
# define BOOST_PP_BOOL26_32 1
# define BOOST_PP_BOOL26_33 1
# define BOOST_PP_BOOL26_34 1
# define BOOST_PP_BOOL26_35 1
# define BOOST_PP_BOOL26_36 1
# define BOOST_PP_BOOL26_37 1
# define BOOST_PP_BOOL26_38 1
# define BOOST_PP_BOOL26_39 1
# define BOOST_PP_BOOL26_40 1
# define BOOST_PP_BOOL26_41 1
# define BOOST_PP_BOOL26_42 1
# define BOOST_PP_BOOL26_43 1
# define BOOST_PP_BOOL26_44 1
# define BOOST_PP_BOOL26_45 1
# define BOOST_PP_BOOL26_46 1
# define BOOST_PP_BOOL26_47 1
# define BOOST_PP_BOOL26_48 1
# define BOOST_PP_BOOL26_49 1
# define BOOST_PP_BOOL26_50 1
# define BOOST_PP_BOOL26_51 1
# define BOOST_PP_BOOL26_52 1
# define BOOST_PP_BOOL26_53 1
# define BOOST_PP_BOOL26_54 1
# define BOOST_PP_BOOL26_55 1
# define BOOST_PP_BOOL26_56 1
# define BOOST_PP_BOOL26_57 1
# define BOOST_PP_BOOL26_58 1
# define BOOST_PP_BOOL26_59 1
# define BOOST_PP_BOOL26_60 1
# define BOOST_PP_BOOL26_61 1
# define BOOST_PP_BOOL26_62 1
# define BOOST_PP_BOOL26_63 1
# define BOOST_PP_BOOL26_64 1
# define BOOST_PP_BOOL26_65 1
# define BOOST_PP_BOOL26_66 1
# define BOOST_PP_BOOL26_67 1
# define BOOST_PP_BOOL26_68 1
# define BOOST_PP_BOOL26_69 1
# define BOOST_PP_BOOL26_70 1
# define BOOST_PP_BOOL26_71 1
# define BOOST_PP_BOOL26_72 1
# define BOOST_PP_BOOL26_73 1
# define BOOST_PP_BOOL26_74 1
# define BOOST_PP_BOOL26_75 1
# define BOOST_PP_BOOL26_76 1
# define BOOST_PP_BOOL26_77 1
# define BOOST_PP_BOOL26_78 1
# define BOOST_PP_BOOL26_79 1
# define BOOST_PP_BOOL26_80 1
# define BOOST_PP_BOOL26_81 1
# define BOOST_PP_BOOL26_82 1
# define BOOST_PP_BOOL26_83 1
# define BOOST_PP_BOOL26_84 1
# define BOOST_PP_BOOL26_85 1
# define BOOST_PP_BOOL26_86 1
# define BOOST_PP_BOOL26_87 1
# define BOOST_PP_BOOL26_88 1
# define BOOST_PP_BOOL26_89 1
# define BOOST_PP_BOOL26_90 1
# define BOOST_PP_BOOL26_91 1
# define BOOST_PP_BOOL26_92 1
# define BOOST_PP_BOOL26_93 1
# define BOOST_PP_BOOL26_94 1
# define BOOST_PP_BOOL26_95 1
# define BOOST_PP_BOOL26_96 1
# define BOOST_PP_BOOL26_97 1
# define BOOST_PP_BOOL26_98 1
# define BOOST_PP_BOOL26_99 1
# define BOOST_PP_BOOL26_100 1
# define BOOST_PP_BOOL26_101 1
# define BOOST_PP_BOOL26_102 1
# define BOOST_PP_BOOL26_103 1
# define BOOST_PP_BOOL26_104 1
# define BOOST_PP_BOOL26_105 1
# define BOOST_PP_BOOL26_106 1
# define BOOST_PP_BOOL26_107 1
# define BOOST_PP_BOOL26_108 1
# define BOOST_PP_BOOL26_109 1
# define BOOST_PP_BOOL26_110 1
# define BOOST_PP_BOOL26_111 1
# define BOOST_PP_BOOL26_112 1
# define BOOST_PP_BOOL26_113 1
# define BOOST_PP_BOOL26_114 1
# define BOOST_PP_BOOL26_115 1
# define BOOST_PP_BOOL26_116 1
# define BOOST_PP_BOOL26_117 1
# define BOOST_PP_BOOL26_118 1
# define BOOST_PP_BOOL26_119 1
# define BOOST_PP_BOOL26_120 1
# define BOOST_PP_BOOL26_121 1
# define BOOST_PP_BOOL26_122 1
# define BOOST_PP_BOOL26_123 1
# define BOOST_PP_BOOL26_124 1
# define BOOST_PP_BOOL26_125 1
# define BOOST_PP_BOOL26_126 1
# define BOOST_PP_BOOL26_127 1
# define BOOST_PP_BOOL26_128 1
# define BOOST_PP_BOOL26_129 1
# define BOOST_PP_BOOL26_130 1
# define BOOST_PP_BOOL26_131 1
# define BOOST_PP_BOOL26_132 1
# define BOOST_PP_BOOL26_133 1
# define BOOST_PP_BOOL26_134 1
# define BOOST_PP_BOOL26_135 1
# define BOOST_PP_BOOL26_136 1
# define BOOST_PP_BOOL26_137 1
# define BOOST_PP_BOOL26_138 1
# define BOOST_PP_BOOL26_139 1
# define BOOST_PP_BOOL26_140 1
# define BOOST_PP_BOOL26_141 1
# define BOOST_PP_BOOL26_142 1
# define BOOST_PP_BOOL26_143 1
# define BOOST_PP_BOOL26_144 1
# define BOOST_PP_BOOL26_145 1
# define BOOST_PP_BOOL26_146 1
# define BOOST_PP_BOOL26_147 1
# define BOOST_PP_BOOL26_148 1
# define BOOST_PP_BOOL26_149 1
# define BOOST_PP_BOOL26_150 1
# define BOOST_PP_BOOL26_151 1
# define BOOST_PP_BOOL26_152 1
# define BOOST_PP_BOOL26_153 1
# define BOOST_PP_BOOL26_154 1
# define BOOST_PP_BOOL26_155 1
# define BOOST_PP_BOOL26_156 1
# define BOOST_PP_BOOL26_157 1
# define BOOST_PP_BOOL26_158 1
# define BOOST_PP_BOOL26_159 1
# define BOOST_PP_BOOL26_160 1
# define BOOST_PP_BOOL26_161 1
# define BOOST_PP_BOOL26_162 1
# define BOOST_PP_BOOL26_163 1
# define BOOST_PP_BOOL26_164 1
# define BOOST_PP_BOOL26_165 1
# define BOOST_PP_BOOL26_166 1
# define BOOST_PP_BOOL26_167 1
# define BOOST_PP_BOOL26_168 1
# define BOOST_PP_BOOL26_169 1
# define BOOST_PP_BOOL26_170 1
# define BOOST_PP_BOOL26_171 1
# define BOOST_PP_BOOL26_172 1
# define BOOST_PP_BOOL26_173 1
# define BOOST_PP_BOOL26_174 1
# define BOOST_PP_BOOL26_175 1
# define BOOST_PP_BOOL26_176 1
# define BOOST_PP_BOOL26_177 1
# define BOOST_PP_BOOL26_178 1
# define BOOST_PP_BOOL26_179 1
# define BOOST_PP_BOOL26_180 1
# define BOOST_PP_BOOL26_181 1
# define BOOST_PP_BOOL26_182 1
# define BOOST_PP_BOOL26_183 1
# define BOOST_PP_BOOL26_184 1
# define BOOST_PP_BOOL26_185 1
# define BOOST_PP_BOOL26_186 1
# define BOOST_PP_BOOL26_187 1
# define BOOST_PP_BOOL26_188 1
# define BOOST_PP_BOOL26_189 1
# define BOOST_PP_BOOL26_190 1
# define BOOST_PP_BOOL26_191 1
# define BOOST_PP_BOOL26_192 1
# define BOOST_PP_BOOL26_193 1
# define BOOST_PP_BOOL26_194 1
# define BOOST_PP_BOOL26_195 1
# define BOOST_PP_BOOL26_196 1
# define BOOST_PP_BOOL26_197 1
# define BOOST_PP_BOOL26_198 1
# define BOOST_PP_BOOL26_199 1
# define BOOST_PP_BOOL26_200 1
# define BOOST_PP_BOOL26_201 1
# define BOOST_PP_BOOL26_202 1
# define BOOST_PP_BOOL26_203 1
# define BOOST_PP_BOOL26_204 1
# define BOOST_PP_BOOL26_205 1
# define BOOST_PP_BOOL26_206 1
# define BOOST_PP_BOOL26_207 1
# define BOOST_PP_BOOL26_208 1
# define BOOST_PP_BOOL26_209 1
# define BOOST_PP_BOOL26_210 1
# define BOOST_PP_BOOL26_211 1
# define BOOST_PP_BOOL26_212 1
# define BOOST_PP_BOOL26_213 1
# define BOOST_PP_BOOL26_214 1
# define BOOST_PP_BOOL26_215 1
# define BOOST_PP_BOOL26_216 1
# define BOOST_PP_BOOL26_217 1
# define BOOST_PP_BOOL26_218 1
# define BOOST_PP_BOOL26_219 1
# define BOOST_PP_BOOL26_220 1
# define BOOST_PP_BOOL26_221 1
# define BOOST_PP_BOOL26_222 1
# define BOOST_PP_BOOL26_223 1
# define BOOST_PP_BOOL26_224 1
# define BOOST_PP_BOOL26_225 1
# define BOOST_PP_BOOL26_226 1
# define BOOST_PP_BOOL26_227 1
# define BOOST_PP_BOOL26_228 1
# define BOOST_PP_BOOL26_229 1
# define BOOST_PP_BOOL26_230 1
# define BOOST_PP_BOOL26_231 1
# define BOOST_PP_BOOL26_232 1
# define BOOST_PP_BOOL26_233 1
# define BOOST_PP_BOOL26_234 1
# define BOOST_PP_BOOL26_235 1
# define BOOST_PP_BOOL26_236 1
# define BOOST_PP_BOOL26_237 1
# define BOOST_PP_BOOL26_238 1
# define BOOST_PP_BOOL26_239 1
# define BOOST_PP_BOOL26_240 1
# define BOOST_PP_BOOL26_241 1
# define BOOST_PP_BOOL26_242 1
# define BOOST_PP_BOOL26_243 1
# define BOOST_PP_BOOL26_244 1
# define BOOST_PP_BOOL26_245 1
# define BOOST_PP_BOOL26_246 1
# define BOOST_PP_BOOL26_247 1
# define BOOST_PP_BOOL26_248 1
# define BOOST_PP_BOOL26_249 1
# define BOOST_PP_BOOL26_250 1
# define BOOST_PP_BOOL26_251 1
# define BOOST_PP_BOOL26_252 1
# define BOOST_PP_BOOL26_253 1
# define BOOST_PP_BOOL26_254 1
# define BOOST_PP_BOOL26_255 1
# define BOOST_PP_BOOL26_256 1