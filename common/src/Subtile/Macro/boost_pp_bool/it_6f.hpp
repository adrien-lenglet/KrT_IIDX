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
# /* BOOST_PP_BOOL111 */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BOOL111(x) BOOST_PP_BOOL111_I(x)
# else
#    define BOOST_PP_BOOL111(x) BOOST_PP_BOOL111_OO((x))
#    define BOOST_PP_BOOL111_OO(par) BOOST_PP_BOOL111_I ## par
# endif
#
# define BOOST_PP_BOOL111_I(x) BOOST_PP_BOOL111_ ## x
#
# define BOOST_PP_BOOL111_0 0
# define BOOST_PP_BOOL111_1 1
# define BOOST_PP_BOOL111_2 1
# define BOOST_PP_BOOL111_3 1
# define BOOST_PP_BOOL111_4 1
# define BOOST_PP_BOOL111_5 1
# define BOOST_PP_BOOL111_6 1
# define BOOST_PP_BOOL111_7 1
# define BOOST_PP_BOOL111_8 1
# define BOOST_PP_BOOL111_9 1
# define BOOST_PP_BOOL111_10 1
# define BOOST_PP_BOOL111_11 1
# define BOOST_PP_BOOL111_12 1
# define BOOST_PP_BOOL111_13 1
# define BOOST_PP_BOOL111_14 1
# define BOOST_PP_BOOL111_15 1
# define BOOST_PP_BOOL111_16 1
# define BOOST_PP_BOOL111_17 1
# define BOOST_PP_BOOL111_18 1
# define BOOST_PP_BOOL111_19 1
# define BOOST_PP_BOOL111_20 1
# define BOOST_PP_BOOL111_21 1
# define BOOST_PP_BOOL111_22 1
# define BOOST_PP_BOOL111_23 1
# define BOOST_PP_BOOL111_24 1
# define BOOST_PP_BOOL111_25 1
# define BOOST_PP_BOOL111_26 1
# define BOOST_PP_BOOL111_27 1
# define BOOST_PP_BOOL111_28 1
# define BOOST_PP_BOOL111_29 1
# define BOOST_PP_BOOL111_30 1
# define BOOST_PP_BOOL111_31 1
# define BOOST_PP_BOOL111_32 1
# define BOOST_PP_BOOL111_33 1
# define BOOST_PP_BOOL111_34 1
# define BOOST_PP_BOOL111_35 1
# define BOOST_PP_BOOL111_36 1
# define BOOST_PP_BOOL111_37 1
# define BOOST_PP_BOOL111_38 1
# define BOOST_PP_BOOL111_39 1
# define BOOST_PP_BOOL111_40 1
# define BOOST_PP_BOOL111_41 1
# define BOOST_PP_BOOL111_42 1
# define BOOST_PP_BOOL111_43 1
# define BOOST_PP_BOOL111_44 1
# define BOOST_PP_BOOL111_45 1
# define BOOST_PP_BOOL111_46 1
# define BOOST_PP_BOOL111_47 1
# define BOOST_PP_BOOL111_48 1
# define BOOST_PP_BOOL111_49 1
# define BOOST_PP_BOOL111_50 1
# define BOOST_PP_BOOL111_51 1
# define BOOST_PP_BOOL111_52 1
# define BOOST_PP_BOOL111_53 1
# define BOOST_PP_BOOL111_54 1
# define BOOST_PP_BOOL111_55 1
# define BOOST_PP_BOOL111_56 1
# define BOOST_PP_BOOL111_57 1
# define BOOST_PP_BOOL111_58 1
# define BOOST_PP_BOOL111_59 1
# define BOOST_PP_BOOL111_60 1
# define BOOST_PP_BOOL111_61 1
# define BOOST_PP_BOOL111_62 1
# define BOOST_PP_BOOL111_63 1
# define BOOST_PP_BOOL111_64 1
# define BOOST_PP_BOOL111_65 1
# define BOOST_PP_BOOL111_66 1
# define BOOST_PP_BOOL111_67 1
# define BOOST_PP_BOOL111_68 1
# define BOOST_PP_BOOL111_69 1
# define BOOST_PP_BOOL111_70 1
# define BOOST_PP_BOOL111_71 1
# define BOOST_PP_BOOL111_72 1
# define BOOST_PP_BOOL111_73 1
# define BOOST_PP_BOOL111_74 1
# define BOOST_PP_BOOL111_75 1
# define BOOST_PP_BOOL111_76 1
# define BOOST_PP_BOOL111_77 1
# define BOOST_PP_BOOL111_78 1
# define BOOST_PP_BOOL111_79 1
# define BOOST_PP_BOOL111_80 1
# define BOOST_PP_BOOL111_81 1
# define BOOST_PP_BOOL111_82 1
# define BOOST_PP_BOOL111_83 1
# define BOOST_PP_BOOL111_84 1
# define BOOST_PP_BOOL111_85 1
# define BOOST_PP_BOOL111_86 1
# define BOOST_PP_BOOL111_87 1
# define BOOST_PP_BOOL111_88 1
# define BOOST_PP_BOOL111_89 1
# define BOOST_PP_BOOL111_90 1
# define BOOST_PP_BOOL111_91 1
# define BOOST_PP_BOOL111_92 1
# define BOOST_PP_BOOL111_93 1
# define BOOST_PP_BOOL111_94 1
# define BOOST_PP_BOOL111_95 1
# define BOOST_PP_BOOL111_96 1
# define BOOST_PP_BOOL111_97 1
# define BOOST_PP_BOOL111_98 1
# define BOOST_PP_BOOL111_99 1
# define BOOST_PP_BOOL111_100 1
# define BOOST_PP_BOOL111_101 1
# define BOOST_PP_BOOL111_102 1
# define BOOST_PP_BOOL111_103 1
# define BOOST_PP_BOOL111_104 1
# define BOOST_PP_BOOL111_105 1
# define BOOST_PP_BOOL111_106 1
# define BOOST_PP_BOOL111_107 1
# define BOOST_PP_BOOL111_108 1
# define BOOST_PP_BOOL111_109 1
# define BOOST_PP_BOOL111_110 1
# define BOOST_PP_BOOL111_111 1
# define BOOST_PP_BOOL111_112 1
# define BOOST_PP_BOOL111_113 1
# define BOOST_PP_BOOL111_114 1
# define BOOST_PP_BOOL111_115 1
# define BOOST_PP_BOOL111_116 1
# define BOOST_PP_BOOL111_117 1
# define BOOST_PP_BOOL111_118 1
# define BOOST_PP_BOOL111_119 1
# define BOOST_PP_BOOL111_120 1
# define BOOST_PP_BOOL111_121 1
# define BOOST_PP_BOOL111_122 1
# define BOOST_PP_BOOL111_123 1
# define BOOST_PP_BOOL111_124 1
# define BOOST_PP_BOOL111_125 1
# define BOOST_PP_BOOL111_126 1
# define BOOST_PP_BOOL111_127 1
# define BOOST_PP_BOOL111_128 1
# define BOOST_PP_BOOL111_129 1
# define BOOST_PP_BOOL111_130 1
# define BOOST_PP_BOOL111_131 1
# define BOOST_PP_BOOL111_132 1
# define BOOST_PP_BOOL111_133 1
# define BOOST_PP_BOOL111_134 1
# define BOOST_PP_BOOL111_135 1
# define BOOST_PP_BOOL111_136 1
# define BOOST_PP_BOOL111_137 1
# define BOOST_PP_BOOL111_138 1
# define BOOST_PP_BOOL111_139 1
# define BOOST_PP_BOOL111_140 1
# define BOOST_PP_BOOL111_141 1
# define BOOST_PP_BOOL111_142 1
# define BOOST_PP_BOOL111_143 1
# define BOOST_PP_BOOL111_144 1
# define BOOST_PP_BOOL111_145 1
# define BOOST_PP_BOOL111_146 1
# define BOOST_PP_BOOL111_147 1
# define BOOST_PP_BOOL111_148 1
# define BOOST_PP_BOOL111_149 1
# define BOOST_PP_BOOL111_150 1
# define BOOST_PP_BOOL111_151 1
# define BOOST_PP_BOOL111_152 1
# define BOOST_PP_BOOL111_153 1
# define BOOST_PP_BOOL111_154 1
# define BOOST_PP_BOOL111_155 1
# define BOOST_PP_BOOL111_156 1
# define BOOST_PP_BOOL111_157 1
# define BOOST_PP_BOOL111_158 1
# define BOOST_PP_BOOL111_159 1
# define BOOST_PP_BOOL111_160 1
# define BOOST_PP_BOOL111_161 1
# define BOOST_PP_BOOL111_162 1
# define BOOST_PP_BOOL111_163 1
# define BOOST_PP_BOOL111_164 1
# define BOOST_PP_BOOL111_165 1
# define BOOST_PP_BOOL111_166 1
# define BOOST_PP_BOOL111_167 1
# define BOOST_PP_BOOL111_168 1
# define BOOST_PP_BOOL111_169 1
# define BOOST_PP_BOOL111_170 1
# define BOOST_PP_BOOL111_171 1
# define BOOST_PP_BOOL111_172 1
# define BOOST_PP_BOOL111_173 1
# define BOOST_PP_BOOL111_174 1
# define BOOST_PP_BOOL111_175 1
# define BOOST_PP_BOOL111_176 1
# define BOOST_PP_BOOL111_177 1
# define BOOST_PP_BOOL111_178 1
# define BOOST_PP_BOOL111_179 1
# define BOOST_PP_BOOL111_180 1
# define BOOST_PP_BOOL111_181 1
# define BOOST_PP_BOOL111_182 1
# define BOOST_PP_BOOL111_183 1
# define BOOST_PP_BOOL111_184 1
# define BOOST_PP_BOOL111_185 1
# define BOOST_PP_BOOL111_186 1
# define BOOST_PP_BOOL111_187 1
# define BOOST_PP_BOOL111_188 1
# define BOOST_PP_BOOL111_189 1
# define BOOST_PP_BOOL111_190 1
# define BOOST_PP_BOOL111_191 1
# define BOOST_PP_BOOL111_192 1
# define BOOST_PP_BOOL111_193 1
# define BOOST_PP_BOOL111_194 1
# define BOOST_PP_BOOL111_195 1
# define BOOST_PP_BOOL111_196 1
# define BOOST_PP_BOOL111_197 1
# define BOOST_PP_BOOL111_198 1
# define BOOST_PP_BOOL111_199 1
# define BOOST_PP_BOOL111_200 1
# define BOOST_PP_BOOL111_201 1
# define BOOST_PP_BOOL111_202 1
# define BOOST_PP_BOOL111_203 1
# define BOOST_PP_BOOL111_204 1
# define BOOST_PP_BOOL111_205 1
# define BOOST_PP_BOOL111_206 1
# define BOOST_PP_BOOL111_207 1
# define BOOST_PP_BOOL111_208 1
# define BOOST_PP_BOOL111_209 1
# define BOOST_PP_BOOL111_210 1
# define BOOST_PP_BOOL111_211 1
# define BOOST_PP_BOOL111_212 1
# define BOOST_PP_BOOL111_213 1
# define BOOST_PP_BOOL111_214 1
# define BOOST_PP_BOOL111_215 1
# define BOOST_PP_BOOL111_216 1
# define BOOST_PP_BOOL111_217 1
# define BOOST_PP_BOOL111_218 1
# define BOOST_PP_BOOL111_219 1
# define BOOST_PP_BOOL111_220 1
# define BOOST_PP_BOOL111_221 1
# define BOOST_PP_BOOL111_222 1
# define BOOST_PP_BOOL111_223 1
# define BOOST_PP_BOOL111_224 1
# define BOOST_PP_BOOL111_225 1
# define BOOST_PP_BOOL111_226 1
# define BOOST_PP_BOOL111_227 1
# define BOOST_PP_BOOL111_228 1
# define BOOST_PP_BOOL111_229 1
# define BOOST_PP_BOOL111_230 1
# define BOOST_PP_BOOL111_231 1
# define BOOST_PP_BOOL111_232 1
# define BOOST_PP_BOOL111_233 1
# define BOOST_PP_BOOL111_234 1
# define BOOST_PP_BOOL111_235 1
# define BOOST_PP_BOOL111_236 1
# define BOOST_PP_BOOL111_237 1
# define BOOST_PP_BOOL111_238 1
# define BOOST_PP_BOOL111_239 1
# define BOOST_PP_BOOL111_240 1
# define BOOST_PP_BOOL111_241 1
# define BOOST_PP_BOOL111_242 1
# define BOOST_PP_BOOL111_243 1
# define BOOST_PP_BOOL111_244 1
# define BOOST_PP_BOOL111_245 1
# define BOOST_PP_BOOL111_246 1
# define BOOST_PP_BOOL111_247 1
# define BOOST_PP_BOOL111_248 1
# define BOOST_PP_BOOL111_249 1
# define BOOST_PP_BOOL111_250 1
# define BOOST_PP_BOOL111_251 1
# define BOOST_PP_BOOL111_252 1
# define BOOST_PP_BOOL111_253 1
# define BOOST_PP_BOOL111_254 1
# define BOOST_PP_BOOL111_255 1
# define BOOST_PP_BOOL111_256 1