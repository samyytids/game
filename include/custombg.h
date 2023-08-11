#ifndef CUSTOMBG_H
#define CUSTOMBG_H

#include "bn_affine_bg_ptr.h"
#include "maptiles.h"
#include "bn_vector.h"
#include "bn_camera_ptr.h"
#include "bn_affine_bg_map_ptr.h"
#include "bn_span.h"
#include "bn_affine_bg_map_cell.h"
#include "bn_fixed_point.h"
#include "bn_size.h"

namespace gm
{
    class CustomBg
    {
        private:
            bn::affine_bg_ptr _bg_ptr;
            bn::span<const bn::affine_bg_map_cell> _map_cells;
            MapTiles _map_tiles;
            bn::camera_ptr _camera;
            int _map_size;

        public:
            CustomBg(bn::affine_bg_ptr bg_ptr, bn::camera_ptr camera);
            bn::vector<int,32> GetEncounterTiles();
            bn::vector<int,32> GetCollisionTiles();
            int GetMapCellTileIndex(const bn::fixed_point* location);
    };
}

#endif