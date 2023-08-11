#ifndef HITBOX_H
#define HITBOX_H

#include "bn_fixed_point.h"
#include "state.h"
#include "custombg.h"
#include "bn_vector.h"

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
            //Also needs Tile information ^
            bool CheckForNPCs(Direction direction);
            //Also needs NPC positions ^
            bn::fixed_point GetPosition() const;
            int GetWidth() const;
            int GetHeight() const;
            void SetPosition(bn::fixed_point position);
            void SetWidth(int width);
            void SetHeight(int height);
            
            
    };
} 


#endif