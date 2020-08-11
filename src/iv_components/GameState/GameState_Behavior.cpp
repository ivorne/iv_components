#include "GameState_Behavior.hpp"
#include "../Defs.hpp"

namespace comp
{

GameState_Behavior::GameState_Behavior( iv::Instance * inst, GameState * m_game ) :
    cm( inst, this, "GameState_Behavior" ),
    m_game( m_game ),
    on_restart( inst, [ this ]()
    {
        this->cm.log( SRC_INFO, Defs::Log::GameState, "Game state change: ", this->m_game->game_state.Get(), " -> ", GameState::State::Running, "." );
        this->m_game->game_state.Modify( &this->cm, GameState::State::Running );
    }),
    on_end( inst, [ this ]()
    {
        if( this->m_game->game_state.Get() != GameState::State::Empty )
        {
            this->cm.log( SRC_INFO, Defs::Log::GameState, "Game state change: ", this->m_game->game_state.Get(), " -> ", GameState::State::Ended, "." );
            this->m_game->game_state.Modify( &this->cm, GameState::State::Ended );
        }
    }),
    on_pause( inst, [ this ]( bool real )
    {
        if( this->on_pause.Get() )
        { // pause
            if( this->m_game->game_state.Get() == GameState::State::Running )
            {
                this->cm.log( SRC_INFO, Defs::Log::GameState, "Game state change: ", this->m_game->game_state.Get(), " -> ", GameState::State::Paused, "." );
                this->m_game->game_state.Modify( &this->cm, GameState::State::Paused );
            }
        }
        else
        { // unpause
            if( this->m_game->game_state.Get() == GameState::State::Paused )
            {
                this->cm.log( SRC_INFO, Defs::Log::GameState, "Game state change: ", this->m_game->game_state.Get(), " -> ", GameState::State::Running, "." );
                this->m_game->game_state.Modify( &this->cm, GameState::State::Running );
            }
        }
    })
{
    this->cm.owns( this->on_restart.cm, this->on_end.cm, this->on_pause.cm );
    
    this->on_restart.Assign_Attribute_R( &m_game->restart );
    this->on_end.Assign_Attribute_R( &m_game->end );
    this->on_pause.Assign_Attribute_R( &m_game->pause );
}

}
