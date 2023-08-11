#include "player.h"
#include "bn_keypad.h"

namespace bn {

    bn::ostringstream& operator<<(bn::ostringstream& stream, gm::SceneType scene_type) {
        switch(scene_type) {
            case gm::SceneType::INTRO:
                stream.append("INTRO");
                break;
            case gm::SceneType::TEST:
                stream.append("TEST");
                break;
            default:
                BN_LOG("Missing enum value for log overload has bugged");
        }
        return stream;
    }

    bn::ostringstream& operator<<(bn::ostringstream& stream, gm::State player_state) {
        switch(player_state) {
            case gm::State::WALKING:
                stream.append("WALKING");
                break;
            case gm::State::RUNNING:
                stream.append("RUNNING");
                break;
            case gm::State::LISTENING:
                stream.append("LISTENING");
                break;
            case gm::State::PAUSED:
                stream.append("PAUSED");
                break;
            case gm::State::STATIONARY:
                stream.append("STATIONARY");
                break;
            default:
                BN_LOG("Missing enum value for log overload has bugged");
        }
        return stream;
    }

    bn::ostringstream& operator<<(bn::ostringstream& stream, gm::Direction player_direction) {
        switch(player_direction) {
            case gm::Direction::UP:
                stream.append("UP");
                break;
            case gm::Direction::DOWN:
                stream.append("DOWN");
                break;
            case gm::Direction::LEFT:
                stream.append("LEFT");
                break;
            case gm::Direction::RIGHT:
                stream.append("RIGHT");
                break;
            default:
                BN_LOG("Missing enum value for log overload has bugged");
        }
        return stream;
    }

} 

namespace gm
{

    Player::Player(StateMachine* state_machine, bn::sprite_ptr sprite, bn::sprite_tiles_item sprite_tiles, bn::camera_ptr camera, Hitbox* hitbox, CustomBg* bg) :
    _state_machine(state_machine), _camera(camera), _sprite(sprite), 
    _sprite_tiles(sprite_tiles), _run_animation(bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 7)),
    _walk_animation(bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 5, 3, 4, 3)), _hitbox(hitbox), _bg(bg)
    {
        _sprite.set_camera(_camera);
    }

    void Player::Spawn(bn::fixed_point spawn_location){
        _sprite.set_position(spawn_location);
        _camera.set_position(spawn_location);
        _position.set_x(spawn_location.x());
        _position.set_y(spawn_location.y());
        _hitbox->SetPosition(spaw_location);
    }

    void Player::CheckMovement(){
        if (_state_machine->GetPlayerState() == State::PAUSED || _state_machine->GetPlayerState() == State::LISTENING){
            BN_LOG("Don't bother checking for movement code, I am listening/paused");
            return;
        } 
    
        switch(_state_machine->GetPlayerState()){
            case State::STATIONARY:
                HandleStationary();
                break;
            case State::TURNING:
                HandleTurning(_state_machine->GetPlayerDirection());
                break;
            case State::RUNNING:
                HandleRunning(_state_machine->GetPlayerDirection(), _movement_vector);
                break;
            case State::WALKING:
                HandleWalking(_state_machine->GetPlayerDirection(), _movement_vector);
                break;
            default:
                BN_LOG("No movement behaviour for state");
                break;
        }
    }

    void Player::HandleStationary() {
        if (!bn::keypad::up_held() && !bn::keypad::down_held() && !bn::keypad::left_held() && !bn::keypad::right_held()){
            ResetSprite(_state_machine->GetPlayerDirection());
        }
        CheckForTurning();
        if (bn::keypad::b_held()){
            CheckForRunning();
            return;
        }
        else {
            CheckForWalking();
        }        
    }

    void Player::CheckForTurning() {
        BN_LOG("You spin me right round", _state_machine->GetPlayerDirection(), ", ",_state_machine->GetPlayerState());
        if ((bn::keypad::up_pressed() && _state_machine->GetPlayerDirection() != Direction::UP) || (_state_machine->GetPlayerState() == State::TURNING && _state_machine->GetPlayerDirection() == Direction::UP)){
            HandleTurning(Direction::UP);
            return;
        }
        else if ((bn::keypad::down_pressed() && _state_machine->GetPlayerDirection() != Direction::DOWN) || (_state_machine->GetPlayerState() == State::TURNING && _state_machine->GetPlayerDirection() == Direction::DOWN)){
            HandleTurning(Direction::DOWN);
            return;
        } 
        if ((bn::keypad::left_pressed() && _state_machine->GetPlayerDirection() != Direction::LEFT) || (_state_machine->GetPlayerState() == State::TURNING && _state_machine->GetPlayerDirection() == Direction::LEFT)){
            HandleTurning(Direction::LEFT);
            return;
        } 
        else if ((bn::keypad::right_pressed() && _state_machine->GetPlayerDirection() != Direction::RIGHT) || (_state_machine->GetPlayerState() == State::TURNING && _state_machine->GetPlayerDirection() == Direction::RIGHT)){
            HandleTurning(Direction::RIGHT);
            return;
        }
    }

    void Player::CheckForRunning() {
        if (bn::keypad::up_held() || (_state_machine->GetPlayerState() == State::RUNNING && _state_machine->GetPlayerDirection() == Direction::UP)){
            if (!CheckCollision(Direction::UP)){
                return;
            }
            _movement_vector = bn::fixed_point(bn::fixed(0), bn::fixed(-2));
            GetRunAnimation(Direction::UP);
            HandleRunning(Direction::UP, _movement_vector);
            return;
        }
        else if (bn::keypad::down_held() || (_state_machine->GetPlayerState() == State::RUNNING && _state_machine->GetPlayerDirection() == Direction::DOWN)){
            if (!CheckCollision(Direction::DOWN)){
                return;
            }
            _movement_vector = bn::fixed_point(bn::fixed(0), bn::fixed(2));
            GetRunAnimation(Direction::DOWN);
            HandleRunning(Direction::DOWN, _movement_vector);
            return;
        } 
        if (bn::keypad::left_held() || (_state_machine->GetPlayerState() == State::RUNNING && _state_machine->GetPlayerDirection() == Direction::LEFT)){
            if (!CheckCollision(Direction::LEFT)){
                return;
            }
            _movement_vector =  bn::fixed_point(bn::fixed(-2), bn::fixed(0));
            GetRunAnimation(Direction::LEFT);
            HandleRunning(Direction::LEFT, _movement_vector);
            return;
        }
        else if (bn::keypad::right_held() || (_state_machine->GetPlayerState() == State::RUNNING && _state_machine->GetPlayerDirection() == Direction::RIGHT)){
            if (!CheckCollision(Direction::RIGHT)){
                return;
            }
            _movement_vector = bn::fixed_point(bn::fixed(2), bn::fixed(0));
            GetRunAnimation(Direction::RIGHT);
            HandleRunning(Direction::RIGHT, _movement_vector);
            return;
        }
    }

    void Player::CheckForWalking() {
        if ((_state_machine->GetPlayerState() != State::TURNING && bn::keypad::up_held()) || (_state_machine->GetPlayerState() == State::WALKING && _state_machine->GetPlayerDirection() == Direction::UP)){
            if (!CheckCollision(Direction::UP)){
                return;
            }
            _movement_vector = bn::fixed_point(bn::fixed(0), bn::fixed(-1));
            GetWalkAnimation(Direction::UP);
            HandleWalking(Direction::UP, _movement_vector);
            return;
        }
        else if ((_state_machine->GetPlayerState() != State::TURNING && bn::keypad::down_held()) || (_state_machine->GetPlayerState() == State::WALKING && _state_machine->GetPlayerDirection() == Direction::DOWN)){
            if (!CheckCollision(Direction::DOWN)){
                return;
            }
            _movement_vector = bn::fixed_point(bn::fixed(0), bn::fixed(1));
            GetWalkAnimation(Direction::DOWN);
            HandleWalking(Direction::DOWN, _movement_vector);
            return;
        } 
        if ((_state_machine->GetPlayerState() != State::TURNING && bn::keypad::left_held()) || (_state_machine->GetPlayerState() == State::WALKING && _state_machine->GetPlayerDirection() == Direction::LEFT)){
            if (!CheckCollision(Direction::LEFT)){
                return;
            }
            _movement_vector = bn::fixed_point(bn::fixed(-1), bn::fixed(0));
            GetWalkAnimation(Direction::LEFT);
            HandleWalking(Direction::LEFT, _movement_vector);
            return;
        }
        else if ((_state_machine->GetPlayerState() != State::TURNING && bn::keypad::right_held()) || (_state_machine->GetPlayerState() == State::WALKING && _state_machine->GetPlayerDirection() == Direction::RIGHT)){
            if (!CheckCollision(Direction::RIGHT)){
                return;
            }
            _movement_vector = bn::fixed_point(bn::fixed(1), bn::fixed(0));
            GetWalkAnimation(Direction::RIGHT);
            HandleWalking(Direction::RIGHT, _movement_vector);
            return;
        }
    }

    void Player::HandleTurning(Direction direction){
        if (_turning_frames <= 0){
            _turning_frames = 5;
            _state_machine->SetPlayerState(State::STATIONARY);
            return;
        } 
        _turning_frames -=1;
        Turn(direction);
        return;
    }
    
    void Player::HandleRunning(Direction direction, bn::fixed_point movement){
        _run_animation.update();
        if (_movement_frames <= 0){
            _movement_frames = 16;
            _run_animation.update();
            _state_machine->SetPlayerState(State::STATIONARY);
            return;
        }
        else {
            _movement_frames -= 2;
            Run(direction, movement);
        }
        return;
    }

    void Player::HandleWalking(Direction direction, bn::fixed_point movement){
        _walk_animation.update();
        if (_movement_frames <= 0){
            _movement_frames = 16;
            _walk_animation.update();
            _state_machine->SetPlayerState(State::STATIONARY);
            return;
        }
        else {
            _movement_frames -= 1;
            Walk(direction, movement);
        }
        return;
    }

    void Player::Run(Direction direction, bn::fixed_point movement){
        UpdatePosition(movement);
        _state_machine->SetPlayerState(State::RUNNING);
        _state_machine->SetPlayerDirection(direction);
    }

    void Player::Turn(Direction direction){
        TurnSprite(direction);
        _state_machine->SetPlayerState(State::TURNING);
        _state_machine->SetPlayerDirection(direction);
    }
    
    void Player::Walk(Direction direction, bn::fixed_point movement){
        UpdatePosition(movement);
        _state_machine->SetPlayerState(State::WALKING);
        _state_machine->SetPlayerDirection(direction);
    }

    void Player::UpdatePosition(bn::fixed_point movement_vector) {
        _sprite.set_position(_sprite.position() + movement_vector);
        _camera.set_position(_camera.position() + movement_vector);
        _position.set_y(_position.y() + movement_vector.y());
        _position.set_x(_position.x() + movement_vector.x());
        _hitbox->SetPosition(_position);
    }

    void Player::TurnSprite(Direction direction) {
        switch(direction) {
            case Direction::UP:
                _sprite.set_tiles(_sprite_tiles.create_tiles(3));
                _sprite.set_horizontal_flip(false);
                break;
            case Direction::DOWN:
                _sprite.set_tiles(_sprite_tiles.create_tiles(0));
                _sprite.set_horizontal_flip(false);
                break;
            case Direction::LEFT:
                _sprite.set_tiles(_sprite_tiles.create_tiles(6));
                _sprite.set_horizontal_flip(false);
                break;
            case Direction::RIGHT:
                _sprite.set_tiles(_sprite_tiles.create_tiles(6));
                _sprite.set_horizontal_flip(true);
                break;
            default:
                BN_LOG("Turn sprite has bugged");
        }
    }

    void Player::GetRunAnimation(Direction direction){
        switch(direction) {
            case Direction::UP:
                if (_run_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 5, 4).graphics_indexes()){
                    _run_animation = bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 5, 4);
                    _sprite.set_horizontal_flip(false);
                }
                break;
            case Direction::DOWN:
                if (_run_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 2, 1).graphics_indexes()){
                    _run_animation = bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 2, 1);
                    _sprite.set_horizontal_flip(false);
                }
                break;
            case Direction::LEFT:
                BN_LOG("Left animation fix");
                if (_run_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 7).graphics_indexes() || _sprite.horizontal_flip()) {
                    BN_LOG("Left animation fix 2");
                    _run_animation = bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 7);
                    _sprite.set_horizontal_flip(false);
                }
                break;
            case Direction::RIGHT:
                BN_LOG("Right animation fix");
                if (_run_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 7).graphics_indexes() || !_sprite.horizontal_flip()){
                    BN_LOG("Right animation fix 2");
                    _run_animation = bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 7);
                    _sprite.set_horizontal_flip(true);
                }
                break;
            default:
                BN_LOG("Get run animation has bugged");
        }
    }

    void Player::GetWalkAnimation(Direction direction) {
        switch(direction) {
            case Direction::UP:
                if (_walk_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 5, 3, 4, 3).graphics_indexes()){
                    _walk_animation = bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 5, 3, 4, 3);
                    _sprite.set_horizontal_flip(false);
                }
                break;
            case Direction::DOWN:
                if (_walk_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 2, 0, 1, 0).graphics_indexes()){
                    _walk_animation = bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 2, 0, 1, 0);
                    _sprite.set_horizontal_flip(false);
                }
                break;
            case Direction::LEFT:
                if (_walk_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 6, 7, 6).graphics_indexes() || _sprite.horizontal_flip()) {
                    _walk_animation = bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 6, 7, 6);
                    _sprite.set_horizontal_flip(false);
                }
                break;
            case Direction::RIGHT:
                if (_walk_animation.graphics_indexes() != bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 6, 7, 6).graphics_indexes() || !_sprite.horizontal_flip()){
                    _walk_animation = bn::create_sprite_animate_action_forever(_sprite, 8, _sprite_tiles, 8, 6, 7, 6);
                    _sprite.set_horizontal_flip(true);
                }
                break;
            default:
                BN_LOG("Get walking animation has bugged");
        }
    }

    void Player::ResetSprite(Direction direction) {
        switch(direction) {
            case Direction::UP:
                _sprite.set_tiles(_sprite_tiles.create_tiles(3));
                _sprite.set_horizontal_flip(false);
                break;
            case Direction::DOWN:
                _sprite.set_tiles(_sprite_tiles.create_tiles(0));
                _sprite.set_horizontal_flip(false);
                break;
            case Direction::LEFT:
                _sprite.set_tiles(_sprite_tiles.create_tiles(6));
                _sprite.set_horizontal_flip(false);
                break;
            case Direction::RIGHT:
                _sprite.set_tiles(_sprite_tiles.create_tiles(6));
                _sprite.set_horizontal_flip(true);
                break;
            default:
                BN_LOG("Reset sprite has bugged");
        }
    }

    bn::fixed_point Player::GetPosition(){
        return _position;
    }

    bool Player::CheckCollision(Direction direction){
        bn::fixed_point collision_position;
        switch(direction){
            case Direction::UP:
                collision_position = bn::fixed_point(_position.x(), _position.y()-16);
                return _hitbox->CheckAdjacentTile(&collision_position, _bg);
                
            case Direction::DOWN:
                collision_position = bn::fixed_point(_position.x(), _position.y()+16);
                return _hitbox->CheckAdjacentTile(&collision_position, _bg);
                
            case Direction::LEFT:
                collision_position = bn::fixed_point(_position.x()-16, _position.y());
                return _hitbox->CheckAdjacentTile(&collision_position, _bg);
                
            case Direction::RIGHT:
                collision_position = bn::fixed_point(_position.x()+16, _position.y());
                return _hitbox->CheckAdjacentTile(&collision_position, _bg);
                
            default:
                BN_LOG("Reset sprite has bugged");
        }
        return true;
    }
}