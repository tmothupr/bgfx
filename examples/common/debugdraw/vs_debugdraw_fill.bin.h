static const uint8_t vs_debugdraw_fill_glsl[333] =
{
	0x56, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0a, 0x75, // VSH............u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x04, 0x01, 0x00, 0x00, 0x01, 0x00, 0x07, // _viewProj.......
	0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x04, 0x20, 0x00, 0x00, 0x20, 0x00, 0x1b, 0x01, 0x00, // u_model. .. ....
	0x00, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, // .attribute highp
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x61, 0x5f, 0x69, 0x6e, 0x64, 0x69, 0x63, 0x65, 0x73, 0x3b, //  vec4 a_indices;
	0x0a, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, // .attribute highp
	0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, //  vec3 a_position
	0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, // ;.uniform highp 
	0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x3b, // mat4 u_viewProj;
	0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, // .uniform mat4 u_
	0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x5b, 0x33, 0x32, 0x5d, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, // model[32];.void 
	0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, // main ().{.  high
	0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, // p vec4 tmpvar_1;
	0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x77, 0x20, 0x3d, 0x20, // .  tmpvar_1.w = 
	0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, // 1.0;.  tmpvar_1.
	0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, // xyz = a_position
	0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, // ;.  gl_Position 
	0x3d, 0x20, 0x28, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x20, 0x2a, 0x20, // = (u_viewProj * 
	0x28, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x5b, 0x69, 0x6e, 0x74, 0x28, 0x61, 0x5f, 0x69, // (u_model[int(a_i
	0x6e, 0x64, 0x69, 0x63, 0x65, 0x73, 0x2e, 0x78, 0x29, 0x5d, 0x20, 0x2a, 0x20, 0x74, 0x6d, 0x70, // ndices.x)] * tmp
	0x76, 0x61, 0x72, 0x5f, 0x31, 0x29, 0x29, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                   // var_1));.}...
};
static const uint8_t vs_debugdraw_fill_spv[1269] =
{
	0x56, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x07, 0x75, // VSH............u
	0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x04, 0x20, 0x40, 0x00, 0x80, 0x00, 0x0a, 0x75, 0x5f, 0x76, // _model. @....u_v
	0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x04, 0x01, 0x00, 0x00, 0x04, 0x00, 0xbc, 0x04, 0x00, // iewProj.........
	0x00, 0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x07, 0x00, 0x08, 0x00, 0x7c, 0x00, 0x00, // ...#.........|..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, // ................
	0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, // .....GLSL.std.45
	0x30, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // 0...............
	0x00, 0x0f, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, // .............mai
	0x6e, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, // n....>...B...E..
	0x00, 0x03, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x05, 0x00, 0x04, // ................
	0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x04, // .....main.......
	0x00, 0x1f, 0x00, 0x00, 0x00, 0x24, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x00, 0x06, 0x00, 0x06, // .....$Global....
	0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, // .........u_viewP
	0x72, 0x6f, 0x6a, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // roj.............
	0x00, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x00, 0x05, 0x00, 0x03, 0x00, 0x21, 0x00, 0x00, // .u_model.....!..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x61, 0x5f, 0x69, // .........>...a_i
	0x6e, 0x64, 0x69, 0x63, 0x65, 0x73, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x42, 0x00, 0x00, // ndices.......B..
	0x00, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x05, 0x00, 0x0a, // .a_position.....
	0x00, 0x45, 0x00, 0x00, 0x00, 0x40, 0x65, 0x6e, 0x74, 0x72, 0x79, 0x50, 0x6f, 0x69, 0x6e, 0x74, // .E...@entryPoint
	0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x2e, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, // Output.gl_Positi
	0x6f, 0x6e, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, // on...G..........
	0x00, 0x40, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .@...H..........
	0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .....H..........
	0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x00, // .#.......H......
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, // .............H..
	0x00, 0x1f, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, // .............H..
	0x00, 0x1f, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, // .........#...@..
	0x00, 0x48, 0x00, 0x05, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, // .H..............
	0x00, 0x10, 0x00, 0x00, 0x00, 0x47, 0x00, 0x03, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // .....G..........
	0x00, 0x47, 0x00, 0x04, 0x00, 0x21, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .G...!..."......
	0x00, 0x47, 0x00, 0x04, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .G...>..........
	0x00, 0x47, 0x00, 0x04, 0x00, 0x42, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // .G...B..........
	0x00, 0x47, 0x00, 0x04, 0x00, 0x45, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .G...E..........
	0x00, 0x13, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, // .........!......
	0x00, 0x02, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, // ............. ..
	0x00, 0x01, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, // ................
	0x00, 0x04, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x09, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, // ............. ..
	0x00, 0x17, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, // ................
	0x00, 0x17, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // ................
	0x00, 0x2b, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // .+..............
	0x3f, 0x18, 0x00, 0x04, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // ?...............
	0x00, 0x15, 0x00, 0x04, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ......... ......
	0x00, 0x2b, 0x00, 0x04, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, // .+........... ..
	0x00, 0x1c, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, // ................
	0x00, 0x1e, 0x00, 0x04, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, // ................
	0x00, 0x20, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, // . ... ..........
	0x00, 0x3b, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // .;... ...!......
	0x00, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // .+......."......
	0x00, 0x20, 0x00, 0x04, 0x00, 0x27, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, // . ...'..........
	0x00, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .+.......-......
	0x00, 0x20, 0x00, 0x04, 0x00, 0x3d, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, // . ...=..........
	0x00, 0x3b, 0x00, 0x04, 0x00, 0x3d, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // .;...=...>......
	0x00, 0x20, 0x00, 0x04, 0x00, 0x41, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, // . ...A..........
	0x00, 0x3b, 0x00, 0x04, 0x00, 0x41, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // .;...A...B......
	0x00, 0x20, 0x00, 0x04, 0x00, 0x44, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, // . ...D..........
	0x00, 0x3b, 0x00, 0x04, 0x00, 0x44, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, // .;...D...E......
	0x00, 0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .6..............
	0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, // .............=..
	0x00, 0x07, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, // .....?...>...=..
	0x00, 0x0a, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, // .....C...B...Q..
	0x00, 0x09, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .........C......
	0x00, 0x51, 0x00, 0x05, 0x00, 0x09, 0x00, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, // .Q.......]...C..
	0x00, 0x01, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x09, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, // .....Q.......^..
	0x00, 0x43, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x50, 0x00, 0x07, 0x00, 0x0c, 0x00, 0x00, // .C.......P......
	0x00, 0x5f, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, // ._.......]...^..
	0x00, 0x16, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, // .....Q.......a..
	0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x27, 0x00, 0x00, // .?.......A...'..
	0x00, 0x62, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, // .b...!..."...a..
	0x00, 0x3d, 0x00, 0x04, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, // .=.......c...b..
	0x00, 0x90, 0x00, 0x05, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, // .........d..._..
	0x00, 0x63, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x27, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, // .c...A...'...f..
	0x00, 0x21, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x1b, 0x00, 0x00, // .!...-...=......
	0x00, 0x67, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00, 0x90, 0x00, 0x05, 0x00, 0x0c, 0x00, 0x00, // .g...f..........
	0x00, 0x68, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, // .h...d...g...Q..
	0x00, 0x09, 0x00, 0x00, 0x00, 0x6b, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // .....k...h......
	0x00, 0x7f, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x6b, 0x00, 0x00, // .........l...k..
	0x00, 0x52, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x7b, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, // .R.......{...l..
	0x00, 0x68, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x45, 0x00, 0x00, // .h.......>...E..
	0x00, 0x7b, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00, 0x00, 0x02, 0x0e, // .{.......8......
	0x00, 0x01, 0x00, 0x40, 0x08,                                                                   // ...@.
};
static const uint8_t vs_debugdraw_fill_dx9[486] =
{
	0x56, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x07, 0x75, // VSH............u
	0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x04, 0x20, 0x00, 0x00, 0x80, 0x00, 0x0a, 0x75, 0x5f, 0x76, // _model. .....u_v
	0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x04, 0x01, 0x80, 0x00, 0x04, 0x00, 0xb4, 0x01, 0x00, // iewProj.........
	0x00, 0x00, 0x03, 0xfe, 0xff, 0xfe, 0xff, 0x2b, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, // .......+.CTAB...
	0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0x02, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, // ................
	0x00, 0x00, 0x91, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // .....x...D......
	0x00, 0x80, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, // .....L..........
	0x00, 0x02, 0x00, 0x80, 0x00, 0x04, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .........h......
	0x00, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x00, 0x03, 0x00, 0x03, 0x00, 0x04, 0x00, 0x04, // .u_model........
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, // . .......u_viewP
	0x72, 0x6f, 0x6a, 0x00, 0xab, 0x03, 0x00, 0x03, 0x00, 0x04, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, // roj.............
	0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, // .....vs_3_0.Micr
	0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, // osoft (R) HLSL S
	0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x31, // hader Compiler 1
	0x30, 0x2e, 0x31, 0x00, 0xab, 0x51, 0x00, 0x00, 0x05, 0x84, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, // 0.1..Q..........
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, // @...............
	0x02, 0x02, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // ................
	0x80, 0x01, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, // ................
	0xe0, 0x05, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x80, 0x84, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, // ................
	0x90, 0x2e, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0xb0, 0x00, 0x00, 0x00, 0x80, 0x05, 0x00, 0x00, // ................
	0x04, 0x00, 0x00, 0x0f, 0x80, 0x01, 0x00, 0x55, 0x90, 0x01, 0x20, 0xe4, 0xa0, 0x00, 0x00, 0x00, // .......U.. .....
	0xb0, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x20, 0xe4, 0xa0, 0x00, 0x00, 0x00, // .......... .....
	0xb0, 0x01, 0x00, 0x00, 0x90, 0x00, 0x00, 0xe4, 0x80, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x0f, // ................
	0x80, 0x02, 0x20, 0xe4, 0xa0, 0x00, 0x00, 0x00, 0xb0, 0x01, 0x00, 0xaa, 0x90, 0x00, 0x00, 0xe4, // .. .............
	0x80, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, 0x03, 0x20, 0xe4, // .............. .
	0xa0, 0x00, 0x00, 0x00, 0xb0, 0x05, 0x00, 0x00, 0x03, 0x01, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x55, // ...............U
	0x80, 0x81, 0x00, 0xe4, 0xa0, 0x04, 0x00, 0x00, 0x04, 0x01, 0x00, 0x0f, 0x80, 0x80, 0x00, 0xe4, // ................
	0xa0, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x04, 0x00, 0x00, 0x04, 0x01, 0x00, 0x0f, // ................
	0x80, 0x82, 0x00, 0xe4, 0xa0, 0x00, 0x00, 0xaa, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x04, 0x00, 0x00, // ................
	0x04, 0x00, 0x00, 0x0f, 0xe0, 0x83, 0x00, 0xe4, 0xa0, 0x00, 0x00, 0xff, 0x80, 0x01, 0x00, 0xe4, // ................
	0x80, 0xff, 0xff, 0x00, 0x00, 0x00,                                                             // ......
};
static const uint8_t vs_debugdraw_fill_dx11[681] =
{
	0x56, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0a, 0x75, // VSH............u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x07, // _viewProj.......
	0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x04, 0x20, 0x40, 0x00, 0x80, 0x00, 0x70, 0x02, 0x00, // u_model. @...p..
	0x00, 0x44, 0x58, 0x42, 0x43, 0x21, 0x99, 0xbc, 0x62, 0x67, 0xb7, 0x95, 0xd6, 0x90, 0x9d, 0x96, // .DXBC!..bg......
	0xc0, 0x0e, 0x98, 0x00, 0xf9, 0x01, 0x00, 0x00, 0x00, 0x70, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, // .........p......
	0x00, 0x2c, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, // .,...........ISG
	0x4e, 0x50, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, // NP...........8..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x0f, 0x01, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .....E..........
	0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x42, 0x4c, 0x45, // .............BLE
	0x4e, 0x44, 0x49, 0x4e, 0x44, 0x49, 0x43, 0x45, 0x53, 0x00, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, // NDINDICES.POSITI
	0x4f, 0x4e, 0x00, 0xab, 0xab, 0x4f, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // ON...OSGN,......
	0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // ..... ..........
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, // .............SV_
	0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x53, 0x48, 0x44, 0x52, 0xb0, 0x01, 0x00, // POSITION.SHDR...
	0x00, 0x40, 0x00, 0x01, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x59, 0x08, 0x00, 0x04, 0x46, 0x8e, 0x20, // .@...l...Y...F. 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x03, 0x12, 0x10, 0x10, // ........._......
	0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x03, 0x72, 0x10, 0x10, 0x00, 0x01, 0x00, 0x00, // ....._...r......
	0x00, 0x67, 0x00, 0x00, 0x04, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // .g.... .........
	0x00, 0x68, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x07, 0x12, 0x00, 0x10, // .h.......)......
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, // ..............@.
	0x00, 0x02, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x0a, 0xf2, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, // .....8..........
	0x00, 0x56, 0x15, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x06, 0x00, 0x00, 0x00, // .V.......F. ....
	0x00, 0x05, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, // .............2..
	0x0c, 0xf2, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x06, 0x00, 0x00, 0x00, // .........F. ....
	0x00, 0x04, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x10, 0x10, // ................
	0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, // .....F.......2..
	0x0c, 0xf2, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x06, 0x00, 0x00, 0x00, // .........F. ....
	0x00, 0x06, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa6, 0x1a, 0x10, // ................
	0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .....F..........
	0x0a, 0xf2, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x01, 0x00, 0x00, // .........F......
	0x00, 0x46, 0x8e, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, // .F. ............
	0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x08, 0xf2, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, // .....8..........
	0x00, 0x56, 0x05, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, // .V.......F. ....
	0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x0a, 0xf2, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, // .....2..........
	0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x10, // .F. ............
	0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, // .....F.......2..
	0x0a, 0xf2, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, // .........F. ....
	0x00, 0x02, 0x00, 0x00, 0x00, 0xa6, 0x0a, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, // .............F..
	0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x0a, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, // .....2.... .....
	0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf6, 0x0f, 0x10, // .F. ............
	0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, // .....F.......>..
	0x01, 0x00, 0x02, 0x0e, 0x00, 0x01, 0x00, 0x40, 0x08,                                           // .......@.
};
static const uint8_t vs_debugdraw_fill_mtl[689] =
{
	0x56, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0a, 0x75, // VSH............u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x04, 0x01, 0x00, 0x00, 0x01, 0x00, 0x07, // _viewProj.......
	0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x04, 0x20, 0x00, 0x00, 0x20, 0x00, 0x7f, 0x02, 0x00, // u_model. .. ....
	0x00, 0x75, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, // .using namespace
	0x20, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, //  metal;.struct x
	0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, // latMtlShaderInpu
	0x74, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x61, 0x5f, 0x69, // t {.  float4 a_i
	0x6e, 0x64, 0x69, 0x63, 0x65, 0x73, 0x20, 0x5b, 0x5b, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, // ndices [[attribu
	0x74, 0x65, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, // te(0)]];.  float
	0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x5b, 0x5b, 0x61, // 3 a_position [[a
	0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x28, 0x31, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, // ttribute(1)]];.}
	0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, // ;.struct xlatMtl
	0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x7b, 0x0a, 0x20, // ShaderOutput {. 
	0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, //  float4 gl_Posit
	0x69, 0x6f, 0x6e, 0x20, 0x5b, 0x5b, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x5d, 0x5d, // ion [[position]]
	0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // ;.};.struct xlat
	0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, // MtlShaderUniform
	0x20, 0x7b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x78, 0x34, 0x20, 0x75, 0x5f, //  {.  float4x4 u_
	0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, // viewProj;.  floa
	0x74, 0x34, 0x78, 0x34, 0x20, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x5b, 0x33, 0x32, 0x5d, // t4x4 u_model[32]
	0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x76, 0x65, 0x72, 0x74, 0x65, 0x78, 0x20, 0x78, 0x6c, 0x61, 0x74, // ;.};.vertex xlat
	0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, // MtlShaderOutput 
	0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x78, 0x6c, 0x61, // xlatMtlMain (xla
	0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, // tMtlShaderInput 
	0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, 0x5f, 0x69, // _mtl_i [[stage_i
	0x6e, 0x5d, 0x5d, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x20, 0x78, 0x6c, // n]], constant xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, // atMtlShaderUnifo
	0x72, 0x6d, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, // rm& _mtl_u [[buf
	0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x78, 0x6c, // fer(0)]]).{.  xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, // atMtlShaderOutpu
	0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, // t _mtl_o;.  floa
	0x74, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x30, 0x3b, // t4 tmpvar_1 = 0;
	0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x77, 0x20, 0x3d, 0x20, // .  tmpvar_1.w = 
	0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, // 1.0;.  tmpvar_1.
	0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x2e, 0x61, 0x5f, 0x70, // xyz = _mtl_i.a_p
	0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, // osition;.  _mtl_
	0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d, 0x20, // o.gl_Position = 
	0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, 0x72, // (_mtl_u.u_viewPr
	0x6f, 0x6a, 0x20, 0x2a, 0x20, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x75, 0x5f, 0x6d, // oj * (_mtl_u.u_m
	0x6f, 0x64, 0x65, 0x6c, 0x5b, 0x69, 0x6e, 0x74, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x2e, // odel[int(_mtl_i.
	0x61, 0x5f, 0x69, 0x6e, 0x64, 0x69, 0x63, 0x65, 0x73, 0x2e, 0x78, 0x29, 0x5d, 0x20, 0x2a, 0x20, // a_indices.x)] * 
	0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, // tmpvar_1));.  re
	0x74, 0x75, 0x72, 0x6e, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, // turn _mtl_o;.}..
	0x00,                                                                                           // .
};
extern const uint8_t* vs_debugdraw_fill_pssl;
extern const uint32_t vs_debugdraw_fill_pssl_size;
