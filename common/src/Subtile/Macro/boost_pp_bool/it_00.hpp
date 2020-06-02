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
# /* BOOST_PP_BOOL0 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL0(x) BOOST_PP_BOOL0_I(x)
# else
#    define BOOST_PP_BOOL0(x) BOOST_PP_BOOL0_OO((x))
#    define BOOST_PP_BOOL0_OO(par) BOOST_PP_BOOL0_I ## par
# endif
#
# define BOOST_PP_BOOL0_I(x) BOOST_PP_BOOL0_ ## x
#
# define BOOST_PP_BOOL0_0 0
# define BOOST_PP_BOOL0_1 1
# define BOOST_PP_BOOL0_2 1
# define BOOST_PP_BOOL0_3 1
# define BOOST_PP_BOOL0_4 1
# define BOOST_PP_BOOL0_5 1
# define BOOST_PP_BOOL0_6 1
# define BOOST_PP_BOOL0_7 1
# define BOOST_PP_BOOL0_8 1
# define BOOST_PP_BOOL0_9 1
# define BOOST_PP_BOOL0_10 1
# define BOOST_PP_BOOL0_11 1
# define BOOST_PP_BOOL0_12 1
# define BOOST_PP_BOOL0_13 1
# define BOOST_PP_BOOL0_14 1
# define BOOST_PP_BOOL0_15 1
# define BOOST_PP_BOOL0_16 1
# define BOOST_PP_BOOL0_17 1
# define BOOST_PP_BOOL0_18 1
# define BOOST_PP_BOOL0_19 1
# define BOOST_PP_BOOL0_20 1
# define BOOST_PP_BOOL0_21 1
# define BOOST_PP_BOOL0_22 1
# define BOOST_PP_BOOL0_23 1
# define BOOST_PP_BOOL0_24 1
# define BOOST_PP_BOOL0_25 1
# define BOOST_PP_BOOL0_26 1
# define BOOST_PP_BOOL0_27 1
# define BOOST_PP_BOOL0_28 1
# define BOOST_PP_BOOL0_29 1
# define BOOST_PP_BOOL0_30 1
# define BOOST_PP_BOOL0_31 1
# define BOOST_PP_BOOL0_32 1
# define BOOST_PP_BOOL0_33 1
# define BOOST_PP_BOOL0_34 1
# define BOOST_PP_BOOL0_35 1
# define BOOST_PP_BOOL0_36 1
# define BOOST_PP_BOOL0_37 1
# define BOOST_PP_BOOL0_38 1
# define BOOST_PP_BOOL0_39 1
# define BOOST_PP_BOOL0_40 1
# define BOOST_PP_BOOL0_41 1
# define BOOST_PP_BOOL0_42 1
# define BOOST_PP_BOOL0_43 1
# define BOOST_PP_BOOL0_44 1
# define BOOST_PP_BOOL0_45 1
# define BOOST_PP_BOOL0_46 1
# define BOOST_PP_BOOL0_47 1
# define BOOST_PP_BOOL0_48 1
# define BOOST_PP_BOOL0_49 1
# define BOOST_PP_BOOL0_50 1
# define BOOST_PP_BOOL0_51 1
# define BOOST_PP_BOOL0_52 1
# define BOOST_PP_BOOL0_53 1
# define BOOST_PP_BOOL0_54 1
# define BOOST_PP_BOOL0_55 1
# define BOOST_PP_BOOL0_56 1
# define BOOST_PP_BOOL0_57 1
# define BOOST_PP_BOOL0_58 1
# define BOOST_PP_BOOL0_59 1
# define BOOST_PP_BOOL0_60 1
# define BOOST_PP_BOOL0_61 1
# define BOOST_PP_BOOL0_62 1
# define BOOST_PP_BOOL0_63 1
# define BOOST_PP_BOOL0_64 1
# define BOOST_PP_BOOL0_65 1
# define BOOST_PP_BOOL0_66 1
# define BOOST_PP_BOOL0_67 1
# define BOOST_PP_BOOL0_68 1
# define BOOST_PP_BOOL0_69 1
# define BOOST_PP_BOOL0_70 1
# define BOOST_PP_BOOL0_71 1
# define BOOST_PP_BOOL0_72 1
# define BOOST_PP_BOOL0_73 1
# define BOOST_PP_BOOL0_74 1
# define BOOST_PP_BOOL0_75 1
# define BOOST_PP_BOOL0_76 1
# define BOOST_PP_BOOL0_77 1
# define BOOST_PP_BOOL0_78 1
# define BOOST_PP_BOOL0_79 1
# define BOOST_PP_BOOL0_80 1
# define BOOST_PP_BOOL0_81 1
# define BOOST_PP_BOOL0_82 1
# define BOOST_PP_BOOL0_83 1
# define BOOST_PP_BOOL0_84 1
# define BOOST_PP_BOOL0_85 1
# define BOOST_PP_BOOL0_86 1
# define BOOST_PP_BOOL0_87 1
# define BOOST_PP_BOOL0_88 1
# define BOOST_PP_BOOL0_89 1
# define BOOST_PP_BOOL0_90 1
# define BOOST_PP_BOOL0_91 1
# define BOOST_PP_BOOL0_92 1
# define BOOST_PP_BOOL0_93 1
# define BOOST_PP_BOOL0_94 1
# define BOOST_PP_BOOL0_95 1
# define BOOST_PP_BOOL0_96 1
# define BOOST_PP_BOOL0_97 1
# define BOOST_PP_BOOL0_98 1
# define BOOST_PP_BOOL0_99 1
# define BOOST_PP_BOOL0_100 1
# define BOOST_PP_BOOL0_101 1
# define BOOST_PP_BOOL0_102 1
# define BOOST_PP_BOOL0_103 1
# define BOOST_PP_BOOL0_104 1
# define BOOST_PP_BOOL0_105 1
# define BOOST_PP_BOOL0_106 1
# define BOOST_PP_BOOL0_107 1
# define BOOST_PP_BOOL0_108 1
# define BOOST_PP_BOOL0_109 1
# define BOOST_PP_BOOL0_110 1
# define BOOST_PP_BOOL0_111 1
# define BOOST_PP_BOOL0_112 1
# define BOOST_PP_BOOL0_113 1
# define BOOST_PP_BOOL0_114 1
# define BOOST_PP_BOOL0_115 1
# define BOOST_PP_BOOL0_116 1
# define BOOST_PP_BOOL0_117 1
# define BOOST_PP_BOOL0_118 1
# define BOOST_PP_BOOL0_119 1
# define BOOST_PP_BOOL0_120 1
# define BOOST_PP_BOOL0_121 1
# define BOOST_PP_BOOL0_122 1
# define BOOST_PP_BOOL0_123 1
# define BOOST_PP_BOOL0_124 1
# define BOOST_PP_BOOL0_125 1
# define BOOST_PP_BOOL0_126 1
# define BOOST_PP_BOOL0_127 1
# define BOOST_PP_BOOL0_128 1
# define BOOST_PP_BOOL0_129 1
# define BOOST_PP_BOOL0_130 1
# define BOOST_PP_BOOL0_131 1
# define BOOST_PP_BOOL0_132 1
# define BOOST_PP_BOOL0_133 1
# define BOOST_PP_BOOL0_134 1
# define BOOST_PP_BOOL0_135 1
# define BOOST_PP_BOOL0_136 1
# define BOOST_PP_BOOL0_137 1
# define BOOST_PP_BOOL0_138 1
# define BOOST_PP_BOOL0_139 1
# define BOOST_PP_BOOL0_140 1
# define BOOST_PP_BOOL0_141 1
# define BOOST_PP_BOOL0_142 1
# define BOOST_PP_BOOL0_143 1
# define BOOST_PP_BOOL0_144 1
# define BOOST_PP_BOOL0_145 1
# define BOOST_PP_BOOL0_146 1
# define BOOST_PP_BOOL0_147 1
# define BOOST_PP_BOOL0_148 1
# define BOOST_PP_BOOL0_149 1
# define BOOST_PP_BOOL0_150 1
# define BOOST_PP_BOOL0_151 1
# define BOOST_PP_BOOL0_152 1
# define BOOST_PP_BOOL0_153 1
# define BOOST_PP_BOOL0_154 1
# define BOOST_PP_BOOL0_155 1
# define BOOST_PP_BOOL0_156 1
# define BOOST_PP_BOOL0_157 1
# define BOOST_PP_BOOL0_158 1
# define BOOST_PP_BOOL0_159 1
# define BOOST_PP_BOOL0_160 1
# define BOOST_PP_BOOL0_161 1
# define BOOST_PP_BOOL0_162 1
# define BOOST_PP_BOOL0_163 1
# define BOOST_PP_BOOL0_164 1
# define BOOST_PP_BOOL0_165 1
# define BOOST_PP_BOOL0_166 1
# define BOOST_PP_BOOL0_167 1
# define BOOST_PP_BOOL0_168 1
# define BOOST_PP_BOOL0_169 1
# define BOOST_PP_BOOL0_170 1
# define BOOST_PP_BOOL0_171 1
# define BOOST_PP_BOOL0_172 1
# define BOOST_PP_BOOL0_173 1
# define BOOST_PP_BOOL0_174 1
# define BOOST_PP_BOOL0_175 1
# define BOOST_PP_BOOL0_176 1
# define BOOST_PP_BOOL0_177 1
# define BOOST_PP_BOOL0_178 1
# define BOOST_PP_BOOL0_179 1
# define BOOST_PP_BOOL0_180 1
# define BOOST_PP_BOOL0_181 1
# define BOOST_PP_BOOL0_182 1
# define BOOST_PP_BOOL0_183 1
# define BOOST_PP_BOOL0_184 1
# define BOOST_PP_BOOL0_185 1
# define BOOST_PP_BOOL0_186 1
# define BOOST_PP_BOOL0_187 1
# define BOOST_PP_BOOL0_188 1
# define BOOST_PP_BOOL0_189 1
# define BOOST_PP_BOOL0_190 1
# define BOOST_PP_BOOL0_191 1
# define BOOST_PP_BOOL0_192 1
# define BOOST_PP_BOOL0_193 1
# define BOOST_PP_BOOL0_194 1
# define BOOST_PP_BOOL0_195 1
# define BOOST_PP_BOOL0_196 1
# define BOOST_PP_BOOL0_197 1
# define BOOST_PP_BOOL0_198 1
# define BOOST_PP_BOOL0_199 1
# define BOOST_PP_BOOL0_200 1
# define BOOST_PP_BOOL0_201 1
# define BOOST_PP_BOOL0_202 1
# define BOOST_PP_BOOL0_203 1
# define BOOST_PP_BOOL0_204 1
# define BOOST_PP_BOOL0_205 1
# define BOOST_PP_BOOL0_206 1
# define BOOST_PP_BOOL0_207 1
# define BOOST_PP_BOOL0_208 1
# define BOOST_PP_BOOL0_209 1
# define BOOST_PP_BOOL0_210 1
# define BOOST_PP_BOOL0_211 1
# define BOOST_PP_BOOL0_212 1
# define BOOST_PP_BOOL0_213 1
# define BOOST_PP_BOOL0_214 1
# define BOOST_PP_BOOL0_215 1
# define BOOST_PP_BOOL0_216 1
# define BOOST_PP_BOOL0_217 1
# define BOOST_PP_BOOL0_218 1
# define BOOST_PP_BOOL0_219 1
# define BOOST_PP_BOOL0_220 1
# define BOOST_PP_BOOL0_221 1
# define BOOST_PP_BOOL0_222 1
# define BOOST_PP_BOOL0_223 1
# define BOOST_PP_BOOL0_224 1
# define BOOST_PP_BOOL0_225 1
# define BOOST_PP_BOOL0_226 1
# define BOOST_PP_BOOL0_227 1
# define BOOST_PP_BOOL0_228 1
# define BOOST_PP_BOOL0_229 1
# define BOOST_PP_BOOL0_230 1
# define BOOST_PP_BOOL0_231 1
# define BOOST_PP_BOOL0_232 1
# define BOOST_PP_BOOL0_233 1
# define BOOST_PP_BOOL0_234 1
# define BOOST_PP_BOOL0_235 1
# define BOOST_PP_BOOL0_236 1
# define BOOST_PP_BOOL0_237 1
# define BOOST_PP_BOOL0_238 1
# define BOOST_PP_BOOL0_239 1
# define BOOST_PP_BOOL0_240 1
# define BOOST_PP_BOOL0_241 1
# define BOOST_PP_BOOL0_242 1
# define BOOST_PP_BOOL0_243 1
# define BOOST_PP_BOOL0_244 1
# define BOOST_PP_BOOL0_245 1
# define BOOST_PP_BOOL0_246 1
# define BOOST_PP_BOOL0_247 1
# define BOOST_PP_BOOL0_248 1
# define BOOST_PP_BOOL0_249 1
# define BOOST_PP_BOOL0_250 1
# define BOOST_PP_BOOL0_251 1
# define BOOST_PP_BOOL0_252 1
# define BOOST_PP_BOOL0_253 1
# define BOOST_PP_BOOL0_254 1
# define BOOST_PP_BOOL0_255 1
# define BOOST_PP_BOOL0_256 1