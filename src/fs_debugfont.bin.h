static const uint8_t fs_debugfont_glsl[358] =
{
	0x46, 0x53, 0x48, 0x06, 0xb8, 0xbe, 0x22, 0x66, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, // FSH..."f.......s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x42, // _texColor......B
	0x01, 0x00, 0x00, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, // ...varying highp
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, //  vec4 v_color0;.
	0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, // varying highp ve
	0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x31, 0x3b, 0x0a, 0x76, 0x61, 0x72, // c4 v_color1;.var
	0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, // ying highp vec2 
	0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, // v_texcoord0;.uni
	0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x73, // form sampler2D s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, // _texColor;.void 
	0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, 0x77, 0x70, // main ().{.  lowp
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, //  vec4 tmpvar_1;.
	0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x6d, 0x69, 0x78, //   tmpvar_1 = mix
	0x20, 0x28, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x31, 0x2c, 0x20, 0x76, 0x5f, 0x63, 0x6f, //  (v_color1, v_co
	0x6c, 0x6f, 0x72, 0x30, 0x2c, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, // lor0, texture2D 
	0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2c, 0x20, 0x76, 0x5f, 0x74, // (s_texColor, v_t
	0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e, 0x78, 0x78, 0x78, 0x78, 0x29, 0x3b, // excoord0).xxxx);
	0x0a, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, // .  if ((tmpvar_1
	0x2e, 0x77, 0x20, 0x3c, 0x20, 0x30, 0x2e, 0x30, 0x30, 0x33, 0x39, 0x32, 0x31, 0x35, 0x36, 0x39, // .w < 0.003921569
	0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x64, 0x69, 0x73, 0x63, 0x61, 0x72, 0x64, // )) {.    discard
	0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, // ;.  };.  gl_Frag
	0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, // Color = tmpvar_1
	0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                             // ;.}...
};
static const uint8_t fs_debugfont_spv[1093] =
{
	0x46, 0x53, 0x48, 0x06, 0xb8, 0xbe, 0x22, 0x66, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, // FSH..."f.......s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // _texColor0......
	0x02, 0x1c, 0x04, 0x00, 0x00, 0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x08, // .......#........
	0x00, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, // ................
	0x00, 0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, // .........GLSL.st
	0x64, 0x2e, 0x34, 0x35, 0x30, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, // d.450...........
	0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x09, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // ................
	0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, // .main....i...l..
	0x00, 0x70, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, // .p...}..........
	0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x00, // ................
	0x00, 0x05, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, // .........main...
	0x00, 0x05, 0x00, 0x07, 0x00, 0x29, 0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, // .....)...s_texCo
	0x6c, 0x6f, 0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x00, 0x00, 0x00, 0x05, 0x00, 0x07, // lorSampler......
	0x00, 0x2c, 0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x54, // .,...s_texColorT
	0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x69, 0x00, 0x00, // exture.......i..
	0x00, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, // .v_color0.......
	0x00, 0x6c, 0x00, 0x00, 0x00, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x31, 0x00, 0x00, 0x00, // .l...v_color1...
	0x00, 0x05, 0x00, 0x05, 0x00, 0x70, 0x00, 0x00, 0x00, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, // .....p...v_texco
	0x6f, 0x72, 0x64, 0x30, 0x00, 0x05, 0x00, 0x06, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, // ord0.....}...bgf
	0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x00, 0x00, 0x47, 0x00, 0x04, // x_FragData0..G..
	0x00, 0x29, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, // .)...".......G..
	0x00, 0x29, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, // .)...!.......G..
	0x00, 0x2c, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, // .,...".......G..
	0x00, 0x2c, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, // .,...!.......G..
	0x00, 0x69, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, // .i...........G..
	0x00, 0x6c, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, // .l...........G..
	0x00, 0x70, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, // .p...........G..
	0x00, 0x7d, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, // .}..............
	0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // .....!..........
	0x00, 0x1a, 0x00, 0x02, 0x00, 0x06, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, // ................
	0x00, 0x20, 0x00, 0x00, 0x00, 0x19, 0x00, 0x09, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, // . ..............
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, // ................
	0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0d, 0x00, 0x00, // ................
	0x00, 0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, // ......... ...(..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, // .........;...(..
	0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x2b, 0x00, 0x00, // .)....... ...+..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x2b, 0x00, 0x00, // .........;...+..
	0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, // .,...........8..
	0x00, 0x08, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, // .....+.......`..
	0x00, 0x81, 0x80, 0x80, 0x3b, 0x14, 0x00, 0x02, 0x00, 0x61, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, // ....;....a... ..
	0x00, 0x68, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, // .h...........;..
	0x00, 0x68, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, // .h...i.......;..
	0x00, 0x68, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, // .h...l....... ..
	0x00, 0x6f, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, // .o...........;..
	0x00, 0x6f, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, // .o...p....... ..
	0x00, 0x7c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, // .|...........;..
	0x00, 0x7c, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, // .|...}.......6..
	0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, // ................
	0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, // .........=......
	0x00, 0x2a, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, // .*...)...=......
	0x00, 0x2d, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0d, 0x00, 0x00, // .-...,...=......
	0x00, 0x6a, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0d, 0x00, 0x00, // .j...i...=......
	0x00, 0x6d, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, // .m...l...=......
	0x00, 0x71, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x56, 0x00, 0x05, 0x00, 0x38, 0x00, 0x00, // .q...p...V...8..
	0x00, 0xb6, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x57, 0x00, 0x05, // .....-...*...W..
	0x00, 0x0d, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0xb6, 0x00, 0x00, 0x00, 0x71, 0x00, 0x00, // .............q..
	0x00, 0x4f, 0x00, 0x09, 0x00, 0x0d, 0x00, 0x00, 0x00, 0xa2, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, // .O..............
	0x00, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x0d, 0x00, 0x00, 0x00, 0xbd, 0x00, 0x00, // ................
	0x00, 0x01, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x6d, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x00, // .........m...j..
	0x00, 0xa2, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xa5, 0x00, 0x00, // .....Q..........
	0x00, 0xbd, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x05, 0x00, 0x61, 0x00, 0x00, // .............a..
	0x00, 0xa6, 0x00, 0x00, 0x00, 0xa5, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xf7, 0x00, 0x03, // .........`......
	0x00, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0x00, 0x04, 0x00, 0xa6, 0x00, 0x00, // ................
	0x00, 0xa8, 0x00, 0x00, 0x00, 0xa7, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0xa8, 0x00, 0x00, // ................
	0x00, 0xfc, 0x00, 0x01, 0x00, 0xf8, 0x00, 0x02, 0x00, 0xa7, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, // .............>..
	0x00, 0x7d, 0x00, 0x00, 0x00, 0xbd, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, // .}...........8..
	0x00, 0x00, 0x00, 0x00, 0x00,                                                                   // .....
};
static const uint8_t fs_debugfont_dx9[368] =
{
	0x46, 0x53, 0x48, 0x06, 0xb8, 0xbe, 0x22, 0x66, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, // FSH..."f.......s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0x4c, // _texColor0.....L
	0x01, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0xff, 0x20, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, // ......... .CTAB.
	0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x1c, // ...S............
	0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x03, // .......L...0....
	0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, // .......<.......s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0xab, 0x04, 0x00, 0x0c, 0x00, 0x01, // _texColor.......
	0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, // ...........ps_3_
	0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, // 0.Microsoft (R) 
	0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, // HLSL Shader Comp
	0x69, 0x6c, 0x65, 0x72, 0x20, 0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, 0x51, 0x00, 0x00, 0x05, 0x00, // iler 10.1..Q....
	0x00, 0x0f, 0xa0, 0x81, 0x80, 0x80, 0xbb, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0xbf, 0x00, // ................
	0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, 0x1f, // ................
	0x00, 0x00, 0x02, 0x0a, 0x00, 0x01, 0x80, 0x01, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x05, // ................
	0x00, 0x00, 0x80, 0x02, 0x00, 0x03, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x90, 0x00, // ................
	0x08, 0x0f, 0xa0, 0x42, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x02, 0x00, 0xe4, 0x90, 0x00, // ...B............
	0x08, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0x90, 0x02, // ................
	0x00, 0x00, 0x03, 0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0x81, 0x00, 0x00, 0xe4, 0x90, 0x04, // ................
	0x00, 0x00, 0x04, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x01, // ................
	0x00, 0xe4, 0x90, 0x02, 0x00, 0x00, 0x03, 0x01, 0x00, 0x01, 0x80, 0x00, 0x00, 0xff, 0x80, 0x00, // ................
	0x00, 0x00, 0xa0, 0x58, 0x00, 0x00, 0x04, 0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0x00, 0x80, 0x00, // ...X............
	0x00, 0x55, 0xa0, 0x00, 0x00, 0xaa, 0xa0, 0x41, 0x00, 0x00, 0x01, 0x01, 0x00, 0x0f, 0x80, 0x01, // .U.....A........
	0x00, 0x00, 0x02, 0x00, 0x08, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, // ................
};
static const uint8_t fs_debugfont_dx11[778] =
{
	0x46, 0x53, 0x48, 0x06, 0xb8, 0xbe, 0x22, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x02, // FSH..."f........
	0x00, 0x00, 0x44, 0x58, 0x42, 0x43, 0x1d, 0xbb, 0xb2, 0xa8, 0xff, 0x65, 0xcd, 0xa5, 0xf7, 0x85, // ..DXBC.....e....
	0xfd, 0xcb, 0xb6, 0xe1, 0x00, 0xc6, 0x01, 0x00, 0x00, 0x00, 0xf4, 0x02, 0x00, 0x00, 0x04, 0x00, // ................
	0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x34, 0x02, 0x00, 0x00, 0xc0, 0x02, // ..0...(...4.....
	0x00, 0x00, 0x41, 0x6f, 0x6e, 0x39, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, // ..Aon9..........
	0xff, 0xff, 0xc8, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, // ......(.....(...
	0x28, 0x00, 0x00, 0x00, 0x28, 0x00, 0x01, 0x00, 0x24, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, // (...(...$...(...
	0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0x51, 0x00, 0x00, 0x05, 0x00, 0x00, 0x0f, 0xa0, 0x81, 0x80, // ......Q.........
	0x80, 0xbb, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, // ................
	0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0xb0, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, // ................
	0x00, 0x80, 0x01, 0x00, 0x0f, 0xb0, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, // ................
	0x03, 0xb0, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x90, 0x00, 0x08, 0x0f, 0xa0, 0x42, 0x00, // ..............B.
	0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x02, 0x00, 0xe4, 0xb0, 0x00, 0x08, 0xe4, 0xa0, 0x01, 0x00, // ................
	0x00, 0x02, 0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0xb0, 0x02, 0x00, 0x00, 0x03, 0x01, 0x00, // ................
	0x0f, 0x80, 0x01, 0x00, 0xe4, 0x81, 0x00, 0x00, 0xe4, 0xb0, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, // ................
	0x0f, 0x80, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x01, 0x00, 0xe4, 0xb0, 0x02, 0x00, // ................
	0x00, 0x03, 0x01, 0x00, 0x01, 0x80, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0xa0, 0x58, 0x00, // ..............X.
	0x00, 0x04, 0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x55, 0xa0, 0x00, 0x00, // ............U...
	0xaa, 0xa0, 0x41, 0x00, 0x00, 0x01, 0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0x00, 0x02, 0x00, 0x08, // ..A.............
	0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, 0xff, 0xff, 0x00, 0x00, 0x53, 0x48, 0x44, 0x52, 0x04, 0x01, // ..........SHDR..
	0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x03, 0x00, 0x60, // ..@...A...Z....`
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x18, 0x00, 0x04, 0x00, 0x70, 0x10, 0x00, 0x00, 0x00, // ......X....p....
	0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x62, 0x10, 0x00, 0x03, 0xf2, 0x10, 0x10, 0x00, 0x01, 0x00, // ..UU..b.........
	0x00, 0x00, 0x62, 0x10, 0x00, 0x03, 0xf2, 0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x62, 0x10, // ..b...........b.
	0x00, 0x03, 0x32, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, // ..2.......e.... 
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x45, 0x00, // ......h.......E.
	0x00, 0x09, 0xf2, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x10, 0x10, 0x00, 0x03, 0x00, // ..........F.....
	0x00, 0x00, 0x46, 0x7e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x10, 0x00, 0x00, 0x00, // ..F~.......`....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xf2, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x1e, // ..............F.
	0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x1e, 0x10, 0x80, 0x41, 0x00, 0x00, 0x00, 0x02, 0x00, // ......F...A.....
	0x00, 0x00, 0x32, 0x00, 0x00, 0x09, 0xf2, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, // ..2.............
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x1e, // ......F.......F.
	0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x07, 0x12, 0x00, 0x10, 0x00, 0x01, 0x00, // ......1.........
	0x00, 0x00, 0x3a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x81, 0x80, // ..:........@....
	0x80, 0x3b, 0x0d, 0x00, 0x04, 0x03, 0x0a, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x36, 0x00, // .;............6.
	0x00, 0x05, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x00, 0x00, // ... ......F.....
	0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0x49, 0x53, 0x47, 0x4e, 0x84, 0x00, 0x00, 0x00, 0x04, 0x00, // ..>...ISGN......
	0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // ......h.........
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x74, 0x00, // ..............t.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, // ................
	0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, // ......t.........
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x7a, 0x00, // ..............z.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, // ................
	0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, // ......SV_POSITIO
	0x4e, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, // N.COLOR.TEXCOORD
	0x00, 0xab, 0x4f, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, // ..OSGN,.........
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, // .. .............
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, 0x52, // ..........SV_TAR
	0x47, 0x45, 0x54, 0x00, 0xab, 0xab, 0x00, 0x00, 0x00, 0x00,                                     // GET.......
};
static const uint8_t fs_debugfont_mtl[783] =
{
	0x46, 0x53, 0x48, 0x06, 0xb8, 0xbe, 0x22, 0x66, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, // FSH..."f.......s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe8, // _texColor.......
	0x02, 0x00, 0x00, 0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0x20, 0x3c, 0x6d, 0x65, 0x74, // ...#include <met
	0x61, 0x6c, 0x5f, 0x73, 0x74, 0x64, 0x6c, 0x69, 0x62, 0x3e, 0x0a, 0x23, 0x69, 0x6e, 0x63, 0x6c, // al_stdlib>.#incl
	0x75, 0x64, 0x65, 0x20, 0x3c, 0x73, 0x69, 0x6d, 0x64, 0x2f, 0x73, 0x69, 0x6d, 0x64, 0x2e, 0x68, // ude <simd/simd.h
	0x3e, 0x0a, 0x0a, 0x75, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, // >..using namespa
	0x63, 0x65, 0x20, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, // ce metal;..struc
	0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, // t xlatMtlMain_ou
	0x74, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, // t.{.    float4 b
	0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, 0x5b, 0x5b, // gfx_FragData0 [[
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, // color(0)]];.};..
	0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, // struct xlatMtlMa
	0x69, 0x6e, 0x5f, 0x69, 0x6e, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, // in_in.{.    floa
	0x74, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x20, 0x5b, 0x5b, 0x75, 0x73, // t4 v_color0 [[us
	0x65, 0x72, 0x28, 0x6c, 0x6f, 0x63, 0x6e, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, // er(locn0)]];.   
	0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x31, //  float4 v_color1
	0x20, 0x5b, 0x5b, 0x75, 0x73, 0x65, 0x72, 0x28, 0x6c, 0x6f, 0x63, 0x6e, 0x31, 0x29, 0x5d, 0x5d, //  [[user(locn1)]]
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x20, 0x76, 0x5f, 0x74, // ;.    float2 v_t
	0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x20, 0x5b, 0x5b, 0x75, 0x73, 0x65, 0x72, 0x28, // excoord0 [[user(
	0x6c, 0x6f, 0x63, 0x6e, 0x32, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x66, 0x72, // locn2)]];.};..fr
	0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, // agment xlatMtlMa
	0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, // in_out xlatMtlMa
	0x69, 0x6e, 0x28, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x69, // in(xlatMtlMain_i
	0x6e, 0x20, 0x69, 0x6e, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, 0x5f, 0x69, 0x6e, 0x5d, // n in [[stage_in]
	0x5d, 0x2c, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x64, 0x3c, 0x66, 0x6c, 0x6f, // ], texture2d<flo
	0x61, 0x74, 0x3e, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x5b, // at> s_texColor [
	0x5b, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x2c, 0x20, 0x73, // [texture(0)]], s
	0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, // ampler s_texColo
	0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, 0x5b, 0x5b, 0x73, 0x61, 0x6d, 0x70, 0x6c, // rSampler [[sampl
	0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x78, // er(0)]]).{.    x
	0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x6f, // latMtlMain_out o
	0x75, 0x74, 0x20, 0x3d, 0x20, 0x7b, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, // ut = {};.    flo
	0x61, 0x74, 0x34, 0x20, 0x5f, 0x31, 0x38, 0x31, 0x20, 0x3d, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, // at4 _181 = s_tex
	0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2e, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x28, 0x73, 0x5f, 0x74, // Color.sample(s_t
	0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2c, 0x20, // exColorSampler, 
	0x69, 0x6e, 0x2e, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x3b, // in.v_texcoord0);
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x5f, 0x31, 0x38, 0x36, // .    float4 _186
	0x20, 0x3d, 0x20, 0x6d, 0x69, 0x78, 0x28, 0x69, 0x6e, 0x2e, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, //  = mix(in.v_colo
	0x72, 0x31, 0x2c, 0x20, 0x69, 0x6e, 0x2e, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x2c, // r1, in.v_color0,
	0x20, 0x5f, 0x31, 0x38, 0x31, 0x2e, 0x78, 0x78, 0x78, 0x78, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, //  _181.xxxx);.   
	0x20, 0x69, 0x66, 0x20, 0x28, 0x5f, 0x31, 0x38, 0x36, 0x2e, 0x77, 0x20, 0x3c, 0x20, 0x30, 0x2e, //  if (_186.w < 0.
	0x30, 0x30, 0x33, 0x39, 0x32, 0x31, 0x35, 0x36, 0x38, 0x38, 0x35, 0x39, 0x33, 0x36, 0x38, 0x35, // 0039215688593685
	0x36, 0x32, 0x36, 0x39, 0x38, 0x33, 0x36, 0x34, 0x32, 0x35, 0x37, 0x38, 0x31, 0x32, 0x35, 0x29, // 626983642578125)
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x64, // .    {.        d
	0x69, 0x73, 0x63, 0x61, 0x72, 0x64, 0x5f, 0x66, 0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x28, // iscard_fragment(
	0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, // );.    }.    out
	0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, // .bgfx_FragData0 
	0x3d, 0x20, 0x5f, 0x31, 0x38, 0x36, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, // = _186;.    retu
	0x72, 0x6e, 0x20, 0x6f, 0x75, 0x74, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0x00,       // rn out;.}......
};
extern const uint8_t* fs_debugfont_pssl;
extern const uint32_t fs_debugfont_pssl_size;
