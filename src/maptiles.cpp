// Mine
#include "maptiles.h"

// Butano
#include "bn_log.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_map_ptr.h"
#include "bn_span.h"
#include "bn_optional.h"
#include "bn_string.h"

namespace gm
{
    MapTiles::MapTiles(bn::span<const bn::affine_bg_map_cell> cells)
    {
        // Essentials
        bool process_map = false;
        int index = 0;
        int empties = 0;
        _no_collision_tiles = {};
        _collision_tiles = {};
        _encounter_tiles = {};

        while(!process_map)
        {
            if(cells.at(index) == 0){
                ++empties;
                if(empties > 3){
                    process_map = true;
                }
            } else {
                if(empties == 0){
                    _no_collision_tiles.push_back(cells.at(index));
                } else if (empties == 1){
                    _collision_tiles.push_back(cells.at(index));
                } else if (empties == 2) {
                    _encounter_tiles.push_back(cells.at(index));
                }
            }
            ++index;
        }
    }

    // Getters
    bn::vector<int,32> MapTiles::NoCollisionTiles(){
        return _no_collision_tiles;
    }

    bn::vector<int,32> MapTiles::CollisionTiles(){
        return _collision_tiles;
    }

    bn::vector<int,32> MapTiles::EncounterTiles(){
        return _encounter_tiles;
    }
}