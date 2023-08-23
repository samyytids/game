#ifndef STATE_H
#define STATE_H

namespace gm
{

    enum class SceneType
    {
        INTRO,
        TEST
    };

    enum class State
    {
        WALKING,
        RUNNING,
        LISTENING,
        PAUSED, 
        STATIONARY,
        TURNING
    };

    enum class Direction
    {
        UP,
        DOWN,
        LEFT, 
        RIGHT,
        END
    };

    class StateMachine
    {
        private:
        SceneType current_scene;
        State current_player_state;
        Direction current_player_direction;

        public: 
        StateMachine();
        SceneType GetScene() const;
        void SetScene(SceneType scene);
        State GetPlayerState() const;
        void SetPlayerState(State player_state);
        Direction GetPlayerDirection() const;
        void SetPlayerDirection(Direction player_direction);

    };
}

#endif