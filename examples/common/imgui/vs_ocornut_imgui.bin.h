static const uint8_t vs_ocornut_imgui_glsl[527] =
{
	0x56, 0x53, 0x48, 0x06, 0xf3, 0xef, 0x58, 0x3c, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x0b, 0x75, // VSH...X<.......u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, // _viewTexel......
	0xea, 0x01, 0x00, 0x00, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, // ....attribute hi
	0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x61, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // ghp vec4 a_color
	0x30, 0x3b, 0x0a, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, 0x67, // 0;.attribute hig
	0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, // hp vec3 a_positi
	0x6f, 0x6e, 0x3b, 0x0a, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x68, 0x69, // on;.attribute hi
	0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x61, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, // ghp vec2 a_texco
	0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, // ord0;.varying hi
	0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // ghp vec4 v_color
	0x30, 0x3b, 0x0a, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, // 0;.varying highp
	0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, //  vec2 v_texcoord
	0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, // 0;.uniform highp
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, //  vec4 u_viewTexe
	0x6c, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, // l;.void main ().
	0x7b, 0x0a, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x74, // {.  highp vec2 t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // mpvar_1;.  tmpva
	0x72, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x28, 0x28, 0x32, 0x2e, 0x30, 0x20, 0x2a, 0x20, 0x61, 0x5f, // r_1 = ((2.0 * a_
	0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x78, 0x79, 0x29, 0x20, 0x2a, 0x20, 0x75, // position.xy) * u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x2e, 0x78, 0x79, 0x29, 0x3b, 0x0a, // _viewTexel.xy);.
	0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, //   highp vec4 tmp
	0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // var_2;.  tmpvar_
	0x32, 0x2e, 0x7a, 0x77, 0x20, 0x3d, 0x20, 0x76, 0x65, 0x63, 0x32, 0x28, 0x30, 0x2e, 0x30, 0x2c, // 2.zw = vec2(0.0,
	0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, //  1.0);.  tmpvar_
	0x32, 0x2e, 0x78, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, // 2.x = (tmpvar_1.
	0x78, 0x20, 0x2d, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, // x - 1.0);.  tmpv
	0x61, 0x72, 0x5f, 0x32, 0x2e, 0x79, 0x20, 0x3d, 0x20, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, // ar_2.y = (1.0 - 
	0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x79, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x67, // tmpvar_1.y);.  g
	0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, // l_Position = tmp
	0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, // var_2;.  v_texco
	0x6f, 0x72, 0x64, 0x30, 0x20, 0x3d, 0x20, 0x61, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, // ord0 = a_texcoor
	0x64, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x20, 0x3d, // d0;.  v_color0 =
	0x20, 0x61, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,       //  a_color0;.}...
};
static const uint8_t vs_ocornut_imgui_spv[1334] =
{
	0x56, 0x53, 0x48, 0x06, 0xf3, 0xef, 0x58, 0x3c, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x0b, 0x75, // VSH...X<.......u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, // _viewTexel......
	0x08, 0x05, 0x00, 0x00, 0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x08, 0x00, // ......#.........
	0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, // ................
	0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, // ........GLSL.std
	0x2e, 0x34, 0x35, 0x30, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, // .450............
	0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, // ................
	0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, // main....B...F...
	0x4a, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, // J...U...X.......
	0x03, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, // ................
	0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, // ....main........
	0x24, 0x00, 0x00, 0x00, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x42, 0x6c, 0x6f, 0x63, 0x6b, // $...UniformBlock
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........$.......
	0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x00, 0x05, 0x00, 0x03, 0x00, // u_viewTexel.....
	0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x42, 0x00, 0x00, 0x00, // &...........B...
	0x61, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, // a_color0........
	0x46, 0x00, 0x00, 0x00, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00, // F...a_position..
	0x05, 0x00, 0x05, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x61, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, // ....J...a_texcoo
	0x72, 0x64, 0x30, 0x00, 0x05, 0x00, 0x0a, 0x00, 0x55, 0x00, 0x00, 0x00, 0x40, 0x65, 0x6e, 0x74, // rd0.....U...@ent
	0x72, 0x79, 0x50, 0x6f, 0x69, 0x6e, 0x74, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x2e, 0x67, 0x6c, // ryPointOutput.gl
	0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x00, 0x05, 0x00, 0x09, 0x00, // _Position.......
	0x58, 0x00, 0x00, 0x00, 0x40, 0x65, 0x6e, 0x74, 0x72, 0x79, 0x50, 0x6f, 0x69, 0x6e, 0x74, 0x4f, // X...@entryPointO
	0x75, 0x74, 0x70, 0x75, 0x74, 0x2e, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x00, 0x00, // utput.v_color0..
	0x05, 0x00, 0x0a, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x40, 0x65, 0x6e, 0x74, 0x72, 0x79, 0x50, 0x6f, // ........@entryPo
	0x69, 0x6e, 0x74, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x2e, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, // intOutput.v_texc
	0x6f, 0x6f, 0x72, 0x64, 0x30, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x24, 0x00, 0x00, 0x00, // oord0...H...$...
	0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x03, 0x00, // ....#.......G...
	0x24, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x26, 0x00, 0x00, 0x00, // $.......G...&...
	0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x26, 0x00, 0x00, 0x00, // ".......G...&...
	0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x42, 0x00, 0x00, 0x00, // !.......G...B...
	0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x46, 0x00, 0x00, 0x00, // ........G...F...
	0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x4a, 0x00, 0x00, 0x00, // ........G...J...
	0x1e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x55, 0x00, 0x00, 0x00, // ........G...U...
	0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x58, 0x00, 0x00, 0x00, // ........G...X...
	0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x5c, 0x00, 0x00, 0x00, // ........G.......
	0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, // ................
	0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, // !...............
	0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, // .... ...........
	0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00, // ................
	0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, // ................
	0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x16, 0x00, 0x00, 0x00, // ................
	0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, //  .......+.......
	0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, // .......?+.......
	0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, // ........+.......
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1e, 0x00, 0x03, 0x00, 0x24, 0x00, 0x00, 0x00, //  ......@....$...
	0x07, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x25, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // .... ...%.......
	0x24, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x25, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, // $...;...%...&...
	0x02, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x16, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, // ....+.......'...
	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // .... ...(.......
	0x07, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x41, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // .... ...A.......
	0x07, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x41, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, // ....;...A...B...
	0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x45, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // .... ...E.......
	0x09, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x45, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, // ....;...E...F...
	0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x49, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // .... ...I.......
	0x0b, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x49, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, // ....;...I...J...
	0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x54, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // .... ...T.......
	0x07, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x54, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, // ....;...T...U...
	0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x54, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, // ....;...T...X...
	0x03, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x5b, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // .... ...[.......
	0x0b, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5b, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, // ....;...[.......
	0x03, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, // ....6...........
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, // ................
	0x3d, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, // =.......C...B...
	0x3d, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, // =.......G...F...
	0x3d, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x4b, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, // =.......K...J...
	0x4f, 0x00, 0x07, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, // O.......v...G...
	0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x8e, 0x00, 0x05, 0x00, // G...............
	0x0b, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, // ....w...v... ...
	0x41, 0x00, 0x05, 0x00, 0x28, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, // A...(...x...&...
	0x27, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, // '...=.......y...
	0x78, 0x00, 0x00, 0x00, 0x4f, 0x00, 0x07, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x7a, 0x00, 0x00, 0x00, // x...O.......z...
	0x79, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // y...y...........
	0x85, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x7b, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, // ........{...w...
	0x7a, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, // z...Q.......}...
	0x7b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, // {...............
	0x7e, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, // ~...}.......Q...
	0x06, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x7b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // ........{.......
	0x83, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, // ................
	0x80, 0x00, 0x00, 0x00, 0x50, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, // ....P...........
	0x7e, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, // ~...............
	0x3e, 0x00, 0x03, 0x00, 0x55, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, // >...U.......>...
	0x58, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x5c, 0x00, 0x00, 0x00, // X...C...>.......
	0x4b, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00, 0x00, 0x03, 0x05, 0x00, // K.......8.......
	0x01, 0x00, 0x10, 0x00, 0x10, 0x00,                                                             // ......
};
static const uint8_t vs_ocornut_imgui_dx9[365] =
{
	0x56, 0x53, 0x48, 0x06, 0xf3, 0xef, 0x58, 0x3c, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x0b, 0x75, // VSH...X<.......u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, // _viewTexel......
	0x48, 0x01, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0xfe, 0xff, 0x20, 0x00, 0x43, 0x54, 0x41, 0x42, // H......... .CTAB
	0x1c, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x00, // ....S...........
	0x1c, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, // ........L...0...
	0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........<.......
	0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x00, 0x01, 0x00, 0x03, 0x00, // u_viewTexel.....
	0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x73, 0x5f, 0x33, // ............vs_3
	0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, // _0.Microsoft (R)
	0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, //  HLSL Shader Com
	0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, 0x51, 0x00, 0x00, 0x05, // piler 10.1..Q...
	0x01, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0xbf, 0x00, 0x00, 0x80, 0x3f, // .......@.......?
	0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, // ................
	0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, // ................
	0x05, 0x00, 0x00, 0x80, 0x02, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, // ................
	0x00, 0x00, 0x0f, 0xe0, 0x1f, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, 0x01, 0x00, 0x0f, 0xe0, // ................
	0x1f, 0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0x80, 0x02, 0x00, 0x03, 0xe0, 0x05, 0x00, 0x00, 0x03, // ................
	0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0xe4, 0x90, 0x04, 0x00, 0x00, 0x04, // ................
	0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0xa0, 0x01, 0x00, 0x55, 0xa0, // ..............U.
	0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0xe0, 0x00, 0x00, 0x55, 0x80, 0x01, 0x00, 0x00, 0xa1, // ..........U.....
	0x01, 0x00, 0xaa, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0c, 0xe0, 0x01, 0x00, 0xb4, 0xa0, // ................
	0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0xe4, 0x90, 0x01, 0x00, 0x00, 0x02, // ................
	0x02, 0x00, 0x03, 0xe0, 0x02, 0x00, 0xe4, 0x90, 0xff, 0xff, 0x00, 0x00, 0x00,                   // .............
};
static const uint8_t vs_ocornut_imgui_dx11[618] =
{
	0x56, 0x53, 0x48, 0x06, 0xf3, 0xef, 0x58, 0x3c, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x0b, 0x75, // VSH...X<.......u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, // _viewTexel......
	0x3c, 0x02, 0x00, 0x00, 0x44, 0x58, 0x42, 0x43, 0x22, 0x5c, 0xcc, 0x36, 0x58, 0xb2, 0x23, 0x45, // <...DXBC"..6X.#E
	0x8a, 0x2b, 0xbd, 0x13, 0xac, 0xf2, 0xa4, 0x09, 0x01, 0x00, 0x00, 0x00, 0x3c, 0x02, 0x00, 0x00, // .+..........<...
	0x03, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, // ....,...........
	0x49, 0x53, 0x47, 0x4e, 0x68, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // ISGNh...........
	0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // P...............
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........V.......
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00, // ................
	0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // _...............
	0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x50, 0x4f, // ........COLOR.PO
	0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, // SITION.TEXCOORD.
	0x4f, 0x53, 0x47, 0x4e, 0x6c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // OSGNl...........
	0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // P...............
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, // ................
	0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // b...............
	0x02, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, // ........SV_POSIT
	0x49, 0x4f, 0x4e, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, // ION.COLOR.TEXCOO
	0x52, 0x44, 0x00, 0xab, 0x53, 0x48, 0x44, 0x52, 0x24, 0x01, 0x00, 0x00, 0x40, 0x00, 0x01, 0x00, // RD..SHDR$...@...
	0x49, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x04, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // I...Y...F. .....
	0x01, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x03, 0xf2, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ...._...........
	0x5f, 0x00, 0x00, 0x03, 0x32, 0x10, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x03, // _...2......._...
	0x32, 0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x04, 0xf2, 0x20, 0x10, 0x00, // 2.......g.... ..
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, // ........e.... ..
	0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0x32, 0x20, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, // ....e...2 ......
	0x68, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x08, 0xc2, 0x20, 0x10, 0x00, // h.......6.... ..
	0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // .....@..........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x38, 0x00, 0x00, 0x08, 0x32, 0x00, 0x10, 0x00, // .......?8...2...
	0x00, 0x00, 0x00, 0x00, 0x46, 0x10, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x80, 0x20, 0x00, // ....F.......F. .
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x09, 0x12, 0x20, 0x10, 0x00, // ........2.... ..
	0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, // .............@..
	0x00, 0x00, 0x00, 0x40, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0xbf, 0x32, 0x00, 0x00, 0x0a, // ...@.@......2...
	0x22, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x10, 0x80, 0x41, 0x00, 0x00, 0x00, // " ..........A...
	0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x40, 0x00, 0x00, // .....@.....@.@..
	0x00, 0x00, 0x80, 0x3f, 0x36, 0x00, 0x00, 0x05, 0xf2, 0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, // ...?6.... ......
	0x46, 0x1e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x05, 0x32, 0x20, 0x10, 0x00, // F.......6...2 ..
	0x02, 0x00, 0x00, 0x00, 0x46, 0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, // ....F.......>...
	0x00, 0x03, 0x05, 0x00, 0x01, 0x00, 0x10, 0x00, 0x10, 0x00,                                     // ..........
};
static const uint8_t vs_ocornut_imgui_mtl[889] =
{
	0x56, 0x53, 0x48, 0x06, 0xf3, 0xef, 0x58, 0x3c, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x0b, 0x75, // VSH...X<.......u
	0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, // _viewTexel......
	0x4b, 0x03, 0x00, 0x00, 0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0x20, 0x3c, 0x6d, 0x65, // K...#include <me
	0x74, 0x61, 0x6c, 0x5f, 0x73, 0x74, 0x64, 0x6c, 0x69, 0x62, 0x3e, 0x0a, 0x23, 0x69, 0x6e, 0x63, // tal_stdlib>.#inc
	0x6c, 0x75, 0x64, 0x65, 0x20, 0x3c, 0x73, 0x69, 0x6d, 0x64, 0x2f, 0x73, 0x69, 0x6d, 0x64, 0x2e, // lude <simd/simd.
	0x68, 0x3e, 0x0a, 0x0a, 0x75, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, // h>..using namesp
	0x61, 0x63, 0x65, 0x20, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, // ace metal;..stru
	0x63, 0x74, 0x20, 0x5f, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, // ct _Global.{.   
	0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, //  float4 u_viewTe
	0x78, 0x65, 0x6c, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, // xel;.};..struct 
	0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x0a, // xlatMtlMain_out.
	0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x5f, 0x65, 0x6e, // {.    float4 _en
	0x74, 0x72, 0x79, 0x50, 0x6f, 0x69, 0x6e, 0x74, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x5f, 0x76, // tryPointOutput_v
	0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x20, 0x5b, 0x5b, 0x75, 0x73, 0x65, 0x72, 0x28, 0x6c, // _color0 [[user(l
	0x6f, 0x63, 0x6e, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, // ocn0)]];.    flo
	0x61, 0x74, 0x32, 0x20, 0x5f, 0x65, 0x6e, 0x74, 0x72, 0x79, 0x50, 0x6f, 0x69, 0x6e, 0x74, 0x4f, // at2 _entryPointO
	0x75, 0x74, 0x70, 0x75, 0x74, 0x5f, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, // utput_v_texcoord
	0x30, 0x20, 0x5b, 0x5b, 0x75, 0x73, 0x65, 0x72, 0x28, 0x6c, 0x6f, 0x63, 0x6e, 0x31, 0x29, 0x5d, // 0 [[user(locn1)]
	0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x67, 0x6c, // ];.    float4 gl
	0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x5b, 0x5b, 0x70, 0x6f, 0x73, 0x69, // _Position [[posi
	0x74, 0x69, 0x6f, 0x6e, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, // tion]];.};..stru
	0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x69, // ct xlatMtlMain_i
	0x6e, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x61, // n.{.    float4 a
	0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x20, 0x5b, 0x5b, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, // _color0 [[attrib
	0x75, 0x74, 0x65, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, // ute(0)]];.    fl
	0x6f, 0x61, 0x74, 0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x20, // oat3 a_position 
	0x5b, 0x5b, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x28, 0x31, 0x29, 0x5d, 0x5d, // [[attribute(1)]]
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x20, 0x61, 0x5f, 0x74, // ;.    float2 a_t
	0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x20, 0x5b, 0x5b, 0x61, 0x74, 0x74, 0x72, 0x69, // excoord0 [[attri
	0x62, 0x75, 0x74, 0x65, 0x28, 0x32, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x76, // bute(2)]];.};..v
	0x65, 0x72, 0x74, 0x65, 0x78, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, // ertex xlatMtlMai
	0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, // n_out xlatMtlMai
	0x6e, 0x28, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x69, 0x6e, // n(xlatMtlMain_in
	0x20, 0x69, 0x6e, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, 0x5f, 0x69, 0x6e, 0x5d, 0x5d, //  in [[stage_in]]
	0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x20, 0x5f, 0x47, 0x6c, 0x6f, 0x62, // , constant _Glob
	0x61, 0x6c, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, // al& _mtl_u [[buf
	0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, // fer(0)]]).{.    
	0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, // xlatMtlMain_out 
	0x6f, 0x75, 0x74, 0x20, 0x3d, 0x20, 0x7b, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, // out = {};.    fl
	0x6f, 0x61, 0x74, 0x32, 0x20, 0x5f, 0x31, 0x32, 0x33, 0x20, 0x3d, 0x20, 0x28, 0x69, 0x6e, 0x2e, // oat2 _123 = (in.
	0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x78, 0x79, 0x20, 0x2a, 0x20, // a_position.xy * 
	0x32, 0x2e, 0x30, 0x29, 0x20, 0x2a, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x75, 0x5f, // 2.0) * _mtl_u.u_
	0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x2e, 0x78, 0x79, 0x3b, 0x0a, 0x20, 0x20, // viewTexel.xy;.  
	0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, //   out.gl_Positio
	0x6e, 0x20, 0x3d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x28, 0x5f, 0x31, 0x32, 0x33, 0x2e, // n = float4(_123.
	0x78, 0x20, 0x2d, 0x20, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, 0x5f, // x - 1.0, 1.0 - _
	0x31, 0x32, 0x33, 0x2e, 0x79, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, // 123.y, 0.0, 1.0)
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x5f, 0x65, 0x6e, 0x74, 0x72, 0x79, // ;.    out._entry
	0x50, 0x6f, 0x69, 0x6e, 0x74, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x5f, 0x76, 0x5f, 0x63, 0x6f, // PointOutput_v_co
	0x6c, 0x6f, 0x72, 0x30, 0x20, 0x3d, 0x20, 0x69, 0x6e, 0x2e, 0x61, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, // lor0 = in.a_colo
	0x72, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x5f, 0x65, 0x6e, 0x74, // r0;.    out._ent
	0x72, 0x79, 0x50, 0x6f, 0x69, 0x6e, 0x74, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x5f, 0x76, 0x5f, // ryPointOutput_v_
	0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x20, 0x3d, 0x20, 0x69, 0x6e, 0x2e, 0x61, // texcoord0 = in.a
	0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, // _texcoord0;.    
	0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x6f, 0x75, 0x74, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00, // return out;.}...
	0x03, 0x05, 0x00, 0x01, 0x00, 0x10, 0x00, 0x10, 0x00,                                           // .........
};
extern const uint8_t* vs_ocornut_imgui_pssl;
extern const uint32_t vs_ocornut_imgui_pssl_size;
