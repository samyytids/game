#ifndef NPC_H
#define NPC_H

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_array.h"
#include "bn_string_view.h"
#include "bn_log.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_tiles_item.h"

namespace gm
{
    class NPC{
        private:
        bn::optional<bn::sprite_ptr> _sprite;
        bn::optional<bn::sprite_tiles_item> _sprite_tiles;
        bn::camera_ptr _camera;
        bn::array<bn::string_view, 2> _voice_lines;
        bn::array<bn::string_view, 2> _yes_no_dialogue;
        bn::optional<bn::sprite_animate_action<4>> _animation;

        public:
        NPC(bn::sprite_ptr sprite, bn::sprite_tiles_item sprite_tiles, bn::camera_ptr camera);
        NPC(bn::sprite_ptr sprite, bn::sprite_animate_action<4> animation, bn::camera_ptr camera);
        NPC(bn::sprite_ptr sprite, bn::array<bn::string_view, 2> voice_lines, bn::camera_ptr camera);
        NPC(bn::sprite_ptr sprite, bn::array<bn::string_view, 2> voice_lines, bn::array<bn::string_view, 2> yes_no_dialogue, bn::camera_ptr camera);

        void animate();
    };
} // namespace gm


#endif