#include "custombg.h"

namespace gm
{
    CustomBg::CustomBg(bn::affine_bg_ptr bg_ptr, bn::camera_ptr camera) : _bg_ptr(bg_ptr), _map_cells(bg_ptr.map().cells_ref().value()), _map_tiles(_map_cells),
        _camera(camera)
        {
            bg_ptr.set_camera(camera);
            _map_size = bg_ptr.dimensions().width();
        }

    bn::vector<int, 32> CustomBg::GetEncounterTiles(){
        return _map_tiles.EncounterTiles();
    }

    bn::vector<int, 32> CustomBg::GetCollisionTiles(){
        return _map_tiles.CollisionTiles();
    }

    int CustomBg::GetMapCellTileIndex(const bn::fixed_point* location){
        int cell = (((location->x() + _map_size/2)/8).integer() - 1) + (((location->y() + _map_size/2)/8).integer() -1)*64;
        return _map_cells.at(cell);
    }
}