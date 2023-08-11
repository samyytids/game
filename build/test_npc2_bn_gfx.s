
@{{BLOCK(test_npc2_bn_gfx)

@=======================================================================
@
@	test_npc2_bn_gfx, 16x16@8, 
@	+ palette 64 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 128 + 256 = 384
@
@	Time-stamp: 2023-08-09, 22:01:10
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global test_npc2_bn_gfxTiles		@ 256 unsigned chars
	.hidden test_npc2_bn_gfxTiles
test_npc2_bn_gfxTiles:
	.word 0x37000000,0x37373737,0x37370000,0x37373737,0x37370000,0x37373737,0x37000000,0x37373737
	.word 0x0D000000,0x0D0D0D0D,0x16000000,0x0D0D0D0D,0x16000000,0x16011616,0x00000000,0x16161616
	.word 0x37373737,0x00000037,0x37373737,0x00003737,0x37373737,0x00003737,0x37373737,0x00000037
	.word 0x0D0D0D0D,0x0000000D,0x0D0D0D0D,0x00000016,0x16160116,0x00000016,0x16161616,0x00000000
	.word 0x37000000,0x16163719,0x37370000,0x37373719,0x37370000,0x37371919,0x37370000,0x19191919
	.word 0x16160000,0x19191919,0x00000000,0x37373737,0x00000000,0x37373737,0x00000000,0x00191919
	.word 0x19371616,0x00000037,0x19373737,0x00003737,0x19193737,0x00003737,0x19191919,0x00003737
	.word 0x19191919,0x00001616,0x37373737,0x00000000,0x37373737,0x00000000,0x19191900,0x00000000

	.section .rodata
	.align	2
	.global test_npc2_bn_gfxPal		@ 128 unsigned chars
	.hidden test_npc2_bn_gfxPal
test_npc2_bn_gfxPal:
	.hword 0x0000,0x4610,0x779B,0x7FFF,0x210F,0x2D70,0x39D3,0x5294
	.hword 0x5EF7,0x6B5A,0x2118,0x2D9F,0x31BB,0x2D6D,0x2D94,0x4657
	.hword 0x52DB,0x675D,0x3A5D,0x3A5B,0x42FF,0x4B1F,0x5B5F,0x18E8
	.hword 0x2A79,0x2F1F,0x2E77,0x36DA,0x42F7,0x433B,0x539D,0x0147
	.hword 0x1A27,0x3310,0x43F6,0x3683,0x42C8,0x530E,0x6354,0x622A
	.hword 0x76AC,0x7AEE,0x1C82,0x28A3,0x30E5,0x55C9,0x6E8C,0x2CC5
	.hword 0x3D27,0x6ED3,0x7337,0x3528,0x3D8C,0x20C8,0x290C,0x2919
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(test_npc2_bn_gfx)