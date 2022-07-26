static const uint8_t vs_base_dx9[413] =
{
	0x56, 0x53, 0x48, 0x05, 0xa4, 0x8b, 0xef, 0x49, 0x01, 0x00, 0x0f, 0x75, 0x5f, 0x6d, 0x6f, 0x64, // VSH....I...u_mod
	0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x04, 0x01, 0x00, 0x00, 0x04, 0x00, // elViewProj......
	0x78, 0x01, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0xfe, 0xff, 0x21, 0x00, 0x43, 0x54, 0x41, 0x42, // x.........!.CTAB
	0x1c, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x00, // ....W...........
	0x1c, 0x00, 0x00, 0x00, 0x04, 0x11, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, // ........P...0...
	0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........@.......
	0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x00, // u_modelViewProj.
	0x03, 0x00, 0x03, 0x00, 0x04, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x76, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, // vs_3_0.Microsoft
	0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, //  (R) HLSL Shader
	0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, //  Compiler 10.1..
	0x51, 0x00, 0x00, 0x05, 0x04, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, // Q..........?....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, // ................
	0x00, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x0f, 0x90, // ................
	0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0xe0, 0x1f, 0x00, 0x00, 0x02, // ................
	0x0a, 0x00, 0x00, 0x80, 0x01, 0x00, 0x0f, 0xe0, 0x05, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, // ................
	0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x90, 0x05, 0x00, 0x00, 0x03, 0x01, 0x00, 0x0f, 0x80, // ................
	0x01, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x55, 0x90, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, // ......U.........
	0x00, 0x00, 0xe4, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x05, 0x00, 0x00, 0x03, 0x01, 0x00, 0x0f, 0x80, // ................
	0x02, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0xaa, 0x90, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, // ................
	0x00, 0x00, 0xe4, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0f, 0x80, // ................
	0x03, 0x00, 0xe4, 0xa0, 0x05, 0x00, 0x00, 0x03, 0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0x80, // ................
	0x04, 0x00, 0x00, 0xa0, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, // ................
	0x01, 0x00, 0xe4, 0x80, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x90, // ................
	0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0xe4, 0x80, 0x01, 0x00, 0x00, 0x02, // ................
	0x01, 0x00, 0x0f, 0xe0, 0x01, 0x00, 0xe4, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00,                   // .............
};
