#ifndef SCENE1_H
#define SCENE1_H

#include "scene.h"

namespace gm 
{
    class Scene1 : public Scene
    {
        private:
        CustomBg* _bg;
        Player* _player;
        bn::camera_ptr _camera;
        bn::array<bn::fixed_point, 32> _starting_positions;
        bn::vector<NPC, 3> _npcs;

        public:
        Scene1(Player* player, CustomBg* bg, bn::camera_ptr camera); 
        void execute();
    };
}

#endif 