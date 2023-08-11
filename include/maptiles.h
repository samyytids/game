#ifndef MAPTILES_H
#define MAPTILES_H

// Mine
#include "bn_affine_bg_ptr.h"

// Butano
#include "bn_vector.h"
#include "bn_span.h"
#include "bn_affine_bg_map_cell.h"

namespace gm
{
    class MapTiles
    {
        private:
        bn::vector<int,32> _no_collision_tiles;
        bn::vector<int,32> _collision_tiles;
        bn::vector<int,32> _encounter_tiles;

        public:
        MapTiles(bn::span<const bn::affine_bg_map_cell> cells);
        [[nodiscard]] bn::vector<int,32> NoCollisionTiles();
        [[nodiscard]] bn::vector<int,32> CollisionTiles();
        [[nodiscard]] bn::vector<int,32> EncounterTiles();
    };
}
#endif