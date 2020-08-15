#include "Simulation.hpp"
#include "../Defs.hpp"

namespace comp
{

Simulation::Simulation( iv::Instance * inst, SimulationState * state, iv::TimeId time_id ) :
    iv::FixedUpdateClient( inst, time_id ),
    cm( inst, this, "Simulation" ),
    state( state ),
    on_restart( inst, [ this ]()
    {
        this->cm.log( SRC_INFO, Defs::Log::Simulation, "Game state change: ", this->state->game_state.Get(), " -> ", SimulationState::Running, "." );
        this->state->game_state.Modify( &this->cm, SimulationState::Running );
        
        this->needs_reset = true;
        this->fixed_update_resume();
    }),
    on_end( inst, [ this ]()
    {
        if( this->state->game_state.Get() != SimulationState::Empty )
        {
            this->cm.log( SRC_INFO, Defs::Log::Simulation, "Game state change: ", this->state->game_state.Get(), " -> ", SimulationState::Ended, "." );
            this->state->game_state.Modify( &this->cm, SimulationState::Ended );
            
            this->needs_reset = true;
            this->fixed_update_pause();
        }
    }),
    on_pause( inst, [ this ]( bool real )
    {
        if( this->on_pause.Get() )
        { // pause
            if( this->state->game_state.Get() == SimulationState::Running )
            {
                this->cm.log( SRC_INFO, Defs::Log::Simulation, "Game state change: ", this->state->game_state.Get(), " -> ", SimulationState::Paused, "." );
                this->state->game_state.Modify( &this->cm, SimulationState::Paused );
                
                this->fixed_update_pause();
            }
        }
        else
        { // unpause
            if( this->state->game_state.Get() == SimulationState::Paused )
            {
                this->cm.log( SRC_INFO, Defs::Log::Simulation, "Game state change: ", this->state->game_state.Get(), " -> ", SimulationState::Running, "." );
                this->state->game_state.Modify( &this->cm, SimulationState::Running );
                
                this->fixed_update_resume();
            }
        }
    }),
    needs_reset( true )
{
    this->cm.inherits( this->iv::FixedUpdateClient::cm );
    this->cm.owns( this->on_restart.cm, this->on_end.cm, this->on_pause.cm );
    
    this->fixed_update_pause();
    
    this->on_restart.Assign_Attribute_R( &state->restart );
    this->on_end.Assign_Attribute_R( &state->end );
    this->on_pause.Assign_Attribute_R( &state->pause );
}

void Simulation::fixed_update( iv::TimeId time, int time_step, int steps )
{
    if( this->needs_reset )
    {
        this->needs_reset = false;
        this->simulation_reset();
    }
    
    for( size_t i = 0; i < steps; i++ )
        this->simulation_step( time_step );
}

}
