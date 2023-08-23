#include "custombg.h"

namespace gm
{
    CustomBg::CustomBg(bn::affine_bg_ptr bg_ptr, bn::camera_ptr camera) : _bg_ptr(bg_ptr), _map_cells(bg_ptr.map().cells_ref().value()), _map_tiles(_map_cells),
        _camera(camera)
        {
            bg_ptr.set_camera(camera);
            _map_size = bg_ptr.dimensions().width();
            bg_ptr.set_wrapping_enabled(false);
        }

    bn::vector<int, 32> CustomBg::GetEncounterTiles(){
        return _map_tiles.EncounterTiles();
    }

    bn::vector<int, 32> CustomBg::GetCollisionTiles(){
        return _map_tiles.CollisionTiles();
    }

    int CustomBg::GetMapCellTileIndex(const bn::fixed_point* collision_position){
        int cell = (((collision_position->x() + _map_size/2)/8).integer()) + (((collision_position->y() + _map_size/2)/8).integer())*64;
        return _map_cells.at(cell);
    }

    void CustomBg::SetUpCoordinateGrid(bn::array<bn::fixed_point, 32>* entity_positions){
        int x;
        int y;
        for (auto& entity: *entity_positions){
            x = (((entity.x() + _map_size/2)-8)/16).integer();
            y = ((entity.y() + _map_size/2)/16).integer();
            co_ordinate_grid[x][y] = 1;
        }

    }

    bool CustomBg::CheckCoordinateGrid(const bn::fixed_point* collision_position, const bn::fixed_point* current_position){
        int x = (((collision_position->x() + _map_size/2)-8)/16).integer();
        int y = ((collision_position->y() + _map_size/2)/16).integer();
        int x2 = (((current_position->x() + _map_size/2)-8)/16).integer();
        int y2 = ((current_position->y() + _map_size/2)/16).integer();
        if (co_ordinate_grid[x][y] == 1){
            return false;
        }
        co_ordinate_grid[x2][y2] = 0;
        co_ordinate_grid[x][y] = 1;
        return true;
    }
}