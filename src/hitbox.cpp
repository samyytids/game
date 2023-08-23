#include "hitbox.h"

namespace gm
{
    Hitbox::Hitbox(bn::fixed_point position, int width, int height) : _position(position), _width(width), _height(height){}

    bool Hitbox::CheckAdjacentTile(const bn::fixed_point* position, CustomBg* bg){
        int cell_to_check = bg->GetMapCellTileIndex(position);
        bn::vector<int, 32> collision_tiles = bg->GetCollisionTiles();
        if (cell_to_check >= collision_tiles.front() && cell_to_check <= collision_tiles.back()){
            return false;
        }
        return true;
    }

    bool Hitbox::CheckForOtherHitboxes(const bn::fixed_point* collision_position, const bn::fixed_point* current_position, CustomBg* bg) {
        return bg->CheckCoordinateGrid(collision_position, current_position);
    }
    
    bn::fixed_point Hitbox::GetPosition() const {
        return _position;
    }

    int Hitbox::GetWidth() const {
        return _width;
    }

    int Hitbox::GetHeight() const {
        return _height;
    }

    void Hitbox::SetPosition(bn::fixed_point position) {
        _position = position;
    }

    void Hitbox::SetWidth(int width) {
        _width = width;
    }

    void Hitbox::SetHeight(int height) {
        _height = height;
    }
}
