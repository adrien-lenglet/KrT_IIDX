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
# /* BOOST_PP_BOOL63 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL63(x) BOOST_PP_BOOL63_I(x)
# else
#    define BOOST_PP_BOOL63(x) BOOST_PP_BOOL63_OO((x))
#    define BOOST_PP_BOOL63_OO(par) BOOST_PP_BOOL63_I ## par
# endif
#
# define BOOST_PP_BOOL63_I(x) BOOST_PP_BOOL63_ ## x
#
# define BOOST_PP_BOOL63_0 0
# define BOOST_PP_BOOL63_1 1
# define BOOST_PP_BOOL63_2 1
# define BOOST_PP_BOOL63_3 1
# define BOOST_PP_BOOL63_4 1
# define BOOST_PP_BOOL63_5 1
# define BOOST_PP_BOOL63_6 1
# define BOOST_PP_BOOL63_7 1
# define BOOST_PP_BOOL63_8 1
# define BOOST_PP_BOOL63_9 1
# define BOOST_PP_BOOL63_10 1
# define BOOST_PP_BOOL63_11 1
# define BOOST_PP_BOOL63_12 1
# define BOOST_PP_BOOL63_13 1
# define BOOST_PP_BOOL63_14 1
# define BOOST_PP_BOOL63_15 1
# define BOOST_PP_BOOL63_16 1
# define BOOST_PP_BOOL63_17 1
# define BOOST_PP_BOOL63_18 1
# define BOOST_PP_BOOL63_19 1
# define BOOST_PP_BOOL63_20 1
# define BOOST_PP_BOOL63_21 1
# define BOOST_PP_BOOL63_22 1
# define BOOST_PP_BOOL63_23 1
# define BOOST_PP_BOOL63_24 1
# define BOOST_PP_BOOL63_25 1
# define BOOST_PP_BOOL63_26 1
# define BOOST_PP_BOOL63_27 1
# define BOOST_PP_BOOL63_28 1
# define BOOST_PP_BOOL63_29 1
# define BOOST_PP_BOOL63_30 1
# define BOOST_PP_BOOL63_31 1
# define BOOST_PP_BOOL63_32 1
# define BOOST_PP_BOOL63_33 1
# define BOOST_PP_BOOL63_34 1
# define BOOST_PP_BOOL63_35 1
# define BOOST_PP_BOOL63_36 1
# define BOOST_PP_BOOL63_37 1
# define BOOST_PP_BOOL63_38 1
# define BOOST_PP_BOOL63_39 1
# define BOOST_PP_BOOL63_40 1
# define BOOST_PP_BOOL63_41 1
# define BOOST_PP_BOOL63_42 1
# define BOOST_PP_BOOL63_43 1
# define BOOST_PP_BOOL63_44 1
# define BOOST_PP_BOOL63_45 1
# define BOOST_PP_BOOL63_46 1
# define BOOST_PP_BOOL63_47 1
# define BOOST_PP_BOOL63_48 1
# define BOOST_PP_BOOL63_49 1
# define BOOST_PP_BOOL63_50 1
# define BOOST_PP_BOOL63_51 1
# define BOOST_PP_BOOL63_52 1
# define BOOST_PP_BOOL63_53 1
# define BOOST_PP_BOOL63_54 1
# define BOOST_PP_BOOL63_55 1
# define BOOST_PP_BOOL63_56 1
# define BOOST_PP_BOOL63_57 1
# define BOOST_PP_BOOL63_58 1
# define BOOST_PP_BOOL63_59 1
# define BOOST_PP_BOOL63_60 1
# define BOOST_PP_BOOL63_61 1
# define BOOST_PP_BOOL63_62 1
# define BOOST_PP_BOOL63_63 1
# define BOOST_PP_BOOL63_64 1
# define BOOST_PP_BOOL63_65 1
# define BOOST_PP_BOOL63_66 1
# define BOOST_PP_BOOL63_67 1
# define BOOST_PP_BOOL63_68 1
# define BOOST_PP_BOOL63_69 1
# define BOOST_PP_BOOL63_70 1
# define BOOST_PP_BOOL63_71 1
# define BOOST_PP_BOOL63_72 1
# define BOOST_PP_BOOL63_73 1
# define BOOST_PP_BOOL63_74 1
# define BOOST_PP_BOOL63_75 1
# define BOOST_PP_BOOL63_76 1
# define BOOST_PP_BOOL63_77 1
# define BOOST_PP_BOOL63_78 1
# define BOOST_PP_BOOL63_79 1
# define BOOST_PP_BOOL63_80 1
# define BOOST_PP_BOOL63_81 1
# define BOOST_PP_BOOL63_82 1
# define BOOST_PP_BOOL63_83 1
# define BOOST_PP_BOOL63_84 1
# define BOOST_PP_BOOL63_85 1
# define BOOST_PP_BOOL63_86 1
# define BOOST_PP_BOOL63_87 1
# define BOOST_PP_BOOL63_88 1
# define BOOST_PP_BOOL63_89 1
# define BOOST_PP_BOOL63_90 1
# define BOOST_PP_BOOL63_91 1
# define BOOST_PP_BOOL63_92 1
# define BOOST_PP_BOOL63_93 1
# define BOOST_PP_BOOL63_94 1
# define BOOST_PP_BOOL63_95 1
# define BOOST_PP_BOOL63_96 1
# define BOOST_PP_BOOL63_97 1
# define BOOST_PP_BOOL63_98 1
# define BOOST_PP_BOOL63_99 1
# define BOOST_PP_BOOL63_100 1
# define BOOST_PP_BOOL63_101 1
# define BOOST_PP_BOOL63_102 1
# define BOOST_PP_BOOL63_103 1
# define BOOST_PP_BOOL63_104 1
# define BOOST_PP_BOOL63_105 1
# define BOOST_PP_BOOL63_106 1
# define BOOST_PP_BOOL63_107 1
# define BOOST_PP_BOOL63_108 1
# define BOOST_PP_BOOL63_109 1
# define BOOST_PP_BOOL63_110 1
# define BOOST_PP_BOOL63_111 1
# define BOOST_PP_BOOL63_112 1
# define BOOST_PP_BOOL63_113 1
# define BOOST_PP_BOOL63_114 1
# define BOOST_PP_BOOL63_115 1
# define BOOST_PP_BOOL63_116 1
# define BOOST_PP_BOOL63_117 1
# define BOOST_PP_BOOL63_118 1
# define BOOST_PP_BOOL63_119 1
# define BOOST_PP_BOOL63_120 1
# define BOOST_PP_BOOL63_121 1
# define BOOST_PP_BOOL63_122 1
# define BOOST_PP_BOOL63_123 1
# define BOOST_PP_BOOL63_124 1
# define BOOST_PP_BOOL63_125 1
# define BOOST_PP_BOOL63_126 1
# define BOOST_PP_BOOL63_127 1
# define BOOST_PP_BOOL63_128 1
# define BOOST_PP_BOOL63_129 1
# define BOOST_PP_BOOL63_130 1
# define BOOST_PP_BOOL63_131 1
# define BOOST_PP_BOOL63_132 1
# define BOOST_PP_BOOL63_133 1
# define BOOST_PP_BOOL63_134 1
# define BOOST_PP_BOOL63_135 1
# define BOOST_PP_BOOL63_136 1
# define BOOST_PP_BOOL63_137 1
# define BOOST_PP_BOOL63_138 1
# define BOOST_PP_BOOL63_139 1
# define BOOST_PP_BOOL63_140 1
# define BOOST_PP_BOOL63_141 1
# define BOOST_PP_BOOL63_142 1
# define BOOST_PP_BOOL63_143 1
# define BOOST_PP_BOOL63_144 1
# define BOOST_PP_BOOL63_145 1
# define BOOST_PP_BOOL63_146 1
# define BOOST_PP_BOOL63_147 1
# define BOOST_PP_BOOL63_148 1
# define BOOST_PP_BOOL63_149 1
# define BOOST_PP_BOOL63_150 1
# define BOOST_PP_BOOL63_151 1
# define BOOST_PP_BOOL63_152 1
# define BOOST_PP_BOOL63_153 1
# define BOOST_PP_BOOL63_154 1
# define BOOST_PP_BOOL63_155 1
# define BOOST_PP_BOOL63_156 1
# define BOOST_PP_BOOL63_157 1
# define BOOST_PP_BOOL63_158 1
# define BOOST_PP_BOOL63_159 1
# define BOOST_PP_BOOL63_160 1
# define BOOST_PP_BOOL63_161 1
# define BOOST_PP_BOOL63_162 1
# define BOOST_PP_BOOL63_163 1
# define BOOST_PP_BOOL63_164 1
# define BOOST_PP_BOOL63_165 1
# define BOOST_PP_BOOL63_166 1
# define BOOST_PP_BOOL63_167 1
# define BOOST_PP_BOOL63_168 1
# define BOOST_PP_BOOL63_169 1
# define BOOST_PP_BOOL63_170 1
# define BOOST_PP_BOOL63_171 1
# define BOOST_PP_BOOL63_172 1
# define BOOST_PP_BOOL63_173 1
# define BOOST_PP_BOOL63_174 1
# define BOOST_PP_BOOL63_175 1
# define BOOST_PP_BOOL63_176 1
# define BOOST_PP_BOOL63_177 1
# define BOOST_PP_BOOL63_178 1
# define BOOST_PP_BOOL63_179 1
# define BOOST_PP_BOOL63_180 1
# define BOOST_PP_BOOL63_181 1
# define BOOST_PP_BOOL63_182 1
# define BOOST_PP_BOOL63_183 1
# define BOOST_PP_BOOL63_184 1
# define BOOST_PP_BOOL63_185 1
# define BOOST_PP_BOOL63_186 1
# define BOOST_PP_BOOL63_187 1
# define BOOST_PP_BOOL63_188 1
# define BOOST_PP_BOOL63_189 1
# define BOOST_PP_BOOL63_190 1
# define BOOST_PP_BOOL63_191 1
# define BOOST_PP_BOOL63_192 1
# define BOOST_PP_BOOL63_193 1
# define BOOST_PP_BOOL63_194 1
# define BOOST_PP_BOOL63_195 1
# define BOOST_PP_BOOL63_196 1
# define BOOST_PP_BOOL63_197 1
# define BOOST_PP_BOOL63_198 1
# define BOOST_PP_BOOL63_199 1
# define BOOST_PP_BOOL63_200 1
# define BOOST_PP_BOOL63_201 1
# define BOOST_PP_BOOL63_202 1
# define BOOST_PP_BOOL63_203 1
# define BOOST_PP_BOOL63_204 1
# define BOOST_PP_BOOL63_205 1
# define BOOST_PP_BOOL63_206 1
# define BOOST_PP_BOOL63_207 1
# define BOOST_PP_BOOL63_208 1
# define BOOST_PP_BOOL63_209 1
# define BOOST_PP_BOOL63_210 1
# define BOOST_PP_BOOL63_211 1
# define BOOST_PP_BOOL63_212 1
# define BOOST_PP_BOOL63_213 1
# define BOOST_PP_BOOL63_214 1
# define BOOST_PP_BOOL63_215 1
# define BOOST_PP_BOOL63_216 1
# define BOOST_PP_BOOL63_217 1
# define BOOST_PP_BOOL63_218 1
# define BOOST_PP_BOOL63_219 1
# define BOOST_PP_BOOL63_220 1
# define BOOST_PP_BOOL63_221 1
# define BOOST_PP_BOOL63_222 1
# define BOOST_PP_BOOL63_223 1
# define BOOST_PP_BOOL63_224 1
# define BOOST_PP_BOOL63_225 1
# define BOOST_PP_BOOL63_226 1
# define BOOST_PP_BOOL63_227 1
# define BOOST_PP_BOOL63_228 1
# define BOOST_PP_BOOL63_229 1
# define BOOST_PP_BOOL63_230 1
# define BOOST_PP_BOOL63_231 1
# define BOOST_PP_BOOL63_232 1
# define BOOST_PP_BOOL63_233 1
# define BOOST_PP_BOOL63_234 1
# define BOOST_PP_BOOL63_235 1
# define BOOST_PP_BOOL63_236 1
# define BOOST_PP_BOOL63_237 1
# define BOOST_PP_BOOL63_238 1
# define BOOST_PP_BOOL63_239 1
# define BOOST_PP_BOOL63_240 1
# define BOOST_PP_BOOL63_241 1
# define BOOST_PP_BOOL63_242 1
# define BOOST_PP_BOOL63_243 1
# define BOOST_PP_BOOL63_244 1
# define BOOST_PP_BOOL63_245 1
# define BOOST_PP_BOOL63_246 1
# define BOOST_PP_BOOL63_247 1
# define BOOST_PP_BOOL63_248 1
# define BOOST_PP_BOOL63_249 1
# define BOOST_PP_BOOL63_250 1
# define BOOST_PP_BOOL63_251 1
# define BOOST_PP_BOOL63_252 1
# define BOOST_PP_BOOL63_253 1
# define BOOST_PP_BOOL63_254 1
# define BOOST_PP_BOOL63_255 1
# define BOOST_PP_BOOL63_256 1