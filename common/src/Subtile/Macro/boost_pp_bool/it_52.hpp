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
# /* BOOST_PP_BOOL82 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL82(x) BOOST_PP_BOOL82_I(x)
# else
#    define BOOST_PP_BOOL82(x) BOOST_PP_BOOL82_OO((x))
#    define BOOST_PP_BOOL82_OO(par) BOOST_PP_BOOL82_I ## par
# endif
#
# define BOOST_PP_BOOL82_I(x) BOOST_PP_BOOL82_ ## x
#
# define BOOST_PP_BOOL82_0 0
# define BOOST_PP_BOOL82_1 1
# define BOOST_PP_BOOL82_2 1
# define BOOST_PP_BOOL82_3 1
# define BOOST_PP_BOOL82_4 1
# define BOOST_PP_BOOL82_5 1
# define BOOST_PP_BOOL82_6 1
# define BOOST_PP_BOOL82_7 1
# define BOOST_PP_BOOL82_8 1
# define BOOST_PP_BOOL82_9 1
# define BOOST_PP_BOOL82_10 1
# define BOOST_PP_BOOL82_11 1
# define BOOST_PP_BOOL82_12 1
# define BOOST_PP_BOOL82_13 1
# define BOOST_PP_BOOL82_14 1
# define BOOST_PP_BOOL82_15 1
# define BOOST_PP_BOOL82_16 1
# define BOOST_PP_BOOL82_17 1
# define BOOST_PP_BOOL82_18 1
# define BOOST_PP_BOOL82_19 1
# define BOOST_PP_BOOL82_20 1
# define BOOST_PP_BOOL82_21 1
# define BOOST_PP_BOOL82_22 1
# define BOOST_PP_BOOL82_23 1
# define BOOST_PP_BOOL82_24 1
# define BOOST_PP_BOOL82_25 1
# define BOOST_PP_BOOL82_26 1
# define BOOST_PP_BOOL82_27 1
# define BOOST_PP_BOOL82_28 1
# define BOOST_PP_BOOL82_29 1
# define BOOST_PP_BOOL82_30 1
# define BOOST_PP_BOOL82_31 1
# define BOOST_PP_BOOL82_32 1
# define BOOST_PP_BOOL82_33 1
# define BOOST_PP_BOOL82_34 1
# define BOOST_PP_BOOL82_35 1
# define BOOST_PP_BOOL82_36 1
# define BOOST_PP_BOOL82_37 1
# define BOOST_PP_BOOL82_38 1
# define BOOST_PP_BOOL82_39 1
# define BOOST_PP_BOOL82_40 1
# define BOOST_PP_BOOL82_41 1
# define BOOST_PP_BOOL82_42 1
# define BOOST_PP_BOOL82_43 1
# define BOOST_PP_BOOL82_44 1
# define BOOST_PP_BOOL82_45 1
# define BOOST_PP_BOOL82_46 1
# define BOOST_PP_BOOL82_47 1
# define BOOST_PP_BOOL82_48 1
# define BOOST_PP_BOOL82_49 1
# define BOOST_PP_BOOL82_50 1
# define BOOST_PP_BOOL82_51 1
# define BOOST_PP_BOOL82_52 1
# define BOOST_PP_BOOL82_53 1
# define BOOST_PP_BOOL82_54 1
# define BOOST_PP_BOOL82_55 1
# define BOOST_PP_BOOL82_56 1
# define BOOST_PP_BOOL82_57 1
# define BOOST_PP_BOOL82_58 1
# define BOOST_PP_BOOL82_59 1
# define BOOST_PP_BOOL82_60 1
# define BOOST_PP_BOOL82_61 1
# define BOOST_PP_BOOL82_62 1
# define BOOST_PP_BOOL82_63 1
# define BOOST_PP_BOOL82_64 1
# define BOOST_PP_BOOL82_65 1
# define BOOST_PP_BOOL82_66 1
# define BOOST_PP_BOOL82_67 1
# define BOOST_PP_BOOL82_68 1
# define BOOST_PP_BOOL82_69 1
# define BOOST_PP_BOOL82_70 1
# define BOOST_PP_BOOL82_71 1
# define BOOST_PP_BOOL82_72 1
# define BOOST_PP_BOOL82_73 1
# define BOOST_PP_BOOL82_74 1
# define BOOST_PP_BOOL82_75 1
# define BOOST_PP_BOOL82_76 1
# define BOOST_PP_BOOL82_77 1
# define BOOST_PP_BOOL82_78 1
# define BOOST_PP_BOOL82_79 1
# define BOOST_PP_BOOL82_80 1
# define BOOST_PP_BOOL82_81 1
# define BOOST_PP_BOOL82_82 1
# define BOOST_PP_BOOL82_83 1
# define BOOST_PP_BOOL82_84 1
# define BOOST_PP_BOOL82_85 1
# define BOOST_PP_BOOL82_86 1
# define BOOST_PP_BOOL82_87 1
# define BOOST_PP_BOOL82_88 1
# define BOOST_PP_BOOL82_89 1
# define BOOST_PP_BOOL82_90 1
# define BOOST_PP_BOOL82_91 1
# define BOOST_PP_BOOL82_92 1
# define BOOST_PP_BOOL82_93 1
# define BOOST_PP_BOOL82_94 1
# define BOOST_PP_BOOL82_95 1
# define BOOST_PP_BOOL82_96 1
# define BOOST_PP_BOOL82_97 1
# define BOOST_PP_BOOL82_98 1
# define BOOST_PP_BOOL82_99 1
# define BOOST_PP_BOOL82_100 1
# define BOOST_PP_BOOL82_101 1
# define BOOST_PP_BOOL82_102 1
# define BOOST_PP_BOOL82_103 1
# define BOOST_PP_BOOL82_104 1
# define BOOST_PP_BOOL82_105 1
# define BOOST_PP_BOOL82_106 1
# define BOOST_PP_BOOL82_107 1
# define BOOST_PP_BOOL82_108 1
# define BOOST_PP_BOOL82_109 1
# define BOOST_PP_BOOL82_110 1
# define BOOST_PP_BOOL82_111 1
# define BOOST_PP_BOOL82_112 1
# define BOOST_PP_BOOL82_113 1
# define BOOST_PP_BOOL82_114 1
# define BOOST_PP_BOOL82_115 1
# define BOOST_PP_BOOL82_116 1
# define BOOST_PP_BOOL82_117 1
# define BOOST_PP_BOOL82_118 1
# define BOOST_PP_BOOL82_119 1
# define BOOST_PP_BOOL82_120 1
# define BOOST_PP_BOOL82_121 1
# define BOOST_PP_BOOL82_122 1
# define BOOST_PP_BOOL82_123 1
# define BOOST_PP_BOOL82_124 1
# define BOOST_PP_BOOL82_125 1
# define BOOST_PP_BOOL82_126 1
# define BOOST_PP_BOOL82_127 1
# define BOOST_PP_BOOL82_128 1
# define BOOST_PP_BOOL82_129 1
# define BOOST_PP_BOOL82_130 1
# define BOOST_PP_BOOL82_131 1
# define BOOST_PP_BOOL82_132 1
# define BOOST_PP_BOOL82_133 1
# define BOOST_PP_BOOL82_134 1
# define BOOST_PP_BOOL82_135 1
# define BOOST_PP_BOOL82_136 1
# define BOOST_PP_BOOL82_137 1
# define BOOST_PP_BOOL82_138 1
# define BOOST_PP_BOOL82_139 1
# define BOOST_PP_BOOL82_140 1
# define BOOST_PP_BOOL82_141 1
# define BOOST_PP_BOOL82_142 1
# define BOOST_PP_BOOL82_143 1
# define BOOST_PP_BOOL82_144 1
# define BOOST_PP_BOOL82_145 1
# define BOOST_PP_BOOL82_146 1
# define BOOST_PP_BOOL82_147 1
# define BOOST_PP_BOOL82_148 1
# define BOOST_PP_BOOL82_149 1
# define BOOST_PP_BOOL82_150 1
# define BOOST_PP_BOOL82_151 1
# define BOOST_PP_BOOL82_152 1
# define BOOST_PP_BOOL82_153 1
# define BOOST_PP_BOOL82_154 1
# define BOOST_PP_BOOL82_155 1
# define BOOST_PP_BOOL82_156 1
# define BOOST_PP_BOOL82_157 1
# define BOOST_PP_BOOL82_158 1
# define BOOST_PP_BOOL82_159 1
# define BOOST_PP_BOOL82_160 1
# define BOOST_PP_BOOL82_161 1
# define BOOST_PP_BOOL82_162 1
# define BOOST_PP_BOOL82_163 1
# define BOOST_PP_BOOL82_164 1
# define BOOST_PP_BOOL82_165 1
# define BOOST_PP_BOOL82_166 1
# define BOOST_PP_BOOL82_167 1
# define BOOST_PP_BOOL82_168 1
# define BOOST_PP_BOOL82_169 1
# define BOOST_PP_BOOL82_170 1
# define BOOST_PP_BOOL82_171 1
# define BOOST_PP_BOOL82_172 1
# define BOOST_PP_BOOL82_173 1
# define BOOST_PP_BOOL82_174 1
# define BOOST_PP_BOOL82_175 1
# define BOOST_PP_BOOL82_176 1
# define BOOST_PP_BOOL82_177 1
# define BOOST_PP_BOOL82_178 1
# define BOOST_PP_BOOL82_179 1
# define BOOST_PP_BOOL82_180 1
# define BOOST_PP_BOOL82_181 1
# define BOOST_PP_BOOL82_182 1
# define BOOST_PP_BOOL82_183 1
# define BOOST_PP_BOOL82_184 1
# define BOOST_PP_BOOL82_185 1
# define BOOST_PP_BOOL82_186 1
# define BOOST_PP_BOOL82_187 1
# define BOOST_PP_BOOL82_188 1
# define BOOST_PP_BOOL82_189 1
# define BOOST_PP_BOOL82_190 1
# define BOOST_PP_BOOL82_191 1
# define BOOST_PP_BOOL82_192 1
# define BOOST_PP_BOOL82_193 1
# define BOOST_PP_BOOL82_194 1
# define BOOST_PP_BOOL82_195 1
# define BOOST_PP_BOOL82_196 1
# define BOOST_PP_BOOL82_197 1
# define BOOST_PP_BOOL82_198 1
# define BOOST_PP_BOOL82_199 1
# define BOOST_PP_BOOL82_200 1
# define BOOST_PP_BOOL82_201 1
# define BOOST_PP_BOOL82_202 1
# define BOOST_PP_BOOL82_203 1
# define BOOST_PP_BOOL82_204 1
# define BOOST_PP_BOOL82_205 1
# define BOOST_PP_BOOL82_206 1
# define BOOST_PP_BOOL82_207 1
# define BOOST_PP_BOOL82_208 1
# define BOOST_PP_BOOL82_209 1
# define BOOST_PP_BOOL82_210 1
# define BOOST_PP_BOOL82_211 1
# define BOOST_PP_BOOL82_212 1
# define BOOST_PP_BOOL82_213 1
# define BOOST_PP_BOOL82_214 1
# define BOOST_PP_BOOL82_215 1
# define BOOST_PP_BOOL82_216 1
# define BOOST_PP_BOOL82_217 1
# define BOOST_PP_BOOL82_218 1
# define BOOST_PP_BOOL82_219 1
# define BOOST_PP_BOOL82_220 1
# define BOOST_PP_BOOL82_221 1
# define BOOST_PP_BOOL82_222 1
# define BOOST_PP_BOOL82_223 1
# define BOOST_PP_BOOL82_224 1
# define BOOST_PP_BOOL82_225 1
# define BOOST_PP_BOOL82_226 1
# define BOOST_PP_BOOL82_227 1
# define BOOST_PP_BOOL82_228 1
# define BOOST_PP_BOOL82_229 1
# define BOOST_PP_BOOL82_230 1
# define BOOST_PP_BOOL82_231 1
# define BOOST_PP_BOOL82_232 1
# define BOOST_PP_BOOL82_233 1
# define BOOST_PP_BOOL82_234 1
# define BOOST_PP_BOOL82_235 1
# define BOOST_PP_BOOL82_236 1
# define BOOST_PP_BOOL82_237 1
# define BOOST_PP_BOOL82_238 1
# define BOOST_PP_BOOL82_239 1
# define BOOST_PP_BOOL82_240 1
# define BOOST_PP_BOOL82_241 1
# define BOOST_PP_BOOL82_242 1
# define BOOST_PP_BOOL82_243 1
# define BOOST_PP_BOOL82_244 1
# define BOOST_PP_BOOL82_245 1
# define BOOST_PP_BOOL82_246 1
# define BOOST_PP_BOOL82_247 1
# define BOOST_PP_BOOL82_248 1
# define BOOST_PP_BOOL82_249 1
# define BOOST_PP_BOOL82_250 1
# define BOOST_PP_BOOL82_251 1
# define BOOST_PP_BOOL82_252 1
# define BOOST_PP_BOOL82_253 1
# define BOOST_PP_BOOL82_254 1
# define BOOST_PP_BOOL82_255 1
# define BOOST_PP_BOOL82_256 1