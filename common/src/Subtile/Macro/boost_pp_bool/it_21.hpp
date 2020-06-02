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
# /* BOOST_PP_BOOL33 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL33(x) BOOST_PP_BOOL33_I(x)
# else
#    define BOOST_PP_BOOL33(x) BOOST_PP_BOOL33_OO((x))
#    define BOOST_PP_BOOL33_OO(par) BOOST_PP_BOOL33_I ## par
# endif
#
# define BOOST_PP_BOOL33_I(x) BOOST_PP_BOOL33_ ## x
#
# define BOOST_PP_BOOL33_0 0
# define BOOST_PP_BOOL33_1 1
# define BOOST_PP_BOOL33_2 1
# define BOOST_PP_BOOL33_3 1
# define BOOST_PP_BOOL33_4 1
# define BOOST_PP_BOOL33_5 1
# define BOOST_PP_BOOL33_6 1
# define BOOST_PP_BOOL33_7 1
# define BOOST_PP_BOOL33_8 1
# define BOOST_PP_BOOL33_9 1
# define BOOST_PP_BOOL33_10 1
# define BOOST_PP_BOOL33_11 1
# define BOOST_PP_BOOL33_12 1
# define BOOST_PP_BOOL33_13 1
# define BOOST_PP_BOOL33_14 1
# define BOOST_PP_BOOL33_15 1
# define BOOST_PP_BOOL33_16 1
# define BOOST_PP_BOOL33_17 1
# define BOOST_PP_BOOL33_18 1
# define BOOST_PP_BOOL33_19 1
# define BOOST_PP_BOOL33_20 1
# define BOOST_PP_BOOL33_21 1
# define BOOST_PP_BOOL33_22 1
# define BOOST_PP_BOOL33_23 1
# define BOOST_PP_BOOL33_24 1
# define BOOST_PP_BOOL33_25 1
# define BOOST_PP_BOOL33_26 1
# define BOOST_PP_BOOL33_27 1
# define BOOST_PP_BOOL33_28 1
# define BOOST_PP_BOOL33_29 1
# define BOOST_PP_BOOL33_30 1
# define BOOST_PP_BOOL33_31 1
# define BOOST_PP_BOOL33_32 1
# define BOOST_PP_BOOL33_33 1
# define BOOST_PP_BOOL33_34 1
# define BOOST_PP_BOOL33_35 1
# define BOOST_PP_BOOL33_36 1
# define BOOST_PP_BOOL33_37 1
# define BOOST_PP_BOOL33_38 1
# define BOOST_PP_BOOL33_39 1
# define BOOST_PP_BOOL33_40 1
# define BOOST_PP_BOOL33_41 1
# define BOOST_PP_BOOL33_42 1
# define BOOST_PP_BOOL33_43 1
# define BOOST_PP_BOOL33_44 1
# define BOOST_PP_BOOL33_45 1
# define BOOST_PP_BOOL33_46 1
# define BOOST_PP_BOOL33_47 1
# define BOOST_PP_BOOL33_48 1
# define BOOST_PP_BOOL33_49 1
# define BOOST_PP_BOOL33_50 1
# define BOOST_PP_BOOL33_51 1
# define BOOST_PP_BOOL33_52 1
# define BOOST_PP_BOOL33_53 1
# define BOOST_PP_BOOL33_54 1
# define BOOST_PP_BOOL33_55 1
# define BOOST_PP_BOOL33_56 1
# define BOOST_PP_BOOL33_57 1
# define BOOST_PP_BOOL33_58 1
# define BOOST_PP_BOOL33_59 1
# define BOOST_PP_BOOL33_60 1
# define BOOST_PP_BOOL33_61 1
# define BOOST_PP_BOOL33_62 1
# define BOOST_PP_BOOL33_63 1
# define BOOST_PP_BOOL33_64 1
# define BOOST_PP_BOOL33_65 1
# define BOOST_PP_BOOL33_66 1
# define BOOST_PP_BOOL33_67 1
# define BOOST_PP_BOOL33_68 1
# define BOOST_PP_BOOL33_69 1
# define BOOST_PP_BOOL33_70 1
# define BOOST_PP_BOOL33_71 1
# define BOOST_PP_BOOL33_72 1
# define BOOST_PP_BOOL33_73 1
# define BOOST_PP_BOOL33_74 1
# define BOOST_PP_BOOL33_75 1
# define BOOST_PP_BOOL33_76 1
# define BOOST_PP_BOOL33_77 1
# define BOOST_PP_BOOL33_78 1
# define BOOST_PP_BOOL33_79 1
# define BOOST_PP_BOOL33_80 1
# define BOOST_PP_BOOL33_81 1
# define BOOST_PP_BOOL33_82 1
# define BOOST_PP_BOOL33_83 1
# define BOOST_PP_BOOL33_84 1
# define BOOST_PP_BOOL33_85 1
# define BOOST_PP_BOOL33_86 1
# define BOOST_PP_BOOL33_87 1
# define BOOST_PP_BOOL33_88 1
# define BOOST_PP_BOOL33_89 1
# define BOOST_PP_BOOL33_90 1
# define BOOST_PP_BOOL33_91 1
# define BOOST_PP_BOOL33_92 1
# define BOOST_PP_BOOL33_93 1
# define BOOST_PP_BOOL33_94 1
# define BOOST_PP_BOOL33_95 1
# define BOOST_PP_BOOL33_96 1
# define BOOST_PP_BOOL33_97 1
# define BOOST_PP_BOOL33_98 1
# define BOOST_PP_BOOL33_99 1
# define BOOST_PP_BOOL33_100 1
# define BOOST_PP_BOOL33_101 1
# define BOOST_PP_BOOL33_102 1
# define BOOST_PP_BOOL33_103 1
# define BOOST_PP_BOOL33_104 1
# define BOOST_PP_BOOL33_105 1
# define BOOST_PP_BOOL33_106 1
# define BOOST_PP_BOOL33_107 1
# define BOOST_PP_BOOL33_108 1
# define BOOST_PP_BOOL33_109 1
# define BOOST_PP_BOOL33_110 1
# define BOOST_PP_BOOL33_111 1
# define BOOST_PP_BOOL33_112 1
# define BOOST_PP_BOOL33_113 1
# define BOOST_PP_BOOL33_114 1
# define BOOST_PP_BOOL33_115 1
# define BOOST_PP_BOOL33_116 1
# define BOOST_PP_BOOL33_117 1
# define BOOST_PP_BOOL33_118 1
# define BOOST_PP_BOOL33_119 1
# define BOOST_PP_BOOL33_120 1
# define BOOST_PP_BOOL33_121 1
# define BOOST_PP_BOOL33_122 1
# define BOOST_PP_BOOL33_123 1
# define BOOST_PP_BOOL33_124 1
# define BOOST_PP_BOOL33_125 1
# define BOOST_PP_BOOL33_126 1
# define BOOST_PP_BOOL33_127 1
# define BOOST_PP_BOOL33_128 1
# define BOOST_PP_BOOL33_129 1
# define BOOST_PP_BOOL33_130 1
# define BOOST_PP_BOOL33_131 1
# define BOOST_PP_BOOL33_132 1
# define BOOST_PP_BOOL33_133 1
# define BOOST_PP_BOOL33_134 1
# define BOOST_PP_BOOL33_135 1
# define BOOST_PP_BOOL33_136 1
# define BOOST_PP_BOOL33_137 1
# define BOOST_PP_BOOL33_138 1
# define BOOST_PP_BOOL33_139 1
# define BOOST_PP_BOOL33_140 1
# define BOOST_PP_BOOL33_141 1
# define BOOST_PP_BOOL33_142 1
# define BOOST_PP_BOOL33_143 1
# define BOOST_PP_BOOL33_144 1
# define BOOST_PP_BOOL33_145 1
# define BOOST_PP_BOOL33_146 1
# define BOOST_PP_BOOL33_147 1
# define BOOST_PP_BOOL33_148 1
# define BOOST_PP_BOOL33_149 1
# define BOOST_PP_BOOL33_150 1
# define BOOST_PP_BOOL33_151 1
# define BOOST_PP_BOOL33_152 1
# define BOOST_PP_BOOL33_153 1
# define BOOST_PP_BOOL33_154 1
# define BOOST_PP_BOOL33_155 1
# define BOOST_PP_BOOL33_156 1
# define BOOST_PP_BOOL33_157 1
# define BOOST_PP_BOOL33_158 1
# define BOOST_PP_BOOL33_159 1
# define BOOST_PP_BOOL33_160 1
# define BOOST_PP_BOOL33_161 1
# define BOOST_PP_BOOL33_162 1
# define BOOST_PP_BOOL33_163 1
# define BOOST_PP_BOOL33_164 1
# define BOOST_PP_BOOL33_165 1
# define BOOST_PP_BOOL33_166 1
# define BOOST_PP_BOOL33_167 1
# define BOOST_PP_BOOL33_168 1
# define BOOST_PP_BOOL33_169 1
# define BOOST_PP_BOOL33_170 1
# define BOOST_PP_BOOL33_171 1
# define BOOST_PP_BOOL33_172 1
# define BOOST_PP_BOOL33_173 1
# define BOOST_PP_BOOL33_174 1
# define BOOST_PP_BOOL33_175 1
# define BOOST_PP_BOOL33_176 1
# define BOOST_PP_BOOL33_177 1
# define BOOST_PP_BOOL33_178 1
# define BOOST_PP_BOOL33_179 1
# define BOOST_PP_BOOL33_180 1
# define BOOST_PP_BOOL33_181 1
# define BOOST_PP_BOOL33_182 1
# define BOOST_PP_BOOL33_183 1
# define BOOST_PP_BOOL33_184 1
# define BOOST_PP_BOOL33_185 1
# define BOOST_PP_BOOL33_186 1
# define BOOST_PP_BOOL33_187 1
# define BOOST_PP_BOOL33_188 1
# define BOOST_PP_BOOL33_189 1
# define BOOST_PP_BOOL33_190 1
# define BOOST_PP_BOOL33_191 1
# define BOOST_PP_BOOL33_192 1
# define BOOST_PP_BOOL33_193 1
# define BOOST_PP_BOOL33_194 1
# define BOOST_PP_BOOL33_195 1
# define BOOST_PP_BOOL33_196 1
# define BOOST_PP_BOOL33_197 1
# define BOOST_PP_BOOL33_198 1
# define BOOST_PP_BOOL33_199 1
# define BOOST_PP_BOOL33_200 1
# define BOOST_PP_BOOL33_201 1
# define BOOST_PP_BOOL33_202 1
# define BOOST_PP_BOOL33_203 1
# define BOOST_PP_BOOL33_204 1
# define BOOST_PP_BOOL33_205 1
# define BOOST_PP_BOOL33_206 1
# define BOOST_PP_BOOL33_207 1
# define BOOST_PP_BOOL33_208 1
# define BOOST_PP_BOOL33_209 1
# define BOOST_PP_BOOL33_210 1
# define BOOST_PP_BOOL33_211 1
# define BOOST_PP_BOOL33_212 1
# define BOOST_PP_BOOL33_213 1
# define BOOST_PP_BOOL33_214 1
# define BOOST_PP_BOOL33_215 1
# define BOOST_PP_BOOL33_216 1
# define BOOST_PP_BOOL33_217 1
# define BOOST_PP_BOOL33_218 1
# define BOOST_PP_BOOL33_219 1
# define BOOST_PP_BOOL33_220 1
# define BOOST_PP_BOOL33_221 1
# define BOOST_PP_BOOL33_222 1
# define BOOST_PP_BOOL33_223 1
# define BOOST_PP_BOOL33_224 1
# define BOOST_PP_BOOL33_225 1
# define BOOST_PP_BOOL33_226 1
# define BOOST_PP_BOOL33_227 1
# define BOOST_PP_BOOL33_228 1
# define BOOST_PP_BOOL33_229 1
# define BOOST_PP_BOOL33_230 1
# define BOOST_PP_BOOL33_231 1
# define BOOST_PP_BOOL33_232 1
# define BOOST_PP_BOOL33_233 1
# define BOOST_PP_BOOL33_234 1
# define BOOST_PP_BOOL33_235 1
# define BOOST_PP_BOOL33_236 1
# define BOOST_PP_BOOL33_237 1
# define BOOST_PP_BOOL33_238 1
# define BOOST_PP_BOOL33_239 1
# define BOOST_PP_BOOL33_240 1
# define BOOST_PP_BOOL33_241 1
# define BOOST_PP_BOOL33_242 1
# define BOOST_PP_BOOL33_243 1
# define BOOST_PP_BOOL33_244 1
# define BOOST_PP_BOOL33_245 1
# define BOOST_PP_BOOL33_246 1
# define BOOST_PP_BOOL33_247 1
# define BOOST_PP_BOOL33_248 1
# define BOOST_PP_BOOL33_249 1
# define BOOST_PP_BOOL33_250 1
# define BOOST_PP_BOOL33_251 1
# define BOOST_PP_BOOL33_252 1
# define BOOST_PP_BOOL33_253 1
# define BOOST_PP_BOOL33_254 1
# define BOOST_PP_BOOL33_255 1
# define BOOST_PP_BOOL33_256 1