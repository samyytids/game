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
#include "bn_fixed_point.h"
#include "state.h"
#include "hitbox.h"
#include "custombg.h"
#include "bn_sprite_animate_actions.h"

namespace gm
{
    class NPC{
        private:
        bn::optional<bn::sprite_ptr> _sprite;
        bn::optional<bn::sprite_tiles_item> _sprite_tiles;
        bn::array<bn::string_view, 2> _voice_lines;
        bn::array<bn::string_view, 2> _yes_no_dialogue;
        bn::optional<bn::sprite_animate_action<4>> _animation;
        bn::camera_ptr _camera;
        bn::array<Direction, 32> _directions;
        int _movement_index = 0;
        int _movement_increment = 16;
        bn::optional<Hitbox> _hitbox;
        bn::fixed_point _position;
        CustomBg* _bg;
        bn::fixed_point movement_vector;
        bn::sprite_animate_action<4> _walk_animation;

        void Move();
        bool CheckCollision();
        void GetWalkAnimation(Direction direction);

        public:
        NPC(bn::sprite_ptr sprite, bn::sprite_tiles_item sprite_tiles, bn::camera_ptr camera, bn::array<Direction, 32> pathing, CustomBg* bg);
        bn::fixed_point GetPosition();
        void CheckMovement();
    };
} // namespace gm


#endif