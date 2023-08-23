#include "scene1.h"
#include "bn_sprite_items_gooch.h"
namespace gm
{
    Scene1::Scene1(Player* player, CustomBg* bg, bn::camera_ptr camera) : Scene(player, bg, camera), _camera(camera)
    {
        _bg = bg;
        _player = player;
        _player->Spawn(bn::fixed_point(-8,0));
    }

    void Scene1::execute(){
        NPC npc1 = NPC(bn::sprite_items::gooch.create_sprite(8,16), bn::sprite_items::gooch.tiles_item(),
            _camera, {Direction::LEFT, Direction::LEFT, Direction::DOWN, Direction::DOWN, 
            Direction::RIGHT, Direction::RIGHT, Direction::UP, Direction::UP, Direction::END}, _bg);
        NPC npc2 = NPC(bn::sprite_items::gooch.create_sprite(8,80), bn::sprite_items::gooch.tiles_item(),
            _camera, {Direction::LEFT, Direction::LEFT, Direction::DOWN, Direction::DOWN, 
            Direction::RIGHT, Direction::RIGHT, Direction::UP, Direction::UP, Direction::END}, _bg);
        NPC npc3 = NPC(bn::sprite_items::gooch.create_sprite(8,144), bn::sprite_items::gooch.tiles_item(),
            _camera, {Direction::LEFT, Direction::LEFT, Direction::DOWN, Direction::DOWN, 
            Direction::RIGHT, Direction::RIGHT, Direction::UP, Direction::UP, Direction::END}, _bg);
        _npcs.push_back(npc1);
        _npcs.push_back(npc2);
        _npcs.push_back(npc3);
        
        _starting_positions[0] = bn::fixed_point(8,16);
        _starting_positions[1] = bn::fixed_point(8,80);
        _starting_positions[2] = bn::fixed_point(8,144);
        _bg->SetUpCoordinateGrid(&_starting_positions);
        while (true) {
            for (auto& npc: _npcs) {
                npc.CheckMovement();
            }
            _player->CheckMovement();
            bn::core::update();
        }
    }
}