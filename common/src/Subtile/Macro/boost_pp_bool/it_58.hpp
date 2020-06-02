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
# /* BOOST_PP_BOOL88 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL88(x) BOOST_PP_BOOL88_I(x)
# else
#    define BOOST_PP_BOOL88(x) BOOST_PP_BOOL88_OO((x))
#    define BOOST_PP_BOOL88_OO(par) BOOST_PP_BOOL88_I ## par
# endif
#
# define BOOST_PP_BOOL88_I(x) BOOST_PP_BOOL88_ ## x
#
# define BOOST_PP_BOOL88_0 0
# define BOOST_PP_BOOL88_1 1
# define BOOST_PP_BOOL88_2 1
# define BOOST_PP_BOOL88_3 1
# define BOOST_PP_BOOL88_4 1
# define BOOST_PP_BOOL88_5 1
# define BOOST_PP_BOOL88_6 1
# define BOOST_PP_BOOL88_7 1
# define BOOST_PP_BOOL88_8 1
# define BOOST_PP_BOOL88_9 1
# define BOOST_PP_BOOL88_10 1
# define BOOST_PP_BOOL88_11 1
# define BOOST_PP_BOOL88_12 1
# define BOOST_PP_BOOL88_13 1
# define BOOST_PP_BOOL88_14 1
# define BOOST_PP_BOOL88_15 1
# define BOOST_PP_BOOL88_16 1
# define BOOST_PP_BOOL88_17 1
# define BOOST_PP_BOOL88_18 1
# define BOOST_PP_BOOL88_19 1
# define BOOST_PP_BOOL88_20 1
# define BOOST_PP_BOOL88_21 1
# define BOOST_PP_BOOL88_22 1
# define BOOST_PP_BOOL88_23 1
# define BOOST_PP_BOOL88_24 1
# define BOOST_PP_BOOL88_25 1
# define BOOST_PP_BOOL88_26 1
# define BOOST_PP_BOOL88_27 1
# define BOOST_PP_BOOL88_28 1
# define BOOST_PP_BOOL88_29 1
# define BOOST_PP_BOOL88_30 1
# define BOOST_PP_BOOL88_31 1
# define BOOST_PP_BOOL88_32 1
# define BOOST_PP_BOOL88_33 1
# define BOOST_PP_BOOL88_34 1
# define BOOST_PP_BOOL88_35 1
# define BOOST_PP_BOOL88_36 1
# define BOOST_PP_BOOL88_37 1
# define BOOST_PP_BOOL88_38 1
# define BOOST_PP_BOOL88_39 1
# define BOOST_PP_BOOL88_40 1
# define BOOST_PP_BOOL88_41 1
# define BOOST_PP_BOOL88_42 1
# define BOOST_PP_BOOL88_43 1
# define BOOST_PP_BOOL88_44 1
# define BOOST_PP_BOOL88_45 1
# define BOOST_PP_BOOL88_46 1
# define BOOST_PP_BOOL88_47 1
# define BOOST_PP_BOOL88_48 1
# define BOOST_PP_BOOL88_49 1
# define BOOST_PP_BOOL88_50 1
# define BOOST_PP_BOOL88_51 1
# define BOOST_PP_BOOL88_52 1
# define BOOST_PP_BOOL88_53 1
# define BOOST_PP_BOOL88_54 1
# define BOOST_PP_BOOL88_55 1
# define BOOST_PP_BOOL88_56 1
# define BOOST_PP_BOOL88_57 1
# define BOOST_PP_BOOL88_58 1
# define BOOST_PP_BOOL88_59 1
# define BOOST_PP_BOOL88_60 1
# define BOOST_PP_BOOL88_61 1
# define BOOST_PP_BOOL88_62 1
# define BOOST_PP_BOOL88_63 1
# define BOOST_PP_BOOL88_64 1
# define BOOST_PP_BOOL88_65 1
# define BOOST_PP_BOOL88_66 1
# define BOOST_PP_BOOL88_67 1
# define BOOST_PP_BOOL88_68 1
# define BOOST_PP_BOOL88_69 1
# define BOOST_PP_BOOL88_70 1
# define BOOST_PP_BOOL88_71 1
# define BOOST_PP_BOOL88_72 1
# define BOOST_PP_BOOL88_73 1
# define BOOST_PP_BOOL88_74 1
# define BOOST_PP_BOOL88_75 1
# define BOOST_PP_BOOL88_76 1
# define BOOST_PP_BOOL88_77 1
# define BOOST_PP_BOOL88_78 1
# define BOOST_PP_BOOL88_79 1
# define BOOST_PP_BOOL88_80 1
# define BOOST_PP_BOOL88_81 1
# define BOOST_PP_BOOL88_82 1
# define BOOST_PP_BOOL88_83 1
# define BOOST_PP_BOOL88_84 1
# define BOOST_PP_BOOL88_85 1
# define BOOST_PP_BOOL88_86 1
# define BOOST_PP_BOOL88_87 1
# define BOOST_PP_BOOL88_88 1
# define BOOST_PP_BOOL88_89 1
# define BOOST_PP_BOOL88_90 1
# define BOOST_PP_BOOL88_91 1
# define BOOST_PP_BOOL88_92 1
# define BOOST_PP_BOOL88_93 1
# define BOOST_PP_BOOL88_94 1
# define BOOST_PP_BOOL88_95 1
# define BOOST_PP_BOOL88_96 1
# define BOOST_PP_BOOL88_97 1
# define BOOST_PP_BOOL88_98 1
# define BOOST_PP_BOOL88_99 1
# define BOOST_PP_BOOL88_100 1
# define BOOST_PP_BOOL88_101 1
# define BOOST_PP_BOOL88_102 1
# define BOOST_PP_BOOL88_103 1
# define BOOST_PP_BOOL88_104 1
# define BOOST_PP_BOOL88_105 1
# define BOOST_PP_BOOL88_106 1
# define BOOST_PP_BOOL88_107 1
# define BOOST_PP_BOOL88_108 1
# define BOOST_PP_BOOL88_109 1
# define BOOST_PP_BOOL88_110 1
# define BOOST_PP_BOOL88_111 1
# define BOOST_PP_BOOL88_112 1
# define BOOST_PP_BOOL88_113 1
# define BOOST_PP_BOOL88_114 1
# define BOOST_PP_BOOL88_115 1
# define BOOST_PP_BOOL88_116 1
# define BOOST_PP_BOOL88_117 1
# define BOOST_PP_BOOL88_118 1
# define BOOST_PP_BOOL88_119 1
# define BOOST_PP_BOOL88_120 1
# define BOOST_PP_BOOL88_121 1
# define BOOST_PP_BOOL88_122 1
# define BOOST_PP_BOOL88_123 1
# define BOOST_PP_BOOL88_124 1
# define BOOST_PP_BOOL88_125 1
# define BOOST_PP_BOOL88_126 1
# define BOOST_PP_BOOL88_127 1
# define BOOST_PP_BOOL88_128 1
# define BOOST_PP_BOOL88_129 1
# define BOOST_PP_BOOL88_130 1
# define BOOST_PP_BOOL88_131 1
# define BOOST_PP_BOOL88_132 1
# define BOOST_PP_BOOL88_133 1
# define BOOST_PP_BOOL88_134 1
# define BOOST_PP_BOOL88_135 1
# define BOOST_PP_BOOL88_136 1
# define BOOST_PP_BOOL88_137 1
# define BOOST_PP_BOOL88_138 1
# define BOOST_PP_BOOL88_139 1
# define BOOST_PP_BOOL88_140 1
# define BOOST_PP_BOOL88_141 1
# define BOOST_PP_BOOL88_142 1
# define BOOST_PP_BOOL88_143 1
# define BOOST_PP_BOOL88_144 1
# define BOOST_PP_BOOL88_145 1
# define BOOST_PP_BOOL88_146 1
# define BOOST_PP_BOOL88_147 1
# define BOOST_PP_BOOL88_148 1
# define BOOST_PP_BOOL88_149 1
# define BOOST_PP_BOOL88_150 1
# define BOOST_PP_BOOL88_151 1
# define BOOST_PP_BOOL88_152 1
# define BOOST_PP_BOOL88_153 1
# define BOOST_PP_BOOL88_154 1
# define BOOST_PP_BOOL88_155 1
# define BOOST_PP_BOOL88_156 1
# define BOOST_PP_BOOL88_157 1
# define BOOST_PP_BOOL88_158 1
# define BOOST_PP_BOOL88_159 1
# define BOOST_PP_BOOL88_160 1
# define BOOST_PP_BOOL88_161 1
# define BOOST_PP_BOOL88_162 1
# define BOOST_PP_BOOL88_163 1
# define BOOST_PP_BOOL88_164 1
# define BOOST_PP_BOOL88_165 1
# define BOOST_PP_BOOL88_166 1
# define BOOST_PP_BOOL88_167 1
# define BOOST_PP_BOOL88_168 1
# define BOOST_PP_BOOL88_169 1
# define BOOST_PP_BOOL88_170 1
# define BOOST_PP_BOOL88_171 1
# define BOOST_PP_BOOL88_172 1
# define BOOST_PP_BOOL88_173 1
# define BOOST_PP_BOOL88_174 1
# define BOOST_PP_BOOL88_175 1
# define BOOST_PP_BOOL88_176 1
# define BOOST_PP_BOOL88_177 1
# define BOOST_PP_BOOL88_178 1
# define BOOST_PP_BOOL88_179 1
# define BOOST_PP_BOOL88_180 1
# define BOOST_PP_BOOL88_181 1
# define BOOST_PP_BOOL88_182 1
# define BOOST_PP_BOOL88_183 1
# define BOOST_PP_BOOL88_184 1
# define BOOST_PP_BOOL88_185 1
# define BOOST_PP_BOOL88_186 1
# define BOOST_PP_BOOL88_187 1
# define BOOST_PP_BOOL88_188 1
# define BOOST_PP_BOOL88_189 1
# define BOOST_PP_BOOL88_190 1
# define BOOST_PP_BOOL88_191 1
# define BOOST_PP_BOOL88_192 1
# define BOOST_PP_BOOL88_193 1
# define BOOST_PP_BOOL88_194 1
# define BOOST_PP_BOOL88_195 1
# define BOOST_PP_BOOL88_196 1
# define BOOST_PP_BOOL88_197 1
# define BOOST_PP_BOOL88_198 1
# define BOOST_PP_BOOL88_199 1
# define BOOST_PP_BOOL88_200 1
# define BOOST_PP_BOOL88_201 1
# define BOOST_PP_BOOL88_202 1
# define BOOST_PP_BOOL88_203 1
# define BOOST_PP_BOOL88_204 1
# define BOOST_PP_BOOL88_205 1
# define BOOST_PP_BOOL88_206 1
# define BOOST_PP_BOOL88_207 1
# define BOOST_PP_BOOL88_208 1
# define BOOST_PP_BOOL88_209 1
# define BOOST_PP_BOOL88_210 1
# define BOOST_PP_BOOL88_211 1
# define BOOST_PP_BOOL88_212 1
# define BOOST_PP_BOOL88_213 1
# define BOOST_PP_BOOL88_214 1
# define BOOST_PP_BOOL88_215 1
# define BOOST_PP_BOOL88_216 1
# define BOOST_PP_BOOL88_217 1
# define BOOST_PP_BOOL88_218 1
# define BOOST_PP_BOOL88_219 1
# define BOOST_PP_BOOL88_220 1
# define BOOST_PP_BOOL88_221 1
# define BOOST_PP_BOOL88_222 1
# define BOOST_PP_BOOL88_223 1
# define BOOST_PP_BOOL88_224 1
# define BOOST_PP_BOOL88_225 1
# define BOOST_PP_BOOL88_226 1
# define BOOST_PP_BOOL88_227 1
# define BOOST_PP_BOOL88_228 1
# define BOOST_PP_BOOL88_229 1
# define BOOST_PP_BOOL88_230 1
# define BOOST_PP_BOOL88_231 1
# define BOOST_PP_BOOL88_232 1
# define BOOST_PP_BOOL88_233 1
# define BOOST_PP_BOOL88_234 1
# define BOOST_PP_BOOL88_235 1
# define BOOST_PP_BOOL88_236 1
# define BOOST_PP_BOOL88_237 1
# define BOOST_PP_BOOL88_238 1
# define BOOST_PP_BOOL88_239 1
# define BOOST_PP_BOOL88_240 1
# define BOOST_PP_BOOL88_241 1
# define BOOST_PP_BOOL88_242 1
# define BOOST_PP_BOOL88_243 1
# define BOOST_PP_BOOL88_244 1
# define BOOST_PP_BOOL88_245 1
# define BOOST_PP_BOOL88_246 1
# define BOOST_PP_BOOL88_247 1
# define BOOST_PP_BOOL88_248 1
# define BOOST_PP_BOOL88_249 1
# define BOOST_PP_BOOL88_250 1
# define BOOST_PP_BOOL88_251 1
# define BOOST_PP_BOOL88_252 1
# define BOOST_PP_BOOL88_253 1
# define BOOST_PP_BOOL88_254 1
# define BOOST_PP_BOOL88_255 1
# define BOOST_PP_BOOL88_256 1