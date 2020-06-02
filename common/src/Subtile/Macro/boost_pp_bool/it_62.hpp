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
# /* BOOST_PP_BOOL98 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL98(x) BOOST_PP_BOOL98_I(x)
# else
#    define BOOST_PP_BOOL98(x) BOOST_PP_BOOL98_OO((x))
#    define BOOST_PP_BOOL98_OO(par) BOOST_PP_BOOL98_I ## par
# endif
#
# define BOOST_PP_BOOL98_I(x) BOOST_PP_BOOL98_ ## x
#
# define BOOST_PP_BOOL98_0 0
# define BOOST_PP_BOOL98_1 1
# define BOOST_PP_BOOL98_2 1
# define BOOST_PP_BOOL98_3 1
# define BOOST_PP_BOOL98_4 1
# define BOOST_PP_BOOL98_5 1
# define BOOST_PP_BOOL98_6 1
# define BOOST_PP_BOOL98_7 1
# define BOOST_PP_BOOL98_8 1
# define BOOST_PP_BOOL98_9 1
# define BOOST_PP_BOOL98_10 1
# define BOOST_PP_BOOL98_11 1
# define BOOST_PP_BOOL98_12 1
# define BOOST_PP_BOOL98_13 1
# define BOOST_PP_BOOL98_14 1
# define BOOST_PP_BOOL98_15 1
# define BOOST_PP_BOOL98_16 1
# define BOOST_PP_BOOL98_17 1
# define BOOST_PP_BOOL98_18 1
# define BOOST_PP_BOOL98_19 1
# define BOOST_PP_BOOL98_20 1
# define BOOST_PP_BOOL98_21 1
# define BOOST_PP_BOOL98_22 1
# define BOOST_PP_BOOL98_23 1
# define BOOST_PP_BOOL98_24 1
# define BOOST_PP_BOOL98_25 1
# define BOOST_PP_BOOL98_26 1
# define BOOST_PP_BOOL98_27 1
# define BOOST_PP_BOOL98_28 1
# define BOOST_PP_BOOL98_29 1
# define BOOST_PP_BOOL98_30 1
# define BOOST_PP_BOOL98_31 1
# define BOOST_PP_BOOL98_32 1
# define BOOST_PP_BOOL98_33 1
# define BOOST_PP_BOOL98_34 1
# define BOOST_PP_BOOL98_35 1
# define BOOST_PP_BOOL98_36 1
# define BOOST_PP_BOOL98_37 1
# define BOOST_PP_BOOL98_38 1
# define BOOST_PP_BOOL98_39 1
# define BOOST_PP_BOOL98_40 1
# define BOOST_PP_BOOL98_41 1
# define BOOST_PP_BOOL98_42 1
# define BOOST_PP_BOOL98_43 1
# define BOOST_PP_BOOL98_44 1
# define BOOST_PP_BOOL98_45 1
# define BOOST_PP_BOOL98_46 1
# define BOOST_PP_BOOL98_47 1
# define BOOST_PP_BOOL98_48 1
# define BOOST_PP_BOOL98_49 1
# define BOOST_PP_BOOL98_50 1
# define BOOST_PP_BOOL98_51 1
# define BOOST_PP_BOOL98_52 1
# define BOOST_PP_BOOL98_53 1
# define BOOST_PP_BOOL98_54 1
# define BOOST_PP_BOOL98_55 1
# define BOOST_PP_BOOL98_56 1
# define BOOST_PP_BOOL98_57 1
# define BOOST_PP_BOOL98_58 1
# define BOOST_PP_BOOL98_59 1
# define BOOST_PP_BOOL98_60 1
# define BOOST_PP_BOOL98_61 1
# define BOOST_PP_BOOL98_62 1
# define BOOST_PP_BOOL98_63 1
# define BOOST_PP_BOOL98_64 1
# define BOOST_PP_BOOL98_65 1
# define BOOST_PP_BOOL98_66 1
# define BOOST_PP_BOOL98_67 1
# define BOOST_PP_BOOL98_68 1
# define BOOST_PP_BOOL98_69 1
# define BOOST_PP_BOOL98_70 1
# define BOOST_PP_BOOL98_71 1
# define BOOST_PP_BOOL98_72 1
# define BOOST_PP_BOOL98_73 1
# define BOOST_PP_BOOL98_74 1
# define BOOST_PP_BOOL98_75 1
# define BOOST_PP_BOOL98_76 1
# define BOOST_PP_BOOL98_77 1
# define BOOST_PP_BOOL98_78 1
# define BOOST_PP_BOOL98_79 1
# define BOOST_PP_BOOL98_80 1
# define BOOST_PP_BOOL98_81 1
# define BOOST_PP_BOOL98_82 1
# define BOOST_PP_BOOL98_83 1
# define BOOST_PP_BOOL98_84 1
# define BOOST_PP_BOOL98_85 1
# define BOOST_PP_BOOL98_86 1
# define BOOST_PP_BOOL98_87 1
# define BOOST_PP_BOOL98_88 1
# define BOOST_PP_BOOL98_89 1
# define BOOST_PP_BOOL98_90 1
# define BOOST_PP_BOOL98_91 1
# define BOOST_PP_BOOL98_92 1
# define BOOST_PP_BOOL98_93 1
# define BOOST_PP_BOOL98_94 1
# define BOOST_PP_BOOL98_95 1
# define BOOST_PP_BOOL98_96 1
# define BOOST_PP_BOOL98_97 1
# define BOOST_PP_BOOL98_98 1
# define BOOST_PP_BOOL98_99 1
# define BOOST_PP_BOOL98_100 1
# define BOOST_PP_BOOL98_101 1
# define BOOST_PP_BOOL98_102 1
# define BOOST_PP_BOOL98_103 1
# define BOOST_PP_BOOL98_104 1
# define BOOST_PP_BOOL98_105 1
# define BOOST_PP_BOOL98_106 1
# define BOOST_PP_BOOL98_107 1
# define BOOST_PP_BOOL98_108 1
# define BOOST_PP_BOOL98_109 1
# define BOOST_PP_BOOL98_110 1
# define BOOST_PP_BOOL98_111 1
# define BOOST_PP_BOOL98_112 1
# define BOOST_PP_BOOL98_113 1
# define BOOST_PP_BOOL98_114 1
# define BOOST_PP_BOOL98_115 1
# define BOOST_PP_BOOL98_116 1
# define BOOST_PP_BOOL98_117 1
# define BOOST_PP_BOOL98_118 1
# define BOOST_PP_BOOL98_119 1
# define BOOST_PP_BOOL98_120 1
# define BOOST_PP_BOOL98_121 1
# define BOOST_PP_BOOL98_122 1
# define BOOST_PP_BOOL98_123 1
# define BOOST_PP_BOOL98_124 1
# define BOOST_PP_BOOL98_125 1
# define BOOST_PP_BOOL98_126 1
# define BOOST_PP_BOOL98_127 1
# define BOOST_PP_BOOL98_128 1
# define BOOST_PP_BOOL98_129 1
# define BOOST_PP_BOOL98_130 1
# define BOOST_PP_BOOL98_131 1
# define BOOST_PP_BOOL98_132 1
# define BOOST_PP_BOOL98_133 1
# define BOOST_PP_BOOL98_134 1
# define BOOST_PP_BOOL98_135 1
# define BOOST_PP_BOOL98_136 1
# define BOOST_PP_BOOL98_137 1
# define BOOST_PP_BOOL98_138 1
# define BOOST_PP_BOOL98_139 1
# define BOOST_PP_BOOL98_140 1
# define BOOST_PP_BOOL98_141 1
# define BOOST_PP_BOOL98_142 1
# define BOOST_PP_BOOL98_143 1
# define BOOST_PP_BOOL98_144 1
# define BOOST_PP_BOOL98_145 1
# define BOOST_PP_BOOL98_146 1
# define BOOST_PP_BOOL98_147 1
# define BOOST_PP_BOOL98_148 1
# define BOOST_PP_BOOL98_149 1
# define BOOST_PP_BOOL98_150 1
# define BOOST_PP_BOOL98_151 1
# define BOOST_PP_BOOL98_152 1
# define BOOST_PP_BOOL98_153 1
# define BOOST_PP_BOOL98_154 1
# define BOOST_PP_BOOL98_155 1
# define BOOST_PP_BOOL98_156 1
# define BOOST_PP_BOOL98_157 1
# define BOOST_PP_BOOL98_158 1
# define BOOST_PP_BOOL98_159 1
# define BOOST_PP_BOOL98_160 1
# define BOOST_PP_BOOL98_161 1
# define BOOST_PP_BOOL98_162 1
# define BOOST_PP_BOOL98_163 1
# define BOOST_PP_BOOL98_164 1
# define BOOST_PP_BOOL98_165 1
# define BOOST_PP_BOOL98_166 1
# define BOOST_PP_BOOL98_167 1
# define BOOST_PP_BOOL98_168 1
# define BOOST_PP_BOOL98_169 1
# define BOOST_PP_BOOL98_170 1
# define BOOST_PP_BOOL98_171 1
# define BOOST_PP_BOOL98_172 1
# define BOOST_PP_BOOL98_173 1
# define BOOST_PP_BOOL98_174 1
# define BOOST_PP_BOOL98_175 1
# define BOOST_PP_BOOL98_176 1
# define BOOST_PP_BOOL98_177 1
# define BOOST_PP_BOOL98_178 1
# define BOOST_PP_BOOL98_179 1
# define BOOST_PP_BOOL98_180 1
# define BOOST_PP_BOOL98_181 1
# define BOOST_PP_BOOL98_182 1
# define BOOST_PP_BOOL98_183 1
# define BOOST_PP_BOOL98_184 1
# define BOOST_PP_BOOL98_185 1
# define BOOST_PP_BOOL98_186 1
# define BOOST_PP_BOOL98_187 1
# define BOOST_PP_BOOL98_188 1
# define BOOST_PP_BOOL98_189 1
# define BOOST_PP_BOOL98_190 1
# define BOOST_PP_BOOL98_191 1
# define BOOST_PP_BOOL98_192 1
# define BOOST_PP_BOOL98_193 1
# define BOOST_PP_BOOL98_194 1
# define BOOST_PP_BOOL98_195 1
# define BOOST_PP_BOOL98_196 1
# define BOOST_PP_BOOL98_197 1
# define BOOST_PP_BOOL98_198 1
# define BOOST_PP_BOOL98_199 1
# define BOOST_PP_BOOL98_200 1
# define BOOST_PP_BOOL98_201 1
# define BOOST_PP_BOOL98_202 1
# define BOOST_PP_BOOL98_203 1
# define BOOST_PP_BOOL98_204 1
# define BOOST_PP_BOOL98_205 1
# define BOOST_PP_BOOL98_206 1
# define BOOST_PP_BOOL98_207 1
# define BOOST_PP_BOOL98_208 1
# define BOOST_PP_BOOL98_209 1
# define BOOST_PP_BOOL98_210 1
# define BOOST_PP_BOOL98_211 1
# define BOOST_PP_BOOL98_212 1
# define BOOST_PP_BOOL98_213 1
# define BOOST_PP_BOOL98_214 1
# define BOOST_PP_BOOL98_215 1
# define BOOST_PP_BOOL98_216 1
# define BOOST_PP_BOOL98_217 1
# define BOOST_PP_BOOL98_218 1
# define BOOST_PP_BOOL98_219 1
# define BOOST_PP_BOOL98_220 1
# define BOOST_PP_BOOL98_221 1
# define BOOST_PP_BOOL98_222 1
# define BOOST_PP_BOOL98_223 1
# define BOOST_PP_BOOL98_224 1
# define BOOST_PP_BOOL98_225 1
# define BOOST_PP_BOOL98_226 1
# define BOOST_PP_BOOL98_227 1
# define BOOST_PP_BOOL98_228 1
# define BOOST_PP_BOOL98_229 1
# define BOOST_PP_BOOL98_230 1
# define BOOST_PP_BOOL98_231 1
# define BOOST_PP_BOOL98_232 1
# define BOOST_PP_BOOL98_233 1
# define BOOST_PP_BOOL98_234 1
# define BOOST_PP_BOOL98_235 1
# define BOOST_PP_BOOL98_236 1
# define BOOST_PP_BOOL98_237 1
# define BOOST_PP_BOOL98_238 1
# define BOOST_PP_BOOL98_239 1
# define BOOST_PP_BOOL98_240 1
# define BOOST_PP_BOOL98_241 1
# define BOOST_PP_BOOL98_242 1
# define BOOST_PP_BOOL98_243 1
# define BOOST_PP_BOOL98_244 1
# define BOOST_PP_BOOL98_245 1
# define BOOST_PP_BOOL98_246 1
# define BOOST_PP_BOOL98_247 1
# define BOOST_PP_BOOL98_248 1
# define BOOST_PP_BOOL98_249 1
# define BOOST_PP_BOOL98_250 1
# define BOOST_PP_BOOL98_251 1
# define BOOST_PP_BOOL98_252 1
# define BOOST_PP_BOOL98_253 1
# define BOOST_PP_BOOL98_254 1
# define BOOST_PP_BOOL98_255 1
# define BOOST_PP_BOOL98_256 1