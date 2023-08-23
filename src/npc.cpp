#include "npc.h"

namespace gm
{

    NPC::NPC(bn::sprite_ptr sprite, bn::sprite_tiles_item sprite_tiles, bn::camera_ptr camera, bn::array<Direction, 32> pathing, CustomBg* bg): _sprite(sprite), _sprite_tiles(sprite_tiles), _walk_animation(bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 5, 3, 4, 3)), _camera(camera){
        _sprite.value().set_camera(_camera);
        _directions = pathing;
        _position = bn::fixed_point(_sprite.value().position().x(), _sprite.value().position().y());
        _hitbox = Hitbox(bn::fixed_point(_sprite.value().position().x(), _sprite.value().position().y()), 8, 8);
        _bg = bg;
    }

    bn::fixed_point NPC::GetPosition(){
        return _sprite.value().position();
    }

    void NPC::CheckMovement(){
        switch (_directions[_movement_index]){
            case Direction::UP:
                if (_movement_increment == 16){
                    GetWalkAnimation(_directions[_movement_index]);
                    if (!CheckCollision()){
                        return;
                    }
                }
            movement_vector = bn::fixed_point(0,-1);
            Move();
                break;
            case Direction::DOWN:
                if (_movement_increment == 16){
                    GetWalkAnimation(_directions[_movement_index]);
                    if (!CheckCollision()){
                        return;
                    }
                }
            movement_vector = bn::fixed_point(0,1);
            Move();
                break;
            case Direction::LEFT:
                if (_movement_increment == 16){
                    GetWalkAnimation(_directions[_movement_index]);
                    if (!CheckCollision()){
                        return;
                    }
                }
            movement_vector = bn::fixed_point(-1,0);
            Move();
                break;
            case Direction::RIGHT:
                if (_movement_increment == 16){
                    GetWalkAnimation(_directions[_movement_index]);
                    if (!CheckCollision()){
                        return;
                    }
                }
            movement_vector = bn::fixed_point(1,0);
            Move();
                break;
            default:
                _movement_increment = 16;
                _movement_index = 0;
        }
    }

    void NPC::Move(){
        --_movement_increment;
        if (_movement_increment == 0){
            _movement_increment = 16;
            ++_movement_index;
        }
        _walk_animation.update();
        _sprite.value().set_position(_sprite.value().position() + movement_vector);
        _position.set_y(_position.y() + movement_vector.y());
        _position.set_x(_position.x() + movement_vector.x());
        BN_LOG(_position.x(), ", ", _position.y());
        BN_LOG("======");
    }

    bool NPC::CheckCollision(){
        bn::fixed_point collision_position;
        switch(_directions[_movement_index]){
            case Direction::UP:
                collision_position = bn::fixed_point(_position.x(), _position.y()-16);
                return _hitbox.value().CheckAdjacentTile(&collision_position, _bg) && _hitbox.value().CheckForOtherHitboxes(&collision_position, &_position, _bg);
                
            case Direction::DOWN:
                collision_position = bn::fixed_point(_position.x(), _position.y()+16);
                return _hitbox.value().CheckAdjacentTile(&collision_position, _bg) && _hitbox.value().CheckForOtherHitboxes(&collision_position, &_position, _bg);
                
            case Direction::LEFT:
                collision_position = bn::fixed_point(_position.x()-16, _position.y());
                return _hitbox.value().CheckAdjacentTile(&collision_position, _bg) && _hitbox.value().CheckForOtherHitboxes(&collision_position, &_position, _bg);
                
            case Direction::RIGHT:
                collision_position = bn::fixed_point(_position.x()+16, _position.y());
                return _hitbox.value().CheckAdjacentTile(&collision_position, _bg) && _hitbox.value().CheckForOtherHitboxes(&collision_position, &_position, _bg);
                
            default:
                BN_LOG("Reset sprite has bugged");
        }
        return true;
    }

    void NPC::GetWalkAnimation(Direction direction){
        switch(direction) {
            case Direction::UP:
                if (_walk_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 5, 3, 4, 3).graphics_indexes()){
                    _walk_animation = bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 5, 3, 4, 3);
                    _sprite.value().set_horizontal_flip(false);
                }
                break;
            case Direction::DOWN:
                if (_walk_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 2, 0, 1, 0).graphics_indexes()){
                    _walk_animation = bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 2, 0, 1, 0);
                    _sprite.value().set_horizontal_flip(false);
                }
                break;
            case Direction::LEFT:
                if (_walk_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 8, 6, 7, 6).graphics_indexes() || _sprite.value().horizontal_flip()) {
                    _walk_animation = bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 8, 6, 7, 6);
                    _sprite.value().set_horizontal_flip(false);
                }
                break;
            case Direction::RIGHT:
                if (_walk_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 8, 6, 7, 6).graphics_indexes() || !_sprite.value().horizontal_flip()){
                    _walk_animation = bn::create_sprite_animate_action_forever(_sprite.value(), 8, _sprite_tiles.value(), 8, 6, 7, 6);
                    _sprite.value().set_horizontal_flip(true);
                }
                break;
            default:
                BN_LOG("Get walking animation has bugged");
        }
    }
}