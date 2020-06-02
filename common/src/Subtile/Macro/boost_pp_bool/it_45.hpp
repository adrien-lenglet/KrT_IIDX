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
# /* BOOST_PP_BOOL69 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL69(x) BOOST_PP_BOOL69_I(x)
# else
#    define BOOST_PP_BOOL69(x) BOOST_PP_BOOL69_OO((x))
#    define BOOST_PP_BOOL69_OO(par) BOOST_PP_BOOL69_I ## par
# endif
#
# define BOOST_PP_BOOL69_I(x) BOOST_PP_BOOL69_ ## x
#
# define BOOST_PP_BOOL69_0 0
# define BOOST_PP_BOOL69_1 1
# define BOOST_PP_BOOL69_2 1
# define BOOST_PP_BOOL69_3 1
# define BOOST_PP_BOOL69_4 1
# define BOOST_PP_BOOL69_5 1
# define BOOST_PP_BOOL69_6 1
# define BOOST_PP_BOOL69_7 1
# define BOOST_PP_BOOL69_8 1
# define BOOST_PP_BOOL69_9 1
# define BOOST_PP_BOOL69_10 1
# define BOOST_PP_BOOL69_11 1
# define BOOST_PP_BOOL69_12 1
# define BOOST_PP_BOOL69_13 1
# define BOOST_PP_BOOL69_14 1
# define BOOST_PP_BOOL69_15 1
# define BOOST_PP_BOOL69_16 1
# define BOOST_PP_BOOL69_17 1
# define BOOST_PP_BOOL69_18 1
# define BOOST_PP_BOOL69_19 1
# define BOOST_PP_BOOL69_20 1
# define BOOST_PP_BOOL69_21 1
# define BOOST_PP_BOOL69_22 1
# define BOOST_PP_BOOL69_23 1
# define BOOST_PP_BOOL69_24 1
# define BOOST_PP_BOOL69_25 1
# define BOOST_PP_BOOL69_26 1
# define BOOST_PP_BOOL69_27 1
# define BOOST_PP_BOOL69_28 1
# define BOOST_PP_BOOL69_29 1
# define BOOST_PP_BOOL69_30 1
# define BOOST_PP_BOOL69_31 1
# define BOOST_PP_BOOL69_32 1
# define BOOST_PP_BOOL69_33 1
# define BOOST_PP_BOOL69_34 1
# define BOOST_PP_BOOL69_35 1
# define BOOST_PP_BOOL69_36 1
# define BOOST_PP_BOOL69_37 1
# define BOOST_PP_BOOL69_38 1
# define BOOST_PP_BOOL69_39 1
# define BOOST_PP_BOOL69_40 1
# define BOOST_PP_BOOL69_41 1
# define BOOST_PP_BOOL69_42 1
# define BOOST_PP_BOOL69_43 1
# define BOOST_PP_BOOL69_44 1
# define BOOST_PP_BOOL69_45 1
# define BOOST_PP_BOOL69_46 1
# define BOOST_PP_BOOL69_47 1
# define BOOST_PP_BOOL69_48 1
# define BOOST_PP_BOOL69_49 1
# define BOOST_PP_BOOL69_50 1
# define BOOST_PP_BOOL69_51 1
# define BOOST_PP_BOOL69_52 1
# define BOOST_PP_BOOL69_53 1
# define BOOST_PP_BOOL69_54 1
# define BOOST_PP_BOOL69_55 1
# define BOOST_PP_BOOL69_56 1
# define BOOST_PP_BOOL69_57 1
# define BOOST_PP_BOOL69_58 1
# define BOOST_PP_BOOL69_59 1
# define BOOST_PP_BOOL69_60 1
# define BOOST_PP_BOOL69_61 1
# define BOOST_PP_BOOL69_62 1
# define BOOST_PP_BOOL69_63 1
# define BOOST_PP_BOOL69_64 1
# define BOOST_PP_BOOL69_65 1
# define BOOST_PP_BOOL69_66 1
# define BOOST_PP_BOOL69_67 1
# define BOOST_PP_BOOL69_68 1
# define BOOST_PP_BOOL69_69 1
# define BOOST_PP_BOOL69_70 1
# define BOOST_PP_BOOL69_71 1
# define BOOST_PP_BOOL69_72 1
# define BOOST_PP_BOOL69_73 1
# define BOOST_PP_BOOL69_74 1
# define BOOST_PP_BOOL69_75 1
# define BOOST_PP_BOOL69_76 1
# define BOOST_PP_BOOL69_77 1
# define BOOST_PP_BOOL69_78 1
# define BOOST_PP_BOOL69_79 1
# define BOOST_PP_BOOL69_80 1
# define BOOST_PP_BOOL69_81 1
# define BOOST_PP_BOOL69_82 1
# define BOOST_PP_BOOL69_83 1
# define BOOST_PP_BOOL69_84 1
# define BOOST_PP_BOOL69_85 1
# define BOOST_PP_BOOL69_86 1
# define BOOST_PP_BOOL69_87 1
# define BOOST_PP_BOOL69_88 1
# define BOOST_PP_BOOL69_89 1
# define BOOST_PP_BOOL69_90 1
# define BOOST_PP_BOOL69_91 1
# define BOOST_PP_BOOL69_92 1
# define BOOST_PP_BOOL69_93 1
# define BOOST_PP_BOOL69_94 1
# define BOOST_PP_BOOL69_95 1
# define BOOST_PP_BOOL69_96 1
# define BOOST_PP_BOOL69_97 1
# define BOOST_PP_BOOL69_98 1
# define BOOST_PP_BOOL69_99 1
# define BOOST_PP_BOOL69_100 1
# define BOOST_PP_BOOL69_101 1
# define BOOST_PP_BOOL69_102 1
# define BOOST_PP_BOOL69_103 1
# define BOOST_PP_BOOL69_104 1
# define BOOST_PP_BOOL69_105 1
# define BOOST_PP_BOOL69_106 1
# define BOOST_PP_BOOL69_107 1
# define BOOST_PP_BOOL69_108 1
# define BOOST_PP_BOOL69_109 1
# define BOOST_PP_BOOL69_110 1
# define BOOST_PP_BOOL69_111 1
# define BOOST_PP_BOOL69_112 1
# define BOOST_PP_BOOL69_113 1
# define BOOST_PP_BOOL69_114 1
# define BOOST_PP_BOOL69_115 1
# define BOOST_PP_BOOL69_116 1
# define BOOST_PP_BOOL69_117 1
# define BOOST_PP_BOOL69_118 1
# define BOOST_PP_BOOL69_119 1
# define BOOST_PP_BOOL69_120 1
# define BOOST_PP_BOOL69_121 1
# define BOOST_PP_BOOL69_122 1
# define BOOST_PP_BOOL69_123 1
# define BOOST_PP_BOOL69_124 1
# define BOOST_PP_BOOL69_125 1
# define BOOST_PP_BOOL69_126 1
# define BOOST_PP_BOOL69_127 1
# define BOOST_PP_BOOL69_128 1
# define BOOST_PP_BOOL69_129 1
# define BOOST_PP_BOOL69_130 1
# define BOOST_PP_BOOL69_131 1
# define BOOST_PP_BOOL69_132 1
# define BOOST_PP_BOOL69_133 1
# define BOOST_PP_BOOL69_134 1
# define BOOST_PP_BOOL69_135 1
# define BOOST_PP_BOOL69_136 1
# define BOOST_PP_BOOL69_137 1
# define BOOST_PP_BOOL69_138 1
# define BOOST_PP_BOOL69_139 1
# define BOOST_PP_BOOL69_140 1
# define BOOST_PP_BOOL69_141 1
# define BOOST_PP_BOOL69_142 1
# define BOOST_PP_BOOL69_143 1
# define BOOST_PP_BOOL69_144 1
# define BOOST_PP_BOOL69_145 1
# define BOOST_PP_BOOL69_146 1
# define BOOST_PP_BOOL69_147 1
# define BOOST_PP_BOOL69_148 1
# define BOOST_PP_BOOL69_149 1
# define BOOST_PP_BOOL69_150 1
# define BOOST_PP_BOOL69_151 1
# define BOOST_PP_BOOL69_152 1
# define BOOST_PP_BOOL69_153 1
# define BOOST_PP_BOOL69_154 1
# define BOOST_PP_BOOL69_155 1
# define BOOST_PP_BOOL69_156 1
# define BOOST_PP_BOOL69_157 1
# define BOOST_PP_BOOL69_158 1
# define BOOST_PP_BOOL69_159 1
# define BOOST_PP_BOOL69_160 1
# define BOOST_PP_BOOL69_161 1
# define BOOST_PP_BOOL69_162 1
# define BOOST_PP_BOOL69_163 1
# define BOOST_PP_BOOL69_164 1
# define BOOST_PP_BOOL69_165 1
# define BOOST_PP_BOOL69_166 1
# define BOOST_PP_BOOL69_167 1
# define BOOST_PP_BOOL69_168 1
# define BOOST_PP_BOOL69_169 1
# define BOOST_PP_BOOL69_170 1
# define BOOST_PP_BOOL69_171 1
# define BOOST_PP_BOOL69_172 1
# define BOOST_PP_BOOL69_173 1
# define BOOST_PP_BOOL69_174 1
# define BOOST_PP_BOOL69_175 1
# define BOOST_PP_BOOL69_176 1
# define BOOST_PP_BOOL69_177 1
# define BOOST_PP_BOOL69_178 1
# define BOOST_PP_BOOL69_179 1
# define BOOST_PP_BOOL69_180 1
# define BOOST_PP_BOOL69_181 1
# define BOOST_PP_BOOL69_182 1
# define BOOST_PP_BOOL69_183 1
# define BOOST_PP_BOOL69_184 1
# define BOOST_PP_BOOL69_185 1
# define BOOST_PP_BOOL69_186 1
# define BOOST_PP_BOOL69_187 1
# define BOOST_PP_BOOL69_188 1
# define BOOST_PP_BOOL69_189 1
# define BOOST_PP_BOOL69_190 1
# define BOOST_PP_BOOL69_191 1
# define BOOST_PP_BOOL69_192 1
# define BOOST_PP_BOOL69_193 1
# define BOOST_PP_BOOL69_194 1
# define BOOST_PP_BOOL69_195 1
# define BOOST_PP_BOOL69_196 1
# define BOOST_PP_BOOL69_197 1
# define BOOST_PP_BOOL69_198 1
# define BOOST_PP_BOOL69_199 1
# define BOOST_PP_BOOL69_200 1
# define BOOST_PP_BOOL69_201 1
# define BOOST_PP_BOOL69_202 1
# define BOOST_PP_BOOL69_203 1
# define BOOST_PP_BOOL69_204 1
# define BOOST_PP_BOOL69_205 1
# define BOOST_PP_BOOL69_206 1
# define BOOST_PP_BOOL69_207 1
# define BOOST_PP_BOOL69_208 1
# define BOOST_PP_BOOL69_209 1
# define BOOST_PP_BOOL69_210 1
# define BOOST_PP_BOOL69_211 1
# define BOOST_PP_BOOL69_212 1
# define BOOST_PP_BOOL69_213 1
# define BOOST_PP_BOOL69_214 1
# define BOOST_PP_BOOL69_215 1
# define BOOST_PP_BOOL69_216 1
# define BOOST_PP_BOOL69_217 1
# define BOOST_PP_BOOL69_218 1
# define BOOST_PP_BOOL69_219 1
# define BOOST_PP_BOOL69_220 1
# define BOOST_PP_BOOL69_221 1
# define BOOST_PP_BOOL69_222 1
# define BOOST_PP_BOOL69_223 1
# define BOOST_PP_BOOL69_224 1
# define BOOST_PP_BOOL69_225 1
# define BOOST_PP_BOOL69_226 1
# define BOOST_PP_BOOL69_227 1
# define BOOST_PP_BOOL69_228 1
# define BOOST_PP_BOOL69_229 1
# define BOOST_PP_BOOL69_230 1
# define BOOST_PP_BOOL69_231 1
# define BOOST_PP_BOOL69_232 1
# define BOOST_PP_BOOL69_233 1
# define BOOST_PP_BOOL69_234 1
# define BOOST_PP_BOOL69_235 1
# define BOOST_PP_BOOL69_236 1
# define BOOST_PP_BOOL69_237 1
# define BOOST_PP_BOOL69_238 1
# define BOOST_PP_BOOL69_239 1
# define BOOST_PP_BOOL69_240 1
# define BOOST_PP_BOOL69_241 1
# define BOOST_PP_BOOL69_242 1
# define BOOST_PP_BOOL69_243 1
# define BOOST_PP_BOOL69_244 1
# define BOOST_PP_BOOL69_245 1
# define BOOST_PP_BOOL69_246 1
# define BOOST_PP_BOOL69_247 1
# define BOOST_PP_BOOL69_248 1
# define BOOST_PP_BOOL69_249 1
# define BOOST_PP_BOOL69_250 1
# define BOOST_PP_BOOL69_251 1
# define BOOST_PP_BOOL69_252 1
# define BOOST_PP_BOOL69_253 1
# define BOOST_PP_BOOL69_254 1
# define BOOST_PP_BOOL69_255 1
# define BOOST_PP_BOOL69_256 1