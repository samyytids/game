#ifndef HITBOX_H
#define HITBOX_H

#include "bn_fixed_point.h"
#include "state.h"
#include "custombg.h"
#include "bn_vector.h"
#include "bn_log.h"

namespace gm
{
    class Hitbox{
        private:
            bn::fixed_point _position;
            int _width;
            int _height;
        public:
            Hitbox(bn::fixed_point position,  int width, int height);
            bool CheckAdjacentTile(const bn::fixed_point* position, CustomBg* bg);
            bool CheckForOtherHitboxes(const bn::fixed_point* collision_position, const bn::fixed_point* current_position, CustomBg* bg);
            //Also needs hitbox positions ^
            bn::fixed_point GetPosition() const;
            int GetWidth() const;
            int GetHeight() const;
            void SetPosition(bn::fixed_point position);
            void SetWidth(int width);
            void SetHeight(int height);   
    };
} 


#endif