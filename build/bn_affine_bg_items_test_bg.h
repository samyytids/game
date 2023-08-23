#ifndef BN_AFFINE_BG_ITEMS_TEST_BG_H
#define BN_AFFINE_BG_ITEMS_TEST_BG_H

#include "bn_affine_bg_item.h"

//{{BLOCK(test_bg_bn_gfx)

//======================================================================
//
//	test_bg_bn_gfx, 512x1536@8, 
//	+ palette 64 entries, not compressed
//	+ 16 tiles (t reduced) not compressed
//	+ affine map, not compressed, 64x192 
//	Total size: 128 + 1024 + 12288 = 13440
//
//	Time-stamp: 2023-08-23, 13:09:51
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TEST_BG_BN_GFX_H
#define GRIT_TEST_BG_BN_GFX_H

#define test_bg_bn_gfxTilesLen 1024
extern const bn::tile test_bg_bn_gfxTiles[32];

#define test_bg_bn_gfxMapLen 12288
extern const bn::affine_bg_map_cell test_bg_bn_gfxMap[12288];

#define test_bg_bn_gfxPalLen 128
extern const bn::color test_bg_bn_gfxPal[64];

#endif // GRIT_TEST_BG_BN_GFX_H

//}}BLOCK(test_bg_bn_gfx)

namespace bn::affine_bg_items
{
    constexpr inline affine_bg_item test_bg(
            affine_bg_tiles_item(span<const tile>(test_bg_bn_gfxTiles, 32), compression_type::NONE), 
            bg_palette_item(span<const color>(test_bg_bn_gfxPal, 64), bpp_mode::BPP_8, compression_type::NONE),
            affine_bg_map_item(test_bg_bn_gfxMap[0], size(64, 64), compression_type::NONE, 3));
}

#endif

