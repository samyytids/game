#ifndef BN_SPRITE_ITEMS_TEST_NPC_H
#define BN_SPRITE_ITEMS_TEST_NPC_H

#include "bn_sprite_item.h"

//{{BLOCK(test_npc_bn_gfx)

//======================================================================
//
//	test_npc_bn_gfx, 16x32@8, 
//	+ palette 64 entries, not compressed
//	+ 8 tiles not compressed
//	Total size: 128 + 512 = 640
//
//	Time-stamp: 2023-08-10, 12:28:20
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TEST_NPC_BN_GFX_H
#define GRIT_TEST_NPC_BN_GFX_H

#define test_npc_bn_gfxTilesLen 512
extern const bn::tile test_npc_bn_gfxTiles[16];

#define test_npc_bn_gfxPalLen 128
extern const bn::color test_npc_bn_gfxPal[64];

#endif // GRIT_TEST_NPC_BN_GFX_H

//}}BLOCK(test_npc_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item test_npc(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(test_npc_bn_gfxTiles, 16), bpp_mode::BPP_8, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(test_npc_bn_gfxPal, 64), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

