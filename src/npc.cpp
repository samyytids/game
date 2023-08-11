#include "npc.h"

namespace gm
{
    NPC::NPC(bn::sprite_ptr sprite, bn::sprite_tiles_item sprite_tiles, bn::camera_ptr camera):_sprite(sprite), _sprite_tiles(sprite_tiles),  _camera(camera){
        _animation = bn::create_sprite_animate_action_forever(_sprite.value(), 16, _sprite_tiles.value(), 0, 1, 2, 3);
        _sprite.value().set_camera(_camera);
    }

    NPC::NPC(bn::sprite_ptr sprite, bn::array<bn::string_view, 2> voice_lines, bn::camera_ptr camera):_sprite(sprite),  _camera(camera){
            _voice_lines = voice_lines;
        for (auto& item: _voice_lines){
            BN_LOG(item);
        }
        _sprite.value().set_camera(_camera);
    }

    NPC::NPC(bn::sprite_ptr sprite, bn::array<bn::string_view, 2> voice_lines, bn::array<bn::string_view, 2> yes_no_dialogue, bn::camera_ptr camera):
        _sprite(sprite),  _camera(camera){
        _voice_lines = voice_lines;
        _yes_no_dialogue = yes_no_dialogue;
        _sprite.value().set_camera(_camera);
    }
        
    
    NPC::NPC(bn::sprite_ptr sprite, bn::sprite_animate_action<4> animation, bn::camera_ptr camera): _sprite(sprite), _camera(camera){
        _animation = animation;
    }

    void NPC::animate(){
        _animation.value().update();
    }
}