//Butano

//Mine
#include "state.h"

namespace gm
{
    StateMachine::StateMachine() : current_scene(SceneType::INTRO), current_player_state(State::STATIONARY), current_player_direction(Direction::DOWN){}

    State StateMachine::GetPlayerState() const{
        return current_player_state;
    }

    void StateMachine::SetPlayerState(State player_state){
        current_player_state = player_state;
    }

    SceneType StateMachine::GetScene() const{
        return current_scene;
    }

    void StateMachine::SetScene(SceneType scene){
        current_scene = scene;
    }

    Direction StateMachine::GetPlayerDirection() const{
        return current_player_direction;
    }

    void StateMachine::SetPlayerDirection(Direction direction){
        current_player_direction = direction;
    }
}