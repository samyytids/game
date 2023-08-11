#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"
#include "bn_log.h"
#include "bn_camera_ptr.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_fixed.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_item.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "hitbox.h"
#include "custombg.h"

namespace gm
{
    class Player{
        private:
        StateMachine* _state_machine;
        bn::camera_ptr _camera;
        int _turning_frames = 5;
        int _movement_frames = 16;
        bn::fixed_point _movement_vector;
        bn::sprite_ptr _sprite;
        bn::sprite_tiles_item _sprite_tiles;
        bn::sprite_animate_action<2> _run_animation;
        bn::sprite_animate_action<4> _walk_animation;
        bn::fixed_point _position;
        Hitbox* _hitbox;
        CustomBg* _bg;

        // Movement
        void HandleStationary();

        void CheckForRunning();
        void CheckForTurning();
        void CheckForWalking();

        void HandleRunning(Direction direction, bn::fixed_point movement);
        void HandleTurning(Direction direction);
        void HandleWalking(Direction direction, bn::fixed_point movement);
        
        void Run(Direction direction, bn::fixed_point movement);
        void Turn(Direction direction);
        void Walk(Direction direction, bn::fixed_point movement);

        void UpdatePosition(bn::fixed_point movement_vector);

        void TurnSprite(Direction direction);
        void GetRunAnimation(Direction direction);
        void GetWalkAnimation(Direction direction);
        void ResetSprite(Direction direction);

        bool CheckCollision(Direction direction);

        public:
        Player(StateMachine* state_machine, bn::sprite_ptr sprite, bn::sprite_tiles_item sprite_tiles, bn::camera_ptr camera, Hitbox* hitbox, CustomBg* bg);
        void CheckMovement();
        bn::fixed_point GetPosition();
        void Spawn(bn::fixed_point spawn_location);

        
        // void move();

    };
}

#endif