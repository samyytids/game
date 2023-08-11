#ifndef BN_SPRITE_ITEMS_GOOCH_H
#define BN_SPRITE_ITEMS_GOOCH_H

#include "bn_sprite_item.h"

//{{BLOCK(gooch_bn_gfx)

//======================================================================
//
//	gooch_bn_gfx, 16x288@8, 
//	+ palette 48 entries, not compressed
//	+ 72 tiles not compressed
//	Total size: 96 + 4608 = 4704
//
//	Time-stamp: 2023-08-10, 17:31:17
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GOOCH_BN_GFX_H
#define GRIT_GOOCH_BN_GFX_H

#define gooch_bn_gfxTilesLen 4608
extern const bn::tile gooch_bn_gfxTiles[144];

#define gooch_bn_gfxPalLen 96
extern const bn::color gooch_bn_gfxPal[48];

#endif // GRIT_GOOCH_BN_GFX_H

//}}BLOCK(gooch_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item gooch(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(gooch_bn_gfxTiles, 144), bpp_mode::BPP_8, compression_type::NONE, 9), 
            sprite_palette_item(span<const color>(gooch_bn_gfxPal, 48), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

