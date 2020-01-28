static const uint8_t fs_clear7_glsl[414] =
{
	0x46, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, // FSH............b
	0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x02, // gfx_clear_color.
	0x08, 0x00, 0x00, 0x08, 0x00, 0x74, 0x01, 0x00, 0x00, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, // .....t...uniform
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, //  vec4 bgfx_clear
	0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x38, 0x5d, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, // _color[8];.void 
	0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, // main ().{.  gl_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x30, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, // ragData[0] = bgf
	0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x30, 0x5d, // x_clear_color[0]
	0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, // ;.  gl_FragData[
	0x31, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, // 1] = bgfx_clear_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x31, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, // color[1];.  gl_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x32, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, // ragData[2] = bgf
	0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x32, 0x5d, // x_clear_color[2]
	0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, // ;.  gl_FragData[
	0x33, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, // 3] = bgfx_clear_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x33, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, // color[3];.  gl_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x34, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, // ragData[4] = bgf
	0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x34, 0x5d, // x_clear_color[4]
	0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, // ;.  gl_FragData[
	0x35, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, // 5] = bgfx_clear_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x35, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, // color[5];.  gl_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x36, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, // ragData[6] = bgf
	0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x36, 0x5d, // x_clear_color[6]
	0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, // ;.  gl_FragData[
	0x37, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, // 7] = bgfx_clear_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x37, 0x5d, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,             // color[7];.}...
};
static const uint8_t fs_clear7_spv[1567] =
{
	0x46, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, // FSH............b
	0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, // gfx_clear_color.
	0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xf0, 0x05, 0x00, 0x00, 0x03, 0x02, 0x23, 0x07, 0x00, // .............#..
	0x00, 0x01, 0x00, 0x08, 0x00, 0x08, 0x00, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, // ................
	0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, // ...............G
	0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30, 0x00, 0x00, 0x00, 0x00, 0x0e, // LSL.std.450.....
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x0d, 0x00, 0x04, // ................
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x5e, // .......main....^
	0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x66, // ...`...b...d...f
	0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x10, // ...h...j...l....
	0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x05, // ................
	0x00, 0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, // ...............m
	0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x27, 0x00, 0x00, 0x00, 0x55, // ain........'...U
	0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x42, 0x6c, 0x6f, 0x63, 0x6b, 0x00, 0x00, 0x00, 0x00, 0x06, // niformBlock.....
	0x00, 0x08, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, // ...'.......bgfx_
	0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x00, 0x05, // clear_color.....
	0x00, 0x03, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x5e, // ...)...........^
	0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, // ...bgfx_FragData
	0x30, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, // 0......`...bgfx_
	0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x31, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x62, // FragData1......b
	0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, // ...bgfx_FragData
	0x32, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x64, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, // 2......d...bgfx_
	0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x33, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x66, // FragData3......f
	0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, // ...bgfx_FragData
	0x34, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x68, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, // 4......h...bgfx_
	0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x35, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x6a, // FragData5......j
	0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, // ...bgfx_FragData
	0x36, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, // 6......l...bgfx_
	0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x37, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x26, // FragData7..G...&
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x27, // ...........H...'
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, // .......#.......G
	0x00, 0x03, 0x00, 0x27, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x29, // ...'.......G...)
	0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x29, // ...".......G...)
	0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x5e, // ...!.......G...^
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x60, // ...........G...`
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x62, // ...........G...b
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x64, // ...........G...d
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x66, // ...........G...f
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x68, // ...........G...h
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x6a, // ...........G...j
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x6c, // ...........G...l
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x02, // ................
	0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x16, // ...!............
	0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x08, // ....... ........
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x24, // ...............$
	0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x24, // ... .......+...$
	0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x04, 0x00, 0x26, // ...%...........&
	0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x03, 0x00, 0x27, // .......%.......'
	0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, // ...&... ...(....
	0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, 0x00, 0x29, // ...'...;...(...)
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x20, // ...........*... 
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x2b, // .......+...*...+
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x02, // ....... ...,....
	0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x2f, // .......+...*.../
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x32, // .......+...*...2
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x35, // .......+...*...5
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x38, // .......+...*...8
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x3b, // .......+...*...;
	0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x3e, // .......+...*...>
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x41, // .......+...*...A
	0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x03, // ....... ...]....
	0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x5e, // .......;...]...^
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x60, // .......;...]...`
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x62, // .......;...]...b
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x64, // .......;...]...d
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x66, // .......;...]...f
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x68, // .......;...]...h
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x6a, // .......;...]...j
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x6c, // .......;...]...l
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, // .......6........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, // ................
	0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x29, // ...A...,.......)
	0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, // ...+...+...=....
	0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x2c, // ...........A...,
	0x00, 0x00, 0x00, 0x85, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x2f, // .......)...+.../
	0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00, 0x85, // ...=............
	0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00, 0x29, // ...A...,.......)
	0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, // ...+...2...=....
	0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x2c, // ...........A...,
	0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x35, // .......)...+...5
	0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x8a, 0x00, 0x00, 0x00, 0x89, // ...=............
	0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x8b, 0x00, 0x00, 0x00, 0x29, // ...A...,.......)
	0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, // ...+...8...=....
	0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00, 0x8b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x2c, // ...........A...,
	0x00, 0x00, 0x00, 0x8d, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x3b, // .......)...+...;
	0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x8e, 0x00, 0x00, 0x00, 0x8d, // ...=............
	0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x8f, 0x00, 0x00, 0x00, 0x29, // ...A...,.......)
	0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, // ...+...>...=....
	0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x8f, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x2c, // ...........A...,
	0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x41, // .......)...+...A
	0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x91, // ...=............
	0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x5e, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x3e, // ...>...^.......>
	0x00, 0x03, 0x00, 0x60, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x62, // ...`.......>...b
	0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x64, 0x00, 0x00, 0x00, 0x8a, // .......>...d....
	0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x66, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00, 0x3e, // ...>...f.......>
	0x00, 0x03, 0x00, 0x68, 0x00, 0x00, 0x00, 0x8e, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x6a, // ...h.......>...j
	0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x92, // .......>...l....
	0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00,       // .......8.......
};
static const uint8_t fs_clear7_dx9[238] =
{
	0x46, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, // FSH............b
	0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, // gfx_clear_color.
	0x08, 0x00, 0x00, 0x04, 0x00, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0xff, 0x22, // ..............."
	0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, 0x00, 0x5b, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, // .CTAB....[......
	0xff, 0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x54, 0x00, 0x00, // .............T..
	0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, // .0...........D..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, // .....bgfx_clear_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0xab, 0xab, 0xab, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x04, // color...........
	0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, // .........ps_3_0.
	0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, // Microsoft (R) HL
	0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, // SL Shader Compil
	0x65, 0x72, 0x20, 0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, 0x01, 0x00, 0x00, 0x02, 0x00, 0x08, 0x0f, // er 10.1.........
	0x80, 0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x01, 0x08, 0x0f, 0x80, 0x01, 0x00, 0xe4, // ................
	0xa0, 0x01, 0x00, 0x00, 0x02, 0x02, 0x08, 0x0f, 0x80, 0x02, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, // ................
	0x02, 0x03, 0x08, 0x0f, 0x80, 0x03, 0x00, 0xe4, 0xa0, 0xff, 0xff, 0x00, 0x00, 0x00,             // ..............
};
static const uint8_t fs_clear7_dx11[685] =
{
	0x46, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, // FSH............b
	0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, // gfx_clear_color.
	0x08, 0x00, 0x00, 0x08, 0x00, 0x80, 0x02, 0x00, 0x00, 0x44, 0x58, 0x42, 0x43, 0xe7, 0x1e, 0xec, // .........DXBC...
	0x06, 0x0c, 0xd8, 0x43, 0x65, 0x9a, 0x6f, 0x6f, 0xc7, 0x6f, 0x21, 0xde, 0xa4, 0x01, 0x00, 0x00, // ...Ce.oo.o!.....
	0x00, 0x80, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, // .........,...`..
	0x00, 0x3c, 0x01, 0x00, 0x00, 0x49, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // .<...ISGN,......
	0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // ..... ..........
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, // .............SV_
	0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x4f, 0x53, 0x47, 0x4e, 0xd4, 0x00, 0x00, // POSITION.OSGN...
	0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, // ................
	0x00, 0xc8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, // ................
	0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, // ................
	0x00, 0xc8, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, // ................
	0x00, 0x03, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, // ................
	0x00, 0xc8, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, // ................
	0x00, 0x05, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, // ................
	0x00, 0xc8, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, // ................
	0x00, 0x07, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, 0x52, 0x47, // .........SV_TARG
	0x45, 0x54, 0x00, 0xab, 0xab, 0x53, 0x48, 0x44, 0x52, 0x3c, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, // ET...SHDR<...@..
	0x00, 0x4f, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x04, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, // .O...Y...F. ....
	0x00, 0x08, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, // .....e.... .....
	0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, // .e.... ......e..
	0x03, 0xf2, 0x20, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, // .. ......e.... .
	0x00, 0x03, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x04, 0x00, 0x00, // .....e.... .....
	0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x05, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, // .e.... ......e..
	0x03, 0xf2, 0x20, 0x10, 0x00, 0x06, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, // .. ......e.... .
	0x00, 0x07, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, // .....6.... .....
	0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, // .F. .........6..
	0x06, 0xf2, 0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, // .. ......F. ....
	0x00, 0x01, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x02, 0x00, 0x00, // .....6.... .....
	0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, // .F. .........6..
	0x06, 0xf2, 0x20, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, // .. ......F. ....
	0x00, 0x03, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x04, 0x00, 0x00, // .....6.... .....
	0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, // .F. .........6..
	0x06, 0xf2, 0x20, 0x10, 0x00, 0x05, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, // .. ......F. ....
	0x00, 0x05, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x06, 0x00, 0x00, // .....6.... .....
	0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, // .F. .........6..
	0x06, 0xf2, 0x20, 0x10, 0x00, 0x07, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, // .. ......F. ....
	0x00, 0x07, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00,                   // .....>.......
};
static const uint8_t fs_clear7_mtl[1071] =
{
	0x46, 0x53, 0x48, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, // FSH............b
	0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, // gfx_clear_color.
	0x08, 0x00, 0x00, 0x08, 0x00, 0x02, 0x04, 0x00, 0x00, 0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, // .........#includ
	0x65, 0x20, 0x3c, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x5f, 0x73, 0x74, 0x64, 0x6c, 0x69, 0x62, 0x3e, // e <metal_stdlib>
	0x0a, 0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0x20, 0x3c, 0x73, 0x69, 0x6d, 0x64, 0x2f, // .#include <simd/
	0x73, 0x69, 0x6d, 0x64, 0x2e, 0x68, 0x3e, 0x0a, 0x0a, 0x75, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x6e, // simd.h>..using n
	0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x20, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x3b, 0x0a, // amespace metal;.
	0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x5f, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x0a, // .struct _Global.
	0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x67, 0x66, // {.    float4 bgf
	0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x38, 0x5d, // x_clear_color[8]
	0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, // ;.};..struct xla
	0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x0a, 0x7b, 0x0a, 0x20, // tMtlMain_out.{. 
	0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, //    float4 bgfx_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // ragData0 [[color
	0x28, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, // (0)]];.    float
	0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x31, // 4 bgfx_FragData1
	0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x31, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, //  [[color(1)]];. 
	0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, //    float4 bgfx_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x32, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // ragData2 [[color
	0x28, 0x32, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, // (2)]];.    float
	0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x33, // 4 bgfx_FragData3
	0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x33, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, //  [[color(3)]];. 
	0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, //    float4 bgfx_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x34, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // ragData4 [[color
	0x28, 0x34, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, // (4)]];.    float
	0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x35, // 4 bgfx_FragData5
	0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x35, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, //  [[color(5)]];. 
	0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, //    float4 bgfx_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x36, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // ragData6 [[color
	0x28, 0x36, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, // (6)]];.    float
	0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x37, // 4 bgfx_FragData7
	0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x37, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, //  [[color(7)]];.}
	0x3b, 0x0a, 0x0a, 0x66, 0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // ;..fragment xlat
	0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // MtlMain_out xlat
	0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x28, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, // MtlMain(constant
	0x20, 0x5f, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, //  _Global& _mtl_u
	0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, //  [[buffer(0)]]).
	0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, // {.    xlatMtlMai
	0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x6f, 0x75, 0x74, 0x20, 0x3d, 0x20, 0x7b, 0x7d, 0x3b, 0x0a, // n_out out = {};.
	0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, //     out.bgfx_Fra
	0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, // gData0 = _mtl_u.
	0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // bgfx_clear_color
	0x5b, 0x30, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x62, 0x67, 0x66, // [0];.    out.bgf
	0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x31, 0x20, 0x3d, 0x20, 0x5f, 0x6d, // x_FragData1 = _m
	0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, // tl_u.bgfx_clear_
	0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x31, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, // color[1];.    ou
	0x74, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x32, // t.bgfx_FragData2
	0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, //  = _mtl_u.bgfx_c
	0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x32, 0x5d, 0x3b, 0x0a, 0x20, // lear_color[2];. 
	0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, //    out.bgfx_Frag
	0x44, 0x61, 0x74, 0x61, 0x33, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, // Data3 = _mtl_u.b
	0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, // gfx_clear_color[
	0x33, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x62, 0x67, 0x66, 0x78, // 3];.    out.bgfx
	0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x34, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, // _FragData4 = _mt
	0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, // l_u.bgfx_clear_c
	0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x34, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, // olor[4];.    out
	0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x35, 0x20, // .bgfx_FragData5 
	0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, // = _mtl_u.bgfx_cl
	0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x35, 0x5d, 0x3b, 0x0a, 0x20, 0x20, // ear_color[5];.  
	0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, //   out.bgfx_FragD
	0x61, 0x74, 0x61, 0x36, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, // ata6 = _mtl_u.bg
	0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x36, // fx_clear_color[6
	0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, // ];.    out.bgfx_
	0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x37, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, // FragData7 = _mtl
	0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, // _u.bgfx_clear_co
	0x6c, 0x6f, 0x72, 0x5b, 0x37, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, // lor[7];.    retu
	0x72, 0x6e, 0x20, 0x6f, 0x75, 0x74, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00, 0x00, 0x80, 0x00,       // rn out;.}......
};
extern const uint8_t* fs_clear7_pssl;
extern const uint32_t fs_clear7_pssl_size;
