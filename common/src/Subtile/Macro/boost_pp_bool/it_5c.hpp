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
# /* BOOST_PP_BOOL92 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL92(x) BOOST_PP_BOOL92_I(x)
# else
#    define BOOST_PP_BOOL92(x) BOOST_PP_BOOL92_OO((x))
#    define BOOST_PP_BOOL92_OO(par) BOOST_PP_BOOL92_I ## par
# endif
#
# define BOOST_PP_BOOL92_I(x) BOOST_PP_BOOL92_ ## x
#
# define BOOST_PP_BOOL92_0 0
# define BOOST_PP_BOOL92_1 1
# define BOOST_PP_BOOL92_2 1
# define BOOST_PP_BOOL92_3 1
# define BOOST_PP_BOOL92_4 1
# define BOOST_PP_BOOL92_5 1
# define BOOST_PP_BOOL92_6 1
# define BOOST_PP_BOOL92_7 1
# define BOOST_PP_BOOL92_8 1
# define BOOST_PP_BOOL92_9 1
# define BOOST_PP_BOOL92_10 1
# define BOOST_PP_BOOL92_11 1
# define BOOST_PP_BOOL92_12 1
# define BOOST_PP_BOOL92_13 1
# define BOOST_PP_BOOL92_14 1
# define BOOST_PP_BOOL92_15 1
# define BOOST_PP_BOOL92_16 1
# define BOOST_PP_BOOL92_17 1
# define BOOST_PP_BOOL92_18 1
# define BOOST_PP_BOOL92_19 1
# define BOOST_PP_BOOL92_20 1
# define BOOST_PP_BOOL92_21 1
# define BOOST_PP_BOOL92_22 1
# define BOOST_PP_BOOL92_23 1
# define BOOST_PP_BOOL92_24 1
# define BOOST_PP_BOOL92_25 1
# define BOOST_PP_BOOL92_26 1
# define BOOST_PP_BOOL92_27 1
# define BOOST_PP_BOOL92_28 1
# define BOOST_PP_BOOL92_29 1
# define BOOST_PP_BOOL92_30 1
# define BOOST_PP_BOOL92_31 1
# define BOOST_PP_BOOL92_32 1
# define BOOST_PP_BOOL92_33 1
# define BOOST_PP_BOOL92_34 1
# define BOOST_PP_BOOL92_35 1
# define BOOST_PP_BOOL92_36 1
# define BOOST_PP_BOOL92_37 1
# define BOOST_PP_BOOL92_38 1
# define BOOST_PP_BOOL92_39 1
# define BOOST_PP_BOOL92_40 1
# define BOOST_PP_BOOL92_41 1
# define BOOST_PP_BOOL92_42 1
# define BOOST_PP_BOOL92_43 1
# define BOOST_PP_BOOL92_44 1
# define BOOST_PP_BOOL92_45 1
# define BOOST_PP_BOOL92_46 1
# define BOOST_PP_BOOL92_47 1
# define BOOST_PP_BOOL92_48 1
# define BOOST_PP_BOOL92_49 1
# define BOOST_PP_BOOL92_50 1
# define BOOST_PP_BOOL92_51 1
# define BOOST_PP_BOOL92_52 1
# define BOOST_PP_BOOL92_53 1
# define BOOST_PP_BOOL92_54 1
# define BOOST_PP_BOOL92_55 1
# define BOOST_PP_BOOL92_56 1
# define BOOST_PP_BOOL92_57 1
# define BOOST_PP_BOOL92_58 1
# define BOOST_PP_BOOL92_59 1
# define BOOST_PP_BOOL92_60 1
# define BOOST_PP_BOOL92_61 1
# define BOOST_PP_BOOL92_62 1
# define BOOST_PP_BOOL92_63 1
# define BOOST_PP_BOOL92_64 1
# define BOOST_PP_BOOL92_65 1
# define BOOST_PP_BOOL92_66 1
# define BOOST_PP_BOOL92_67 1
# define BOOST_PP_BOOL92_68 1
# define BOOST_PP_BOOL92_69 1
# define BOOST_PP_BOOL92_70 1
# define BOOST_PP_BOOL92_71 1
# define BOOST_PP_BOOL92_72 1
# define BOOST_PP_BOOL92_73 1
# define BOOST_PP_BOOL92_74 1
# define BOOST_PP_BOOL92_75 1
# define BOOST_PP_BOOL92_76 1
# define BOOST_PP_BOOL92_77 1
# define BOOST_PP_BOOL92_78 1
# define BOOST_PP_BOOL92_79 1
# define BOOST_PP_BOOL92_80 1
# define BOOST_PP_BOOL92_81 1
# define BOOST_PP_BOOL92_82 1
# define BOOST_PP_BOOL92_83 1
# define BOOST_PP_BOOL92_84 1
# define BOOST_PP_BOOL92_85 1
# define BOOST_PP_BOOL92_86 1
# define BOOST_PP_BOOL92_87 1
# define BOOST_PP_BOOL92_88 1
# define BOOST_PP_BOOL92_89 1
# define BOOST_PP_BOOL92_90 1
# define BOOST_PP_BOOL92_91 1
# define BOOST_PP_BOOL92_92 1
# define BOOST_PP_BOOL92_93 1
# define BOOST_PP_BOOL92_94 1
# define BOOST_PP_BOOL92_95 1
# define BOOST_PP_BOOL92_96 1
# define BOOST_PP_BOOL92_97 1
# define BOOST_PP_BOOL92_98 1
# define BOOST_PP_BOOL92_99 1
# define BOOST_PP_BOOL92_100 1
# define BOOST_PP_BOOL92_101 1
# define BOOST_PP_BOOL92_102 1
# define BOOST_PP_BOOL92_103 1
# define BOOST_PP_BOOL92_104 1
# define BOOST_PP_BOOL92_105 1
# define BOOST_PP_BOOL92_106 1
# define BOOST_PP_BOOL92_107 1
# define BOOST_PP_BOOL92_108 1
# define BOOST_PP_BOOL92_109 1
# define BOOST_PP_BOOL92_110 1
# define BOOST_PP_BOOL92_111 1
# define BOOST_PP_BOOL92_112 1
# define BOOST_PP_BOOL92_113 1
# define BOOST_PP_BOOL92_114 1
# define BOOST_PP_BOOL92_115 1
# define BOOST_PP_BOOL92_116 1
# define BOOST_PP_BOOL92_117 1
# define BOOST_PP_BOOL92_118 1
# define BOOST_PP_BOOL92_119 1
# define BOOST_PP_BOOL92_120 1
# define BOOST_PP_BOOL92_121 1
# define BOOST_PP_BOOL92_122 1
# define BOOST_PP_BOOL92_123 1
# define BOOST_PP_BOOL92_124 1
# define BOOST_PP_BOOL92_125 1
# define BOOST_PP_BOOL92_126 1
# define BOOST_PP_BOOL92_127 1
# define BOOST_PP_BOOL92_128 1
# define BOOST_PP_BOOL92_129 1
# define BOOST_PP_BOOL92_130 1
# define BOOST_PP_BOOL92_131 1
# define BOOST_PP_BOOL92_132 1
# define BOOST_PP_BOOL92_133 1
# define BOOST_PP_BOOL92_134 1
# define BOOST_PP_BOOL92_135 1
# define BOOST_PP_BOOL92_136 1
# define BOOST_PP_BOOL92_137 1
# define BOOST_PP_BOOL92_138 1
# define BOOST_PP_BOOL92_139 1
# define BOOST_PP_BOOL92_140 1
# define BOOST_PP_BOOL92_141 1
# define BOOST_PP_BOOL92_142 1
# define BOOST_PP_BOOL92_143 1
# define BOOST_PP_BOOL92_144 1
# define BOOST_PP_BOOL92_145 1
# define BOOST_PP_BOOL92_146 1
# define BOOST_PP_BOOL92_147 1
# define BOOST_PP_BOOL92_148 1
# define BOOST_PP_BOOL92_149 1
# define BOOST_PP_BOOL92_150 1
# define BOOST_PP_BOOL92_151 1
# define BOOST_PP_BOOL92_152 1
# define BOOST_PP_BOOL92_153 1
# define BOOST_PP_BOOL92_154 1
# define BOOST_PP_BOOL92_155 1
# define BOOST_PP_BOOL92_156 1
# define BOOST_PP_BOOL92_157 1
# define BOOST_PP_BOOL92_158 1
# define BOOST_PP_BOOL92_159 1
# define BOOST_PP_BOOL92_160 1
# define BOOST_PP_BOOL92_161 1
# define BOOST_PP_BOOL92_162 1
# define BOOST_PP_BOOL92_163 1
# define BOOST_PP_BOOL92_164 1
# define BOOST_PP_BOOL92_165 1
# define BOOST_PP_BOOL92_166 1
# define BOOST_PP_BOOL92_167 1
# define BOOST_PP_BOOL92_168 1
# define BOOST_PP_BOOL92_169 1
# define BOOST_PP_BOOL92_170 1
# define BOOST_PP_BOOL92_171 1
# define BOOST_PP_BOOL92_172 1
# define BOOST_PP_BOOL92_173 1
# define BOOST_PP_BOOL92_174 1
# define BOOST_PP_BOOL92_175 1
# define BOOST_PP_BOOL92_176 1
# define BOOST_PP_BOOL92_177 1
# define BOOST_PP_BOOL92_178 1
# define BOOST_PP_BOOL92_179 1
# define BOOST_PP_BOOL92_180 1
# define BOOST_PP_BOOL92_181 1
# define BOOST_PP_BOOL92_182 1
# define BOOST_PP_BOOL92_183 1
# define BOOST_PP_BOOL92_184 1
# define BOOST_PP_BOOL92_185 1
# define BOOST_PP_BOOL92_186 1
# define BOOST_PP_BOOL92_187 1
# define BOOST_PP_BOOL92_188 1
# define BOOST_PP_BOOL92_189 1
# define BOOST_PP_BOOL92_190 1
# define BOOST_PP_BOOL92_191 1
# define BOOST_PP_BOOL92_192 1
# define BOOST_PP_BOOL92_193 1
# define BOOST_PP_BOOL92_194 1
# define BOOST_PP_BOOL92_195 1
# define BOOST_PP_BOOL92_196 1
# define BOOST_PP_BOOL92_197 1
# define BOOST_PP_BOOL92_198 1
# define BOOST_PP_BOOL92_199 1
# define BOOST_PP_BOOL92_200 1
# define BOOST_PP_BOOL92_201 1
# define BOOST_PP_BOOL92_202 1
# define BOOST_PP_BOOL92_203 1
# define BOOST_PP_BOOL92_204 1
# define BOOST_PP_BOOL92_205 1
# define BOOST_PP_BOOL92_206 1
# define BOOST_PP_BOOL92_207 1
# define BOOST_PP_BOOL92_208 1
# define BOOST_PP_BOOL92_209 1
# define BOOST_PP_BOOL92_210 1
# define BOOST_PP_BOOL92_211 1
# define BOOST_PP_BOOL92_212 1
# define BOOST_PP_BOOL92_213 1
# define BOOST_PP_BOOL92_214 1
# define BOOST_PP_BOOL92_215 1
# define BOOST_PP_BOOL92_216 1
# define BOOST_PP_BOOL92_217 1
# define BOOST_PP_BOOL92_218 1
# define BOOST_PP_BOOL92_219 1
# define BOOST_PP_BOOL92_220 1
# define BOOST_PP_BOOL92_221 1
# define BOOST_PP_BOOL92_222 1
# define BOOST_PP_BOOL92_223 1
# define BOOST_PP_BOOL92_224 1
# define BOOST_PP_BOOL92_225 1
# define BOOST_PP_BOOL92_226 1
# define BOOST_PP_BOOL92_227 1
# define BOOST_PP_BOOL92_228 1
# define BOOST_PP_BOOL92_229 1
# define BOOST_PP_BOOL92_230 1
# define BOOST_PP_BOOL92_231 1
# define BOOST_PP_BOOL92_232 1
# define BOOST_PP_BOOL92_233 1
# define BOOST_PP_BOOL92_234 1
# define BOOST_PP_BOOL92_235 1
# define BOOST_PP_BOOL92_236 1
# define BOOST_PP_BOOL92_237 1
# define BOOST_PP_BOOL92_238 1
# define BOOST_PP_BOOL92_239 1
# define BOOST_PP_BOOL92_240 1
# define BOOST_PP_BOOL92_241 1
# define BOOST_PP_BOOL92_242 1
# define BOOST_PP_BOOL92_243 1
# define BOOST_PP_BOOL92_244 1
# define BOOST_PP_BOOL92_245 1
# define BOOST_PP_BOOL92_246 1
# define BOOST_PP_BOOL92_247 1
# define BOOST_PP_BOOL92_248 1
# define BOOST_PP_BOOL92_249 1
# define BOOST_PP_BOOL92_250 1
# define BOOST_PP_BOOL92_251 1
# define BOOST_PP_BOOL92_252 1
# define BOOST_PP_BOOL92_253 1
# define BOOST_PP_BOOL92_254 1
# define BOOST_PP_BOOL92_255 1
# define BOOST_PP_BOOL92_256 1