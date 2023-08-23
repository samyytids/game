#ifndef SCENE_H
#define SCENE_H

#include "custombg.h"
#include "state.h"
#include "player.h"
#include "bn_core.h"
#include "npc.h"
#include "bn_camera_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_vector.h"

namespace gm
{
    class Scene
    {
        private: 
        CustomBg* _bg;
        Player* _player;
        bn::camera_ptr _camera;

        public:
        Scene(Player* player, CustomBg* bg, bn::camera_ptr camera) : _bg(bg), _player(player), _camera(camera){};
        virtual ~Scene() = default;
        virtual void execute() = 0;
    };
}

#endif