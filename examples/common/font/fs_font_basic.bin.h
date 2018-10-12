static const uint8_t fs_font_basic_glsl[557] =
{
	0x46, 0x53, 0x48, 0x05, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, // FSH............s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x09, // _texColor.......
	0x02, 0x00, 0x00, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, // ...varying highp
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, //  vec4 v_color0;.
	0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, // varying highp ve
	0x63, 0x34, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, // c4 v_texcoord0;.
	0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, 0x73, 0x61, 0x6d, // uniform lowp sam
	0x70, 0x6c, 0x65, 0x72, 0x43, 0x75, 0x62, 0x65, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, // plerCube s_texCo
	0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, // lor;.void main (
	0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, // ).{.  lowp float
	0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, 0x5b, 0x34, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, //  rgba_1[4];.  lo
	0x77, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, // wp vec4 tmpvar_2
	0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x20, 0x3d, 0x20, 0x74, // ;.  tmpvar_2 = t
	0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x43, 0x75, 0x62, 0x65, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, // extureCube (s_te
	0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, // xColor, v_texcoo
	0x72, 0x64, 0x30, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, // rd0.xyz);.  high
	0x70, 0x20, 0x69, 0x6e, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x3b, 0x0a, // p int tmpvar_3;.
	0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x69, 0x6e, 0x74, //   tmpvar_3 = int
	0x28, 0x28, 0x28, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x2e, 0x77, // (((v_texcoord0.w
	0x20, 0x2a, 0x20, 0x34, 0x2e, 0x30, 0x29, 0x20, 0x2b, 0x20, 0x30, 0x2e, 0x35, 0x29, 0x29, 0x3b, //  * 4.0) + 0.5));
	0x0a, 0x20, 0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, 0x5b, 0x30, 0x5d, 0x20, 0x3d, 0x20, 0x74, // .  rgba_1[0] = t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x7a, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x67, 0x62, // mpvar_2.z;.  rgb
	0x61, 0x5f, 0x31, 0x5b, 0x31, 0x5d, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // a_1[1] = tmpvar_
	0x32, 0x2e, 0x79, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, 0x5b, 0x32, 0x5d, // 2.y;.  rgba_1[2]
	0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x78, 0x3b, 0x0a, 0x20, //  = tmpvar_2.x;. 
	0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, 0x5b, 0x33, 0x5d, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, //  rgba_1[3] = tmp
	0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x77, 0x3b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, // var_2.w;.  lowp 
	0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x3b, 0x0a, 0x20, // vec4 tmpvar_4;. 
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, //  tmpvar_4.xyz = 
	0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x2e, 0x78, 0x79, 0x7a, 0x3b, 0x0a, 0x20, 0x20, // v_color0.xyz;.  
	0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x2e, 0x77, 0x20, 0x3d, 0x20, 0x28, 0x76, 0x5f, // tmpvar_4.w = (v_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x2e, 0x77, 0x20, 0x2a, 0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, // color0.w * rgba_
	0x31, 0x5b, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x5d, 0x29, 0x3b, 0x0a, 0x20, 0x20, // 1[tmpvar_3]);.  
	0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, // gl_FragColor = t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                   // mpvar_4;.}...
};
static const uint8_t fs_font_basic_spv[1690] =
{
	0x46, 0x53, 0x48, 0x05, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x06, // FSH.............
	0x00, 0x00, 0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x07, 0x00, 0x08, 0x00, 0xd8, 0x00, // ....#...........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, // ................
	0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, // ......GLSL.std.4
	0x35, 0x30, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // 50..............
	0x00, 0x00, 0x0f, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, // ..............ma
	0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x87, 0x00, // in....y...|.....
	0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x00, // ................
	0x03, 0x00, 0x05, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x04, 0x00, // ................
	0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x09, 0x00, // ..main..........
	0x00, 0x00, 0x42, 0x67, 0x66, 0x78, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x43, 0x75, 0x62, // ..BgfxSamplerCub
	0x65, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x5f, // e.............m_
	0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, // sampler.........
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x6d, 0x5f, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x00, // ......m_texture.
	0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x20, 0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, // ...... ...s_texC
	0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x05, 0x00, 0x07, 0x00, 0x22, 0x00, 0x00, 0x00, 0x73, 0x5f, // olor......"...s_
	0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x00, // texColorSampler.
	0x00, 0x00, 0x05, 0x00, 0x07, 0x00, 0x25, 0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, // ......%...s_texC
	0x6f, 0x6c, 0x6f, 0x72, 0x54, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x00, 0x00, 0x00, 0x05, 0x00, // olorTexture.....
	0x05, 0x00, 0x79, 0x00, 0x00, 0x00, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x00, 0x00, // ..y...v_color0..
	0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, // ......|...v_texc
	0x6f, 0x6f, 0x72, 0x64, 0x30, 0x00, 0x05, 0x00, 0x06, 0x00, 0x87, 0x00, 0x00, 0x00, 0x62, 0x67, // oord0.........bg
	0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x00, 0x00, 0x47, 0x00, // fx_FragData0..G.
	0x04, 0x00, 0x25, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, // ..%...".......G.
	0x04, 0x00, 0x25, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, // ..%...!.......G.
	0x04, 0x00, 0x79, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, // ..y...........G.
	0x04, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, // ..|...........G.
	0x04, 0x00, 0x87, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, // ................
	0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, // ......!.........
	0x00, 0x00, 0x1a, 0x00, 0x02, 0x00, 0x06, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x07, 0x00, // ................
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x19, 0x00, 0x09, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, // .. .............
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x04, 0x00, 0x09, 0x00, // ................
	0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0b, 0x00, // ................
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0d, 0x00, // ................
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x13, 0x00, // .......... .....
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x1f, 0x00, // .......... .....
	0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x1f, 0x00, // ..........;.....
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x21, 0x00, // .. ....... ...!.
	0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x21, 0x00, // ..........;...!.
	0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x24, 0x00, // .."....... ...$.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x24, 0x00, // ..........;...$.
	0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x28, 0x00, // ..%...........(.
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x28, 0x00, // .. .......+...(.
	0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x28, 0x00, // ..).......+...(.
	0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x03, 0x00, 0x31, 0x00, // ..-...........1.
	0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x4b, 0x00, 0x00, 0x00, 0x20, 0x00, // ..........K... .
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x4f, 0x00, // ......+.......O.
	0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x2b, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x51, 0x00, // .....@+.......Q.
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x2b, 0x00, 0x04, 0x00, 0x4b, 0x00, 0x00, 0x00, 0x54, 0x00, // .....?+...K...T.
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x04, 0x00, 0x55, 0x00, 0x00, 0x00, 0x07, 0x00, // ..........U.....
	0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x56, 0x00, 0x00, 0x00, 0x07, 0x00, // ..T... ...V.....
	0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, 0x00, 0x60, 0x00, // ..U...+...(...`.
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, 0x00, 0x65, 0x00, // ......+...(...e.
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x78, 0x00, 0x00, 0x00, 0x01, 0x00, // ...... ...x.....
	0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x78, 0x00, 0x00, 0x00, 0x79, 0x00, // ......;...x...y.
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x78, 0x00, 0x00, 0x00, 0x7c, 0x00, // ......;...x...|.
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x86, 0x00, 0x00, 0x00, 0x03, 0x00, // ...... .........
	0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x86, 0x00, 0x00, 0x00, 0x87, 0x00, // ......;.........
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, // ......6.........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, // ................
	0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x56, 0x00, 0x00, 0x00, 0xa1, 0x00, 0x00, 0x00, 0x07, 0x00, // ..;...V.........
	0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x22, 0x00, // ..=.......#...".
	0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x25, 0x00, // ..=.......&...%.
	0x00, 0x00, 0x50, 0x00, 0x05, 0x00, 0x09, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x23, 0x00, // ..P.......'...#.
	0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x20, 0x00, 0x00, 0x00, 0x27, 0x00, // ..&...>... ...'.
	0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x7a, 0x00, 0x00, 0x00, 0x79, 0x00, // ..=.......z...y.
	0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x7c, 0x00, // ..=.......}...|.
	0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 0x20, 0x00, // ..=........... .
	0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0xd6, 0x00, 0x00, 0x00, 0xa4, 0x00, // ..Q.............
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x08, 0x00, 0x00, 0x00, 0xd7, 0x00, // ......Q.........
	0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4f, 0x00, 0x08, 0x00, 0x0b, 0x00, // ..........O.....
	0x00, 0x00, 0xa6, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, // ......}...}.....
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x56, 0x00, 0x05, 0x00, 0x31, 0x00, // ..........V...1.
	0x00, 0x00, 0xd1, 0x00, 0x00, 0x00, 0xd7, 0x00, 0x00, 0x00, 0xd6, 0x00, 0x00, 0x00, 0x57, 0x00, // ..............W.
	0x05, 0x00, 0x0d, 0x00, 0x00, 0x00, 0xd3, 0x00, 0x00, 0x00, 0xd1, 0x00, 0x00, 0x00, 0xa6, 0x00, // ................
	0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xa9, 0x00, 0x00, 0x00, 0x7d, 0x00, // ..Q...........}.
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xaa, 0x00, // ................
	0x00, 0x00, 0xa9, 0x00, 0x00, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x81, 0x00, 0x05, 0x00, 0x07, 0x00, // ......O.........
	0x00, 0x00, 0xab, 0x00, 0x00, 0x00, 0xaa, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x6e, 0x00, // ..........Q...n.
	0x04, 0x00, 0x28, 0x00, 0x00, 0x00, 0xac, 0x00, 0x00, 0x00, 0xab, 0x00, 0x00, 0x00, 0x51, 0x00, // ..(...........Q.
	0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xae, 0x00, 0x00, 0x00, 0xd3, 0x00, 0x00, 0x00, 0x02, 0x00, // ................
	0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x13, 0x00, 0x00, 0x00, 0xaf, 0x00, 0x00, 0x00, 0xa1, 0x00, // ..A.............
	0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0xaf, 0x00, 0x00, 0x00, 0xae, 0x00, // ..-...>.........
	0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xb1, 0x00, 0x00, 0x00, 0xd3, 0x00, // ..Q.............
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x13, 0x00, 0x00, 0x00, 0xb2, 0x00, // ......A.........
	0x00, 0x00, 0xa1, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0xb2, 0x00, // ......)...>.....
	0x00, 0x00, 0xb1, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xb4, 0x00, // ......Q.........
	0x00, 0x00, 0xd3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x13, 0x00, // ..........A.....
	0x00, 0x00, 0xb5, 0x00, 0x00, 0x00, 0xa1, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x3e, 0x00, // ..........`...>.
	0x03, 0x00, 0xb5, 0x00, 0x00, 0x00, 0xb4, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x07, 0x00, // ..........Q.....
	0x00, 0x00, 0xb7, 0x00, 0x00, 0x00, 0xd3, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x41, 0x00, // ..............A.
	0x05, 0x00, 0x13, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0xa1, 0x00, 0x00, 0x00, 0x65, 0x00, // ..............e.
	0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0xb8, 0x00, 0x00, 0x00, 0xb7, 0x00, 0x00, 0x00, 0x41, 0x00, // ..>...........A.
	0x05, 0x00, 0x13, 0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0xa1, 0x00, 0x00, 0x00, 0xac, 0x00, // ................
	0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0xbb, 0x00, 0x00, 0x00, 0xba, 0x00, // ..=.............
	0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 0x7a, 0x00, // ..Q...........z.
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xc1, 0x00, // ................
	0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 0xbb, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x07, 0x00, // ..........Q.....
	0x00, 0x00, 0xc2, 0x00, 0x00, 0x00, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x00, // ......z.......Q.
	0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x00, 0x7a, 0x00, 0x00, 0x00, 0x01, 0x00, // ..........z.....
	0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xc4, 0x00, 0x00, 0x00, 0x7a, 0x00, // ..Q...........z.
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x50, 0x00, 0x07, 0x00, 0x0d, 0x00, 0x00, 0x00, 0xc5, 0x00, // ......P.........
	0x00, 0x00, 0xc2, 0x00, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x00, 0xc4, 0x00, 0x00, 0x00, 0xc1, 0x00, // ................
	0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x87, 0x00, 0x00, 0x00, 0xc5, 0x00, 0x00, 0x00, 0xfd, 0x00, // ..>.............
	0x01, 0x00, 0x38, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,                                     // ..8.......
};
static const uint8_t fs_font_basic_dx9[460] =
{
	0x46, 0x53, 0x48, 0x05, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, // FSH............s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0xa8, // _texColor0......
	0x01, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0xff, 0x20, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, // ......... .CTAB.
	0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x1c, // ...S............
	0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x03, // .......L...0....
	0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, // .......<.......s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0xab, 0x04, 0x00, 0x0e, 0x00, 0x01, // _texColor.......
	0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, // ...........ps_3_
	0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, // 0.Microsoft (R) 
	0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, // HLSL Shader Comp
	0x69, 0x6c, 0x65, 0x72, 0x20, 0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, 0x51, 0x00, 0x00, 0x05, 0x00, // iler 10.1..Q....
	0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, // ......@...?.....
	0x00, 0x80, 0x3f, 0x51, 0x00, 0x00, 0x05, 0x01, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x00, 0x80, 0x00, // ..?Q............
	0x00, 0x80, 0xbf, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x40, 0xc0, 0x1f, 0x00, 0x00, 0x02, 0x0a, // .........@......
	0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0x80, 0x01, // ................
	0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x98, 0x00, 0x08, 0x0f, 0xa0, 0x04, // ................
	0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0x80, 0x01, 0x00, 0xff, 0x90, 0x00, 0x00, 0x00, 0xa0, 0x00, // ................
	0x00, 0x55, 0xa0, 0x13, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x80, 0x58, // .U.............X
	0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x80, 0x00, 0x00, 0x55, 0x81, 0x00, 0x00, 0xaa, 0xa0, 0x00, // .........U......
	0x00, 0xff, 0xa0, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, // ................
	0x00, 0x55, 0x81, 0x58, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, // .U.X............
	0x00, 0xaa, 0xa0, 0x00, 0x00, 0xaa, 0x80, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x80, 0x00, // ................
	0x00, 0x00, 0x80, 0x00, 0x00, 0x55, 0x80, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x00, // .....U..........
	0x00, 0x00, 0x80, 0x01, 0x00, 0xe4, 0xa0, 0x58, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0f, 0x80, 0x00, // .......X........
	0x00, 0xe4, 0x8c, 0x00, 0x00, 0xff, 0xa0, 0x00, 0x00, 0xaa, 0xa0, 0x42, 0x00, 0x00, 0x03, 0x01, // ...........B....
	0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0x90, 0x00, 0x08, 0xe4, 0xa0, 0x09, 0x00, 0x00, 0x03, 0x00, // ................
	0x00, 0x01, 0x80, 0x01, 0x00, 0xc6, 0x80, 0x00, 0x00, 0xe4, 0x80, 0x05, 0x00, 0x00, 0x03, 0x00, // ................
	0x08, 0x08, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0xff, 0x90, 0x01, 0x00, 0x00, 0x02, 0x00, // ................
	0x08, 0x07, 0x80, 0x00, 0x00, 0xe4, 0x90, 0xff, 0xff, 0x00, 0x00, 0x00,                         // ............
};
static const uint8_t fs_font_basic_dx11[623] =
{
	0x46, 0x53, 0x48, 0x05, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, // FSH............s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0x48, // _texColor0.....H
	0x02, 0x00, 0x00, 0x44, 0x58, 0x42, 0x43, 0xdb, 0x69, 0x11, 0xe0, 0xc0, 0xf9, 0x23, 0x5b, 0x4d, // ...DXBC.i....#[M
	0x65, 0x8f, 0xa1, 0x99, 0x34, 0xff, 0x76, 0x01, 0x00, 0x00, 0x00, 0x48, 0x02, 0x00, 0x00, 0x03, // e...4.v....H....
	0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 0x49, // ...,...........I
	0x53, 0x47, 0x4e, 0x6c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x50, // SGNl...........P
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x62, // ...............b
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, // ................
	0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, // .......SV_POSITI
	0x4f, 0x4e, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, // ON.COLOR.TEXCOOR
	0x44, 0x00, 0xab, 0x4f, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, // D..OSGN,........
	0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, // ... ............
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, // ...........SV_TA
	0x52, 0x47, 0x45, 0x54, 0x00, 0xab, 0xab, 0x53, 0x48, 0x44, 0x52, 0x6c, 0x01, 0x00, 0x00, 0x40, // RGET...SHDRl...@
	0x00, 0x00, 0x00, 0x5b, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x03, 0x00, 0x60, 0x10, 0x00, 0x00, // ...[...Z....`...
	0x00, 0x00, 0x00, 0x58, 0x30, 0x00, 0x04, 0x00, 0x70, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, // ...X0...p......U
	0x55, 0x00, 0x00, 0x62, 0x10, 0x00, 0x03, 0xf2, 0x10, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x62, // U..b...........b
	0x10, 0x00, 0x03, 0xf2, 0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, // ...........e....
	0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x69, //  ......h.......i
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x45, // ...............E
	0x00, 0x00, 0x09, 0xf2, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x12, 0x10, 0x00, 0x02, // ...........F....
	0x00, 0x00, 0x00, 0x46, 0x7e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x10, 0x00, 0x00, // ...F~.......`...
	0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0x12, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ...6....0 ......
	0x00, 0x00, 0x00, 0x2a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0x12, // ...*.......6....
	0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x10, 0x00, 0x00, // 0 ..............
	0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0x12, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // ...6....0 ......
	0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0x12, // ...........6....
	0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x10, 0x00, 0x00, // 0 .........:....
	0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x09, 0x12, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, // ...2...........:
	0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x01, // ........@.....@.
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x1b, 0x00, 0x00, 0x05, 0x12, 0x00, 0x10, 0x00, 0x00, // @.....?.........
	0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x07, 0x12, // ...........6....
	0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x30, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x0a, // ........0 ......
	0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x07, 0x82, 0x20, 0x10, 0x00, 0x00, // .......8.... ...
	0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x10, 0x10, 0x00, 0x01, // ...........:....
	0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x05, 0x72, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, // ...6...r ......F
	0x12, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,       // .......>.......
};
static const uint8_t fs_font_basic_mtl[941] =
{
	0x46, 0x53, 0x48, 0x05, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9a, 0x03, // FSH.............
	0x00, 0x00, 0x75, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, // ..using namespac
	0x65, 0x20, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, // e metal;.struct 
	0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, // xlatMtlShaderInp
	0x75, 0x74, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x76, 0x5f, // ut {.  float4 v_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, // color0;.  float4
	0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x7d, 0x3b, //  v_texcoord0;.};
	0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, // .struct xlatMtlS
	0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x7b, 0x0a, 0x20, 0x20, // haderOutput {.  
	0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, // float4 gl_FragCo
	0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, // lor;.};.struct x
	0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, // latMtlShaderUnif
	0x6f, 0x72, 0x6d, 0x20, 0x7b, 0x0a, 0x7d, 0x3b, 0x0a, 0x66, 0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, // orm {.};.fragmen
	0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, // t xlatMtlShaderO
	0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, // utput xlatMtlMai
	0x6e, 0x20, 0x28, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, // n (xlatMtlShader
	0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x20, 0x5b, 0x5b, 0x73, // Input _mtl_i [[s
	0x74, 0x61, 0x67, 0x65, 0x5f, 0x69, 0x6e, 0x5d, 0x5d, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, // tage_in]], const
	0x61, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, // ant xlatMtlShade
	0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, // rUniform& _mtl_u
	0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x0a, 0x20, //  [[buffer(0)]]. 
	0x20, 0x2c, 0x20, 0x20, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x63, 0x75, 0x62, 0x65, //  ,   texturecube
	0x3c, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x3e, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, // <float> s_texCol
	0x6f, 0x72, 0x20, 0x5b, 0x5b, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x28, 0x30, 0x29, 0x5d, // or [[texture(0)]
	0x5d, 0x2c, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x73, // ], sampler _mtls
	0x6d, 0x70, 0x5f, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x5b, 0x5b, // mp_s_texColor [[
	0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, // sampler(0)]]).{.
	0x20, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, //   xlatMtlShaderO
	0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x20, 0x20, // utput _mtl_o;.  
	0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, 0x5b, 0x34, 0x5d, 0x3b, // float rgba_1[4];
	0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, // .  float4 tmpvar
	0x5f, 0x32, 0x20, 0x3d, 0x20, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, // _2 = 0;.  tmpvar
	0x5f, 0x32, 0x20, 0x3d, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2e, // _2 = s_texColor.
	0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x73, 0x6d, 0x70, 0x5f, 0x73, // sample(_mtlsmp_s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2c, 0x20, 0x28, 0x66, 0x6c, 0x6f, 0x61, // _texColor, (floa
	0x74, 0x33, 0x29, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x2e, 0x76, 0x5f, 0x74, 0x65, 0x78, // t3)(_mtl_i.v_tex
	0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x2e, 0x78, 0x79, 0x7a, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, // coord0.xyz));.  
	0x69, 0x6e, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x30, // int tmpvar_3 = 0
	0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x69, // ;.  tmpvar_3 = i
	0x6e, 0x74, 0x28, 0x28, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x2e, 0x76, 0x5f, 0x74, 0x65, // nt(((_mtl_i.v_te
	0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x2e, 0x77, 0x20, 0x2a, 0x20, 0x34, 0x2e, 0x30, 0x29, // xcoord0.w * 4.0)
	0x20, 0x2b, 0x20, 0x30, 0x2e, 0x35, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x67, 0x62, 0x61, //  + 0.5));.  rgba
	0x5f, 0x31, 0x5b, 0x30, 0x5d, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, // _1[0] = tmpvar_2
	0x2e, 0x7a, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, 0x5b, 0x31, 0x5d, 0x20, // .z;.  rgba_1[1] 
	0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x79, 0x3b, 0x0a, 0x20, 0x20, // = tmpvar_2.y;.  
	0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, 0x5b, 0x32, 0x5d, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, // rgba_1[2] = tmpv
	0x61, 0x72, 0x5f, 0x32, 0x2e, 0x78, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, // ar_2.x;.  rgba_1
	0x5b, 0x33, 0x5d, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x77, // [3] = tmpvar_2.w
	0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // ;.  float4 tmpva
	0x72, 0x5f, 0x34, 0x20, 0x3d, 0x20, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // r_4 = 0;.  tmpva
	0x72, 0x5f, 0x34, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, // r_4.xyz = _mtl_i
	0x2e, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x2e, 0x78, 0x79, 0x7a, 0x3b, 0x0a, 0x20, // .v_color0.xyz;. 
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x2e, 0x77, 0x20, 0x3d, 0x20, 0x28, 0x5f, //  tmpvar_4.w = (_
	0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x2e, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x2e, 0x77, // mtl_i.v_color0.w
	0x20, 0x2a, 0x20, 0x72, 0x67, 0x62, 0x61, 0x5f, 0x31, 0x5b, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, //  * rgba_1[tmpvar
	0x5f, 0x33, 0x5d, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, // _3]);.  _mtl_o.g
	0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, 0x6d, // l_FragColor = tm
	0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, // pvar_4;.  return
	0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                   //  _mtl_o;.}...
};
extern const uint8_t* fs_font_basic_pssl;
extern const uint32_t fs_font_basic_pssl_size;
