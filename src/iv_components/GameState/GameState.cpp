#include "GameState.hpp"

namespace iv
{
const StringIO< comp::GameState::State >::ValuesType StringIO< comp::GameState::State >::Values = 
{
    { comp::GameState::State::Empty, "Empty" },
    { comp::GameState::State::Running, "Running" },
    { comp::GameState::State::Paused, "Paused" },
    { comp::GameState::State::Ended, "Ended" }
};

}

namespace comp
{

GameState::GameState( iv::Instance * inst ) :
    cm( inst, this, "GameState" ),
    restart( &this->cm ),
    end( &this->cm ),
    pause( &this->cm ),
    game_state( &this->cm, State::Empty )
{
}

iv::Instance * GameState::instance()
{
    return this->cm.instance();
}

}
