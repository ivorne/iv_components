#include "SimulationState.hpp"

namespace iv
{
const StringIO< comp::SimulationState::State >::ValuesType StringIO< comp::SimulationState::State >::Values = 
{
    { comp::SimulationState::State::Empty, "Empty" },
    { comp::SimulationState::State::Running, "Running" },
    { comp::SimulationState::State::Paused, "Paused" },
    { comp::SimulationState::State::Ended, "Ended" }
};

}

namespace comp
{

SimulationState::SimulationState( iv::Instance * inst ) :
    cm( inst, this, "SimulationState" ),
    restart( &this->cm ),
    end( &this->cm ),
    pause( &this->cm ),
    state( &this->cm, SimulationState::Empty ),
    time_ms( &this->cm, 0 )
{
}

iv::Instance * SimulationState::instance()
{
    return this->cm.instance();
}

}
